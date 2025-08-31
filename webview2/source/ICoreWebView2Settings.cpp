#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"


/**
* ICoreWebView2Settings
*/

EXPORT HRESULT get_IsScriptEnabled(Settings* settings, BOOL* isScriptEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsScriptEnabled(isScriptEnabled);
}

EXPORT HRESULT put_IsScriptEnabled(Settings* settings, BOOL isScriptEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsScriptEnabled(isScriptEnabled);
}

EXPORT HRESULT get_IsWebMessageEnabled(Settings* settings, BOOL* isWebMessageEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsWebMessageEnabled(isWebMessageEnabled);
}

EXPORT HRESULT put_IsWebMessageEnabled(Settings* settings, BOOL isWebMessageEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsWebMessageEnabled(isWebMessageEnabled);
}

EXPORT HRESULT get_AreDefaultScriptDialogsEnabled(Settings* settings, BOOL* areDefaultScriptDialogsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_AreDefaultScriptDialogsEnabled(areDefaultScriptDialogsEnabled);
}

EXPORT HRESULT put_AreDefaultScriptDialogsEnabled(Settings* settings, BOOL areDefaultScriptDialogsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_AreDefaultScriptDialogsEnabled(areDefaultScriptDialogsEnabled);
}

EXPORT HRESULT get_IsStatusBarEnabled(Settings* settings, BOOL* isStatusBarEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsStatusBarEnabled(isStatusBarEnabled);
}

EXPORT HRESULT put_IsStatusBarEnabled(Settings* settings, BOOL isStatusBarEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsStatusBarEnabled(isStatusBarEnabled);
}

EXPORT HRESULT get_AreDevToolsEnabled(Settings* settings, BOOL* areDevToolsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_AreDevToolsEnabled(areDevToolsEnabled);
}

EXPORT HRESULT put_AreDevToolsEnabled(Settings* settings, BOOL areDevToolsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_AreDevToolsEnabled(areDevToolsEnabled);
}

EXPORT HRESULT get_AreDefaultContextMenusEnabled(Settings* settings, BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_AreDefaultContextMenusEnabled(enabled);
}

EXPORT HRESULT put_AreDefaultContextMenusEnabled(Settings* settings, BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_AreDefaultContextMenusEnabled(enabled);
}

EXPORT HRESULT get_AreHostObjectsAllowed(Settings* settings, BOOL* allowed) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_AreHostObjectsAllowed(allowed);
}

EXPORT HRESULT put_AreHostObjectsAllowed(Settings* settings, BOOL allowed) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_AreHostObjectsAllowed(allowed);
}

EXPORT HRESULT get_IsZoomControlEnabled(Settings* settings, BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsZoomControlEnabled(enabled);
}

EXPORT HRESULT put_IsZoomControlEnabled(Settings* settings, BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsZoomControlEnabled(enabled);
}

EXPORT HRESULT get_IsBuiltInErrorPageEnabled(Settings* settings, BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsBuiltInErrorPageEnabled(enabled);
}

EXPORT HRESULT put_IsBuiltInErrorPageEnabled(Settings* settings, BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsBuiltInErrorPageEnabled(enabled);
}

/**
* ICoreWebView2Settings2
*/

EXPORT HRESULT get_UserAgent(Settings* settings, LPWSTR userAgent, rsize_t* size) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings2);
	wil::unique_cotaskmem_string data;
	HRESULT result = settings->settings2->get_UserAgent(&data);

	if (FAILED(result)) {
		if (size) {
			*size = 0;
		}
		return result;
	}

	CopyString(data.get(), size, userAgent);

	return result;
}

EXPORT HRESULT put_UserAgent(Settings* settings, LPCWSTR userAgent) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings2);
	return settings->settings2->put_UserAgent(userAgent);
}

/**
* ICoreWebView2Settings3
*/

EXPORT HRESULT get_AreBrowserAcceleratorKeysEnabled(Settings* settings, BOOL* areBrowserAcceleratorKeysEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings3);
	return settings->settings3->get_AreBrowserAcceleratorKeysEnabled(areBrowserAcceleratorKeysEnabled);
}

EXPORT HRESULT put_AreBrowserAcceleratorKeysEnabled(Settings* settings, BOOL areBrowserAcceleratorKeysEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings3);
	return settings->settings3->put_AreBrowserAcceleratorKeysEnabled(areBrowserAcceleratorKeysEnabled);
}

/**
* ICoreWebView2Settings4
*/

EXPORT HRESULT get_IsPasswordAutosaveEnabled(Settings* settings, BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings4);
	return settings->settings4->get_IsPasswordAutosaveEnabled(value);
}

EXPORT HRESULT put_IsPasswordAutosaveEnabled(Settings* settings, BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings4);
	return settings->settings4->put_IsPasswordAutosaveEnabled(value);
}

EXPORT HRESULT get_IsGeneralAutofillEnabled(Settings* settings, BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings4);
	return settings->settings4->get_IsGeneralAutofillEnabled(value);
}

EXPORT HRESULT put_IsGeneralAutofillEnabled(Settings* settings, BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings4);
	return settings->settings4->put_IsGeneralAutofillEnabled(value);
}

/**
* ICoreWebView2Settings5
*/

EXPORT HRESULT get_IsPinchZoomEnabled(Settings* settings, /* [retval][out] */ BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings5);
	return settings->settings5->get_IsPinchZoomEnabled(enabled);
}

EXPORT HRESULT put_IsPinchZoomEnabled(Settings* settings, /* [in] */ BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings5);
	return settings->settings5->put_IsPinchZoomEnabled(enabled);
}

/**
* ICoreWebView2Settings6
*/

EXPORT HRESULT get_IsSwipeNavigationEnabled(Settings* settings, /* [retval][out] */ BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings6);
	return settings->settings6->get_IsSwipeNavigationEnabled(enabled);
}

EXPORT HRESULT put_IsSwipeNavigationEnabled(Settings* settings, /* [in] */ BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings6);
	return settings->settings6->put_IsSwipeNavigationEnabled(enabled);
}

/**
* ICoreWebView2Settings7
*/

EXPORT HRESULT get_HiddenPdfToolbarItems(Settings* settings, COREWEBVIEW2_PDF_TOOLBAR_ITEMS* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings7);
	return settings->settings7->get_HiddenPdfToolbarItems(value);
}

EXPORT HRESULT put_HiddenPdfToolbarItems(Settings* settings, COREWEBVIEW2_PDF_TOOLBAR_ITEMS value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings7);
	return settings->settings7->put_HiddenPdfToolbarItems(value);
}

/**
* ICoreWebView2Settings8
*/

EXPORT HRESULT get_IsReputationCheckingRequired(Settings* settings, BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings8);
	return settings->settings8->get_IsReputationCheckingRequired(value);
}

EXPORT HRESULT put_IsReputationCheckingRequired(Settings* settings, BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings8);
	return settings->settings8->put_IsReputationCheckingRequired(value);
}

/**
* ICoreWebView2Settings9
*/

EXPORT HRESULT get_IsNonClientRegionSupportEnabled(Settings* settings, BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings9);
	return settings->settings9->get_IsNonClientRegionSupportEnabled(value);
}

EXPORT HRESULT put_IsNonClientRegionSupportEnabled(Settings* settings, BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings9);
	return settings->settings9->put_IsNonClientRegionSupportEnabled(value);
}

#endif
