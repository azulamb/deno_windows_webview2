import type {
  EventRegistrationToken,
  WEBVIEW2_FUNCS,
} from './webview2_types.ts';
import type { HRESULT, HWND, LPVOID } from 'jsr:@azulamb/winapi@^0.1.6';
import type { Rect } from 'jsr:@azulamb/winapi@^0.1.6';

function createStringPointer(value: string) {
  const buffer = new Uint16Array(
    <number[]> [].map.call(value + '\0', (c: string) => {
      return c.charCodeAt(0);
    }),
  );
  return Deno.UnsafePointer.of(buffer);
}

/**
 * The WebView2 class provides an interface for interacting with the WebView2 control.
 */
export class WebView2 {
  protected webview2Connector!: Deno.PointerValue<unknown>;

  /**
   * Creates an instance of the WebView2 class.
   * @param lib The dynamic library containing the WebView2 functions.
   * @param env The environment pointer.
   */
  constructor(
    readonly lib: Deno.DynamicLibrary<WEBVIEW2_FUNCS>,
    env: LPVOID = null,
  ) {
    this.CreateWebView2Connector(env);
  }

  /**
   * Creates a CoreWebView2Environment.
   * @param callback The callback to invoke when the operation completes.
   * @returns The HRESULT of the operation.
   */
  public CreateCoreWebView2Environment(
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
    return this.lib.symbols._CreateCoreWebView2Environment(
      this.webview2Connector,
      func.pointer,
    );
  }

  /**
   * Creates a CoreWebView2Environment with options.
   * @param browserExecutableFolder The path to the browser executable folder.
   * @param userDataFolder The path to the user data folder.
   * @param environmentOptions The environment options.
   * @param callback The callback to invoke when the operation completes.
   * @returns The HRESULT of the operation.
   */
  public CreateCoreWebView2EnvironmentWithOptions(
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

    return this.lib.symbols._CreateCoreWebView2EnvironmentWithOptions(
      this.webview2Connector,
      browserExecutableFolder
        ? createStringPointer(browserExecutableFolder)
        : null,
      userDataFolder ? createStringPointer(userDataFolder) : null,
      environmentOptions,
      func.pointer,
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

  /**
   * Creates a WebView2 connector.
   * @param env The environment pointer.
   * @returns The WebView2 connector pointer.
   */
  public CreateWebView2Connector(
    env: LPVOID, // ICoreWebView2Environment*
  ): LPVOID {
    this.webview2Connector = this.lib.symbols.CreateWebView2Connector(env);
    return this.webview2Connector;
  }

  /*readonly SetWebview2Environment: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'pointer';
  };*/

  /**
   * Initializes the settings for the WebView2 control.
   * @returns The pointer to the initialized settings.
   */
  public InitSettings(): LPVOID {
    return this.lib.symbols.InitSettings(this.webview2Connector);
  }

  /**
   * Initializes the controllers for the WebView2 control.
   * @param controller The controller pointer.
   * @returns The pointer to the initialized controllers.
   */
  public InitControllers(
    controller: LPVOID, // ICoreWebView2Controller*
  ): LPVOID {
    return this.lib.symbols.InitControllers(this.webview2Connector, controller);
  }

  /**
   * Creates a CoreWebView2Controller.
   * @param hWnd The window handle.
   * @param callback The callback to invoke when the operation completes.
   * @returns The HRESULT of the operation.
   */
  public CreateCoreWebView2Controller(
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
      this.webview2Connector,
      hWnd,
      func.pointer,
    );
  }

  /**
   * Creates an event registration token.
   * @returns The event registration token.
   */
  public CreateEventRegistrationToken(): EventRegistrationToken {
    return this.lib.symbols.CreateEventRegistrationToken();
  }

  /**
   * Removes an event registration token.
   * @param token The event registration token to remove.
   */
  public RemoveEventRegistrationToken(token: EventRegistrationToken): void {
    this.lib.symbols.RemoveEventRegistrationToken(token);
  }

  /*readonly get_IsScriptEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Enables or disables script execution in the WebView2 control.
   * @param enable True to enable script execution; false to disable it.
   */
  public set IsScriptEnabled(enable: boolean) {
    this.lib.symbols.put_IsScriptEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether script execution is enabled in the WebView2 control.
   * @returns True if script execution is enabled; false otherwise.
   */
  public get IsScriptEnabled(): boolean {
    const data = new Int32Array([0]);
    const bool = Deno.UnsafePointer.of(data);
    this.lib.symbols.get_IsScriptEnabled(this.webview2Connector, bool);
    return data[0] !== 0;
  }

  /**
   * Enables or disables web message handling in the WebView2 control.
   * @param enable True to enable web message handling; false to disable it.
   */
  public set IsWebMessageEnabled(enable: boolean) {
    this.lib.symbols.put_IsWebMessageEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /*readonly get_AreDefaultScriptDialogsEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Enables or disables default script dialogs in the WebView2 control.
   * @param enable True to enable default script dialogs; false to disable them.
   */
  public set AreDefaultScriptDialogsEnabled(enable: boolean) {
    this.lib.symbols.put_AreDefaultScriptDialogsEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /*readonly get_IsStatusBarEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Enables or disables the status bar in the WebView2 control.
   * @param enable True to enable the status bar; false to disable it.
   */
  public set IsStatusBarEnabled(enable: boolean) {
    this.lib.symbols.put_IsStatusBarEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /*readonly get_AreDevToolsEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Enables or disables the Developer Tools in the WebView2 control.
   * @param enable True to enable Developer Tools; false to disable them.
   */
  public set AreDevToolsEnabled(enable: boolean) {
    this.lib.symbols.put_AreDevToolsEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /*readonly get_AreDefaultContextMenusEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Enables or disables the default context menus in the WebView2 control.
   * @param enable True to enable default context menus; false to disable them.
   */
  public set AreDefaultContextMenusEnabled(enable: boolean) {
    this.lib.symbols.put_AreDefaultContextMenusEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /*readonly get_AreHostObjectsAllowed: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Enables or disables host objects in the WebView2 control.
   * @param enable True to allow host objects; false to disallow them.
   */
  public set AreHostObjectsAllowed(enable: boolean) {
    this.lib.symbols.put_AreHostObjectsAllowed(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /*readonly get_IsZoomControlEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Enables or disables the zoom control in the WebView2 control.
   * @param enable True to enable the zoom control; false to disable it.
   */
  public set IsZoomControlEnabled(enable: boolean) {
    this.lib.symbols.put_IsZoomControlEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /*readonly get_IsBuiltInErrorPageEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Enables or disables the built-in error page in the WebView2 control.
   * @param enable True to enable the built-in error page; false to disable it.
   */
  public set IsBuiltInErrorPageEnabled(enable: boolean) {
    this.lib.symbols.put_IsBuiltInErrorPageEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }

  /*readonly get_UserAgent: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_UserAgent: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly get_AreBrowserAcceleratorKeysEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_AreBrowserAcceleratorKeysEnabled: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly get_IsPasswordAutosaveEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_IsPasswordAutosaveEnabled: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly get_IsGeneralAutofillEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_IsGeneralAutofillEnabled: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly get_IsPinchZoomEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_IsPinchZoomEnabled: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly get_IsSwipeNavigationEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_IsSwipeNavigationEnabled: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly add_AcceleratorKeyPressed: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_AcceleratorKeyPressed: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_Bounds: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Sets the bounds of the WebView2 control.
   * @param bounds The new bounds for the control.
   */
  public set Bounds(bounds: Rect) {
    this.lib.symbols.put_Bounds(this.webview2Connector, bounds.data);
  }

  /*readonly Close: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Gets the CoreWebView2 instance associated with the WebView2 control.
   * @returns The HRESULT result of the operation.
   */
  public CoreWebView2(): HRESULT {
    return this.lib.symbols.get_CoreWebView2(this.webview2Connector);
  }

  /*readonly add_GotFocus: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_GotFocus: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_IsVisible: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_IsVisible: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly add_LostFocus: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_LostFocus: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly MoveFocus: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly add_MoveFocusRequested: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_MoveFocusRequested: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly NotifyParentWindowPositionChanged: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };
  readonly get_ParentWindow: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_ParentWindow: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly SetBoundsAndZoomFactor: {
    readonly parameters: ['pointer', 'buffer', 'f64'];
    readonly result: 'i32';
  };
  readonly get_ZoomFactor: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_ZoomFactor: {
    readonly parameters: ['pointer', 'f64'];
    readonly result: 'i32';
  };
  readonly add_ZoomFactorChanged: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_ZoomFactorChanged: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_DefaultBackgroundColor: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_DefaultBackgroundColor: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_RasterizationScaleChanged: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_RasterizationScaleChanged: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_BoundsMode: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_BoundsMode: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly get_RasterizationScale: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_RasterizationScale: {
    readonly parameters: ['pointer', 'f64'];
    readonly result: 'i32';
  };
  readonly get_ShouldDetectMonitorScaleChanges: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_ShouldDetectMonitorScaleChanges: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly get_AllowExternalDrop: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_AllowExternalDrop: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly CallDevToolsProtocolMethod: {
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
  public PostWebMessageAsJson(
    // deno-lint-ignore no-explicit-any
    json: any,
  ): HRESULT {
    return this.lib.symbols.PostWebMessageAsJson(
      this.webview2Connector,
      createStringPointer(JSON.stringify(json)),
    );
  }

  /**
   * Posts a message to the WebView2 control as a string.
   * @param data The string to post.
   * @returns The HRESULT result of the operation.
   */
  public PostWebMessageAsString(data: string): HRESULT {
    return this.lib.symbols.PostWebMessageAsString(
      this.webview2Connector,
      createStringPointer(data),
    );
  }

  /**
   * Adds a handler for the WebMessageReceived event.
   * @param callback The function to call when the event is raised.
   * @returns The EventRegistrationToken for the event handler.
   */
  public add_WebMessageReceived(
    callback: (coreWebView2: LPVOID, eventArgs: LPVOID) => HRESULT,
  ): EventRegistrationToken {
    const token = this.CreateEventRegistrationToken();
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
    this.lib.symbols.add_WebMessageReceived(
      this.webview2Connector,
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
  public remove_WebMessageReceived(token: EventRegistrationToken): HRESULT {
    const result = this.lib.symbols.remove_WebMessageReceived(
      this.webview2Connector,
      token,
    );
    this.RemoveEventRegistrationToken(token);
    return result;
  }

  /**
   * Navigates the WebView2 control to the specified URL.
   * @param url The URL to navigate to.
   * @returns The HRESULT result of the operation.
   */
  public Navigate(url: string): HRESULT {
    return this.lib.symbols.Navigate(
      this.webview2Connector,
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

  /**
   * Gets the settings for the WebView2 control.
   * @returns The result of the operation.
   */
  public Settings(): HRESULT {
    return this.lib.symbols.get_Settings(this.webview2Connector);
  }

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
  };
  readonly add_WebResourceRequested: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_WebResourceRequested: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly AddWebResourceRequestedFilter: {
    readonly parameters: ['pointer', 'pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly RemoveWebResourceRequestedFilter: {
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
  };*/
}
