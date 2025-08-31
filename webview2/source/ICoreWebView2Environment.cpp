#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2Environment
*/

EXPORT HRESULT CreateCoreWebView2Controller(
	Environments* environments,
	HWND hWnd,
	HRESULT(*callback)(HRESULT, ICoreWebView2Controller*),
	Controllers* controllers
) {
	Log(__FUNCTIONW__ L"\n");
	return environments->env1->CreateCoreWebView2Controller(
		hWnd,
		Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
			[callback, controllers](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				wprintf(L"ICoreWebView2CreateCoreWebView2ControllerCompletedHandler:%x\n", result);
				controllers->controller1 = controller;
				InitControllers(controllers);

				return callback(result, controller);
			}
		).Get()
	);
}

EXPORT HRESULT CreateWebResourceResponse(
	Environments* environments,
	IStream* content,
	int statusCode,
	LPCWSTR reasonPhrase,
	LPCWSTR headers,
	ICoreWebView2WebResourceResponse** response
) {
	Log(__FUNCTIONW__ L"\n");
	return environments->env1->CreateWebResourceResponse(
		content,
		statusCode,
		reasonPhrase,
		headers,
		response
	);
}

#endif
