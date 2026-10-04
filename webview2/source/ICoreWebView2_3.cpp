#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2_3
*/

EXPORT HRESULT WebView2_SetVirtualHostNameToFolderMapping(
	WebView2* webview2,
	LPCWSTR hostName,
	LPCWSTR folderPath,
	COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND accessKind
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview3);
	return webview2->webview3->SetVirtualHostNameToFolderMapping(
		hostName,
		folderPath,
		accessKind
	);
}

EXPORT HRESULT WebView2_ClearVirtualHostNameToFolderMapping(
	WebView2* webview2,
	LPCWSTR hostName
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview3);
	return webview2->webview3->ClearVirtualHostNameToFolderMapping(hostName);
}

EXPORT HRESULT WebView2_get_IsSuspended(WebView2* webview2, BOOL* isSuspended) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview3);
	return webview2->webview3->get_IsSuspended(isSuspended);
}

EXPORT HRESULT WebView2_TrySuspend(WebView2* webview2, HRESULT(*callback)(HRESULT errorCode, BOOL isSuccessful)) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview3);
	return webview2->webview3->TrySuspend(
		Callback<ICoreWebView2TrySuspendCompletedHandler>(
			[callback](HRESULT errorCode, BOOL isSuccessful) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(errorCode, isSuccessful);
			}
		).Get()
	);
}

EXPORT HRESULT WebView2_Resume(WebView2* webview2) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview3);
	return webview2->webview3->Resume();
}

#endif
