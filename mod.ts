import { params } from './src/webview2_params.ts';
import { Microsoft_Web_WebView2, Microsoft_Windows_ImplementationLibrary } from './src/version.ts';
export type { WEBVIEW2_FUNCS } from './src/webview2.d.ts';

export function createWebView2(dllPath = 'webview2.dll') {
  return Deno.dlopen(
    dllPath,
    params,
  );
}

export const version = {
  Microsoft: {
    Web: {
      WebView2: Microsoft_Web_WebView2,
    },
    Windows: {
      ImplementationLibrary: Microsoft_Windows_ImplementationLibrary,
    },
  },
};
