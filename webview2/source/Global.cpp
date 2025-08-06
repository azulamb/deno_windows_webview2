#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* Global
*/

EXPORT HRESULT _CreateCoreWebView2Environment(
	WebView2Connector* webview2,
	HRESULT(*callback)(HRESULT, ICoreWebView2Environment*)
) {
	Log(__FUNCTIONW__ L"\n");
	return ::CreateCoreWebView2Environment(
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[callback, webview2](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				webview2->setWebView2Environment(env);
				return callback(result, env);
			}
		).Get()
	);
}

EXPORT HRESULT _CreateCoreWebView2EnvironmentWithOptions(
	WebView2Connector* webview2,
	PCWSTR browserExecutableFolder,
	PCWSTR userDataFolder,
	ICoreWebView2EnvironmentOptions* environmentOptions,
	HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
) {
	Log(__FUNCTIONW__ L"\n");
	return ::CreateCoreWebView2EnvironmentWithOptions(
		browserExecutableFolder,
		browserExecutableFolder,
		environmentOptions,
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[callback, webview2](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				webview2->setWebView2Environment(env);
				return callback(result, env);
			}
		).Get()
	);
}

EXPORT HRESULT _CompareBrowserVersions(
	PCWSTR version1,
	PCWSTR version2,
	int* result
) {
	Log(__FUNCTIONW__ L"\n");
	return ::CompareBrowserVersions(version1, version2, result);
}

// TODO: CreateWebViewEnvironmentWithOptionsInternal

EXPORT HRESULT _GetAvailableCoreWebView2BrowserVersionString(
	PCWSTR browserExecutableFolder,
	LPWSTR* versionInfo
) {
	Log(__FUNCTIONW__ L"\n");
	return ::GetAvailableCoreWebView2BrowserVersionString(browserExecutableFolder, versionInfo);
}

// TODO: GetAvailableCoreWebView2BrowserVersionStringWithOptions

#endif
