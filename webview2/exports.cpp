#ifndef _WINDOWS
#include "source/WebView2.hpp"
#include "./exports.h"

/**
* Original
*/

EXPORT const char* GetDllVersion() {
	return "\\StringFileInfo\\040904b0\\FileVersion";
}

EXPORT WebView2Connector* CreateWebView2Connector(
	ICoreWebView2Environment* env
) {
	Log(__FUNCTIONW__ L"\n");
	if (!env) {
		return new WC();
	}
	return (new WC())->setWebView2Environment(env);
}

EXPORT EventRegistrationToken* CreateEventRegistrationToken() {
	return (EventRegistrationToken*)calloc(1, sizeof(EventRegistrationToken));
}

EXPORT void RemoveEventRegistrationToken(EventRegistrationToken* token) {
	free(token);
}

#endif
