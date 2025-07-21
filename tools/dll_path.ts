/**
 * Create the path to the webview2.dll file.
 * @param isDebug Whether to use the debug version.
 * @returns The URL to the webview2.dll file.
 */
export function createDLLPath(isDebug?: boolean) {
  const type = isDebug ? 'Debug' : 'Release';
  return new URL(import.meta.resolve(
    `../webview2/x64/${type}/webview2.dll`,
  ));
}
