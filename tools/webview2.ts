/**
 * This module provides functions to manage the webview2.dll file.
 * @module @azulamb/webview2/webview2
 */

import { createDLLPath } from './dll_path.ts';
// import webview2Release from '../webview2/x64/Release/webview2.dll' with { type: 'bytes' };
// import webview2Debug from '../webview2/x64/Debug/webview2.dll' with { type: 'bytes' };

/**
 * Get the webview2.dll file binary.
 * @param isDebug Whether to get the debug version.
 * @returns The webview2.dll file as a Uint8Array.
 */
export function getDll(isDebug = false): Promise<Uint8Array> {
  const dllPath = createDLLPath(isDebug);
  if (dllPath.toString().match(/^https:\/\//)) {
    // Download file.
    return fetch(dllPath).then((response) => {
      if (!response.ok) {
        throw new Error(
          `Failed to fetch ${dllPath}: ${response.statusText}`,
        );
      }
      return response.arrayBuffer();
    }).then((buffer) => {
      return new Uint8Array(buffer);
    });
  }
  return Deno.readFile(dllPath);
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
  return getDll(isDebug).then((body) => {
    return Deno.writeFile(path, body);
  });
}
