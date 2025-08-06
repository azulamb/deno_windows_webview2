#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2WebMessageReceivedEventArgs
*/

void copyString(wchar_t const* source, rsize_t* size, LPWSTR target, bool tmp = false) {
	rsize_t wsize = wcslen(source) + 1;

	// TryGetWebMessageAsString get string "XXX
	// Bug ?
	if (tmp && 0 < wsize) {
		++wsize;
	}

	return CopyString(source, size, target);
}

EXPORT HRESULT MessageReceivedEventArgs_get_Source(
	ICoreWebView2WebMessageReceivedEventArgs* args,
	LPWSTR uri,
	rsize_t* size
) {
	wil::unique_cotaskmem_string data;
	HRESULT result = args->get_Source(&data);

	if (FAILED(result)) {
		if (size) {
			*size = 0;
		}
		return result;
	}

	copyString(data.get(), size, uri);

	return result;
}

EXPORT HRESULT MessageReceivedEventArgs_get_WebMessageAsJson(
	ICoreWebView2WebMessageReceivedEventArgs* args,
	LPWSTR webMessageAsJson,
	rsize_t* size
) {
	wil::unique_cotaskmem_string data;
	HRESULT result = args->get_WebMessageAsJson(&data);

	if (FAILED(result)) {
		if (size) {
			*size = 0;
		}
		return result;
	}

	copyString(data.get(), size, webMessageAsJson);

	return result;
}

EXPORT HRESULT MessageReceivedEventArgs_TryGetWebMessageAsString(
	ICoreWebView2WebMessageReceivedEventArgs* args,
	LPWSTR webMessageAsString,
	rsize_t* size
) {
	wil::unique_cotaskmem_string data;
	HRESULT result = args->TryGetWebMessageAsString(&data);

	if (result == E_INVALIDARG) {
		if (size) {
			*size = 0;
		}
		return S_OK;
	}

	copyString(data.get(), size, webMessageAsString, true);

	return result;
}

#endif
