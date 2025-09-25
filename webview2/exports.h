#pragma once
#include "./source/WebView2.hpp"

#define EXPORT extern "C" __declspec(dllexport)

/**
* Original
*/

EXPORT const char* GetDllVersion();

EXPORT WebView2* CreateWebView2();
EXPORT WebView2* InitWebView2(WebView2* webview2);

EXPORT Environments* CreateEnvironments();

EXPORT Settings* CreateSettings();
EXPORT Settings* InitSettings(Settings* settings);

EXPORT Controllers* CreateControllers();
EXPORT Controllers* InitControllers(Controllers* controllers);

/**
* EventRegistrationToken
*/
EXPORT EventRegistrationToken* CreateEventRegistrationToken();
EXPORT void RemoveEventRegistrationToken(EventRegistrationToken* token);

/**
* Stream
*/
EXPORT IStream* CreateJStream(
	HRESULT(*queryInterface)(REFIID riid, void** ppvObject),
	ULONG(*addRef)(void),
	ULONG(*release)(void),
	HRESULT(*read)(void* pv, ULONG cb, ULONG* pcbRead),
	HRESULT(*write)(const void* pv, ULONG cb, ULONG* pcbWritten),
	HRESULT(*seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition),
	HRESULT(*setSize)(ULARGE_INTEGER libNewSize),
	HRESULT(*copyTo)(IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead, ULARGE_INTEGER* pcbWritten),
	HRESULT(*commit)(DWORD grfCommitFlags),
	HRESULT(*revert)(void),
	HRESULT(*lockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType),
	HRESULT(*unlockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType),
	HRESULT(*stat)(STATSTG* pstatstg, DWORD grfStatFlag),
	HRESULT(*clone)(IStream** ppstm)
);

/**
* Global
*/

EXPORT HRESULT _CreateCoreWebView2Environment(
	Environments* environments,
	HRESULT(*callback)(HRESULT, ICoreWebView2Environment*)
);

EXPORT HRESULT _CreateCoreWebView2EnvironmentWithOptions(
	Environments* environments,
	PCWSTR browserExecutableFolder,
	PCWSTR userDataFolder,
	ICoreWebView2EnvironmentOptions* environmentOptions,
	HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
);

EXPORT HRESULT _CompareBrowserVersions(
	PCWSTR version1,
	PCWSTR version2,
	int* result
);

EXPORT HRESULT _GetAvailableCoreWebView2BrowserVersionString(
	PCWSTR browserExecutableFolder,
	LPWSTR* versionInfo
);

EXPORT HRESULT _GetAvailableCoreWebView2BrowserVersionStringWithOptions(
	PCWSTR browserExecutableFolder,
	ICoreWebView2EnvironmentOptions* environmentOptions,
	LPWSTR* versionInfo
);

/**
* ICoreWebView2Environment
*/

EXPORT HRESULT CreateCoreWebView2Controller(
	Environments* environments,
	HWND hWnd,
	HRESULT(*callback)(HRESULT, ICoreWebView2Controller*),
	Controllers* controllers
);

EXPORT HRESULT CreateWebResourceResponse(
	Environments* environments,
	IStream* content,
	int statusCode,
	LPCWSTR reasonPhrase,
	LPCWSTR headers,
	ICoreWebView2WebResourceResponse** response
);

/**
* ICoreWebView2Settings
*/

EXPORT HRESULT get_IsScriptEnabled(Settings* settings, BOOL* isScriptEnabled);

EXPORT HRESULT put_IsScriptEnabled(Settings* settings, BOOL isScriptEnabled);

EXPORT HRESULT get_IsWebMessageEnabled(Settings* settings, BOOL* isWebMessageEnabled);

EXPORT HRESULT put_IsWebMessageEnabled(Settings* settings, BOOL isWebMessageEnabled);

EXPORT HRESULT get_AreDefaultScriptDialogsEnabled(Settings* settings, BOOL* areDefaultScriptDialogsEnabled);

EXPORT HRESULT put_AreDefaultScriptDialogsEnabled(Settings* settings, BOOL areDefaultScriptDialogsEnabled);

EXPORT HRESULT get_IsStatusBarEnabled(Settings* settings, BOOL* isStatusBarEnabled);

EXPORT HRESULT put_IsStatusBarEnabled(Settings* settings, BOOL isStatusBarEnabled);

EXPORT HRESULT get_AreDevToolsEnabled(Settings* settings, BOOL* areDevToolsEnabled);

EXPORT HRESULT put_AreDevToolsEnabled(Settings* settings, BOOL areDevToolsEnabled);

EXPORT HRESULT get_AreDefaultContextMenusEnabled(Settings* settings, BOOL* enabled);

EXPORT HRESULT put_AreDefaultContextMenusEnabled(Settings* settings, BOOL enabled);

EXPORT HRESULT get_AreHostObjectsAllowed(Settings* settings, BOOL* allowed);

EXPORT HRESULT put_AreHostObjectsAllowed(Settings* settings, BOOL allowed);

EXPORT HRESULT get_IsZoomControlEnabled(Settings* settings, BOOL* enabled);

EXPORT HRESULT put_IsZoomControlEnabled(Settings* settings, BOOL enabled);

EXPORT HRESULT get_IsBuiltInErrorPageEnabled(Settings* settings, BOOL* enabled);

EXPORT HRESULT put_IsBuiltInErrorPageEnabled(Settings* settings, BOOL enabled);

/**
* ICoreWebView2Settings2
*/

EXPORT HRESULT get_UserAgent(Settings* settings, LPWSTR userAgent, rsize_t* size);

EXPORT HRESULT put_UserAgent(Settings* settings, LPCWSTR userAgent);

/**
* ICoreWebView2Settings3
*/

EXPORT HRESULT get_AreBrowserAcceleratorKeysEnabled(Settings* settings, BOOL* areBrowserAcceleratorKeysEnabled);

EXPORT HRESULT put_AreBrowserAcceleratorKeysEnabled(Settings* settings, BOOL areBrowserAcceleratorKeysEnabled);

/**
* ICoreWebView2Settings4
*/

EXPORT HRESULT get_IsPasswordAutosaveEnabled(Settings* settings, BOOL* value);

EXPORT HRESULT put_IsPasswordAutosaveEnabled(Settings* settings, BOOL value);

EXPORT HRESULT get_IsGeneralAutofillEnabled(Settings* settings, BOOL* value);

EXPORT HRESULT put_IsGeneralAutofillEnabled(Settings* settings, BOOL value);

/**
* ICoreWebView2Settings5
*/

EXPORT HRESULT get_IsPinchZoomEnabled(Settings* settings, /* [retval][out] */ BOOL* enabled);

EXPORT HRESULT put_IsPinchZoomEnabled(Settings* settings, /* [in] */ BOOL enabled);

/**
* ICoreWebView2Settings6
*/

EXPORT HRESULT get_IsSwipeNavigationEnabled(Settings* settings, /* [retval][out] */ BOOL* enabled);

EXPORT HRESULT put_IsSwipeNavigationEnabled(Settings* settings, /* [in] */ BOOL enabled);

/**
* ICoreWebView2Settings6
*/

EXPORT HRESULT get_HiddenPdfToolbarItems(Settings* settings, COREWEBVIEW2_PDF_TOOLBAR_ITEMS* value);

EXPORT HRESULT put_HiddenPdfToolbarItems(Settings* settings, COREWEBVIEW2_PDF_TOOLBAR_ITEMS value);

/**
* ICoreWebView2Settings8
*/

EXPORT HRESULT get_IsReputationCheckingRequired(Settings* settings, BOOL* value);

EXPORT HRESULT put_IsReputationCheckingRequired(Settings* settings, BOOL value);

/**
* ICoreWebView2Settings9
*/

EXPORT HRESULT get_IsNonClientRegionSupportEnabled(Settings* settings, BOOL* value);

EXPORT HRESULT put_IsNonClientRegionSupportEnabled(Settings* settings, BOOL value);

/*
* ICoreWebView2Controller
*/

EXPORT HRESULT add_AcceleratorKeyPressed(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2AcceleratorKeyPressedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_AcceleratorKeyPressed(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT get_Bounds(
	Controllers* controllers,
	/* [retval][out] */ RECT* bounds
);

EXPORT HRESULT put_Bounds(
	Controllers* controllers,
	/* [in] */ RECT bounds
);

EXPORT HRESULT Close(Controllers* controllers);

EXPORT HRESULT get_CoreWebView2(Controllers* controllers, WebView2* webview2);

EXPORT HRESULT add_GotFocus(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_GotFocus(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT get_IsVisible(
	Controllers* controllers,
	/* [retval][out] */ BOOL* isVisible
);

EXPORT HRESULT put_IsVisible(
	Controllers* controllers,
	/* [in] */ BOOL isVisible
);

EXPORT HRESULT add_LostFocus(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_LostFocus(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT MoveFocus(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_MOVE_FOCUS_REASON reason
);

EXPORT HRESULT add_MoveFocusRequested(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2MoveFocusRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_MoveFocusRequested(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT NotifyParentWindowPositionChanged(Controllers* controllers);

EXPORT HRESULT get_ParentWindow(
	Controllers* controllers,
	/* [retval][out] */ HWND* parentWindow
);

EXPORT HRESULT put_ParentWindow(
	Controllers* controllers,
	/* [in] */ HWND parentWindow
);

EXPORT HRESULT SetBoundsAndZoomFactor(
	Controllers* controllers,
	/* [in] */ RECT bounds,
	/* [in] */ double zoomFactor
);

EXPORT HRESULT get_ZoomFactor(
	Controllers* controllers,
	/* [retval][out] */ double* zoomFactor
);

EXPORT HRESULT put_ZoomFactor(
	Controllers* controllers,
	/* [in] */ double zoomFactor
);

EXPORT HRESULT add_ZoomFactorChanged(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_ZoomFactorChanged(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
);

/*
* ICoreWebView2Controller2
*/

EXPORT HRESULT get_DefaultBackgroundColor(
	Controllers* controllers,
	/* [retval][out] */ COREWEBVIEW2_COLOR* backgroundColor
);

EXPORT HRESULT put_DefaultBackgroundColor(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_COLOR backgroundColor
);

/*
* ICoreWebView2Controller3
*/

EXPORT HRESULT add_RasterizationScaleChanged(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_RasterizationScaleChanged(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT get_BoundsMode(
	Controllers* controllers,
	/* [retval][out] */ COREWEBVIEW2_BOUNDS_MODE* boundsMode
);

EXPORT HRESULT put_BoundsMode(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_BOUNDS_MODE boundsMode
);

EXPORT HRESULT get_RasterizationScale(
	Controllers* controllers,
	/* [retval][out] */ double* scale
);

EXPORT HRESULT put_RasterizationScale(
	Controllers* controllers,
	/* [in] */ double scale
);

EXPORT HRESULT get_ShouldDetectMonitorScaleChanges(
	Controllers* controllers,
	/* [retval][out] */ BOOL* value
);

EXPORT HRESULT put_ShouldDetectMonitorScaleChanges(
	Controllers* controllers,
	/* [in] */ BOOL value
);

/*
* ICoreWebView2Controller4
*/

EXPORT HRESULT get_AllowExternalDrop(
	Controllers* controllers,
	/* [retval][out] */ BOOL* value
);

EXPORT HRESULT put_AllowExternalDrop(
	Controllers* controllers,
	/* [in] */ BOOL value
);

/*
* ICoreWebView2Deferral
*/

EXPORT HRESULT Deferral_Complete(ICoreWebView2Deferral* deferral);

/**
* ICoreWebView2
*/

/* Development */

EXPORT HRESULT CallDevToolsProtocolMethod(
	WebView2* webview2,
	/* [in] */ LPCWSTR methodName,
	/* [in] */ LPCWSTR parametersAsJson,
	/* [in] */ HRESULT(*callback)(/* [in] */ HRESULT, /* [in] */ LPCWSTR)
);

EXPORT HRESULT GetDevToolsProtocolEventReceiver(
	WebView2* webview2,
	/* [in] */ LPCWSTR eventName,
	/* [retval][out] */ ICoreWebView2DevToolsProtocolEventReceiver** receiver
);

EXPORT HRESULT OpenDevToolsWindow(WebView2* webview2);

/* Document */

EXPORT HRESULT add_DocumentTitleChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(/* [in] */ ICoreWebView2*, /* [in] */ IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_DocumentTitleChanged(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT get_DocumentTitle(
	WebView2* webview2,
	// TODO: LPWSTR
	/* [retval][out] */ LPWSTR* title
);

/* History */

EXPORT HRESULT add_HistoryChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_HistoryChanged(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

/* Message */

EXPORT HRESULT PostWebMessageAsJson(
	WebView2* webview2,
	/* [in] */ LPCWSTR webMessageAsJson
);

EXPORT HRESULT PostWebMessageAsString(
	WebView2* webview2,
	/* [in] */ LPCWSTR webMessageAsString
);

EXPORT HRESULT add_WebMessageReceived(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebMessageReceivedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_WebMessageReceived(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

/* Navigation */

EXPORT HRESULT Navigate(
	WebView2* webview2,
	/* [in] */ LPCWSTR uri
);

EXPORT HRESULT add_NavigationCompleted(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_NavigationCompleted(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT add_NavigationStarting(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_NavigationStarting(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT NavigateToString(
	WebView2* webview2,
	/* [in] */ LPCWSTR htmlContent
);

EXPORT HRESULT add_FrameNavigationCompleted(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_FrameNavigationCompleted(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT add_FrameNavigationStarting(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_FrameNavigationStarting(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

/* Permission */

EXPORT HRESULT add_PermissionRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2PermissionRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_PermissionRequested(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

/* Script */

EXPORT HRESULT add_ScriptDialogOpening(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ScriptDialogOpeningEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_ScriptDialogOpening(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT AddScriptToExecuteOnDocumentCreated(
	WebView2* webview2,
	/* [in] */ LPCWSTR javaScript,
	/* [in] */ HRESULT(*callback)(HRESULT, LPCWSTR)
);

EXPORT HRESULT RemoveScriptToExecuteOnDocumentCreated(
	WebView2* webview2,
	/* [in] */ LPCWSTR id
);

EXPORT HRESULT ExecuteScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR javaScript,
	/* [in] */ HRESULT(*callback)(HRESULT, LPCWSTR)
);

EXPORT HRESULT AddHostObjectToScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR name,
	/* [in] */ VARIANT* object
);

EXPORT HRESULT RemoveHostObjectFromScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR name
);

/* Source */

EXPORT HRESULT get_Source(
	WebView2* webview2,
	// TODO: LPWSTR
	/* [retval][out] */ LPWSTR* uri
);

EXPORT HRESULT add_SourceChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2SourceChangedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_SourceChanged(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

/* Operation */

EXPORT HRESULT Reload(WebView2* webview2);

EXPORT HRESULT get_CanGoBack(
	WebView2* webview2,
	/* [retval][out] */ BOOL* canGoBack
);

EXPORT HRESULT get_CanGoForward(
	WebView2* webview2,
	/* [retval][out] */ BOOL* canGoForward
);

EXPORT HRESULT GoBack(WebView2* webview2);

EXPORT HRESULT GoForward(WebView2* webview2);

EXPORT HRESULT Stop(WebView2* webview2);

/* Other */

EXPORT HRESULT add_ContentLoading(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ContentLoadingEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_ContentLoading(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT add_ProcessFailed(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ProcessFailedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_ProcessFailed(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT get_Settings(WebView2* webview2, Settings* settings);

EXPORT HRESULT CapturePreview(
	WebView2* webview2,
	/* [in] */ COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT imageFormat,
	/* [in] */ IStream* imageStream,
	/* [in] */ HRESULT(*callback)(HRESULT errorCode)
);

EXPORT HRESULT get_BrowserProcessId(
	WebView2* webview2,
	/* [retval][out] */ UINT32* value
);

EXPORT HRESULT add_NewWindowRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NewWindowRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_NewWindowRequested(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT add_ContainsFullScreenElementChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_ContainsFullScreenElementChanged(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT get_ContainsFullScreenElement(
	WebView2* webview2,
	/* [retval][out] */ BOOL* containsFullScreenElement
);

EXPORT HRESULT add_WebResourceRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_WebResourceRequested(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

EXPORT HRESULT AddWebResourceRequestedFilter(
	WebView2* webview2,
	/* [in] */ const LPCWSTR uri,
	/* [in] */ const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
);

EXPORT HRESULT RemoveWebResourceRequestedFilter(
	WebView2* webview2,
	/* [in] */ const LPCWSTR uri,
	/* [in] */ const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
);

EXPORT HRESULT add_WindowCloseRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT remove_WindowCloseRequested(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
);

/**
* ICoreWebView2_2
*/

EXPORT HRESULT add_DOMContentLoaded(
	WebView2* webview2,
	HRESULT(*callback)(ICoreWebView2* sender, ICoreWebView2DOMContentLoadedEventArgs* args),
	EventRegistrationToken* token
);

EXPORT HRESULT add_WebResourceResponseReceived(
	WebView2* webview2,
	HRESULT(*callback)(ICoreWebView2* sender, ICoreWebView2WebResourceResponseReceivedEventArgs* args),
	EventRegistrationToken* token
);

EXPORT HRESULT get_CookieManager(
	WebView2* webview2,
	ICoreWebView2CookieManager** cookieManager
);

EXPORT HRESULT get_Environment(
	WebView2* webview2,
	ICoreWebView2Environment** environment
);

EXPORT HRESULT NavigateWithWebResourceRequest(
	WebView2* webview2,
	ICoreWebView2WebResourceRequest* request
);

EXPORT HRESULT remove_DOMContentLoaded(
	WebView2* webview2,
	EventRegistrationToken token
);

EXPORT HRESULT remove_WebResourceResponseReceived(
	WebView2* webview2,
	EventRegistrationToken token
);

/**
* ICoreWebView2_3
*/

EXPORT HRESULT SetVirtualHostNameToFolderMapping(
	WebView2* webview2,
	LPCWSTR hostName,
	LPCWSTR folderPath,
	COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND accessKind
);

EXPORT HRESULT ClearVirtualHostNameToFolderMapping(
	WebView2* webview2,
	LPCWSTR hostName
);

EXPORT HRESULT get_IsSuspended(WebView2* webview2, BOOL* isSuspended);

EXPORT HRESULT TrySuspend(WebView2* webview2, HRESULT(*callback)(HRESULT errorCode, BOOL isSuccessful));

EXPORT HRESULT Resume(WebView2* webview2);

/**
* ICoreWebView2WebMessageReceivedEventArgs
*/

EXPORT HRESULT WebMessageReceivedEventArgs_get_Source(
	ICoreWebView2WebMessageReceivedEventArgs* args,
	LPWSTR dest,
	rsize_t* size
);

EXPORT HRESULT WebMessageReceivedEventArgs_get_WebMessageAsJson(
	ICoreWebView2WebMessageReceivedEventArgs* args,
	LPWSTR webMessageAsJson,
	rsize_t* size
);

EXPORT HRESULT WebMessageReceivedEventArgs_TryGetWebMessageAsString(
	ICoreWebView2WebMessageReceivedEventArgs* args,
	LPWSTR webMessageAsString,
	rsize_t* size
);

/**
* IStream
*/

EXPORT HRESULT IStream_Read(
	IStream* stream,
	void* pv,
	ULONG cb,
	ULONG* pcbRead
);

EXPORT HRESULT IStream_Write(
	IStream* stream,
	void* pv,
	ULONG cb,
	ULONG* pcbWritten
);

/**
* ICoreWebView2HttpRequestHeaders
*/

EXPORT HRESULT HttpRequestHeaders_Contains(
	ICoreWebView2HttpRequestHeaders* headers,
	LPCWSTR name,
	BOOL* contains
);

EXPORT HRESULT HttpRequestHeaders_GetHeader(
	ICoreWebView2HttpRequestHeaders* headers,
	LPCWSTR name,
	LPWSTR value,
	rsize_t* size
);

EXPORT HRESULT HttpRequestHeaders_GetHeaders(
	ICoreWebView2HttpRequestHeaders* headers,
	LPCWSTR name,
	BOOL(*callback)(PWSTR value)
);

EXPORT HRESULT HttpRequestHeaders_GetIterator(
	ICoreWebView2HttpRequestHeaders* headers,
	BOOL(*callback)(PWSTR name, PWSTR value)
);

EXPORT HRESULT HttpRequestHeaders_RemoveHeader(
	ICoreWebView2HttpRequestHeaders* headers,
	LPCWSTR name
);

EXPORT HRESULT HttpRequestHeaders_SetHeader(
	ICoreWebView2HttpRequestHeaders* headers,
	LPCWSTR name,
	LPCWSTR value
);

/**
* ICoreWebView2WebResourceRequest
*/

EXPORT HRESULT WebResourceRequest_get_Content(
	ICoreWebView2WebResourceRequest* request,
	IStream** content
);

EXPORT HRESULT WebResourceRequest_get_Headers(
	ICoreWebView2WebResourceRequest* request,
	ICoreWebView2HttpRequestHeaders** headers
);

EXPORT HRESULT WebResourceRequest_get_Method(
	ICoreWebView2WebResourceRequest* request,
	LPWSTR method
);

EXPORT HRESULT WebResourceRequest_get_Uri(
	ICoreWebView2WebResourceRequest* request,
	LPWSTR uri,
	rsize_t* size
);

EXPORT HRESULT WebResourceRequest_put_Content(
	ICoreWebView2WebResourceRequest* request,
	IStream* content
);

EXPORT HRESULT WebResourceRequest_put_Method(
	ICoreWebView2WebResourceRequest* request,
	LPCWSTR method
);

EXPORT HRESULT WebResourceRequest_put_Uri(
	ICoreWebView2WebResourceRequest* request,
	LPCWSTR uri
);

/**
* ICoreWebView2WebResourceResponse
*/

EXPORT HRESULT WebResourceResponse_get_Content(
	ICoreWebView2WebResourceResponse* response,
	IStream** content
);

EXPORT HRESULT WebResourceResponse_get_Headers(
	ICoreWebView2WebResourceResponse* response,
	ICoreWebView2HttpResponseHeaders** headers
);

EXPORT HRESULT WebResourceResponse_get_ReasonPhrase(
	ICoreWebView2WebResourceResponse* response,
	LPWSTR reasonPhrase,
	rsize_t* size
);

EXPORT HRESULT WebResourceResponse_get_StatusCode(
	ICoreWebView2WebResourceResponse* response,
	int* statusCode
);

EXPORT HRESULT WebResourceResponse_put_Content(
	ICoreWebView2WebResourceResponse* response,
	IStream* content
);

EXPORT HRESULT WebResourceResponse_put_ReasonPhrase(
	ICoreWebView2WebResourceResponse* response,
	LPCWSTR reasonPhrase
);

EXPORT HRESULT WebResourceResponse_put_StatusCode(
	ICoreWebView2WebResourceResponse* response,
	int statusCode
);

/**
* ICoreWebView2WebResourceRequestedEventArgs
*/

EXPORT HRESULT WebResourceRequestedEventArgs_get_Request(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	ICoreWebView2WebResourceRequest** request
);

EXPORT HRESULT WebResourceRequestedEventArgs_get_ResourceContext(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	COREWEBVIEW2_WEB_RESOURCE_CONTEXT* context
);

EXPORT HRESULT WebResourceRequestedEventArgs_get_Response(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	ICoreWebView2WebResourceResponse** response
);

EXPORT HRESULT WebResourceRequestedEventArgs_GetDeferral(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	ICoreWebView2Deferral** deferral
);

EXPORT HRESULT WebResourceRequestedEventArgs_put_Response(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	ICoreWebView2WebResourceResponse* response
);
