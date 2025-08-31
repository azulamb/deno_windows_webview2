#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2WebResourceRequest
*/

EXPORT HRESULT WebResourceRequest_get_Content(
	ICoreWebView2WebResourceRequest* request,
	IStream** content
) {
	return request->get_Content(content);
}

EXPORT HRESULT WebResourceRequest_get_Headers(
	ICoreWebView2WebResourceRequest* request,
	ICoreWebView2HttpRequestHeaders** headers
) {
	return request->get_Headers(headers);
}

EXPORT HRESULT WebResourceRequest_get_Method(
	ICoreWebView2WebResourceRequest* request,
	LPWSTR method
) {
	wil::unique_cotaskmem_string data;
	HRESULT result = request->get_Method(&data);

	CopyString(data.get(), nullptr, method);

	return result;
}

EXPORT HRESULT WebResourceRequest_get_Uri(
	ICoreWebView2WebResourceRequest* request,
	LPWSTR uri,
	rsize_t* size
) {
	wil::unique_cotaskmem_string data;
	HRESULT result = request->get_Uri(&data);

	if (FAILED(result)) {
		if (size) {
			*size = 0;
		}
		return result;
	}

	CopyString(data.get(), size, uri);

	return result;
}

EXPORT HRESULT WebResourceRequest_put_Content(
	ICoreWebView2WebResourceRequest* request,
	IStream* content
) {
	return request->put_Content(content);
}

EXPORT HRESULT WebResourceRequest_put_Method(
	ICoreWebView2WebResourceRequest* request,
	LPCWSTR method
) {
	return request->put_Method(method);
}

EXPORT HRESULT WebResourceRequest_put_Uri(
	ICoreWebView2WebResourceRequest* request,
	LPCWSTR uri
) {
	return request->put_Uri(uri);
}

#endif
