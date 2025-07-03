import { params } from './src/webview2_params.ts';
import {
  Deno_Webview2,
  Microsoft_Web_WebView2,
  Microsoft_Windows_ImplementationLibrary,
} from './src/version.ts';
import { createDLLPath } from './tools/dll_path.ts';
import type { WEBVIEW2_FUNCS } from './src/webview2_types.ts';
import { WebView2 } from './src/webview2.ts';
export * from './src/webview2.ts';
export type { WEBVIEW2_FUNCS } from './src/webview2_types.ts';

export type PREPARE_WEBVIEW2_DLL_OPTION = {
  includePath?: boolean | string | URL; // deno compile --include [includePath] ..., true: default path.
  download?: boolean | string | URL; // true: download from GitHub
  //update?: boolean; // TODO: update DLL and version check.
  debugMode?: boolean; // TODO: debug mode.
};

async function copyFile(to: string, from: URL) {
  const response = await fetch(from);
  if (!response.ok || response.body === null) {
    throw new Error(`[Failure] Load: ${response.statusText}`);
  }

  const file = await Deno.open(to, { create: true, write: true });
  await response.body.pipeTo(file.writable);
}

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
    if (option?.debugMode) {
      console.error(error);
    }
    if (!(error instanceof Deno.errors.NotFound)) {
      throw error;
    }
  }
  // DLL not found.
  if (option?.includePath) {
    try {
      let includePath: URL;
      if (option.includePath === true) {
        includePath = createDLLPath();
        if (option.debugMode) {
          console.info(includePath);
        }
        try {
          const stat = await Deno.stat(includePath);
          if (option.debugMode) {
            console.info(stat);
          }
          if (stat.mode !== 0) {
            return {
              path: includePath.pathname.substring(1), // TODO:
            };
          }
        } catch (error) {
          // Not exists dll in local.
          if (option?.debugMode) {
            console.error(error);
          }
        }
      } else {
        includePath = typeof option.includePath === 'string'
          ? new URL(import.meta.resolve(option.includePath))
          : option.includePath;
      }

      await copyFile(dllPath, includePath);
      return {
        path: dllPath,
      };
    } catch (error) {
      if (option?.debugMode) {
        console.error(error);
      }
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

    await copyFile(dllPath, option.download);
    return {
      path: dllPath,
    };
  }
  throw new Error(`[Failure] Create: ${dllPath}`);
}

export function loadWebview2(
  dllPath = 'webview2.dll',
): Deno.DynamicLibrary<WEBVIEW2_FUNCS> {
  return Deno.dlopen(
    dllPath,
    params,
  );
}

export function createWebView2(
  dllPath = 'webview2.dll',
): WebView2 {
  return new WebView2(loadWebview2(dllPath));
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
