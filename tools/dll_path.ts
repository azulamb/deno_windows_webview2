export function createDLLPath(isDebug?: boolean) {
  const type = isDebug ? 'Debug' : 'Release';
  return new URL(import.meta.resolve(
    `../webview2/x64/${type}/webview2.dll`,
  ));
}
