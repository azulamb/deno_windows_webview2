#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2_2
*/

EXPORT HRESULT WebView2_add_DOMContentLoaded(
	WebView2* webview2,
	HRESULT(*callback)(ICoreWebView2* sender, ICoreWebView2DOMContentLoadedEventArgs* args),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview2);
	return webview2->webview2->add_DOMContentLoaded(
		Callback<ICoreWebView2DOMContentLoadedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2DOMContentLoadedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT WebView2_add_WebResourceResponseReceived(
	WebView2* webview2,
	HRESULT(*callback)(ICoreWebView2* sender, ICoreWebView2WebResourceResponseReceivedEventArgs* args),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview2);
	return webview2->webview2->add_WebResourceResponseReceived(
		Callback<ICoreWebView2WebResourceResponseReceivedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2WebResourceResponseReceivedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT WebView2_get_CookieManager(
	WebView2* webview2,
	ICoreWebView2CookieManager** cookieManager
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview2);
	return webview2->webview2->get_CookieManager(cookieManager);
}

EXPORT HRESULT WebView2_get_Environment(
	WebView2* webview2,
	ICoreWebView2Environment** environment
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview2);
	return webview2->webview2->get_Environment(environment);
}

EXPORT HRESULT WebView2_NavigateWithWebResourceRequest(
	WebView2* webview2,
	ICoreWebView2WebResourceRequest* request
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview2);
	return webview2->webview2->NavigateWithWebResourceRequest(request);
}

EXPORT HRESULT WebView2_remove_DOMContentLoaded(
	WebView2* webview2,
	const EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview2);
	return webview2->webview2->remove_DOMContentLoaded(*token);
}

EXPORT HRESULT WebView2_remove_WebResourceResponseReceived(
	WebView2* webview2,
	const EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview2);
	return webview2->webview2->remove_WebResourceResponseReceived(*token);
}

#endif
