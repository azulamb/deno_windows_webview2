import type { Webview2Funcs } from './webview2_types.ts';
import type { HRESULT, HWND, LPVOID } from './libs/winapi.ts';
import { createStringPointer } from './libs/convert.ts';
import type { IStream } from './class/IStream.ts';
import { DoublePointer } from './class/DoublePointer.ts';
import { WebResourceResponse } from './class/WebResourceResponse.ts';
import { Core } from './libs/core.ts';
import type { Webview2Context } from './libs/types.ts';
import { EventRegistrationToken } from './libs/event_registration_token.ts';
import { Environments } from './libs/environments.ts';
import { Settings } from './libs/settings.ts';
import { Controllers } from './libs/controllers.ts';

/**
 * The WebView2 class provides an interface for interacting with the WebView2 control.
 */
export class WebView2 implements Webview2Context {
  public core: Core;
  public environments: Environments;
  public settings: Settings;
  public controllers!: Controllers;
  public eventRegistrationToken: EventRegistrationToken;

  /**
   * Creates an instance of the WebView2 class.
   * @param lib The dynamic library containing the WebView2 functions.
   * @param env The environment pointer.
   */
  constructor(
    readonly lib: Webview2Funcs,
  ) {
    this.eventRegistrationToken = new EventRegistrationToken(this);
    this.core = new Core(this);
    this.environments = new Environments(this);
    this.settings = new Settings(this);
    this.controllers = new Controllers(this);
  }

  /** Gets the version of the webview2.dll. */
  public get dllVersion(): string {
    const pointer = this.lib.symbols.GetDllVersion();
    if (!pointer) {
      return '';
    }
    const str = new Deno.UnsafePointerView(pointer);
    return str.getCString();
  }

  /**
   * Creates a CoreWebView2Environment with options.
   * @param browserExecutableFolder The path to the browser executable folder.
   * @param userDataFolder The path to the user data folder.
   * @param environmentOptions The environment options.
   * @param callback The callback to invoke when the operation completes.
   * @returns The HRESULT of the operation.
   */
  public createCoreWebView2EnvironmentWithOptions(
    browserExecutableFolder: string | null, // PCWSTR
    userDataFolder: string | null, // PCWSTR
    environmentOptions: LPVOID, // ICoreWebView2EnvironmentOptions*
    callback: (result: HRESULT, env: LPVOID) => HRESULT, // HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
  ): HRESULT {
    const func = new Deno.UnsafeCallback(
      {
        parameters: [
          'i32', // HRESULT
          'pointer', // LPVOID
        ],
        result: 'i32', // HRESULT
      },
      callback,
    );

    return this.lib.symbols.CreateCoreWebView2EnvironmentWithOptions(
      this.environments.pointer,
      browserExecutableFolder
        ? createStringPointer(browserExecutableFolder)
        : null,
      userDataFolder ? createStringPointer(userDataFolder) : null,
      environmentOptions,
      func.pointer,
    );
  }

  /**
   * Gets the settings for the WebView2 control.
   * @returns The result of the operation.
   */
  public getSettings(): HRESULT {
    return this.lib.symbols.get_Settings(
      this.core.pointer,
      this.settings.pointer,
    );
  }

  /*readonly _CompareBrowserVersions: {
    readonly parameters: ['pointer', 'pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly _GetAvailableCoreWebView2BrowserVersionString: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /*readonly SetWebview2Environment: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'pointer';
  };*/

  /**
   * Creates a CoreWebView2Controller.
   * @param hWnd The window handle.
   * @param callback The callback to invoke when the operation completes.
   * @returns The HRESULT of the operation.
   */
  public createCoreWebView2Controller(
    hWnd: HWND,
    callback: (errorCode: HRESULT, controller: LPVOID) => HRESULT, // HRESULT(*callback)(HRESULT, ICoreWebView2Controller*)
  ): HRESULT {
    const func = new Deno.UnsafeCallback(
      {
        parameters: [
          'i32', // HRESULT errorCode,
          'pointer', // ICoreWebView2Controller* controller
        ],
        result: 'i32',
      },
      callback,
    );
    return this.lib.symbols.CreateCoreWebView2Controller(
      this.environments.pointer,
      hWnd,
      func.pointer,
      this.controllers.pointer,
    );
  }

  /**
   * Gets the CoreWebView2 instance associated with the WebView2 control.
   * @returns The HRESULT result of the operation.
   */
  public getCoreWebView2(): HRESULT {
    return this.lib.symbols.get_CoreWebView2(
      this.controllers.pointer,
      this.core.pointer,
    );
  }

  /**
   * Creates a new WebResourceResponse.
   * @param libs The Webview2 functions.
   * @param content The content stream.
   * @param statusCode The HTTP status code.
   * @param reasonPhrase The HTTP reason phrase.
   * @param headers The HTTP headers.
   * @returns The created WebResourceResponse.
   */
  createWebResourceResponse(
    content: IStream,
    statusCode: number,
    reasonPhrase: string,
    headers: string,
  ): WebResourceResponse {
    const response = new DoublePointer();
    console.log('CreateWebResourceResponse----');
    const result = this.lib.symbols.CreateWebResourceResponse(
      this.environments.pointer,
      content.getPointer(),
      statusCode,
      createStringPointer(reasonPhrase),
      createStringPointer(headers),
      response.getDoublePointer(),
    );
    console.log(result);
    console.log(Deno.UnsafePointer.value(response.getPointer()));
    console.log('---');
    return new WebResourceResponse(this.lib, response);
  }
}
