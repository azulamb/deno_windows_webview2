/**
 * Copy or ensure the matching WebView2 DLL, with optional file version validation.
 * Can also be run as a command to prepare a DLL at the requested destination.
 * @module
 */

import { isAbsolute, join } from '@std/path';
import { copyAtomic, dllVersion } from './copy_file.ts';
import { createDLLPath } from './dll_path.ts';
export { Dll as DLL_VERSION } from '../src/version.ts';

/**
 * Copy webview2.dll to a new location.
 * @param toFilePath The path to the destination file.
 * @param option Options for the copy operation.
 * @returns A promise that resolves when the copy is complete.
 */
export function copy(
  toFilePath: string,
  option?: {
    isDebug?: boolean; // Copy Debug DLL.
    log?: boolean; // Output log.
    signal?: AbortSignal;
    expectedVersion?: string;
  },
): Promise<void> {
  const fromFilePath = createDLLPath(option?.isDebug);

  if (option?.log) {
    console.log(`Module dir: ${import.meta.dirname}`);
    console.log(`From: ${fromFilePath.toString()}`);
    console.log(`To: ${toFilePath}`);
  }

  return copyAtomic(toFilePath, fromFilePath, option);
}

/** Ensures a DLL exists without overwriting an existing file; optional version verification. */
export async function ensureDLL(
  path: string,
  option?: {
    signal?: AbortSignal;
    expectedVersion?: string;
    existingOnly?: boolean;
  },
): Promise<void> {
  try {
    const stat = await Deno.stat(path);
    if (!stat.isFile) throw new Error(`Not a DLL file: ${path}`);
    if (
      option?.expectedVersion &&
      dllVersion(await Deno.readFile(path, { signal: option.signal })) !==
        option.expectedVersion
    ) {
      throw new Error(
        `DLL version mismatch: expected ${option.expectedVersion}: ${path}`,
      );
    }
  } catch (error) {
    if (!(error instanceof Deno.errors.NotFound)) throw error;
    if (option?.existingOnly) throw error;
    await copy(path, option);
  }
}

if (import.meta.main) {
  let isDebug = false;
  let dest = '';

  for (const arg of Deno.args) {
    if (arg === '--debug') {
      isDebug = true;
      continue;
    }
    dest = arg;
    break;
  }

  if (!dest) {
    console.error('Usage: deno task copy [--debug] <dest dir path>');
    Deno.exit(1);
  }

  // Directory check.
  if (dest.match(/\/$/) || dest.match(/\\$/)) {
    try {
      const stat = await Deno.stat(dest);
      if (!stat.isDirectory) {
        throw new Error();
      }
    } catch (_error) {
      console.error(`"${dest}" is not a directory`);
      Deno.exit(1);
    }
    dest = join(dest, 'webview2.dll');
  }

  if (!isAbsolute(dest)) {
    dest = join(Deno.cwd(), dest);
  }

  console.log('Copying...');
  await copy(dest, { isDebug, log: true });
  console.log('Done');
}
