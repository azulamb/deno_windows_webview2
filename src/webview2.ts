import type { WEBVIEW2_FUNCS } from './webview2_types.ts';
import type { HRESULT, HWND, LPVOID } from 'jsr:@azulamb/winapi';
import type { Rect } from 'jsr:@azulamb/winapi@^0.1.6';

function createStringPointer(value: string) {
  const buffer = new Uint16Array(
    <number[]> [].map.call(value + '\0', (c: string) => {
      return c.charCodeAt(0);
    }),
  );
  return Deno.UnsafePointer.of(buffer);
}

export class WebView2 {
  protected webview2Connector!: Deno.PointerValue<unknown>;
  public lib: Deno.DynamicLibrary<WEBVIEW2_FUNCS>;
  constructor(lib: Deno.DynamicLibrary<WEBVIEW2_FUNCS>, env: LPVOID = null) {
    this.lib = lib;
    this.CreateWebView2Connector(env);
  }

  public CreateCoreWebView2Environment(
    callback: (result: HRESULT, env: LPVOID) => HRESULT, // HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
  ) {
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

  public CreateCoreWebView2EnvironmentWithOptions(
    browserExecutableFolder: string | null, // PCWSTR
    userDataFolder: string | null, // PCWSTR
    environmentOptions: LPVOID, // ICoreWebView2EnvironmentOptions*
    callback: (result: HRESULT, env: LPVOID) => HRESULT, // HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
  ) {
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

  public CreateWebView2Connector(
    env: LPVOID, // ICoreWebView2Environment*
  ) {
    this.webview2Connector = this.lib.symbols.CreateWebView2Connector(env);
    return this.webview2Connector;
  }
  /*readonly SetWebview2Environment: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'pointer';
  };*/
  public InitSettings() {
    return this.lib.symbols.InitSettings(this.webview2Connector);
  }
  public InitControllers(
    controller: LPVOID, // ICoreWebView2Controller*
  ) {
    return this.lib.symbols.InitControllers(this.webview2Connector, controller);
  }
  public CreateCoreWebView2Controller(
    hWnd: HWND,
    callback: (errorCode: HRESULT, controller: LPVOID) => HRESULT, // HRESULT(*callback)(HRESULT, ICoreWebView2Controller*)
  ) {
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
  /*readonly get_IsScriptEnabled: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/
  public set IsScriptEnabled(enable: boolean) {
    this.lib.symbols.put_IsScriptEnabled(
      this.webview2Connector,
      enable ? 1 : 0,
    );
  }
  public get IsScriptEnabled(): boolean {
    const data = new Int32Array([0]);
    const bool = Deno.UnsafePointer.of(data);
    this.lib.symbols.get_IsScriptEnabled(this.webview2Connector, bool);
    return data[0] !== 0;
  }
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
  public set Bounds(bounds: Rect) {
    this.lib.symbols.put_Bounds(this.webview2Connector, bounds.data);
  }
  /*readonly Close: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };*/
  public CoreWebView2() {
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
  };
  readonly PostWebMessageAsJson: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly PostWebMessageAsString: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly add_WebMessageReceived: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_WebMessageReceived: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };*/
  public Navigate(url: string) {
    return this.lib.symbols.Navigate(this.webview2Connector, createStringPointer(url));
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
  public Settings() {
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
