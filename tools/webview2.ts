export function getDll(isDebug = false): Promise<Uint8Array> {
  return Deno.readFile(
    `../webview2/x64/${isDebug ? 'Debug' : 'Release'}/webview2.dll`,
  );
}

export function createDllFile(
  path: string | URL,
  isDebug = false,
): Promise<void> {
  return getDll(isDebug).then((body) => {
    return Deno.writeFile(path, body);
  });
}
