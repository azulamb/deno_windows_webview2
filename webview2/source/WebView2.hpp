#pragma once
#include <WebView2.h>
#include <windows.h>

class WebView2Connector {
public:
	virtual WebView2Connector* setWebView2Environment(ICoreWebView2Environment* env) = 0;

	virtual WebView2Connector* initSettings() = 0;

	virtual WebView2Connector* initControllers(ICoreWebView2Controller* controller) = 0;

	/**
	* ICoreWebView2Environment
	*/

	virtual HRESULT CreateCoreWebView2Controller(HWND hWnd, HRESULT(*callback)(HRESULT, ICoreWebView2Controller*)) = 0;

	/**
	* ICoreWebView2Settings
	*/

	virtual HRESULT get_IsScriptEnabled(BOOL* isScriptEnabled) = 0;

	virtual HRESULT put_IsScriptEnabled(BOOL isScriptEnabled) = 0;

	virtual HRESULT get_IsWebMessageEnabled(BOOL* isWebMessageEnabled) = 0;

	virtual HRESULT put_IsWebMessageEnabled(BOOL isWebMessageEnabled) = 0;

	virtual HRESULT get_AreDefaultScriptDialogsEnabled(BOOL* areDefaultScriptDialogsEnabled) = 0;

	virtual HRESULT put_AreDefaultScriptDialogsEnabled(BOOL areDefaultScriptDialogsEnabled) = 0;

	virtual HRESULT get_IsStatusBarEnabled(BOOL* isStatusBarEnabled) = 0;

	virtual HRESULT put_IsStatusBarEnabled(BOOL isStatusBarEnabled) = 0;

	virtual HRESULT get_AreDevToolsEnabled(BOOL* areDevToolsEnabled) = 0;

	virtual HRESULT put_AreDevToolsEnabled(BOOL areDevToolsEnabled) = 0;

	virtual HRESULT get_AreDefaultContextMenusEnabled(BOOL* enabled) = 0;

	virtual HRESULT put_AreDefaultContextMenusEnabled(BOOL enabled) = 0;

	virtual HRESULT get_AreHostObjectsAllowed(BOOL* allowed) = 0;

	virtual HRESULT put_AreHostObjectsAllowed(BOOL allowed) = 0;

	virtual HRESULT get_IsZoomControlEnabled(BOOL* enabled) = 0;

	virtual HRESULT put_IsZoomControlEnabled(BOOL enabled) = 0;

	virtual HRESULT get_IsBuiltInErrorPageEnabled(BOOL* enabled) = 0;

	virtual HRESULT put_IsBuiltInErrorPageEnabled(BOOL enabled) = 0;

	/**
	* ICoreWebView2Settings2
	*/

	virtual HRESULT get_UserAgent(LPWSTR userAgent, rsize_t* size) = 0;

	virtual HRESULT put_UserAgent(LPCWSTR userAgent) = 0;

	/**
	* ICoreWebView2Settings3
	*/

	virtual HRESULT get_AreBrowserAcceleratorKeysEnabled(BOOL* areBrowserAcceleratorKeysEnabled) = 0;

	virtual HRESULT put_AreBrowserAcceleratorKeysEnabled(BOOL areBrowserAcceleratorKeysEnabled) = 0;

	/**
	* ICoreWebView2Settings4
	*/

	virtual HRESULT get_IsPasswordAutosaveEnabled(BOOL* value) = 0;

	virtual HRESULT put_IsPasswordAutosaveEnabled(BOOL value) = 0;

	virtual HRESULT get_IsGeneralAutofillEnabled(BOOL* value) = 0;

	virtual HRESULT put_IsGeneralAutofillEnabled(BOOL value) = 0;

	/**
	* ICoreWebView2Settings5
	*/

	virtual HRESULT get_IsPinchZoomEnabled(BOOL* enabled) = 0;

	virtual HRESULT put_IsPinchZoomEnabled(BOOL enabled) = 0;

	/**
	* ICoreWebView2Settings6
	*/

	virtual HRESULT get_IsSwipeNavigationEnabled(BOOL* enabled) = 0;

	virtual HRESULT put_IsSwipeNavigationEnabled(BOOL enabled) = 0;


	/**
	* ICoreWebView2Settings7
	*/

	virtual HRESULT get_HiddenPdfToolbarItems(COREWEBVIEW2_PDF_TOOLBAR_ITEMS* value) = 0;

	virtual HRESULT put_HiddenPdfToolbarItems(COREWEBVIEW2_PDF_TOOLBAR_ITEMS value) = 0;

	/**
	* ICoreWebView2Settings8
	*/

	virtual HRESULT get_IsReputationCheckingRequired(BOOL* value) = 0;

	virtual HRESULT put_IsReputationCheckingRequired(BOOL value) = 0;

	/**
	* ICoreWebView2Settings9
	*/

	virtual HRESULT get_IsNonClientRegionSupportEnabled(BOOL* value) = 0;

	virtual HRESULT put_IsNonClientRegionSupportEnabled(BOOL value) = 0;

	/*
	* ICoreWebView2Controller
	*/

	virtual HRESULT add_AcceleratorKeyPressed(
		HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2AcceleratorKeyPressedEventArgs*), // ICoreWebView2AcceleratorKeyPressedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_AcceleratorKeyPressed(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT get_Bounds(
		RECT* bounds
	) = 0;

	virtual HRESULT put_Bounds(
		RECT bounds
	) = 0;

	virtual HRESULT Close(void) = 0;

	virtual HRESULT get_CoreWebView2(
		// ICoreWebView2** coreWebView2
	) = 0;

	virtual HRESULT add_GotFocus(
		HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*), // ICoreWebView2FocusChangedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_GotFocus(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT get_IsVisible(
		BOOL* isVisible
	) = 0;

	virtual HRESULT put_IsVisible(
		BOOL isVisible
	) = 0;

	virtual HRESULT add_LostFocus(
		HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*), // ICoreWebView2FocusChangedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_LostFocus(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT MoveFocus(
		COREWEBVIEW2_MOVE_FOCUS_REASON reason
	) = 0;

	virtual HRESULT add_MoveFocusRequested(
		HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2MoveFocusRequestedEventArgs*), // ICoreWebView2MoveFocusRequestedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_MoveFocusRequested(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT NotifyParentWindowPositionChanged(void) = 0;

	virtual HRESULT get_ParentWindow(
		HWND* parentWindow
	) = 0;

	virtual HRESULT put_ParentWindow(
		HWND parentWindow
	) = 0;

	virtual HRESULT SetBoundsAndZoomFactor(
		RECT bounds,
		double zoomFactor
	) = 0;

	virtual HRESULT get_ZoomFactor(
		double* zoomFactor
	) = 0;

	virtual HRESULT put_ZoomFactor(
		double zoomFactor
	) = 0;

	virtual HRESULT add_ZoomFactorChanged(
		HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*), // ICoreWebView2ZoomFactorChangedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_ZoomFactorChanged(
		EventRegistrationToken token
	) = 0;

	/*
	* ICoreWebView2Controller2
	*/

	virtual HRESULT get_DefaultBackgroundColor(
		COREWEBVIEW2_COLOR* backgroundColor
	) = 0;

	virtual HRESULT put_DefaultBackgroundColor(
		COREWEBVIEW2_COLOR backgroundColor
	) = 0;

	/*
	* ICoreWebView2Controller3
	*/

	virtual HRESULT add_RasterizationScaleChanged(
		HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*), // ICoreWebView2RasterizationScaleChangedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_RasterizationScaleChanged(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT get_BoundsMode(
		COREWEBVIEW2_BOUNDS_MODE* boundsMode
	) = 0;

	virtual HRESULT put_BoundsMode(
		COREWEBVIEW2_BOUNDS_MODE boundsMode
	) = 0;

	virtual HRESULT get_RasterizationScale(
		double* scale
	) = 0;

	virtual HRESULT put_RasterizationScale(
		double scale
	) = 0;

	virtual HRESULT get_ShouldDetectMonitorScaleChanges(
		BOOL* value
	) = 0;

	virtual HRESULT put_ShouldDetectMonitorScaleChanges(
		BOOL value
	) = 0;

	/*
	* ICoreWebView2Controller4
	*/

	virtual HRESULT get_AllowExternalDrop(
		BOOL* value
	) = 0;

	virtual HRESULT put_AllowExternalDrop(
		BOOL value
	) = 0;

	/**
	* ICoreWebView2
	*/

	/* Development */

	virtual HRESULT CallDevToolsProtocolMethod(
		LPCWSTR methodName,
		LPCWSTR parametersAsJson,
		HRESULT(*callback)(HRESULT, LPCWSTR)// ICoreWebView2CallDevToolsProtocolMethodCompletedHandler* handler
	) = 0;

	virtual HRESULT GetDevToolsProtocolEventReceiver(
		LPCWSTR eventName,
		ICoreWebView2DevToolsProtocolEventReceiver** receiver
	) = 0;

	virtual HRESULT OpenDevToolsWindow(void) = 0;

	/* Document */

	virtual HRESULT add_DocumentTitleChanged(
		HRESULT(*callback)(ICoreWebView2*, IUnknown*), // ICoreWebView2DocumentTitleChangedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_DocumentTitleChanged(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT get_DocumentTitle(
		LPWSTR* title
	) = 0;

	/* History */

	virtual HRESULT add_HistoryChanged(
		HRESULT(*callback)(ICoreWebView2*, IUnknown*), //ICoreWebView2HistoryChangedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_HistoryChanged(
		EventRegistrationToken token
	) = 0;

	/* Message */

	virtual HRESULT PostWebMessageAsJson(
		LPCWSTR webMessageAsJson
	) = 0;

	virtual HRESULT PostWebMessageAsString(
		LPCWSTR webMessageAsString
	) = 0;

	virtual HRESULT add_WebMessageReceived(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebMessageReceivedEventArgs*), // ICoreWebView2WebMessageReceivedEventHandler* handler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_WebMessageReceived(
		EventRegistrationToken token
	) = 0;

	/* Navigation */

	virtual HRESULT Navigate(
		LPCWSTR uri
	) = 0;

	virtual HRESULT add_NavigationCompleted(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*), // ICoreWebView2NavigationCompletedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_NavigationCompleted(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT add_NavigationStarting(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*), // ICoreWebView2NavigationStartingEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_NavigationStarting(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT NavigateToString(
		LPCWSTR htmlContent
	) = 0;

	virtual HRESULT add_FrameNavigationCompleted(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*), //ICoreWebView2NavigationCompletedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_FrameNavigationCompleted(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT add_FrameNavigationStarting(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*), // ICoreWebView2NavigationStartingEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_FrameNavigationStarting(
		EventRegistrationToken token
	) = 0;

	/* Permission */

	virtual HRESULT add_PermissionRequested(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2PermissionRequestedEventArgs*), // ICoreWebView2PermissionRequestedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_PermissionRequested(
		EventRegistrationToken token
	) = 0;

	/* Script */

	virtual HRESULT add_ScriptDialogOpening(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ScriptDialogOpeningEventArgs*), // ICoreWebView2ScriptDialogOpeningEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_ScriptDialogOpening(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT AddScriptToExecuteOnDocumentCreated(
		LPCWSTR javaScript,
		HRESULT(*callback)(HRESULT, LPCWSTR) // ICoreWebView2AddScriptToExecuteOnDocumentCreatedCompletedHandler* handler
	) = 0;

	virtual HRESULT RemoveScriptToExecuteOnDocumentCreated(
		LPCWSTR id
	) = 0;

	virtual HRESULT ExecuteScript(
		LPCWSTR javaScript,
		HRESULT(*callback)(HRESULT, LPCWSTR) // ICoreWebView2ExecuteScriptCompletedHandler* handler
	) = 0;

	virtual HRESULT AddHostObjectToScript(
		LPCWSTR name,
		VARIANT* object
	) = 0;

	virtual HRESULT RemoveHostObjectFromScript(
		LPCWSTR name
	) = 0;

	/* Source */

	virtual HRESULT get_Source(
		LPWSTR* uri
	) = 0;

	virtual HRESULT add_SourceChanged(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2SourceChangedEventArgs*), // ICoreWebView2SourceChangedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_SourceChanged(
		EventRegistrationToken token
	) = 0;

	/* Operation */

	virtual HRESULT Reload(void) = 0;

	virtual HRESULT get_CanGoBack(
		BOOL* canGoBack
	) = 0;

	virtual HRESULT get_CanGoForward(
		BOOL* canGoForward
	) = 0;

	virtual HRESULT GoBack(void) = 0;

	virtual HRESULT GoForward(void) = 0;

	virtual HRESULT Stop(void) = 0;

	/* Other */

	virtual HRESULT add_ContentLoading(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ContentLoadingEventArgs*), // ICoreWebView2ContentLoadingEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_ContentLoading(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT add_ProcessFailed(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ProcessFailedEventArgs*), // ICoreWebView2ProcessFailedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_ProcessFailed(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT get_Settings(
		// ICoreWebView2Settings** settings
	) = 0;

	virtual HRESULT CapturePreview(
		COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT imageFormat,
		IStream* imageStream,
		HRESULT(*callback)(HRESULT errorCode)// ICoreWebView2CapturePreviewCompletedHandler* handler
	) = 0;

	virtual HRESULT get_BrowserProcessId(
		UINT32* value
	) = 0;

	virtual HRESULT add_NewWindowRequested(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NewWindowRequestedEventArgs*), // ICoreWebView2NewWindowRequestedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_NewWindowRequested(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT add_ContainsFullScreenElementChanged(
		HRESULT(*callback)(ICoreWebView2*, IUnknown*), // ICoreWebView2ContainsFullScreenElementChangedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_ContainsFullScreenElementChanged(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT get_ContainsFullScreenElement(
		BOOL* containsFullScreenElement
	) = 0;

	virtual HRESULT add_WebResourceRequested(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceRequestedEventArgs*), // ICoreWebView2WebResourceRequestedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_WebResourceRequested(
		EventRegistrationToken token
	) = 0;

	virtual HRESULT AddWebResourceRequestedFilter(
		const LPCWSTR uri,
		const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
	) = 0;

	virtual HRESULT RemoveWebResourceRequestedFilter(
		const LPCWSTR uri,
		const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
	) = 0;

	virtual HRESULT add_WindowCloseRequested(
		HRESULT(*callback)(ICoreWebView2*, IUnknown*), // ICoreWebView2WindowCloseRequestedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT remove_WindowCloseRequested(
		EventRegistrationToken token
	) = 0;

	/**
	* ICoreWebView2_2
	*/

	virtual HRESULT add_DOMContentLoaded(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2DOMContentLoadedEventArgs*), // ICoreWebView2DOMContentLoadedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;

	virtual HRESULT add_WebResourceResponseReceived(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceResponseReceivedEventArgs*), // ICoreWebView2WebResourceResponseReceivedEventHandler* eventHandler,
		EventRegistrationToken* token
	) = 0;
	virtual HRESULT get_CookieManager(ICoreWebView2CookieManager** cookieManager) = 0;
	virtual HRESULT get_Environment(ICoreWebView2Environment** environment) = 0;
	virtual HRESULT NavigateWithWebResourceRequest(ICoreWebView2WebResourceRequest* request) = 0;
	virtual HRESULT remove_DOMContentLoaded(EventRegistrationToken token) = 0;
	virtual HRESULT remove_WebResourceResponseReceived(EventRegistrationToken token) = 0;

	/**
	* ICoreWebView2_3
	*/

	virtual HRESULT SetVirtualHostNameToFolderMapping(
		LPCWSTR hostName,
		LPCWSTR folderPath,
		COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND accessKind
	) = 0;

	virtual HRESULT ClearVirtualHostNameToFolderMapping(LPCWSTR hostName) = 0;

	virtual HRESULT get_IsSuspended(BOOL* isSuspended) = 0;

	virtual HRESULT TrySuspend(
		HRESULT(*callback)(HRESULT errorCode, BOOL isSuccessful) // ICoreWebView2TrySuspendCompletedHandler* handler,
	) = 0;

	virtual HRESULT Resume() = 0;
};

#ifndef _WINDOWS
#include <wil/com.h>
#include <wrl.h>

using namespace Microsoft::WRL;

#define CHECK(p) if (!p) { return E_POINTER; }
void Log(const WCHAR* message);
void CopyString(wchar_t const* source, rsize_t* size, LPWSTR target);


class WC : public WebView2Connector {
protected:
	wil::com_ptr<ICoreWebView2> webview;
	wil::com_ptr<ICoreWebView2_2> webview2;
	wil::com_ptr<ICoreWebView2_3> webview3;
	ICoreWebView2Environment* env;
	wil::com_ptr<ICoreWebView2Settings> settings1;
	wil::com_ptr<ICoreWebView2Settings2> settings2;
	wil::com_ptr<ICoreWebView2Settings3> settings3;
	wil::com_ptr<ICoreWebView2Settings4> settings4;
	wil::com_ptr<ICoreWebView2Settings5> settings5;
	wil::com_ptr<ICoreWebView2Settings6> settings6;
	wil::com_ptr<ICoreWebView2Settings7> settings7;
	wil::com_ptr<ICoreWebView2Settings8> settings8;
	wil::com_ptr<ICoreWebView2Settings9> settings9;
	wil::com_ptr<ICoreWebView2Controller> controller1;
	wil::com_ptr<ICoreWebView2Controller2> controller2;
	wil::com_ptr<ICoreWebView2Controller3> controller3;
	wil::com_ptr<ICoreWebView2Controller4> controller4;

public:
	virtual ~WC() {
		Log(__FUNCTIONW__ L"\n");
		this->Close();
	}

	virtual WebView2Connector* setWebView2Environment(ICoreWebView2Environment* env);
	virtual WebView2Connector* initSettings();
	virtual WebView2Connector* initControllers(ICoreWebView2Controller* controller);
	virtual HRESULT CreateCoreWebView2Controller(HWND hWnd, HRESULT(*callback)(HRESULT, ICoreWebView2Controller*));

	/**
	* ICoreWebView2Settings
	*/

	virtual HRESULT get_IsScriptEnabled(BOOL* isScriptEnabled);
	virtual HRESULT put_IsScriptEnabled(BOOL isScriptEnabled);
	virtual HRESULT get_IsWebMessageEnabled(BOOL* isWebMessageEnabled);
	virtual HRESULT put_IsWebMessageEnabled(BOOL isWebMessageEnabled);
	virtual HRESULT get_AreDefaultScriptDialogsEnabled(BOOL* areDefaultScriptDialogsEnabled);
	virtual HRESULT put_AreDefaultScriptDialogsEnabled(BOOL areDefaultScriptDialogsEnabled);
	virtual HRESULT get_IsStatusBarEnabled(BOOL* isStatusBarEnabled);
	virtual HRESULT put_IsStatusBarEnabled(BOOL isStatusBarEnabled);
	virtual HRESULT get_AreDevToolsEnabled(BOOL* areDevToolsEnabled);
	virtual HRESULT put_AreDevToolsEnabled(BOOL areDevToolsEnabled);
	virtual HRESULT get_AreDefaultContextMenusEnabled(BOOL* enabled);
	virtual HRESULT put_AreDefaultContextMenusEnabled(BOOL enabled);
	virtual HRESULT get_AreHostObjectsAllowed(BOOL* allowed);
	virtual HRESULT put_AreHostObjectsAllowed(BOOL allowed);
	virtual HRESULT get_IsZoomControlEnabled(BOOL* enabled);
	virtual HRESULT put_IsZoomControlEnabled(BOOL enabled);
	virtual HRESULT get_IsBuiltInErrorPageEnabled(BOOL* enabled);
	virtual HRESULT put_IsBuiltInErrorPageEnabled(BOOL enabled);

	/**
	* ICoreWebView2Settings2
	*/

	virtual HRESULT get_UserAgent(LPWSTR userAgent, rsize_t* size);
	virtual HRESULT put_UserAgent(LPCWSTR userAgent);

	/**
	* ICoreWebView2Settings3
	*/

	virtual HRESULT get_AreBrowserAcceleratorKeysEnabled(BOOL* areBrowserAcceleratorKeysEnabled);
	virtual HRESULT put_AreBrowserAcceleratorKeysEnabled(BOOL areBrowserAcceleratorKeysEnabled);

	/**
	* ICoreWebView2Settings4
	*/

	virtual HRESULT get_IsPasswordAutosaveEnabled(BOOL* value);
	virtual HRESULT put_IsPasswordAutosaveEnabled(BOOL value);
	virtual HRESULT get_IsGeneralAutofillEnabled(BOOL* value);
	virtual HRESULT put_IsGeneralAutofillEnabled(BOOL value);

	/**
	* ICoreWebView2Settings5
	*/

	virtual HRESULT get_IsPinchZoomEnabled(BOOL* enabled);
	virtual HRESULT put_IsPinchZoomEnabled(BOOL enabled);

	/**
	* ICoreWebView2Settings6
	*/

	virtual HRESULT get_IsSwipeNavigationEnabled(BOOL* enabled);
	virtual HRESULT put_IsSwipeNavigationEnabled(BOOL enabled);

	/**
	* ICoreWebView2Settings7
	*/

	virtual HRESULT get_HiddenPdfToolbarItems(COREWEBVIEW2_PDF_TOOLBAR_ITEMS* value);
	virtual HRESULT put_HiddenPdfToolbarItems(COREWEBVIEW2_PDF_TOOLBAR_ITEMS value);

	/**
	* ICoreWebView2Settings8
	*/

	virtual HRESULT get_IsReputationCheckingRequired(BOOL* value);
	virtual HRESULT put_IsReputationCheckingRequired(BOOL value);

	/**
	* ICoreWebView2Settings9
	*/

	virtual HRESULT get_IsNonClientRegionSupportEnabled(BOOL* value);
	virtual HRESULT put_IsNonClientRegionSupportEnabled(BOOL value);

	/*
	* ICoreWebView2Controller
	*/

	virtual HRESULT add_AcceleratorKeyPressed(
		HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2AcceleratorKeyPressedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_AcceleratorKeyPressed(EventRegistrationToken token);
	virtual HRESULT get_Bounds(RECT* bounds);
	virtual HRESULT put_Bounds(RECT bounds);
	virtual HRESULT Close(void);
	virtual HRESULT get_CoreWebView2();
	virtual HRESULT add_GotFocus(
		HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_GotFocus(EventRegistrationToken token);
	virtual HRESULT get_IsVisible(BOOL* isVisible);
	virtual HRESULT put_IsVisible(BOOL isVisible);
	virtual HRESULT add_LostFocus(
		HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_LostFocus(EventRegistrationToken token);
	virtual HRESULT MoveFocus(COREWEBVIEW2_MOVE_FOCUS_REASON reason);
	virtual HRESULT add_MoveFocusRequested(
		HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2MoveFocusRequestedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_MoveFocusRequested(EventRegistrationToken token);
	virtual HRESULT NotifyParentWindowPositionChanged(void);
	virtual HRESULT get_ParentWindow(HWND* parentWindow);
	virtual HRESULT put_ParentWindow(HWND parentWindow);
	virtual HRESULT SetBoundsAndZoomFactor(RECT bounds, double zoomFactor);
	virtual HRESULT get_ZoomFactor(double* zoomFactor);
	virtual HRESULT put_ZoomFactor(double zoomFactor);
	virtual HRESULT add_ZoomFactorChanged(
		HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_ZoomFactorChanged(EventRegistrationToken token);

	/*
	* ICoreWebView2Controller2
	*/

	virtual HRESULT get_DefaultBackgroundColor(COREWEBVIEW2_COLOR* backgroundColor);
	virtual HRESULT put_DefaultBackgroundColor(COREWEBVIEW2_COLOR backgroundColor);

	/*
	* ICoreWebView2Controller3
	*/

	virtual HRESULT add_RasterizationScaleChanged(
		HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_RasterizationScaleChanged(EventRegistrationToken token);
	virtual HRESULT get_BoundsMode(COREWEBVIEW2_BOUNDS_MODE* boundsMode);
	virtual HRESULT put_BoundsMode(COREWEBVIEW2_BOUNDS_MODE boundsMode);
	virtual HRESULT get_RasterizationScale(double* scale);
	virtual HRESULT put_RasterizationScale(double scale);
	virtual HRESULT get_ShouldDetectMonitorScaleChanges(BOOL* value);
	virtual HRESULT put_ShouldDetectMonitorScaleChanges(BOOL value);

	/*
	* ICoreWebView2Controller4
	*/

	virtual HRESULT get_AllowExternalDrop(BOOL* value);
	virtual HRESULT put_AllowExternalDrop(BOOL value);

	/**
	* ICoreWebView2
	*/

	/* Development */

	virtual HRESULT CallDevToolsProtocolMethod(
		LPCWSTR methodName,
		LPCWSTR parametersAsJson,
		HRESULT(*callback)(HRESULT, LPCWSTR)
	);
	virtual HRESULT GetDevToolsProtocolEventReceiver(
		LPCWSTR eventName,
		ICoreWebView2DevToolsProtocolEventReceiver** receiver
	);
	virtual HRESULT OpenDevToolsWindow(void);

	/* Document */

	virtual HRESULT add_DocumentTitleChanged(
		HRESULT(*callback)(ICoreWebView2*, IUnknown*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_DocumentTitleChanged(EventRegistrationToken token);
	virtual HRESULT get_DocumentTitle(LPWSTR* title);

	/* History */

	virtual HRESULT add_HistoryChanged(
		HRESULT(*callback)(ICoreWebView2*, IUnknown*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_HistoryChanged(EventRegistrationToken token);

	/* Message */

	virtual HRESULT PostWebMessageAsJson(LPCWSTR webMessageAsJson);
	virtual HRESULT PostWebMessageAsString(LPCWSTR webMessageAsString);
	virtual HRESULT add_WebMessageReceived(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebMessageReceivedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_WebMessageReceived(EventRegistrationToken token);

	/* Navigation */

	virtual HRESULT Navigate(LPCWSTR uri);
	virtual HRESULT add_NavigationCompleted(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_NavigationCompleted(EventRegistrationToken token);
	virtual HRESULT add_NavigationStarting(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_NavigationStarting(EventRegistrationToken token);
	virtual HRESULT NavigateToString(LPCWSTR htmlContent);
	virtual HRESULT add_FrameNavigationCompleted(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_FrameNavigationCompleted(
		EventRegistrationToken token
	);
	virtual HRESULT add_FrameNavigationStarting(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_FrameNavigationStarting(EventRegistrationToken token);

	/* Permission */

	virtual HRESULT add_PermissionRequested(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2PermissionRequestedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_PermissionRequested(EventRegistrationToken token);

	/* Script */

	virtual HRESULT add_ScriptDialogOpening(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ScriptDialogOpeningEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_ScriptDialogOpening(EventRegistrationToken token);
	virtual HRESULT AddScriptToExecuteOnDocumentCreated(LPCWSTR javaScript, HRESULT(*callback)(HRESULT, LPCWSTR));
	virtual HRESULT RemoveScriptToExecuteOnDocumentCreated(LPCWSTR id);
	virtual HRESULT ExecuteScript(LPCWSTR javaScript, HRESULT(*callback)(HRESULT, LPCWSTR));
	virtual HRESULT AddHostObjectToScript(LPCWSTR name, VARIANT* object);
	virtual HRESULT RemoveHostObjectFromScript(LPCWSTR name);

	/* Source */

	virtual HRESULT get_Source(LPWSTR* uri);
	virtual HRESULT add_SourceChanged(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2SourceChangedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_SourceChanged(EventRegistrationToken token);

	/* Operation */

	virtual HRESULT Reload(void);
	virtual HRESULT get_CanGoBack(BOOL* canGoBack);
	virtual HRESULT get_CanGoForward(BOOL* canGoForward);
	virtual HRESULT GoBack(void);
	virtual HRESULT GoForward(void);
	virtual HRESULT Stop(void);

	/* Other */

	virtual HRESULT add_ContentLoading(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ContentLoadingEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_ContentLoading(EventRegistrationToken token);
	virtual HRESULT add_ProcessFailed(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ProcessFailedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_ProcessFailed(EventRegistrationToken token);
	virtual HRESULT get_Settings();
	virtual HRESULT CapturePreview(
		COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT imageFormat,
		IStream* imageStream,
		HRESULT(*callback)(HRESULT errorCode)
	);
	virtual HRESULT get_BrowserProcessId(UINT32* value);
	virtual HRESULT add_NewWindowRequested(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NewWindowRequestedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_NewWindowRequested(EventRegistrationToken token);
	virtual HRESULT add_ContainsFullScreenElementChanged(
		HRESULT(*callback)(ICoreWebView2*, IUnknown*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_ContainsFullScreenElementChanged(EventRegistrationToken token);
	virtual HRESULT get_ContainsFullScreenElement(BOOL* containsFullScreenElement);
	virtual HRESULT add_WebResourceRequested(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceRequestedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_WebResourceRequested(EventRegistrationToken token);
	virtual HRESULT AddWebResourceRequestedFilter(
		const LPCWSTR uri,
		const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
	);
	virtual HRESULT RemoveWebResourceRequestedFilter(
		const LPCWSTR uri,
		const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
	);
	virtual HRESULT add_WindowCloseRequested(
		HRESULT(*callback)(ICoreWebView2*, IUnknown*),
		EventRegistrationToken* token
	);
	virtual HRESULT remove_WindowCloseRequested(EventRegistrationToken token);

	/**
	* ICoreWebView2_2
	*/

	virtual HRESULT add_DOMContentLoaded(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2DOMContentLoadedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT add_WebResourceResponseReceived(
		HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceResponseReceivedEventArgs*),
		EventRegistrationToken* token
	);
	virtual HRESULT get_CookieManager(ICoreWebView2CookieManager** cookieManager);
	virtual HRESULT get_Environment(ICoreWebView2Environment** environment);
	virtual HRESULT NavigateWithWebResourceRequest(ICoreWebView2WebResourceRequest* request);
	virtual HRESULT remove_DOMContentLoaded(EventRegistrationToken token);
	virtual HRESULT remove_WebResourceResponseReceived(EventRegistrationToken token);

	/**
	* ICoreWebView2_3
	*/

	virtual HRESULT SetVirtualHostNameToFolderMapping(
		LPCWSTR hostName,
		LPCWSTR folderPath,
		COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND accessKind
	);
	virtual HRESULT ClearVirtualHostNameToFolderMapping(LPCWSTR hostName);
	virtual HRESULT get_IsSuspended(BOOL* isSuspended);
	virtual HRESULT TrySuspend(
		HRESULT(*callback)(HRESULT errorCode, BOOL isSuccessful)
	);
	virtual HRESULT Resume();
};

#endif
