#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* Global
*/

EXPORT HRESULT _CreateCoreWebView2Environment(
	Environments* environments,
	HRESULT(*callback)(HRESULT, ICoreWebView2Environment*)
) {
	Log(__FUNCTIONW__ L"\n");
	return ::CreateCoreWebView2Environment(
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[callback, environments](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				environments->env1 = env;
				return callback(result, env);
			}
		).Get()
	);
}

EXPORT HRESULT _CreateCoreWebView2EnvironmentWithOptions(
	Environments* environments,
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
			[callback, environments](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				environments->env1 = env;
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

EXPORT HRESULT _GetAvailableCoreWebView2BrowserVersionStringWithOptions(
	PCWSTR browserExecutableFolder,
	ICoreWebView2EnvironmentOptions* environmentOptions,
	LPWSTR* versionInfo
) {
	Log(__FUNCTIONW__ L"\n");
	return ::GetAvailableCoreWebView2BrowserVersionStringWithOptions(browserExecutableFolder, environmentOptions, versionInfo);
}

#pragma comment(linker, "/EXPORT:CreateCoreWebView2Environment=_CreateCoreWebView2Environment")
#pragma comment(linker, "/EXPORT:CreateCoreWebView2EnvironmentWithOptions=_CreateCoreWebView2EnvironmentWithOptions")
#pragma comment(linker, "/EXPORT:CompareBrowserVersions=_CompareBrowserVersions")
#pragma comment(linker, "/EXPORT:GetAvailableCoreWebView2BrowserVersionString=_GetAvailableCoreWebView2BrowserVersionString")
#pragma comment(linker, "/EXPORT:GetAvailableCoreWebView2BrowserVersionStringWithOptions=_GetAvailableCoreWebView2BrowserVersionStringWithOptions")

#endif
