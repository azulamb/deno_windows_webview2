import { loadWebview2, prepareWebview2DLL, version } from '../mod.ts';
const nativePath = './extracted.dll';
await prepareWebview2DLL(nativePath, { includePath: true });
const library = loadWebview2(nativePath);
try {
  const pointer = library.symbols.Global_GetDllVersion();
  if (
    !pointer || new Deno.UnsafePointerView(pointer).getCString() !== version.Dll
  ) throw new Error('Embedded DLL version mismatch');
  console.log('Embedded DLL extraction: OK');
} finally {
  library.close();
  await Deno.remove(nativePath);
}
