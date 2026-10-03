import { dirname } from '@std/path';

async function removeTemporary(path: string): Promise<void> {
  try {
    await Deno.remove(path);
  } catch (error) {
    if (!(error instanceof Deno.errors.NotFound)) throw error;
  }
}

/** Copies a local/embedded file or downloads HTTP bytes, then replaces the destination atomically. */
export async function copyAtomic(to: string, from: URL): Promise<void> {
  await Deno.mkdir(dirname(to), { recursive: true });
  const temporary = await Deno.makeTempFile({
    dir: dirname(to),
    prefix: '.webview2-',
  });
  try {
    if (from.protocol === 'file:') {
      await Deno.copyFile(from, temporary);
    } else if (from.protocol === 'https:' || from.protocol === 'http:') {
      const response = await fetch(from);
      if (!response.ok) {
        throw new Error(
          `Failed to fetch ${from}: ${response.status} ${response.statusText}`,
        );
      }
      await Deno.writeFile(
        temporary,
        new Uint8Array(await response.arrayBuffer()),
      );
    } else {
      throw new Error(`Unsupported DLL source protocol: ${from.protocol}`);
    }
    await Deno.rename(temporary, to);
  } finally {
    await removeTemporary(temporary);
  }
}
