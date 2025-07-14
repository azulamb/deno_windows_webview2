import release from '../webview2/x64/Release/webview2.dll' with {
  type: 'bytes',
};
import debug from '../webview2/x64/Debug/webview2.dll' with { type: 'bytes' };

export function getDll(isDebug = false): Uint8Array {
  if (isDebug) {
    return debug;
  }
  return release;
}

export function createDllFile(
  path: string | URL,
  isDebug = false,
): Promise<void> {
  return Deno.writeFile(path, isDebug ? debug : release);
}
