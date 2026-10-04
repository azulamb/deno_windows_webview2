import { dirname, fromFileUrl } from '@std/path';

/** Reads a local/embedded or HTTP DLL using the same source rules as copying. */
export async function readDLLBytes(
  from: URL,
  signal?: AbortSignal,
): Promise<Uint8Array> {
  signal?.throwIfAborted();
  if (from.protocol === 'file:') return await Deno.readFile(from, { signal });
  if (from.protocol !== 'https:' && from.protocol !== 'http:') {
    throw new Error(`Unsupported DLL source protocol: ${from.protocol}`);
  }
  const response = await fetch(from, { signal });
  if (!response.ok) {
    throw new Error(
      `Failed to fetch ${from}: ${response.status} ${response.statusText}`,
    );
  }
  return new Uint8Array(await response.arrayBuffer());
}

/** Reads the fixed file version from the Windows VERSIONINFO resource. */
export function dllVersion(bytes: Uint8Array): string | undefined {
  const key = new TextEncoder().encode('VS_VERSION_INFO');
  const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  for (let offset = 0; offset + 92 < bytes.length; ++offset) {
    if (
      !key.every((byte, index) =>
        bytes[offset + index * 2] === byte &&
        bytes[offset + index * 2 + 1] === 0
      )
    ) continue;
    const fixed = (offset + 32 + 3) & ~3;
    if (view.getUint32(fixed, true) !== 0xFEEF04BD) continue;
    const high = view.getUint32(fixed + 8, true),
      low = view.getUint32(fixed + 12, true);
    return `${high >>> 16}.${high & 0xFFFF}.${low >>> 16}.${low & 0xFFFF}`;
  }
  return undefined;
}

async function removeTemporary(path: string): Promise<void> {
  try {
    await Deno.remove(path);
  } catch (error) {
    if (!(error instanceof Deno.errors.NotFound)) throw error;
  }
}

/** Copies a local/embedded file or downloads HTTP bytes, then replaces the destination atomically. */
export async function copyAtomic(
  to: string | URL,
  from: URL,
  option?: { signal?: AbortSignal; expectedVersion?: string },
): Promise<void> {
  const destination = to instanceof URL ? fromFileUrl(to) : to;
  option?.signal?.throwIfAborted();
  await Deno.mkdir(dirname(destination), { recursive: true });
  const temporary = await Deno.makeTempFile({
    dir: dirname(destination),
    prefix: '.webview2-',
  });
  try {
    if (from.protocol === 'file:' && !option?.expectedVersion) {
      await Deno.copyFile(from, temporary);
    } else {
      const bytes = await readDLLBytes(from, option?.signal);
      if (
        option?.expectedVersion && dllVersion(bytes) !== option.expectedVersion
      ) {
        throw new Error(
          `DLL version mismatch: expected ${option.expectedVersion}, received ${
            dllVersion(bytes) ?? 'unknown'
          }`,
        );
      }
      await Deno.writeFile(temporary, bytes, { signal: option?.signal });
    }
    option?.signal?.throwIfAborted();
    await Deno.rename(temporary, destination);
  } finally {
    await removeTemporary(temporary);
  }
}
