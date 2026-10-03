#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"
#include "../version.h"

EXPORT const char* Global_GetDllVersion() {
	return WEAPN_DLL_VERSION;
}

EXPORT WebView2* WebView2_Create() {
	Log(__FUNCTIONW__ L"\n");
	return new WebView2();
}

EXPORT WebView2* WebView2_Init(WebView2* webview2) {
	webview2->webview2 = webview2->webview1.try_query<ICoreWebView2_2>();
	webview2->webview3 = webview2->webview1.try_query<ICoreWebView2_3>();

	return webview2;
}

EXPORT Environments* Environments_Create() {
	Log(__FUNCTIONW__ L"\n");
	return new Environments();
}

EXPORT Settings* Settings_Create()
{
	Log(__FUNCTIONW__ L"\n");
	return new Settings();
}

EXPORT Settings* Settings_Init(Settings* settings) {
	Log(__FUNCTIONW__ L"\n");
	settings->settings2 = settings->settings1.try_query<ICoreWebView2Settings2>();
	settings->settings3 = settings->settings1.try_query<ICoreWebView2Settings3>();
	settings->settings4 = settings->settings1.try_query<ICoreWebView2Settings4>();
	settings->settings5 = settings->settings1.try_query<ICoreWebView2Settings5>();
	settings->settings6 = settings->settings1.try_query<ICoreWebView2Settings6>();
	settings->settings7 = settings->settings1.try_query<ICoreWebView2Settings7>();
	settings->settings8 = settings->settings1.try_query<ICoreWebView2Settings8>();
	settings->settings9 = settings->settings1.try_query<ICoreWebView2Settings9>();

	return settings;
}

EXPORT Controllers* Controllers_Create() {
	Log(__FUNCTIONW__ L"\n");
	return new Controllers();
}

EXPORT Controllers* Controllers_Init(
	Controllers* controllers
) {
	Log(__FUNCTIONW__ L"\n");
	controllers->controller2 = controllers->controller1.try_query<ICoreWebView2Controller2>();
	controllers->controller3 = controllers->controller1.try_query<ICoreWebView2Controller3>();
	controllers->controller4 = controllers->controller1.try_query<ICoreWebView2Controller4>();

	return controllers;
}

/**
* EventRegistrationToken
*/

EXPORT EventRegistrationToken* EventRegistrationToken_Create() {
	return (EventRegistrationToken*)calloc(1, sizeof(EventRegistrationToken));
}

EXPORT void EventRegistrationToken_Remove(EventRegistrationToken* token) {
	free(token);
}


EXPORT ULONG COM_AddRef(IUnknown* value) { return value ? value->AddRef() : 0; }
EXPORT ULONG COM_Release(IUnknown* value) { return value ? value->Release() : 0; }
EXPORT void WebView2_Destroy(WebView2* value) { delete value; }
EXPORT void Environments_Destroy(Environments* value) { delete value; }
EXPORT void Settings_Destroy(Settings* value) { delete value; }
EXPORT void Controllers_Destroy(Controllers* value) { delete value; }

#endif
