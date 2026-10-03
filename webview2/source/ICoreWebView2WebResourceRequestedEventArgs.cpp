#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2WebResourceRequestedEventArgs
*/

EXPORT HRESULT WebResourceRequestedEventArgs_get_Request(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	ICoreWebView2WebResourceRequest** request
) {
	return args->get_Request(request);
}

EXPORT HRESULT WebResourceRequestedEventArgs_get_ResourceContext(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	COREWEBVIEW2_WEB_RESOURCE_CONTEXT* context
) {
	return args->get_ResourceContext(context);
}

EXPORT HRESULT WebResourceRequestedEventArgs_get_Response(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	ICoreWebView2WebResourceResponse** response
) {
	return args->get_Response(response);
}

EXPORT HRESULT WebResourceRequestedEventArgs_GetDeferral(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	ICoreWebView2Deferral** deferral
) {
	return args->GetDeferral(deferral);
}

EXPORT HRESULT WebResourceRequestedEventArgs_put_Response(
	ICoreWebView2WebResourceRequestedEventArgs* args,
	ICoreWebView2WebResourceResponse* response
) {
	try {
		HRESULT result = args->put_Response(response);
		return result;
	}
	catch (...) {
		printf("err");
	}
	return E_FAIL;
}

#endif
