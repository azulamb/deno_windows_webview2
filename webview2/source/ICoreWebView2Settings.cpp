#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"


/**
* ICoreWebView2Settings
*/

HRESULT WC::get_IsScriptEnabled(BOOL* isScriptEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_IsScriptEnabled(isScriptEnabled);
}
EXPORT HRESULT get_IsScriptEnabled(WebView2Connector* webview2, BOOL* isScriptEnabled) {
	return webview2->get_IsScriptEnabled(isScriptEnabled);
}

HRESULT WC::put_IsScriptEnabled(BOOL isScriptEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_IsScriptEnabled(isScriptEnabled);
}
EXPORT HRESULT put_IsScriptEnabled(WebView2Connector* webview2, BOOL isScriptEnabled) {
	return webview2->put_IsScriptEnabled(isScriptEnabled);
}
HRESULT WC::get_IsWebMessageEnabled(BOOL* isWebMessageEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_IsWebMessageEnabled(isWebMessageEnabled);
}
EXPORT HRESULT get_IsWebMessageEnabled(WebView2Connector* webview2, BOOL* isWebMessageEnabled) {
	return webview2->get_IsWebMessageEnabled(isWebMessageEnabled);
}

HRESULT WC::put_IsWebMessageEnabled(BOOL isWebMessageEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_IsWebMessageEnabled(isWebMessageEnabled);
}
EXPORT HRESULT put_IsWebMessageEnabled(WebView2Connector* webview2, BOOL isWebMessageEnabled) {
	return webview2->put_IsWebMessageEnabled(isWebMessageEnabled);
}

HRESULT WC::get_AreDefaultScriptDialogsEnabled(BOOL* areDefaultScriptDialogsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_AreDefaultScriptDialogsEnabled(areDefaultScriptDialogsEnabled);
}
EXPORT HRESULT get_AreDefaultScriptDialogsEnabled(WebView2Connector* webview2, BOOL* areDefaultScriptDialogsEnabled) {
	return webview2->get_AreDefaultScriptDialogsEnabled(areDefaultScriptDialogsEnabled);
}

HRESULT WC::put_AreDefaultScriptDialogsEnabled(BOOL areDefaultScriptDialogsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_AreDefaultScriptDialogsEnabled(areDefaultScriptDialogsEnabled);
}
EXPORT HRESULT put_AreDefaultScriptDialogsEnabled(WebView2Connector* webview2, BOOL areDefaultScriptDialogsEnabled) {
	return webview2->put_AreDefaultScriptDialogsEnabled(areDefaultScriptDialogsEnabled);
}

HRESULT WC::get_IsStatusBarEnabled(BOOL* isStatusBarEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_IsStatusBarEnabled(isStatusBarEnabled);
}
EXPORT HRESULT get_IsStatusBarEnabled(WebView2Connector* webview2, BOOL* isStatusBarEnabled) {
	return webview2->get_IsStatusBarEnabled(isStatusBarEnabled);
}

HRESULT WC::put_IsStatusBarEnabled(BOOL isStatusBarEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_IsStatusBarEnabled(isStatusBarEnabled);
}
EXPORT HRESULT put_IsStatusBarEnabled(WebView2Connector* webview2, BOOL isStatusBarEnabled) {
	return webview2->put_IsStatusBarEnabled(isStatusBarEnabled);
}

HRESULT WC::get_AreDevToolsEnabled(BOOL* areDevToolsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_AreDevToolsEnabled(areDevToolsEnabled);
}
EXPORT HRESULT get_AreDevToolsEnabled(WebView2Connector* webview2, BOOL* areDevToolsEnabled) {
	return webview2->get_AreDevToolsEnabled(areDevToolsEnabled);
}

HRESULT WC::put_AreDevToolsEnabled(BOOL areDevToolsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_AreDevToolsEnabled(areDevToolsEnabled);
}
EXPORT HRESULT put_AreDevToolsEnabled(WebView2Connector* webview2, BOOL areDevToolsEnabled) {
	return webview2->put_AreDevToolsEnabled(areDevToolsEnabled);
}

HRESULT WC::get_AreDefaultContextMenusEnabled(BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_AreDefaultContextMenusEnabled(enabled);
}
EXPORT HRESULT get_AreDefaultContextMenusEnabled(WebView2Connector* webview2, BOOL* enabled) {
	return webview2->get_AreDefaultContextMenusEnabled(enabled);
}

HRESULT WC::put_AreDefaultContextMenusEnabled(BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_AreDefaultContextMenusEnabled(enabled);
}
EXPORT HRESULT put_AreDefaultContextMenusEnabled(WebView2Connector* webview2, BOOL enabled) {
	return webview2->put_AreDefaultContextMenusEnabled(enabled);
}

HRESULT WC::get_AreHostObjectsAllowed(BOOL* allowed) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_AreHostObjectsAllowed(allowed);
}
EXPORT HRESULT get_AreHostObjectsAllowed(WebView2Connector* webview2, BOOL* allowed) {
	return webview2->get_AreHostObjectsAllowed(allowed);
}

HRESULT WC::put_AreHostObjectsAllowed(BOOL allowed) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_AreHostObjectsAllowed(allowed);
}
EXPORT HRESULT put_AreHostObjectsAllowed(WebView2Connector* webview2, BOOL allowed) {
	return webview2->put_AreHostObjectsAllowed(allowed);
}

HRESULT WC::get_IsZoomControlEnabled(BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_IsZoomControlEnabled(enabled);
}
EXPORT HRESULT get_IsZoomControlEnabled(WebView2Connector* webview2, BOOL* enabled) {
	return webview2->get_IsZoomControlEnabled(enabled);
}

HRESULT WC::put_IsZoomControlEnabled(BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_IsZoomControlEnabled(enabled);
}
EXPORT HRESULT put_IsZoomControlEnabled(WebView2Connector* webview2, BOOL enabled) {
	return webview2->put_IsZoomControlEnabled(enabled);
}

HRESULT WC::get_IsBuiltInErrorPageEnabled(BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->get_IsBuiltInErrorPageEnabled(enabled);
}
EXPORT HRESULT get_IsBuiltInErrorPageEnabled(WebView2Connector* webview2, BOOL* enabled) {
	return webview2->get_IsBuiltInErrorPageEnabled(enabled);
}

HRESULT WC::put_IsBuiltInErrorPageEnabled(BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings1->put_IsBuiltInErrorPageEnabled(enabled);
}
EXPORT HRESULT put_IsBuiltInErrorPageEnabled(WebView2Connector* webview2, BOOL enabled) {
	return webview2->put_IsBuiltInErrorPageEnabled(enabled);
}

/**
* ICoreWebView2Settings2
*/

HRESULT WC::get_UserAgent(LPWSTR userAgent, rsize_t* size) {
	Log(__FUNCTIONW__ L"\n");
	wil::unique_cotaskmem_string data;
	HRESULT result = this->settings2->get_UserAgent(&data);

	if (FAILED(result)) {
		if (size) {
			*size = 0;
		}
		return result;
	}

	CopyString(data.get(), size, userAgent);

	return result;
}
EXPORT HRESULT get_UserAgent(WebView2Connector* webview2, LPWSTR userAgent, rsize_t* size) {
	return webview2->get_UserAgent(userAgent, size);
}

HRESULT WC::put_UserAgent(LPCWSTR userAgent) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings2->put_UserAgent(userAgent);
}
EXPORT HRESULT put_UserAgent(WebView2Connector* webview2, LPCWSTR userAgent) {
	return webview2->put_UserAgent(userAgent);
}

/**
* ICoreWebView2Settings3
*/

HRESULT WC::get_AreBrowserAcceleratorKeysEnabled(BOOL* areBrowserAcceleratorKeysEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings3->get_AreBrowserAcceleratorKeysEnabled(areBrowserAcceleratorKeysEnabled);
}
EXPORT HRESULT get_AreBrowserAcceleratorKeysEnabled(WebView2Connector* webview2, BOOL* areBrowserAcceleratorKeysEnabled) {
	return webview2->get_AreBrowserAcceleratorKeysEnabled(areBrowserAcceleratorKeysEnabled);
}

HRESULT WC::put_AreBrowserAcceleratorKeysEnabled(BOOL areBrowserAcceleratorKeysEnabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings3->put_AreBrowserAcceleratorKeysEnabled(areBrowserAcceleratorKeysEnabled);
}
EXPORT HRESULT put_AreBrowserAcceleratorKeysEnabled(WebView2Connector* webview2, BOOL areBrowserAcceleratorKeysEnabled) {
	return webview2->put_AreBrowserAcceleratorKeysEnabled(areBrowserAcceleratorKeysEnabled);
}

/**
* ICoreWebView2Settings4
*/

HRESULT WC::get_IsPasswordAutosaveEnabled(BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings4->get_IsPasswordAutosaveEnabled(value);
}
EXPORT HRESULT get_IsPasswordAutosaveEnabled(WebView2Connector* webview2, BOOL* value) {
	return webview2->get_IsPasswordAutosaveEnabled(value);
}

HRESULT WC::put_IsPasswordAutosaveEnabled(BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings4->put_IsPasswordAutosaveEnabled(value);
}
EXPORT HRESULT put_IsPasswordAutosaveEnabled(WebView2Connector* webview2, BOOL value) {
	return webview2->put_IsPasswordAutosaveEnabled(value);
}

HRESULT WC::get_IsGeneralAutofillEnabled(BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings4->get_IsGeneralAutofillEnabled(value);
}
EXPORT HRESULT get_IsGeneralAutofillEnabled(WebView2Connector* webview2, BOOL* value) {
	return webview2->get_IsGeneralAutofillEnabled(value);
}

 HRESULT WC::put_IsGeneralAutofillEnabled(BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings4->put_IsGeneralAutofillEnabled(value);
}
EXPORT HRESULT put_IsGeneralAutofillEnabled(WebView2Connector* webview2, BOOL value) {
	return webview2->put_IsGeneralAutofillEnabled(value);
}

/**
* ICoreWebView2Settings5
*/

HRESULT WC::get_IsPinchZoomEnabled(BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings5->get_IsPinchZoomEnabled(enabled);
}
EXPORT HRESULT get_IsPinchZoomEnabled(WebView2Connector* webview2, /* [retval][out] */ BOOL* enabled) {
	return webview2->get_IsPinchZoomEnabled(enabled);
}

HRESULT WC::put_IsPinchZoomEnabled(BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings5->put_IsPinchZoomEnabled(enabled);
}
EXPORT HRESULT put_IsPinchZoomEnabled(WebView2Connector* webview2, /* [in] */ BOOL enabled) {
	return webview2->put_IsPinchZoomEnabled(enabled);
}

/**
* ICoreWebView2Settings6
*/

HRESULT WC::get_IsSwipeNavigationEnabled(BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings6->get_IsSwipeNavigationEnabled(enabled);
}
EXPORT HRESULT get_IsSwipeNavigationEnabled(WebView2Connector* webview2, /* [retval][out] */ BOOL* enabled) {
	return webview2->get_IsSwipeNavigationEnabled(enabled);
}

HRESULT WC::put_IsSwipeNavigationEnabled(BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings6->put_IsSwipeNavigationEnabled(enabled);
}
EXPORT HRESULT put_IsSwipeNavigationEnabled(WebView2Connector* webview2, /* [in] */ BOOL enabled) {
	return webview2->put_IsSwipeNavigationEnabled(enabled);
}

/**
* ICoreWebView2Settings7
*/

HRESULT WC::get_HiddenPdfToolbarItems(COREWEBVIEW2_PDF_TOOLBAR_ITEMS* value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings7->get_HiddenPdfToolbarItems(value);
}
EXPORT HRESULT get_HiddenPdfToolbarItems(WebView2Connector* webview2, COREWEBVIEW2_PDF_TOOLBAR_ITEMS* value) {
	return webview2->get_HiddenPdfToolbarItems(value);
}

HRESULT WC::put_HiddenPdfToolbarItems(COREWEBVIEW2_PDF_TOOLBAR_ITEMS value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings7->put_HiddenPdfToolbarItems(value);
}
EXPORT HRESULT put_HiddenPdfToolbarItems(WebView2Connector* webview2, COREWEBVIEW2_PDF_TOOLBAR_ITEMS value) {
	return webview2->put_HiddenPdfToolbarItems(value);
}

/**
* ICoreWebView2Settings8
*/

HRESULT WC::get_IsReputationCheckingRequired(BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings8->get_IsReputationCheckingRequired(value);
}
EXPORT HRESULT get_IsReputationCheckingRequired(WebView2Connector* webview2, BOOL* value) {
	return webview2->get_IsReputationCheckingRequired(value);
}

HRESULT WC::put_IsReputationCheckingRequired(BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings8->put_IsReputationCheckingRequired(value);
}
EXPORT HRESULT put_IsReputationCheckingRequired(WebView2Connector* webview2, BOOL value) {
	return webview2->put_IsReputationCheckingRequired(value);
}

/**
* ICoreWebView2Settings9
*/

HRESULT WC::get_IsNonClientRegionSupportEnabled(BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings9->get_IsNonClientRegionSupportEnabled(value);
}
EXPORT HRESULT get_IsNonClientRegionSupportEnabled(WebView2Connector* webview2, BOOL* value) {
	return webview2->get_IsNonClientRegionSupportEnabled(value);
}

HRESULT WC::put_IsNonClientRegionSupportEnabled(BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	return this->settings9->put_IsNonClientRegionSupportEnabled(value);
}
EXPORT HRESULT put_IsNonClientRegionSupportEnabled(WebView2Connector* webview2, BOOL value) {
	return webview2->put_IsNonClientRegionSupportEnabled(value);
}

#endif
