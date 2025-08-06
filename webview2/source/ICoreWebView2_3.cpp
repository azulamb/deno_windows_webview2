#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2_3
*/

HRESULT WC::SetVirtualHostNameToFolderMapping(
	LPCWSTR hostName,
	LPCWSTR folderPath,
	COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND accessKind
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview3);
	return this->webview3->SetVirtualHostNameToFolderMapping(
		hostName,
		folderPath,
		accessKind
	);
}
EXPORT HRESULT SetVirtualHostNameToFolderMapping(
	WebView2Connector* webview2,
	LPCWSTR hostName,
	LPCWSTR folderPath,
	COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND accessKind
) {
	return webview2->SetVirtualHostNameToFolderMapping(hostName, folderPath, accessKind);
}


HRESULT WC::ClearVirtualHostNameToFolderMapping(LPCWSTR hostName) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview3);
	return this->webview3->ClearVirtualHostNameToFolderMapping(hostName);
}
EXPORT HRESULT ClearVirtualHostNameToFolderMapping(
	WebView2Connector* webview2,
	LPCWSTR hostName
) {
	return webview2->ClearVirtualHostNameToFolderMapping(hostName);
}

HRESULT WC::get_IsSuspended(BOOL* isSuspended) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview3);
	return this->webview3->get_IsSuspended(isSuspended);
}
EXPORT HRESULT get_IsSuspended(WebView2Connector* webview2, BOOL* isSuspended) {
	return webview2->get_IsSuspended(isSuspended);
}

HRESULT WC::TrySuspend(
	HRESULT(*callback)(HRESULT errorCode, BOOL isSuccessful)
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview3);
	return this->webview3->TrySuspend(
		Callback<ICoreWebView2TrySuspendCompletedHandler>(
			[callback](HRESULT errorCode, BOOL isSuccessful) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(errorCode, isSuccessful);
			}
		).Get()
	);
}
EXPORT HRESULT Resume(WebView2Connector* webview2) {
	return webview2->Resume();
}

HRESULT WC::Resume() {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->webview3);
	return this->webview3->Resume();
}
EXPORT HRESULT TrySuspend(WebView2Connector* webview2, HRESULT(*callback)(HRESULT errorCode, BOOL isSuccessful)) {
	return webview2->TrySuspend(callback);
}

#endif
