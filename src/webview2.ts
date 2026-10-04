import type { Webview2Funcs } from './webview2_types.ts';
import type { HRESULT, HWND, LPVOID } from './libs/winapi.ts';
import { CompletionCallbacks } from './libs/completion_callbacks.ts';
import { createStringBuffer, createStringPointer } from './libs/convert.ts';
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
  public readonly completions: CompletionCallbacks = new CompletionCallbacks();
  private closing: boolean = false;
  private disposed: boolean = false;
  private ownsPointers: boolean;
  private resolveClosed!: () => void;
  private rejectClosed!: (error: unknown) => void;
  public readonly closed: Promise<void> = new Promise((resolve, reject) => {
    this.resolveClosed = resolve;
    this.rejectClosed = reject;
  });
  public get lib(): Webview2Funcs {
    if (this.disposed) throw new Error('WebView2 is closed.');
    return this.library;
  }
  /** Unregister events, wait for completions, then release owned wrappers. Keep pumping the STA until completion. */
  public close(): void {
    if (this.closing) return;
    this.closing = true;
    this.completions.beginClose();
    queueMicrotask(() => {
      try {
        this.core.closeEvents();
        this.controllers.closeEvents();
        this.completions.close(() => {
          try {
            if (this.ownsPointers) {
              this.library.symbols.Controllers_Close(this.controllers.pointer);
              this.library.symbols.Controllers_Destroy(
                this.controllers.pointer,
              );
              this.library.symbols.Settings_Destroy(this.settings.pointer);
              this.library.symbols.WebView2_Destroy(this.core.pointer);
              this.library.symbols.Environments_Destroy(
                this.environments.pointer,
              );
            }
            this.disposed = true;
            if (this.ownsLibrary) this.library.close();
            this.resolveClosed();
          } catch (error) {
            this.rejectClosed(error);
          }
        });
      } catch (error) {
        this.rejectClosed(error);
      }
    });
  }
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
    private readonly library: Webview2Funcs,
    pointers?: {
      core: Deno.PointerValue;
      environments: Deno.PointerValue;
      settings: Deno.PointerValue;
      controllers: Deno.PointerValue;
    },
    private ownsLibrary: boolean = false,
  ) {
    if (pointers && Object.values(pointers).some((pointer) => !pointer)) {
      throw new Error('Borrowed wrapper pointers must all be non-null.');
    }
    this.ownsPointers = !pointers;
    this.eventRegistrationToken = new EventRegistrationToken(this);
    this.core = new Core(this, pointers?.core);
    this.environments = new Environments(this, pointers?.environments);
    this.settings = new Settings(this, pointers?.settings);
    this.controllers = new Controllers(this, pointers?.controllers);
  }

  /** Gets the version of the webview2.dll. */
  public get dllVersion(): string {
    const pointer = this.lib.symbols.Global_GetDllVersion();
    if (!pointer) {
      return '';
    }
    const str = new Deno.UnsafePointerView(pointer);
    return str.getCString();
  }

  /** @deprecated Raw pointers are only usable on the creating STA; use message-based UI Worker commands. */
  public exportData(): {
    core: bigint;
    environments: bigint;
    settings: bigint;
    controllers: bigint;
  } {
    return {
      core: Deno.UnsafePointer.value(this.core.pointer),
      environments: Deno.UnsafePointer.value(this.environments.pointer),
      settings: Deno.UnsafePointer.value(this.settings.pointer),
      controllers: Deno.UnsafePointer.value(this.controllers.pointer),
    };
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
    const folder = browserExecutableFolder === null
      ? null
      : createStringBuffer(browserExecutableFolder);
    const data = userDataFolder === null
      ? null
      : createStringBuffer(userDataFolder);
    const func = this.completions.create(callback, [folder, data]);
    const result = this.lib.symbols
      .Global_CreateCoreWebView2EnvironmentWithOptions(
        this.environments.pointer,
        folder ? Deno.UnsafePointer.of(folder) : null,
        data ? Deno.UnsafePointer.of(data) : null,
        environmentOptions,
        func.pointer,
      );
    if (result < 0) this.completions.cancel(func);
    return result;
  }

  /**
   * Gets the settings for the WebView2 control.
   * @returns The result of the operation.
   */
  public getSettings(): HRESULT {
    return this.lib.symbols.WebView2_get_Settings(
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
    const func = this.completions.create(callback);
    const result = this.lib.symbols.Environments_CreateCoreWebView2Controller(
      this.environments.pointer,
      hWnd,
      func.pointer,
      this.controllers.pointer,
    );
    if (result < 0) this.completions.cancel(func);
    return result;
  }

  /**
   * Gets the CoreWebView2 instance associated with the WebView2 control.
   * @returns The HRESULT result of the operation.
   */
  public getCoreWebView2(): HRESULT {
    return this.lib.symbols.Controllers_get_CoreWebView2(
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
    const result = this.lib.symbols.Environments_CreateWebResourceResponse(
      this.environments.pointer,
      content.getPointer(),
      statusCode,
      createStringPointer(reasonPhrase),
      createStringPointer(headers),
      response.getDoublePointer(),
    );
    if (result < 0) {
      throw new Error(`CreateWebResourceResponse failed: ${result}`);
    }
    return new WebResourceResponse(this.lib, response);
  }
}
