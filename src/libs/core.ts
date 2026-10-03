import type { HRESULT, LPVOID } from './winapi.ts';
import type { Webview2Context } from './types.ts';
import {
  createStringBuffer,
  createStringPointer,
  getBool,
  getWString,
} from './convert.ts';
import type {
  EventRegistrationToken,
  Webview2Funcs,
} from '../webview2_types.ts';
import type { WEB_RESOURCE_CONTEXT_TYPES } from '../constants/WEB_RESOURCE_CONTEXT.ts';

export class Core {
  private callbacks: Map<
    EventRegistrationToken,
    { close(): void; remove(token: EventRegistrationToken): number }
  > = new Map();
  public closeEvents(): void {
    for (const token of [...this.callbacks.keys()]) {
      const result = this.removeEvent(token);
      if (result < 0) throw new Error(`Event removal failed: ${result}`);
    }
  }
  private removeEvent(token: EventRegistrationToken): HRESULT {
    const entry = this.callbacks.get(token);
    if (!entry) throw new Error('Unknown or already removed event token.');
    const result = entry.remove(token);
    if (result < 0) return result;
    this.callbacks.delete(token);
    this.context.eventRegistrationToken.remove(token);
    queueMicrotask(() => entry.close());
    return result;
  }
  protected core: Deno.PointerValue<unknown>;

  public get pointer(): Deno.PointerValue<unknown> {
    return this.core;
  }

  protected get libs(): Webview2Funcs {
    return this.context.lib;
  }

  constructor(
    protected context: Webview2Context,
    core?: Deno.PointerValue<unknown>,
  ) {
    this.core = core ?? this.libs.symbols.WebView2_Create();
  }

  /*readonly CallDevToolsProtocolMethod: {
    readonly parameters: ['pointer', 'pointer', 'pointer', 'function'];
    readonly result: 'i32';
  };
  readonly GetDevToolsProtocolEventReceiver: {
    readonly parameters: ['pointer', 'pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly OpenDevToolsWindow: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };
  readonly add_DocumentTitleChanged: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_DocumentTitleChanged: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_DocumentTitle: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly add_HistoryChanged: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_HistoryChanged: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };*/

  /**
   * Post the specified webMessage to the top level document in this WebView.
   * @param json The JSON object to post.
   * @returns The HRESULT result of the operation.
   */
  public postWebMessageAsJson(
    // deno-lint-ignore no-explicit-any
    json: any,
  ): HRESULT {
    // TODO: use sender.
    return this.libs.symbols.WebView2_PostWebMessageAsJson(
      this.core,
      createStringPointer(JSON.stringify(json)),
    );
  }

  /**
   * Posts a message that is a simple string rather than a JSON string representation of a JavaScript object.
   * @param data The string to post.
   * @returns The HRESULT result of the operation.
   */
  public postWebMessageAsString(data: string): HRESULT {
    // TODO: use sender.
    return this.libs.symbols.WebView2_PostWebMessageAsString(
      this.core,
      createStringPointer(data),
    );
  }

  /**
   * Add an event handler for the WebMessageReceived event.
   * @param callback The function to call when the event is raised.
   * @returns The EventRegistrationToken for the event handler.
   */
  public addWebMessageReceived(
    callback: (coreWebView2: LPVOID, eventArgs: LPVOID) => HRESULT,
  ): EventRegistrationToken {
    const token = this.context.eventRegistrationToken.create();
    const func = new Deno.UnsafeCallback(
      {
        parameters: [
          'pointer', // ICoreWebView2*
          'pointer', // ICoreWebView2WebMessageReceivedEventArgs*
        ],
        result: 'i32', // HRESULT
      },
      callback,
    );
    const result = this.libs.symbols.WebView2_add_WebMessageReceived(
      this.core,
      func.pointer,
      token,
    );
    if (result < 0) {
      func.close();
      this.context.eventRegistrationToken.remove(token);
      throw new Error(`addWebMessageReceived failed: ${result}`);
    }
    this.callbacks.set(token, {
      close: () => func.close(),
      remove: (value) =>
        this.libs.symbols.WebView2_remove_WebMessageReceived(this.core, value),
    });
    return token;
  }

  /**
   * Remove an event handler previously added with addWebMessageReceived.
   * @param token The EventRegistrationToken for the event handler.
   * @returns The HRESULT result of the operation.
   */
  public removeWebMessageReceived(token: EventRegistrationToken): HRESULT {
    return this.removeEvent(token);
  }

  /**
   * Cause a navigation of the top-level document to run to the specified URI.
   * @param url The URL to navigate to.
   * @returns The HRESULT result of the operation.
   */
  public navigate(url: string): HRESULT {
    return this.libs.symbols.WebView2_Navigate(
      this.core,
      createStringPointer(url),
    );
  }

  /*readonly add_NavigationCompleted: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_NavigationCompleted: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_NavigationStarting: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_NavigationStarting: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly NavigateToString: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly add_FrameNavigationCompleted: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_FrameNavigationCompleted: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_FrameNavigationStarting: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_FrameNavigationStarting: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_PermissionRequested: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_PermissionRequested: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_ScriptDialogOpening: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_ScriptDialogOpening: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly AddScriptToExecuteOnDocumentCreated: {
    readonly parameters: ['pointer', 'pointer', 'function'];
    readonly result: 'i32';
  };
  readonly RemoveScriptToExecuteOnDocumentCreated: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  public executeScript(
    source: string,
    callback: (errorCode: HRESULT, resultObjectAsJson: string) => HRESULT,
  ): HRESULT {
    const buffer = createStringBuffer(source);
    const func = this.context.completions.create(
      (errorCode, result) => callback(errorCode, getWString(result)),
      [buffer],
    );
    const result = this.libs.symbols.WebView2_ExecuteScript(
      this.core,
      Deno.UnsafePointer.of(buffer),
      func.pointer,
    );
    if (result < 0) this.context.completions.cancel(func);
    return result;
  }

  /*readonly AddHostObjectToScript: {
    readonly parameters: ['pointer', 'pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly RemoveHostObjectFromScript: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly get_Source: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly add_SourceChanged: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_SourceChanged: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };*/

  /**
   * Reload the current page.
   * @returns The HRESULT result of the operation.
   */
  public reload(): HRESULT {
    return this.libs.symbols.WebView2_Reload(this.core);
  }

  /**
   * true if the WebView is able to navigate to a previous page in the navigation history.
   */
  public get canGoBack(): boolean {
    return getBool(
      this.core,
      this.libs.symbols.WebView2_get_CanGoBack,
    );
  }

  /**
   * true if the WebView is able to navigate to a next page in the navigation history.
   */
  public get canGoForward(): boolean {
    return getBool(
      this.core,
      this.libs.symbols.WebView2_get_CanGoForward,
    );
  }

  /**
   * Navigates the WebView to the previous page in the navigation history.
   * @returns The HRESULT result of the operation.
   */
  public goBack(): HRESULT {
    return this.libs.symbols.WebView2_GoBack(this.core);
  }

  /**
   * Navigates the WebView to the next page in the navigation history.
   * @returns The HRESULT result of the operation.
   */
  public goForward(): HRESULT {
    return this.libs.symbols.WebView2_GoForward(this.core);
  }

  /**
   * Stop all navigations and pending resource fetches. Does not stop scripts.
   * @returns The HRESULT result of the operation.
   */
  public stop(): HRESULT {
    return this.libs.symbols.WebView2_Stop(this.core);
  }

  /*readonly add_ContentLoading: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_ContentLoading: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_ProcessFailed: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_ProcessFailed: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };*/

  /*readonly CapturePreview: {
    readonly parameters: ['pointer', 'i32', 'pointer', 'function'];
    readonly result: 'i32';
  };
  readonly get_BrowserProcessId: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly add_NewWindowRequested: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_NewWindowRequested: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_ContainsFullScreenElementChanged: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_ContainsFullScreenElementChanged: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_ContainsFullScreenElement: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Add an event handler for the WebResourceRequested event.
   * @param callback The callback function to invoke when the event is raised.
   * @returns The event registration token.
   */
  public addWebResourceRequested(
    callback: (coreWebView2: LPVOID, eventArgs: LPVOID) => HRESULT,
  ): EventRegistrationToken {
    const token = this.context.eventRegistrationToken.create();
    const func = new Deno.UnsafeCallback(
      {
        parameters: [
          'pointer', // ICoreWebView2*
          'pointer', // ICoreWebView2WebResourceRequestedEventArgs*
        ],
        result: 'i32', // HRESULT
      },
      callback,
    );
    const result = this.libs.symbols.WebView2_add_WebResourceRequested(
      this.core,
      func.pointer,
      token,
    );
    if (result < 0) {
      func.close();
      this.context.eventRegistrationToken.remove(token);
      throw new Error(`addWebResourceRequested failed: ${result}`);
    }
    this.callbacks.set(token, {
      close: () => func.close(),
      remove: (value) =>
        this.libs.symbols.WebView2_remove_WebResourceRequested(
          this.core,
          value,
        ),
    });
    return token;
  }

  /**
   * Remove an event handler previously added with add_WebResourceRequested.
   * @param token The event registration token.
   * @returns The HRESULT result of the operation.
   */
  public removeWebResourceRequested(token: EventRegistrationToken): HRESULT {
    return this.removeEvent(token);
  }

  /**
   * Warning: This method is deprecated and does not behave as expected for iframes.
   * @param uri The URI to filter.
   * @param resourceContext The resource context to filter.
   * @returns The HRESULT result of the operation.
   */
  public addWebResourceRequestedFilter(
    uri: string,
    resourceContext: WEB_RESOURCE_CONTEXT_TYPES = 0,
  ): HRESULT {
    return this.libs.symbols.WebView2_AddWebResourceRequestedFilter(
      this.core,
      createStringPointer(uri),
      resourceContext,
    );
  }

  /**
   * Warning: This method and addWebResourceRequestedFilter are deprecated.
   * @param uri The URI to filter.
   * @param resourceContext The resource context to filter.
   * @returns The HRESULT result of the operation.
   */
  public removeWebResourceRequestedFilter(
    uri: string,
    resourceContext: WEB_RESOURCE_CONTEXT_TYPES = 0,
  ): HRESULT {
    return this.libs.symbols.WebView2_RemoveWebResourceRequestedFilter(
      this.core,
      createStringPointer(uri),
      resourceContext,
    );
  }

  /*readonly add_WindowCloseRequested: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_WindowCloseRequested: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_DOMContentLoaded: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly add_WebResourceResponseReceived: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  get_CookieManager: {
    parameters: ['pointer', 'pointer'],
    result: 'i32',
  },
  get_Environment: {
    parameters: ['pointer', 'pointer'],
    result: 'i32',
  },
  NavigateWithWebResourceRequest: {
    parameters: ['pointer', 'pointer'],
    result: 'i32',
  },
  remove_DOMContentLoaded: {
    parameters: ['pointer', 'pointer'],
    result: 'i32',
  },
  remove_WebResourceResponseReceived: {
    parameters: ['pointer', 'pointer'],
    result: 'i32',
  },*/

  /**
   * Sets a mapping between a virtual host name and a folder path to make available to web sites via that host name.
   * @param hostName The host name to map.
   * @param folderPath The folder path to map to the host name.
   * @param accessKind The access kind for the mapping.
   * @returns The HRESULT result of the operation.
   */
  public setVirtualHostNameToFolderMapping(
    hostName: string,
    folderPath: string,
    accessKind?: {
      deny?: boolean;
      allow?: boolean;
      denyCors?: boolean;
    } | {
      deny: true;
      allow?: false;
      denyCors?: false;
    } | {
      deny?: false;
      allow: true;
      denyCors?: false;
    } | {
      deny?: false;
      allow?: false;
      denyCors: true;
    },
  ): number {
    let accessKindValue = 0;
    if (accessKind) {
      if (accessKind.allow) {
        accessKindValue = 1;
      } else if (accessKind.denyCors) {
        accessKindValue = 2;
      }
    }
    return this.libs.symbols.WebView2_SetVirtualHostNameToFolderMapping(
      this.core,
      createStringPointer(hostName),
      createStringPointer(folderPath),
      accessKindValue,
    );
  }

  /**
   * Clears a host name mapping for local folder that was added by setVirtualHostNameToFolderMapping.
   * @param hostName The host name to clear the mapping for.
   * @returns The HRESULT result of the operation.
   */
  public clearVirtualHostNameToFolderMapping(
    hostName: string,
  ): HRESULT {
    return this.libs.symbols.WebView2_ClearVirtualHostNameToFolderMapping(
      this.core,
      createStringPointer(hostName),
    );
  }

  /*readonly get_IsSuspended: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly TrySuspend: {
    readonly parameters: ['pointer', 'function'];
    readonly result: 'i32';
  };
  readonly Resume: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };*/
}
