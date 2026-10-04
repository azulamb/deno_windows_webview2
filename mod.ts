/**
 * This module provides a Windows WebView2 implementation for Deno.
 * @module @azulamb/webview2
 */

import { copyAtomic } from './tools/copy_file.ts';
import { ensureDLL } from './tools/copy.ts';
import { params } from './src/webview2_params.ts';
import {
  Deno_Webview2,
  Dll,
  Microsoft_Web_WebView2,
  Microsoft_Windows_ImplementationLibrary,
} from './src/version.ts';
import { createDLLPath } from './tools/dll_path.ts';
import type { Webview2Funcs } from './src/webview2_types.ts';
import { WebView2 } from './src/webview2.ts';
export * from './src/webview2.ts';
/** The result type for WebView2 functions. */
export type { WEBVIEW2_FUNCS, Webview2Funcs } from './src/webview2_types.ts';

/** The options for preparing the WebView2 DLL. */
export type PREPARE_WEBVIEW2_DLL_OPTION = {
  includePath?: boolean | string | URL; // deno compile --include [includePath] ..., true: default path.
  download?: boolean | string | URL; // true: download from GitHub
  signal?: AbortSignal;
  expectedVersion?: string;
  debugMode?: boolean; // TODO: debug mode.
};

export type WEAPN_CONFIG = {
  title?: string;
  width?: number;
  height?: number;
};

/**
 * Prepares the WebView2 DLL for use.
 * @param dllPath The path to the WebView2 DLL.
 * @param option The options for preparing the DLL.
 * @returns An object containing the path to the prepared DLL.
 */
export async function prepareWebview2DLL(
  dllPath: string,
  option?: PREPARE_WEBVIEW2_DLL_OPTION,
): Promise<{
  path: string;
}> {
  try {
    await ensureDLL(dllPath, { ...option, existingOnly: true });
    return { path: dllPath };
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
      } else {
        includePath = typeof option.includePath === 'string'
          ? new URL(option.includePath, import.meta.url)
          : option.includePath;
      }

      await copyAtomic(dllPath, includePath, option);
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
        `https://raw.githubusercontent.com/azulamb/deno_windows_webview2/v${Deno_Webview2}/webview2/x64/Release/webview2.dll`,
      );
    } else if (typeof option.download === 'string') {
      option.download = new URL(option.download);
    }

    await copyAtomic(dllPath, option.download, option);
    return {
      path: dllPath,
    };
  }
  throw new Error(`[Failure] Create: ${dllPath}`);
}

/**
 * Loads the WebView2 DLL.
 * @param dllPath The path to the WebView2 DLL.
 * @returns A dynamic library instance for the WebView2 functions.
 */
export function loadWebview2(
  dllPath = 'webview2.dll',
): Webview2Funcs {
  if (Deno.build.os !== 'windows' || Deno.build.arch !== 'x86_64') {
    throw new Error('WebView2 requires 64-bit Windows (x86_64).');
  }
  return Deno.dlopen(
    dllPath,
    params,
  );
}

/**
 * Creates a new WebView2 instance.
 * @param dllPath The path to the WebView2 DLL.
 * @returns A new WebView2 instance.
 */
export function createWebView2(
  dllPath = 'webview2.dll',
  pointers?: {
    core: Deno.PointerValue;
    environments: Deno.PointerValue;
    settings: Deno.PointerValue;
    controllers: Deno.PointerValue;
  },
): WebView2 {
  return new WebView2(loadWebview2(dllPath), pointers, true);
}

/** The version information for the WebView2 module. */
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
  Dll: Dll,
};

/**
 * Exports web resource context constants.
 */
export * from './src/constants/WEB_RESOURCE_CONTEXT.ts';
export * from './src/constants/MOVE_FOCUS_REASON.ts';

/**
 * Exports support classes.
 */
export * from './src/class/Deferral.ts';
export * from './src/class/IStream.ts';
export * from './src/class/WebMessageReceivedEventArgs.ts';
export * from './src/class/WebResourceRequest.ts';
export * from './src/class/WebResourceResponse.ts';
export * from './src/class/WebResourceRequestedEventArgs.ts';
