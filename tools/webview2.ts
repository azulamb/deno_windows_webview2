/**
 * Read the bundled debug or release WebView2 DLL, or write it to a destination.
 * Use these functions when build scripts need direct access to the native binary.
 * @module
 */

import { createDLLPath } from './dll_path.ts';
import { copyAtomic, readDLLBytes } from './copy_file.ts';
// import webview2Release from '../webview2/x64/Release/webview2.dll' with { type: 'bytes' };
// import webview2Debug from '../webview2/x64/Debug/webview2.dll' with { type: 'bytes' };

/**
 * Get the webview2.dll file binary.
 * @param isDebug Whether to get the debug version.
 * @returns The webview2.dll file as a Uint8Array.
 */
export function getDll(isDebug = false): Promise<Uint8Array> {
  return readDLLBytes(createDLLPath(isDebug));
}

/**
 * Create the webview2.dll file.
 * @param path The path to the webview2.dll file.
 * @param isDebug Whether to create the debug version.
 * @returns A promise that resolves when the file is created.
 */
export function createDllFile(
  path: string | URL,
  isDebug = false,
): Promise<void> {
  return copyAtomic(path, createDLLPath(isDebug));
}
