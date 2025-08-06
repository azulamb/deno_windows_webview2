#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2Environment
*/

HRESULT WC::CreateCoreWebView2Controller(HWND hWnd, HRESULT(*callback)(HRESULT, ICoreWebView2Controller*)) {
	Log(__FUNCTIONW__ L"\n");
	return this->env->CreateCoreWebView2Controller(
		hWnd,
		Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
			[callback](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				wprintf(L"ICoreWebView2CreateCoreWebView2ControllerCompletedHandler:%x\n", result);
				return callback(result, controller);
			}
		).Get()
	);
}

EXPORT HRESULT CreateCoreWebView2Controller(
	WebView2Connector* webview2,
	HWND hWnd,
	HRESULT(*callback)(HRESULT, ICoreWebView2Controller*)
) {
	return webview2->CreateCoreWebView2Controller(hWnd, callback);
}

#endif
