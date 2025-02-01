import { params } from './src/webview2_params.ts';
import {
  Deno_Webview2,
  Microsoft_Web_WebView2,
  Microsoft_Windows_ImplementationLibrary,
} from './src/version.ts';
import { createDLLPath } from './tools/dll_path.ts';
export type { WEBVIEW2_FUNCS } from './src/webview2.d.ts';

export type PREPARE_WEBVIEW2_DLL_OPTION = {
  includePath?: boolean | string | URL; // deno compile --include [includePath] ..., true: default path.
  download?: boolean | string | URL; // true: download from GitHub
  //update?: boolean; // TODO: update DLL and version check.
};

export async function prepareWebview2DLL(
  dllPath: string,
  option?: PREPARE_WEBVIEW2_DLL_OPTION,
): Promise<{
  path: string;
}> {
  // TODO: DLL check.
  try {
    const stat = Deno.statSync(dllPath);
    if (stat.isFile) {
      return {
        path: dllPath,
      };
    }
    throw new Error(`[Failure] Not a file: ${dllPath}`);
  } catch (error) {
    if (!(error instanceof Deno.errors.NotFound)) {
      throw error;
    }
  }
  // DLL not found.
  if (option?.includePath) {
    try {
      if (option.includePath === true) {
        option.includePath = createDLLPath();
        try {
          const stat = await Deno.stat(option.includePath);
          if (stat.mode !== 0) {
            return {
              path: option.includePath.pathname.substring(1), // TODO:
            };
          }
        } catch (_error) {
          // Not exists dll in local.
        }
      }
      const includePath = typeof option.includePath === 'string'
        ? new URL(import.meta.resolve(option.includePath))
        : option.includePath;

      await Deno.writeFile(
        dllPath,
        new Uint8Array(await Deno.readFile(includePath)),
      );

      return {
        path: dllPath,
      };
    } catch (error) {
      if (!option.download) {
        throw error;
      }
    }
  }
  if (option?.download) {
    if (typeof option.download === 'boolean') {
      // Download from GitHub.
      option.download = new URL(
        'https://github.com/azulamb/deno_windows_webview2/raw/refs/heads/main/webview2/x64/Release/webview2.dll',
      );
    } else if (typeof option.download === 'string') {
      option.download = new URL(option.download);
    }
    const response = await fetch(option.download);
    if (!response.ok || response.body === null) {
      throw new Error(`[Failure] Download: ${response.statusText}`);
    }
    const file = await Deno.open(dllPath, { create: true, write: true });
    await response.body.pipeTo(file.writable);
    file.close();
    return {
      path: dllPath,
    };
  }
  throw new Error(`[Failure] Create: ${dllPath}`);
}

export function createWebView2(dllPath = 'webview2.dll') {
  return Deno.dlopen(
    dllPath,
    params,
  );
}

export const version = {
  Deno: {
    Webview2: Deno_Webview2,
  },
  Microsoft: {
    Web: {
      WebView2: Microsoft_Web_WebView2,
    },
    Windows: {
      ImplementationLibrary: Microsoft_Windows_ImplementationLibrary,
    },
  },
};
