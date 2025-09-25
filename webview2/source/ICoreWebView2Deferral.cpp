#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/*
* ICoreWebView2Deferral
*/

EXPORT HRESULT Deferral_Complete(ICoreWebView2Deferral * deferral) {
	return deferral->Complete();
}

#endif
