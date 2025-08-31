#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2HttpRequestHeaders
*/

EXPORT HRESULT HttpRequestHeaders_Contains(ICoreWebView2HttpRequestHeaders* headers, LPCWSTR name, BOOL* contains) {
	return headers->Contains(name, contains);
}

EXPORT HRESULT HttpRequestHeaders_GetHeader(
	ICoreWebView2HttpRequestHeaders* headers,
	LPCWSTR name,
	LPWSTR value,
	rsize_t* size
) {
	wil::unique_cotaskmem_string data;
	HRESULT result = headers->GetHeader(name, &data);

	if (FAILED(result)) {
		if (size) {
			*size = 0;
		}
		return result;
	}

	CopyString(data.get(), size, value);

	return result;
}

EXPORT HRESULT HttpRequestHeaders_GetHeaders(
	ICoreWebView2HttpRequestHeaders* headers,
	LPCWSTR name,
	BOOL(*callback)(PWSTR value)
) {
	wil::com_ptr<ICoreWebView2HttpHeadersCollectionIterator> iterator;
	HRESULT result = headers->GetHeaders(name, &iterator);
	if (result != S_OK) {
		return result;
	}

	BOOL hasCurrent = FALSE;
	while (SUCCEEDED(iterator->get_HasCurrentHeader(&hasCurrent)) && hasCurrent)
	{
		wil::unique_cotaskmem_string name;
		wil::unique_cotaskmem_string value;

		HRESULT result = iterator->GetCurrentHeader(&name, &value);
		if (result != S_OK) {
			continue;
		}
		if (callback(value.get())) {
			break;
		}
	}
}

EXPORT HRESULT HttpRequestHeaders_GetIterator(
	ICoreWebView2HttpRequestHeaders* headers,
	BOOL(*callback)(PWSTR name, PWSTR value)
) {
	wil::com_ptr<ICoreWebView2HttpHeadersCollectionIterator> iterator;
	HRESULT result = headers->GetIterator(&iterator);
	if (result != S_OK) {
		return result;
	}

	BOOL hasCurrent = FALSE;
	while (SUCCEEDED(iterator->get_HasCurrentHeader(&hasCurrent)) && hasCurrent)
	{
		wil::unique_cotaskmem_string name;
		wil::unique_cotaskmem_string value;

		HRESULT result = iterator->GetCurrentHeader(&name, &value);
		if (result != S_OK) {
			continue;
		}
		if (callback(name.get(), value.get())) {
			break;
		}
	}
}

EXPORT HRESULT HttpRequestHeaders_RemoveHeader(ICoreWebView2HttpRequestHeaders* headers, LPCWSTR name) {
	return headers->RemoveHeader(name);
}

EXPORT HRESULT HttpRequestHeaders_SetHeader(ICoreWebView2HttpRequestHeaders* headers, LPCWSTR name, LPCWSTR value) {
	return headers->SetHeader(name, value);
}

#endif
