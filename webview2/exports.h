#pragma once
#include "./source/WebView2.hpp"

#define EXPORT extern "C" __declspec(dllexport)

/**
* Original
*/

EXPORT const char* Global_GetDllVersion();

EXPORT ULONG COM_AddRef(IUnknown* value);
EXPORT ULONG COM_Release(IUnknown* value);
EXPORT void WebView2_Destroy(WebView2* value);
EXPORT void Environments_Destroy(Environments* value);
EXPORT void Settings_Destroy(Settings* value);
EXPORT void Controllers_Destroy(Controllers* value);

EXPORT WebView2* WebView2_Create();
EXPORT WebView2* WebView2_Init(WebView2* webview2);

EXPORT Environments* Environments_Create();

EXPORT Settings* Settings_Create();
EXPORT Settings* Settings_Init(Settings* settings);

EXPORT Controllers* Controllers_Create();
EXPORT Controllers* Controllers_Init(Controllers* controllers);

/**
* EventRegistrationToken
*/
EXPORT EventRegistrationToken* EventRegistrationToken_Create();
EXPORT void EventRegistrationToken_Remove(EventRegistrationToken* token);

/**
* Stream
*/
EXPORT IStream* JStream_Create(
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
	HRESULT(*clone)(IStream** ppstm),
	void(*destroyed)(void)
);

/**
* Global
*/

EXPORT HRESULT Global_CreateCoreWebView2Environment(
	Environments* environments,
	HRESULT(*callback)(HRESULT, ICoreWebView2Environment*)
);

EXPORT HRESULT Global_CreateCoreWebView2EnvironmentWithOptions(
	Environments* environments,
	PCWSTR browserExecutableFolder,
	PCWSTR userDataFolder,
	ICoreWebView2EnvironmentOptions* environmentOptions,
	HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
);

EXPORT HRESULT Global_CompareBrowserVersions(
	PCWSTR version1,
	PCWSTR version2,
	int* result
);

EXPORT HRESULT Global_GetAvailableCoreWebView2BrowserVersionString(
	PCWSTR browserExecutableFolder,
	LPWSTR* versionInfo
);

EXPORT HRESULT Global_GetAvailableCoreWebView2BrowserVersionStringWithOptions(
	PCWSTR browserExecutableFolder,
	ICoreWebView2EnvironmentOptions* environmentOptions,
	LPWSTR* versionInfo
);

/**
* ICoreWebView2Environment
*/

EXPORT HRESULT Environments_CreateCoreWebView2Controller(
	Environments* environments,
	HWND hWnd,
	HRESULT(*callback)(HRESULT, ICoreWebView2Controller*),
	Controllers* controllers
);

EXPORT HRESULT Environments_CreateWebResourceResponse(
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

EXPORT HRESULT Settings_get_IsScriptEnabled(Settings* settings, BOOL* isScriptEnabled);

EXPORT HRESULT Settings_put_IsScriptEnabled(Settings* settings, BOOL isScriptEnabled);

EXPORT HRESULT Settings_get_IsWebMessageEnabled(Settings* settings, BOOL* isWebMessageEnabled);

EXPORT HRESULT Settings_put_IsWebMessageEnabled(Settings* settings, BOOL isWebMessageEnabled);

EXPORT HRESULT Settings_get_AreDefaultScriptDialogsEnabled(Settings* settings, BOOL* areDefaultScriptDialogsEnabled);

EXPORT HRESULT Settings_put_AreDefaultScriptDialogsEnabled(Settings* settings, BOOL areDefaultScriptDialogsEnabled);

EXPORT HRESULT Settings_get_IsStatusBarEnabled(Settings* settings, BOOL* isStatusBarEnabled);

EXPORT HRESULT Settings_put_IsStatusBarEnabled(Settings* settings, BOOL isStatusBarEnabled);

EXPORT HRESULT Settings_get_AreDevToolsEnabled(Settings* settings, BOOL* areDevToolsEnabled);

EXPORT HRESULT Settings_put_AreDevToolsEnabled(Settings* settings, BOOL areDevToolsEnabled);

EXPORT HRESULT Settings_get_AreDefaultContextMenusEnabled(Settings* settings, BOOL* enabled);

EXPORT HRESULT Settings_put_AreDefaultContextMenusEnabled(Settings* settings, BOOL enabled);

EXPORT HRESULT Settings_get_AreHostObjectsAllowed(Settings* settings, BOOL* allowed);

EXPORT HRESULT Settings_put_AreHostObjectsAllowed(Settings* settings, BOOL allowed);

EXPORT HRESULT Settings_get_IsZoomControlEnabled(Settings* settings, BOOL* enabled);

EXPORT HRESULT Settings_put_IsZoomControlEnabled(Settings* settings, BOOL enabled);

EXPORT HRESULT Settings_get_IsBuiltInErrorPageEnabled(Settings* settings, BOOL* enabled);

EXPORT HRESULT Settings_put_IsBuiltInErrorPageEnabled(Settings* settings, BOOL enabled);

/**
* ICoreWebView2Settings2
*/

EXPORT HRESULT Settings_get_UserAgent(Settings* settings, LPWSTR userAgent, rsize_t* size);

EXPORT HRESULT Settings_put_UserAgent(Settings* settings, LPCWSTR userAgent);

/**
* ICoreWebView2Settings3
*/

EXPORT HRESULT Settings_get_AreBrowserAcceleratorKeysEnabled(Settings* settings, BOOL* areBrowserAcceleratorKeysEnabled);

EXPORT HRESULT Settings_put_AreBrowserAcceleratorKeysEnabled(Settings* settings, BOOL areBrowserAcceleratorKeysEnabled);

/**
* ICoreWebView2Settings4
*/

EXPORT HRESULT Settings_get_IsPasswordAutosaveEnabled(Settings* settings, BOOL* value);

EXPORT HRESULT Settings_put_IsPasswordAutosaveEnabled(Settings* settings, BOOL value);

EXPORT HRESULT Settings_get_IsGeneralAutofillEnabled(Settings* settings, BOOL* value);

EXPORT HRESULT Settings_put_IsGeneralAutofillEnabled(Settings* settings, BOOL value);

/**
* ICoreWebView2Settings5
*/

EXPORT HRESULT Settings_get_IsPinchZoomEnabled(Settings* settings, /* [retval][out] */ BOOL* enabled);

EXPORT HRESULT Settings_put_IsPinchZoomEnabled(Settings* settings, /* [in] */ BOOL enabled);

/**
* ICoreWebView2Settings6
*/

EXPORT HRESULT Settings_get_IsSwipeNavigationEnabled(Settings* settings, /* [retval][out] */ BOOL* enabled);

EXPORT HRESULT Settings_put_IsSwipeNavigationEnabled(Settings* settings, /* [in] */ BOOL enabled);

/**
* ICoreWebView2Settings6
*/

EXPORT HRESULT Settings_get_HiddenPdfToolbarItems(Settings* settings, COREWEBVIEW2_PDF_TOOLBAR_ITEMS* value);

EXPORT HRESULT Settings_put_HiddenPdfToolbarItems(Settings* settings, COREWEBVIEW2_PDF_TOOLBAR_ITEMS value);

/**
* ICoreWebView2Settings8
*/

EXPORT HRESULT Settings_get_IsReputationCheckingRequired(Settings* settings, BOOL* value);

EXPORT HRESULT Settings_put_IsReputationCheckingRequired(Settings* settings, BOOL value);

/**
* ICoreWebView2Settings9
*/

EXPORT HRESULT Settings_get_IsNonClientRegionSupportEnabled(Settings* settings, BOOL* value);

EXPORT HRESULT Settings_put_IsNonClientRegionSupportEnabled(Settings* settings, BOOL value);

/*
* ICoreWebView2Controller
*/

EXPORT HRESULT Controllers_add_AcceleratorKeyPressed(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2AcceleratorKeyPressedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT Controllers_remove_AcceleratorKeyPressed(
	Controllers* controllers,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT Controllers_get_Bounds(
	Controllers* controllers,
	/* [retval][out] */ RECT* bounds
);

EXPORT HRESULT Controllers_put_Bounds(
	Controllers* controllers,
	/* [in] */ RECT bounds
);

EXPORT HRESULT Controllers_Close(Controllers* controllers);

EXPORT HRESULT Controllers_get_CoreWebView2(Controllers* controllers, WebView2* webview2);

EXPORT HRESULT Controllers_add_GotFocus(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT Controllers_remove_GotFocus(
	Controllers* controllers,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT Controllers_get_IsVisible(
	Controllers* controllers,
	/* [retval][out] */ BOOL* isVisible
);

EXPORT HRESULT Controllers_put_IsVisible(
	Controllers* controllers,
	/* [in] */ BOOL isVisible
);

EXPORT HRESULT Controllers_add_LostFocus(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT Controllers_remove_LostFocus(
	Controllers* controllers,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT Controllers_MoveFocus(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_MOVE_FOCUS_REASON reason
);

EXPORT HRESULT Controllers_add_MoveFocusRequested(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2MoveFocusRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT Controllers_remove_MoveFocusRequested(
	Controllers* controllers,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT Controllers_NotifyParentWindowPositionChanged(Controllers* controllers);

EXPORT HRESULT Controllers_get_ParentWindow(
	Controllers* controllers,
	/* [retval][out] */ HWND* parentWindow
);

EXPORT HRESULT Controllers_put_ParentWindow(
	Controllers* controllers,
	/* [in] */ HWND parentWindow
);

EXPORT HRESULT Controllers_SetBoundsAndZoomFactor(
	Controllers* controllers,
	/* [in] */ RECT bounds,
	/* [in] */ double zoomFactor
);

EXPORT HRESULT Controllers_get_ZoomFactor(
	Controllers* controllers,
	/* [retval][out] */ double* zoomFactor
);

EXPORT HRESULT Controllers_put_ZoomFactor(
	Controllers* controllers,
	/* [in] */ double zoomFactor
);

EXPORT HRESULT Controllers_add_ZoomFactorChanged(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT Controllers_remove_ZoomFactorChanged(
	Controllers* controllers,
	/* [in] */ const EventRegistrationToken* token
);

/*
* ICoreWebView2Controller2
*/

EXPORT HRESULT Controllers_get_DefaultBackgroundColor(
	Controllers* controllers,
	/* [retval][out] */ COREWEBVIEW2_COLOR* backgroundColor
);

EXPORT HRESULT Controllers_put_DefaultBackgroundColor(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_COLOR backgroundColor
);

/*
* ICoreWebView2Controller3
*/

EXPORT HRESULT Controllers_add_RasterizationScaleChanged(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT Controllers_remove_RasterizationScaleChanged(
	Controllers* controllers,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT Controllers_get_BoundsMode(
	Controllers* controllers,
	/* [retval][out] */ COREWEBVIEW2_BOUNDS_MODE* boundsMode
);

EXPORT HRESULT Controllers_put_BoundsMode(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_BOUNDS_MODE boundsMode
);

EXPORT HRESULT Controllers_get_RasterizationScale(
	Controllers* controllers,
	/* [retval][out] */ double* scale
);

EXPORT HRESULT Controllers_put_RasterizationScale(
	Controllers* controllers,
	/* [in] */ double scale
);

EXPORT HRESULT Controllers_get_ShouldDetectMonitorScaleChanges(
	Controllers* controllers,
	/* [retval][out] */ BOOL* value
);

EXPORT HRESULT Controllers_put_ShouldDetectMonitorScaleChanges(
	Controllers* controllers,
	/* [in] */ BOOL value
);

/*
* ICoreWebView2Controller4
*/

EXPORT HRESULT Controllers_get_AllowExternalDrop(
	Controllers* controllers,
	/* [retval][out] */ BOOL* value
);

EXPORT HRESULT Controllers_put_AllowExternalDrop(
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

EXPORT HRESULT WebView2_CallDevToolsProtocolMethod(
	WebView2* webview2,
	/* [in] */ LPCWSTR methodName,
	/* [in] */ LPCWSTR parametersAsJson,
	/* [in] */ HRESULT(*callback)(/* [in] */ HRESULT, /* [in] */ LPCWSTR)
);

EXPORT HRESULT WebView2_GetDevToolsProtocolEventReceiver(
	WebView2* webview2,
	/* [in] */ LPCWSTR eventName,
	/* [retval][out] */ ICoreWebView2DevToolsProtocolEventReceiver** receiver
);

EXPORT HRESULT WebView2_OpenDevToolsWindow(WebView2* webview2);

/* Document */

EXPORT HRESULT WebView2_add_DocumentTitleChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(/* [in] */ ICoreWebView2*, /* [in] */ IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_DocumentTitleChanged(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_get_DocumentTitle(
	WebView2* webview2,
	// TODO: LPWSTR
	/* [retval][out] */ LPWSTR* title
);

/* History */

EXPORT HRESULT WebView2_add_HistoryChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_HistoryChanged(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

/* Message */

EXPORT HRESULT WebView2_PostWebMessageAsJson(
	WebView2* webview2,
	/* [in] */ LPCWSTR webMessageAsJson
);

EXPORT HRESULT WebView2_PostWebMessageAsString(
	WebView2* webview2,
	/* [in] */ LPCWSTR webMessageAsString
);

EXPORT HRESULT WebView2_add_WebMessageReceived(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebMessageReceivedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_WebMessageReceived(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

/* Navigation */

EXPORT HRESULT WebView2_Navigate(
	WebView2* webview2,
	/* [in] */ LPCWSTR uri
);

EXPORT HRESULT WebView2_add_NavigationCompleted(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_NavigationCompleted(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_add_NavigationStarting(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_NavigationStarting(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_NavigateToString(
	WebView2* webview2,
	/* [in] */ LPCWSTR htmlContent
);

EXPORT HRESULT WebView2_add_FrameNavigationCompleted(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_FrameNavigationCompleted(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_add_FrameNavigationStarting(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_FrameNavigationStarting(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

/* Permission */

EXPORT HRESULT WebView2_add_PermissionRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2PermissionRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_PermissionRequested(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

/* Script */

EXPORT HRESULT WebView2_add_ScriptDialogOpening(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ScriptDialogOpeningEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_ScriptDialogOpening(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_AddScriptToExecuteOnDocumentCreated(
	WebView2* webview2,
	/* [in] */ LPCWSTR javaScript,
	/* [in] */ HRESULT(*callback)(HRESULT, LPCWSTR)
);

EXPORT HRESULT WebView2_RemoveScriptToExecuteOnDocumentCreated(
	WebView2* webview2,
	/* [in] */ LPCWSTR id
);

EXPORT HRESULT WebView2_ExecuteScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR javaScript,
	/* [in] */ HRESULT(*callback)(HRESULT, LPCWSTR)
);

EXPORT HRESULT WebView2_AddHostObjectToScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR name,
	/* [in] */ VARIANT* object
);

EXPORT HRESULT WebView2_RemoveHostObjectFromScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR name
);

/* Source */

EXPORT HRESULT WebView2_get_Source(
	WebView2* webview2,
	// TODO: LPWSTR
	/* [retval][out] */ LPWSTR* uri
);

EXPORT HRESULT WebView2_add_SourceChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2SourceChangedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_SourceChanged(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

/* Operation */

EXPORT HRESULT WebView2_Reload(WebView2* webview2);

EXPORT HRESULT WebView2_get_CanGoBack(
	WebView2* webview2,
	/* [retval][out] */ BOOL* canGoBack
);

EXPORT HRESULT WebView2_get_CanGoForward(
	WebView2* webview2,
	/* [retval][out] */ BOOL* canGoForward
);

EXPORT HRESULT WebView2_GoBack(WebView2* webview2);

EXPORT HRESULT WebView2_GoForward(WebView2* webview2);

EXPORT HRESULT WebView2_Stop(WebView2* webview2);

/* Other */

EXPORT HRESULT WebView2_add_ContentLoading(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ContentLoadingEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_ContentLoading(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_add_ProcessFailed(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ProcessFailedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_ProcessFailed(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_get_Settings(WebView2* webview2, Settings* settings);

EXPORT HRESULT WebView2_CapturePreview(
	WebView2* webview2,
	/* [in] */ COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT imageFormat,
	/* [in] */ IStream* imageStream,
	/* [in] */ HRESULT(*callback)(HRESULT errorCode)
);

EXPORT HRESULT WebView2_get_BrowserProcessId(
	WebView2* webview2,
	/* [retval][out] */ UINT32* value
);

EXPORT HRESULT WebView2_add_NewWindowRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NewWindowRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_NewWindowRequested(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_add_ContainsFullScreenElementChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_ContainsFullScreenElementChanged(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_get_ContainsFullScreenElement(
	WebView2* webview2,
	/* [retval][out] */ BOOL* containsFullScreenElement
);

EXPORT HRESULT WebView2_add_WebResourceRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_WebResourceRequested(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_AddWebResourceRequestedFilter(
	WebView2* webview2,
	/* [in] */ const LPCWSTR uri,
	/* [in] */ const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
);

EXPORT HRESULT WebView2_RemoveWebResourceRequestedFilter(
	WebView2* webview2,
	/* [in] */ const LPCWSTR uri,
	/* [in] */ const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
);

EXPORT HRESULT WebView2_add_WindowCloseRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_WindowCloseRequested(
	WebView2* webview2,
	/* [in] */ const EventRegistrationToken* token
);

/**
* ICoreWebView2_2
*/

EXPORT HRESULT WebView2_add_DOMContentLoaded(
	WebView2* webview2,
	HRESULT(*callback)(ICoreWebView2* sender, ICoreWebView2DOMContentLoadedEventArgs* args),
	EventRegistrationToken* token
);

EXPORT HRESULT WebView2_add_WebResourceResponseReceived(
	WebView2* webview2,
	HRESULT(*callback)(ICoreWebView2* sender, ICoreWebView2WebResourceResponseReceivedEventArgs* args),
	EventRegistrationToken* token
);

EXPORT HRESULT WebView2_get_CookieManager(
	WebView2* webview2,
	ICoreWebView2CookieManager** cookieManager
);

EXPORT HRESULT WebView2_get_Environment(
	WebView2* webview2,
	ICoreWebView2Environment** environment
);

EXPORT HRESULT WebView2_NavigateWithWebResourceRequest(
	WebView2* webview2,
	ICoreWebView2WebResourceRequest* request
);

EXPORT HRESULT WebView2_remove_DOMContentLoaded(
	WebView2* webview2,
	const EventRegistrationToken* token
);

EXPORT HRESULT WebView2_remove_WebResourceResponseReceived(
	WebView2* webview2,
	const EventRegistrationToken* token
);

/**
* ICoreWebView2_3
*/

EXPORT HRESULT WebView2_SetVirtualHostNameToFolderMapping(
	WebView2* webview2,
	LPCWSTR hostName,
	LPCWSTR folderPath,
	COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND accessKind
);

EXPORT HRESULT WebView2_ClearVirtualHostNameToFolderMapping(
	WebView2* webview2,
	LPCWSTR hostName
);

EXPORT HRESULT WebView2_get_IsSuspended(WebView2* webview2, BOOL* isSuspended);

EXPORT HRESULT WebView2_TrySuspend(WebView2* webview2, HRESULT(*callback)(HRESULT errorCode, BOOL isSuccessful));

EXPORT HRESULT WebView2_Resume(WebView2* webview2);

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
	LPWSTR method,
	rsize_t* size
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

EXPORT HRESULT HttpResponseHeaders_Contains(
	ICoreWebView2HttpResponseHeaders* headers,
	LPCWSTR name,
	BOOL* contains
);

EXPORT HRESULT HttpResponseHeaders_GetHeader(
	ICoreWebView2HttpResponseHeaders* headers,
	LPCWSTR name,
	LPWSTR value,
	rsize_t* size
);

EXPORT HRESULT HttpResponseHeaders_GetHeaders(
	ICoreWebView2HttpResponseHeaders* headers,
	LPCWSTR name,
	BOOL(*callback)(PWSTR value)
);

EXPORT HRESULT HttpResponseHeaders_GetIterator(
	ICoreWebView2HttpResponseHeaders* headers,
	BOOL(*callback)(PWSTR name, PWSTR value)
);


EXPORT HRESULT NavigationStartingEventArgs_get_Uri(ICoreWebView2NavigationStartingEventArgs* args, LPWSTR value, rsize_t* size);
EXPORT HRESULT NavigationStartingEventArgs_get_IsUserInitiated(ICoreWebView2NavigationStartingEventArgs* args, BOOL* value);
EXPORT HRESULT NavigationStartingEventArgs_get_IsRedirected(ICoreWebView2NavigationStartingEventArgs* args, BOOL* value);
EXPORT HRESULT NavigationStartingEventArgs_get_Cancel(ICoreWebView2NavigationStartingEventArgs* args, BOOL* value);
EXPORT HRESULT NavigationStartingEventArgs_put_Cancel(ICoreWebView2NavigationStartingEventArgs* args, BOOL value);
EXPORT HRESULT NavigationStartingEventArgs_get_NavigationId(ICoreWebView2NavigationStartingEventArgs* args, UINT64* value);
EXPORT HRESULT NavigationCompletedEventArgs_get_IsSuccess(ICoreWebView2NavigationCompletedEventArgs* args, BOOL* value);
EXPORT HRESULT NavigationCompletedEventArgs_get_WebErrorStatus(ICoreWebView2NavigationCompletedEventArgs* args, COREWEBVIEW2_WEB_ERROR_STATUS* value);
EXPORT HRESULT NavigationCompletedEventArgs_get_NavigationId(ICoreWebView2NavigationCompletedEventArgs* args, UINT64* value);
EXPORT HRESULT NewWindowRequestedEventArgs_get_Uri(ICoreWebView2NewWindowRequestedEventArgs* args, LPWSTR value, rsize_t* size);
EXPORT HRESULT NewWindowRequestedEventArgs_get_IsUserInitiated(ICoreWebView2NewWindowRequestedEventArgs* args, BOOL* value);
EXPORT HRESULT NewWindowRequestedEventArgs_get_Handled(ICoreWebView2NewWindowRequestedEventArgs* args, BOOL* value);
EXPORT HRESULT NewWindowRequestedEventArgs_put_Handled(ICoreWebView2NewWindowRequestedEventArgs* args, BOOL value);
EXPORT HRESULT NewWindowRequestedEventArgs_GetDeferral(ICoreWebView2NewWindowRequestedEventArgs* args, ICoreWebView2Deferral** value);
EXPORT HRESULT PermissionRequestedEventArgs_get_Uri(ICoreWebView2PermissionRequestedEventArgs* args, LPWSTR value, rsize_t* size);
EXPORT HRESULT PermissionRequestedEventArgs_get_PermissionKind(ICoreWebView2PermissionRequestedEventArgs* args, COREWEBVIEW2_PERMISSION_KIND* value);
EXPORT HRESULT PermissionRequestedEventArgs_get_IsUserInitiated(ICoreWebView2PermissionRequestedEventArgs* args, BOOL* value);
EXPORT HRESULT PermissionRequestedEventArgs_get_State(ICoreWebView2PermissionRequestedEventArgs* args, COREWEBVIEW2_PERMISSION_STATE* value);
EXPORT HRESULT PermissionRequestedEventArgs_put_State(ICoreWebView2PermissionRequestedEventArgs* args, COREWEBVIEW2_PERMISSION_STATE value);
EXPORT HRESULT PermissionRequestedEventArgs_GetDeferral(ICoreWebView2PermissionRequestedEventArgs* args, ICoreWebView2Deferral** value);

EXPORT HRESULT HttpResponseHeaders_AppendHeader(
	ICoreWebView2HttpResponseHeaders* headers,
	LPCWSTR name,
	LPCWSTR value
);
