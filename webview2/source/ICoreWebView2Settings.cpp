#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"


/**
* ICoreWebView2Settings
*/

EXPORT HRESULT Settings_get_IsScriptEnabled(Settings* settings, BOOL* isScriptEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsScriptEnabled(isScriptEnabled);
}

EXPORT HRESULT Settings_put_IsScriptEnabled(Settings* settings, BOOL isScriptEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsScriptEnabled(isScriptEnabled);
}

EXPORT HRESULT Settings_get_IsWebMessageEnabled(Settings* settings, BOOL* isWebMessageEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsWebMessageEnabled(isWebMessageEnabled);
}

EXPORT HRESULT Settings_put_IsWebMessageEnabled(Settings* settings, BOOL isWebMessageEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsWebMessageEnabled(isWebMessageEnabled);
}

EXPORT HRESULT Settings_get_AreDefaultScriptDialogsEnabled(Settings* settings, BOOL* areDefaultScriptDialogsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_AreDefaultScriptDialogsEnabled(areDefaultScriptDialogsEnabled);
}

EXPORT HRESULT Settings_put_AreDefaultScriptDialogsEnabled(Settings* settings, BOOL areDefaultScriptDialogsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_AreDefaultScriptDialogsEnabled(areDefaultScriptDialogsEnabled);
}

EXPORT HRESULT Settings_get_IsStatusBarEnabled(Settings* settings, BOOL* isStatusBarEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsStatusBarEnabled(isStatusBarEnabled);
}

EXPORT HRESULT Settings_put_IsStatusBarEnabled(Settings* settings, BOOL isStatusBarEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsStatusBarEnabled(isStatusBarEnabled);
}

EXPORT HRESULT Settings_get_AreDevToolsEnabled(Settings* settings, BOOL* areDevToolsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_AreDevToolsEnabled(areDevToolsEnabled);
}

EXPORT HRESULT Settings_put_AreDevToolsEnabled(Settings* settings, BOOL areDevToolsEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_AreDevToolsEnabled(areDevToolsEnabled);
}

EXPORT HRESULT Settings_get_AreDefaultContextMenusEnabled(Settings* settings, BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_AreDefaultContextMenusEnabled(enabled);
}

EXPORT HRESULT Settings_put_AreDefaultContextMenusEnabled(Settings* settings, BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_AreDefaultContextMenusEnabled(enabled);
}

EXPORT HRESULT Settings_get_AreHostObjectsAllowed(Settings* settings, BOOL* allowed) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_AreHostObjectsAllowed(allowed);
}

EXPORT HRESULT Settings_put_AreHostObjectsAllowed(Settings* settings, BOOL allowed) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_AreHostObjectsAllowed(allowed);
}

EXPORT HRESULT Settings_get_IsZoomControlEnabled(Settings* settings, BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsZoomControlEnabled(enabled);
}

EXPORT HRESULT Settings_put_IsZoomControlEnabled(Settings* settings, BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsZoomControlEnabled(enabled);
}

EXPORT HRESULT Settings_get_IsBuiltInErrorPageEnabled(Settings* settings, BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->get_IsBuiltInErrorPageEnabled(enabled);
}

EXPORT HRESULT Settings_put_IsBuiltInErrorPageEnabled(Settings* settings, BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings1);
	return settings->settings1->put_IsBuiltInErrorPageEnabled(enabled);
}

/**
* ICoreWebView2Settings2
*/

EXPORT HRESULT Settings_get_UserAgent(Settings* settings, LPWSTR userAgent, rsize_t* size) {
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

EXPORT HRESULT Settings_put_UserAgent(Settings* settings, LPCWSTR userAgent) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings2);
	return settings->settings2->put_UserAgent(userAgent);
}

/**
* ICoreWebView2Settings3
*/

EXPORT HRESULT Settings_get_AreBrowserAcceleratorKeysEnabled(Settings* settings, BOOL* areBrowserAcceleratorKeysEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings3);
	return settings->settings3->get_AreBrowserAcceleratorKeysEnabled(areBrowserAcceleratorKeysEnabled);
}

EXPORT HRESULT Settings_put_AreBrowserAcceleratorKeysEnabled(Settings* settings, BOOL areBrowserAcceleratorKeysEnabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings3);
	return settings->settings3->put_AreBrowserAcceleratorKeysEnabled(areBrowserAcceleratorKeysEnabled);
}

/**
* ICoreWebView2Settings4
*/

EXPORT HRESULT Settings_get_IsPasswordAutosaveEnabled(Settings* settings, BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings4);
	return settings->settings4->get_IsPasswordAutosaveEnabled(value);
}

EXPORT HRESULT Settings_put_IsPasswordAutosaveEnabled(Settings* settings, BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings4);
	return settings->settings4->put_IsPasswordAutosaveEnabled(value);
}

EXPORT HRESULT Settings_get_IsGeneralAutofillEnabled(Settings* settings, BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings4);
	return settings->settings4->get_IsGeneralAutofillEnabled(value);
}

EXPORT HRESULT Settings_put_IsGeneralAutofillEnabled(Settings* settings, BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings4);
	return settings->settings4->put_IsGeneralAutofillEnabled(value);
}

/**
* ICoreWebView2Settings5
*/

EXPORT HRESULT Settings_get_IsPinchZoomEnabled(Settings* settings, /* [retval][out] */ BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings5);
	return settings->settings5->get_IsPinchZoomEnabled(enabled);
}

EXPORT HRESULT Settings_put_IsPinchZoomEnabled(Settings* settings, /* [in] */ BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings5);
	return settings->settings5->put_IsPinchZoomEnabled(enabled);
}

/**
* ICoreWebView2Settings6
*/

EXPORT HRESULT Settings_get_IsSwipeNavigationEnabled(Settings* settings, /* [retval][out] */ BOOL* enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings6);
	return settings->settings6->get_IsSwipeNavigationEnabled(enabled);
}

EXPORT HRESULT Settings_put_IsSwipeNavigationEnabled(Settings* settings, /* [in] */ BOOL enabled) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings6);
	return settings->settings6->put_IsSwipeNavigationEnabled(enabled);
}

/**
* ICoreWebView2Settings7
*/

EXPORT HRESULT Settings_get_HiddenPdfToolbarItems(Settings* settings, COREWEBVIEW2_PDF_TOOLBAR_ITEMS* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings7);
	return settings->settings7->get_HiddenPdfToolbarItems(value);
}

EXPORT HRESULT Settings_put_HiddenPdfToolbarItems(Settings* settings, COREWEBVIEW2_PDF_TOOLBAR_ITEMS value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings7);
	return settings->settings7->put_HiddenPdfToolbarItems(value);
}

/**
* ICoreWebView2Settings8
*/

EXPORT HRESULT Settings_get_IsReputationCheckingRequired(Settings* settings, BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings8);
	return settings->settings8->get_IsReputationCheckingRequired(value);
}

EXPORT HRESULT Settings_put_IsReputationCheckingRequired(Settings* settings, BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings8);
	return settings->settings8->put_IsReputationCheckingRequired(value);
}

/**
* ICoreWebView2Settings9
*/

EXPORT HRESULT Settings_get_IsNonClientRegionSupportEnabled(Settings* settings, BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings9);
	return settings->settings9->get_IsNonClientRegionSupportEnabled(value);
}

EXPORT HRESULT Settings_put_IsNonClientRegionSupportEnabled(Settings* settings, BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(settings->settings9);
	return settings->settings9->put_IsNonClientRegionSupportEnabled(value);
}

#endif
