#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2WebResourceResponse
*/

EXPORT HRESULT WebResourceResponse_get_Content(
	ICoreWebView2WebResourceResponse* response,
	IStream** content
) {
	return response->get_Content(content);
}

EXPORT HRESULT WebResourceResponse_get_Headers(
	ICoreWebView2WebResourceResponse* response,
	ICoreWebView2HttpResponseHeaders** headers
) {
	return response->get_Headers(headers);
}

EXPORT HRESULT WebResourceResponse_get_ReasonPhrase(
	ICoreWebView2WebResourceResponse* response,
	LPWSTR reasonPhrase,
	rsize_t* size
) {
	wil::unique_cotaskmem_string data;
	HRESULT result = response->get_ReasonPhrase(&data);

	if (FAILED(result)) {
		if (size) {
			*size = 0;
		}
		return result;
	}

	CopyString(data.get(), size, reasonPhrase);

	return result;
}

EXPORT HRESULT WebResourceResponse_get_StatusCode(
	ICoreWebView2WebResourceResponse* response,
	int* statusCode
) {
	return response->get_StatusCode(statusCode);
}

EXPORT HRESULT WebResourceResponse_put_Content(
	ICoreWebView2WebResourceResponse* response,
	IStream* content
) {
	return response->put_Content(content);
}

EXPORT HRESULT WebResourceResponse_put_ReasonPhrase(
	ICoreWebView2WebResourceResponse* response,
	LPCWSTR reasonPhrase
) {
	return response->put_ReasonPhrase(reasonPhrase);
}

EXPORT HRESULT WebResourceResponse_put_StatusCode(
	ICoreWebView2WebResourceResponse* response,
	int statusCode
) {
	return response->put_StatusCode(statusCode);
}

#endif
