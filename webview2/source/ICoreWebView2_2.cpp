#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2_2
*/

HRESULT WC::add_DOMContentLoaded(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2DOMContentLoadedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview2);
	return this->webview2->add_DOMContentLoaded(
		Callback<ICoreWebView2DOMContentLoadedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2DOMContentLoadedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_DOMContentLoaded(
	WebView2Connector* webview2,
	HRESULT(*callback)(ICoreWebView2* sender, ICoreWebView2DOMContentLoadedEventArgs* args),
	EventRegistrationToken* token
) {
	return webview2->add_DOMContentLoaded(callback, token);
}

HRESULT WC::add_WebResourceResponseReceived(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceResponseReceivedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview2);
	return this->webview2->add_WebResourceResponseReceived(
		Callback<ICoreWebView2WebResourceResponseReceivedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2WebResourceResponseReceivedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_WebResourceResponseReceived(
	WebView2Connector* webview2,
	HRESULT(*callback)(ICoreWebView2* sender, ICoreWebView2WebResourceResponseReceivedEventArgs* args),
	EventRegistrationToken* token
) {
	return webview2->add_WebResourceResponseReceived(callback, token);
}

HRESULT WC::get_CookieManager(ICoreWebView2CookieManager** cookieManager) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview2);
	return this->webview2->get_CookieManager(cookieManager);
}
EXPORT HRESULT get_CookieManager(
	WebView2Connector* webview2,
	ICoreWebView2CookieManager** cookieManager
) {
	return webview2->get_CookieManager(cookieManager);
}

HRESULT WC::get_Environment(ICoreWebView2Environment** environment) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview2);
	return this->webview2->get_Environment(environment);
}
EXPORT HRESULT get_Environment(
	WebView2Connector* webview2,
	ICoreWebView2Environment** environment
) {
	return webview2->get_Environment(environment);
}

HRESULT WC::NavigateWithWebResourceRequest(ICoreWebView2WebResourceRequest* request) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview2);
	return this->webview2->NavigateWithWebResourceRequest(request);
}
EXPORT HRESULT NavigateWithWebResourceRequest(
	WebView2Connector* webview2,
	ICoreWebView2WebResourceRequest* request
) {
	return webview2->NavigateWithWebResourceRequest(request);
}

HRESULT WC::remove_DOMContentLoaded(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview2);
	return this->webview2->remove_DOMContentLoaded(token);
}
EXPORT HRESULT remove_DOMContentLoaded(
	WebView2Connector* webview2,
	EventRegistrationToken token
) {
	return webview2->remove_DOMContentLoaded(token);
}

HRESULT WC::remove_WebResourceResponseReceived(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview2);
	return this->webview2->remove_WebResourceResponseReceived(token);
}
EXPORT HRESULT remove_WebResourceResponseReceived(
	WebView2Connector* webview2,
	EventRegistrationToken token
) {
	return webview2->remove_WebResourceResponseReceived(token);
}

#endif
