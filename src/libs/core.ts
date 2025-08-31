import type { HRESULT, LPVOID } from './winapi.ts';
import type { Webview2Context } from './types.ts';
import { createStringPointer } from './convert.ts';
import type {
  EventRegistrationToken,
  Webview2Funcs,
} from '../webview2_types.ts';
import type { WEB_RESOURCE_CONTEXT_TYPES } from '../constants/WEB_RESOURCE_CONTEXT.ts';

export class Core {
  protected webview2: Deno.PointerValue<unknown>;

  public get pointer(): Deno.PointerValue<unknown> {
    return this.webview2;
  }

  protected get libs(): Webview2Funcs {
    return this.context.lib;
  }

  constructor(protected context: Webview2Context) {
    this.webview2 = this.libs.symbols.CreateWebView2();
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
   * Posts a message to the WebView2 control as JSON.
   * @param json The JSON object to post.
   * @returns The HRESULT result of the operation.
   */
  public postWebMessageAsJson(
    // deno-lint-ignore no-explicit-any
    json: any,
  ): HRESULT {
    // TODO: use sender.
    return this.libs.symbols.PostWebMessageAsJson(
      this.webview2,
      createStringPointer(JSON.stringify(json)),
    );
  }

  /**
   * Posts a message to the WebView2 control as a string.
   * @param data The string to post.
   * @returns The HRESULT result of the operation.
   */
  public postWebMessageAsString(data: string): HRESULT {
    // TODO: use sender.
    return this.libs.symbols.PostWebMessageAsString(
      this.webview2,
      createStringPointer(data),
    );
  }

  /**
   * Adds a handler for the WebMessageReceived event.
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
    this.libs.symbols.add_WebMessageReceived(
      this.webview2,
      func.pointer,
      token,
    );
    return token;
  }

  /**
   * Removes a handler for the WebMessageReceived event.
   * @param token The EventRegistrationToken for the event handler.
   * @returns The HRESULT result of the operation.
   */
  public removeWebMessageReceived(token: EventRegistrationToken): HRESULT {
    const result = this.libs.symbols.remove_WebMessageReceived(
      this.webview2,
      token,
    );
    this.context.eventRegistrationToken.remove(token);
    return result;
  }

  /**
   * Navigates the WebView2 control to the specified URL.
   * @param url The URL to navigate to.
   * @returns The HRESULT result of the operation.
   */
  public navigate(url: string): HRESULT {
    return this.libs.symbols.Navigate(
      this.webview2,
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
  };
  readonly ExecuteScript: {
    readonly parameters: ['pointer', 'pointer', 'function'];
    readonly result: 'i32';
  };
  readonly AddHostObjectToScript: {
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
  };
  readonly Reload: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };
  readonly get_CanGoBack: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly get_CanGoForward: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly GoBack: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };
  readonly GoForward: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };
  readonly Stop: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };
  readonly add_ContentLoading: {
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
    this.libs.symbols.add_WebResourceRequested(
      this.webview2,
      func.pointer,
      token,
    );
    return token;
  }

  public removeWebResourceRequested(token: EventRegistrationToken): HRESULT {
    return this.libs.symbols.remove_WebResourceRequested(
      this.webview2,
      token,
    );
  }

  public addWebResourceRequestedFilter(
    uri: string,
    resourceContext: WEB_RESOURCE_CONTEXT_TYPES = 0,
  ) {
    return this.libs.symbols.AddWebResourceRequestedFilter(
      this.webview2,
      createStringPointer(uri),
      resourceContext,
    );
  }
  /*readonly RemoveWebResourceRequestedFilter: {
    readonly parameters: ['pointer', 'pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly add_WindowCloseRequested: {
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
   * Sets a virtual host name to folder mapping for the WebView2 control.
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
    return this.libs.symbols.SetVirtualHostNameToFolderMapping(
      this.webview2,
      createStringPointer(hostName),
      createStringPointer(folderPath),
      accessKindValue,
    );
  }

  /**
   * Clears the virtual host name to folder mapping for the specified host name.
   * @param hostName The host name to clear the mapping for.
   * @returns The HRESULT result of the operation.
   */
  public clearVirtualHostNameToFolderMapping(
    hostName: string,
  ): HRESULT {
    return this.libs.symbols.ClearVirtualHostNameToFolderMapping(
      this.webview2,
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
