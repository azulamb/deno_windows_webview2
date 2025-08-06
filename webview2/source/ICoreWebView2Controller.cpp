#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/*
* ICoreWebView2Controller
*/

HRESULT WC::add_AcceleratorKeyPressed(
	HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2AcceleratorKeyPressedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->add_AcceleratorKeyPressed(
		Callback<ICoreWebView2AcceleratorKeyPressedEventHandler>(
			[callback](ICoreWebView2Controller* sender, ICoreWebView2AcceleratorKeyPressedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_AcceleratorKeyPressed(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2AcceleratorKeyPressedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_AcceleratorKeyPressed(callback, token);
}

HRESULT WC::remove_AcceleratorKeyPressed(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->remove_AcceleratorKeyPressed(token);
}
EXPORT HRESULT remove_AcceleratorKeyPressed(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_AcceleratorKeyPressed(token);
}

HRESULT WC::get_Bounds(
	RECT* bounds
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->get_Bounds(bounds);
}
EXPORT HRESULT get_Bounds(
	WebView2Connector* webview2,
	/* [retval][out] */ RECT* bounds
) {
	return webview2->get_Bounds(bounds);
}


HRESULT WC::put_Bounds(RECT bounds) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->put_Bounds(bounds);
}
EXPORT HRESULT put_Bounds(
	WebView2Connector* webview2,
	/* [in] */ RECT bounds
) {
	return webview2->put_Bounds(bounds);
}

HRESULT WC::Close(void) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->Close();
}
EXPORT HRESULT Close(WebView2Connector* webview2) {
	return webview2->Close();
}

HRESULT WC::get_CoreWebView2() {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	HRESULT result = this->controller1->get_CoreWebView2(&this->webview);

	this->webview2 = this->webview.try_query<ICoreWebView2_2>();
	this->webview3 = this->webview.try_query<ICoreWebView2_3>();

	return result;
}
EXPORT HRESULT get_CoreWebView2(WebView2Connector* webview2) {
	return webview2->get_CoreWebView2();
}

HRESULT WC::add_GotFocus(
	HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->add_GotFocus(
		Callback<ICoreWebView2FocusChangedEventHandler>(
			[callback](ICoreWebView2Controller* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_GotFocus(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_GotFocus(callback, token);
}

HRESULT WC::remove_GotFocus(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->remove_GotFocus(token);
}
EXPORT HRESULT remove_GotFocus(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_GotFocus(token);
}

HRESULT WC::get_IsVisible(
	BOOL* isVisible
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->get_IsVisible(isVisible);
}
EXPORT HRESULT get_IsVisible(
	WebView2Connector* webview2,
	/* [retval][out] */ BOOL* isVisible
) {
	return webview2->get_IsVisible(isVisible);
}

HRESULT WC::put_IsVisible(
	BOOL isVisible
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->put_IsVisible(isVisible);
}
EXPORT HRESULT put_IsVisible(
	WebView2Connector* webview2,
	/* [in] */ BOOL isVisible
) {
	return webview2->put_IsVisible(isVisible);
}

HRESULT WC::add_LostFocus(
	HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->add_LostFocus(
		Callback<ICoreWebView2FocusChangedEventHandler>(
			[callback](ICoreWebView2Controller* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_LostFocus(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_LostFocus(callback, token);
}


HRESULT WC::remove_LostFocus(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->remove_LostFocus(token);
}
EXPORT HRESULT remove_LostFocus(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_LostFocus(token);
}

HRESULT WC::MoveFocus(
	COREWEBVIEW2_MOVE_FOCUS_REASON reason
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->MoveFocus(reason);
}
EXPORT HRESULT MoveFocus(
	WebView2Connector* webview2,
	/* [in] */ COREWEBVIEW2_MOVE_FOCUS_REASON reason
) {
	return webview2->MoveFocus(reason);
}

HRESULT WC::add_MoveFocusRequested(
	HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2MoveFocusRequestedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->add_MoveFocusRequested(
		Callback<ICoreWebView2MoveFocusRequestedEventHandler>(
			[callback](ICoreWebView2Controller* sender, ICoreWebView2MoveFocusRequestedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_MoveFocusRequested(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2MoveFocusRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_MoveFocusRequested(callback, token);
}

HRESULT WC::remove_MoveFocusRequested(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->remove_MoveFocusRequested(token);
}
EXPORT HRESULT remove_MoveFocusRequested(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_MoveFocusRequested(token);
}

HRESULT WC::NotifyParentWindowPositionChanged(void) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->NotifyParentWindowPositionChanged();
}
EXPORT HRESULT NotifyParentWindowPositionChanged(WebView2Connector* webview2) {
	return webview2->NotifyParentWindowPositionChanged();
}

HRESULT WC::get_ParentWindow(
	HWND* parentWindow
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->get_ParentWindow(parentWindow);
}
EXPORT HRESULT get_ParentWindow(
	WebView2Connector* webview2,
	/* [retval][out] */ HWND* parentWindow
) {
	return webview2->get_ParentWindow(parentWindow);
}

HRESULT WC::put_ParentWindow(
	HWND parentWindow
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->put_ParentWindow(parentWindow);
}
EXPORT HRESULT put_ParentWindow(
	WebView2Connector* webview2,
	/* [in] */ HWND parentWindow
) {
	return webview2->put_ParentWindow(parentWindow);
}

HRESULT WC::SetBoundsAndZoomFactor(
	RECT bounds,
	double zoomFactor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->SetBoundsAndZoomFactor(bounds, zoomFactor);
}
EXPORT HRESULT SetBoundsAndZoomFactor(
	WebView2Connector* webview2,
	/* [in] */ RECT bounds,
	/* [in] */ double zoomFactor
) {
	return webview2->SetBoundsAndZoomFactor(bounds, zoomFactor);
}

HRESULT WC::get_ZoomFactor(
	double* zoomFactor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->get_ZoomFactor(zoomFactor);
}
EXPORT HRESULT get_ZoomFactor(
	WebView2Connector* webview2,
	/* [retval][out] */ double* zoomFactor
) {
	return webview2->get_ZoomFactor(zoomFactor);
}

HRESULT WC::put_ZoomFactor(
	double zoomFactor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->put_ZoomFactor(zoomFactor);
}
EXPORT HRESULT put_ZoomFactor(
	WebView2Connector* webview2,
	/* [in] */ double zoomFactor
) {
	return webview2->put_ZoomFactor(zoomFactor);
}

HRESULT WC::add_ZoomFactorChanged(
	HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->add_ZoomFactorChanged(
		Callback<ICoreWebView2ZoomFactorChangedEventHandler>(
			[callback](ICoreWebView2Controller* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_ZoomFactorChanged(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_ZoomFactorChanged(callback, token);
}

HRESULT WC::remove_ZoomFactorChanged(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller1);
	return this->controller1->remove_ZoomFactorChanged(token);
}
EXPORT HRESULT remove_ZoomFactorChanged(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_ZoomFactorChanged(token);
}

/*
* ICoreWebView2Controller2
*/

HRESULT WC::get_DefaultBackgroundColor(
	COREWEBVIEW2_COLOR* backgroundColor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller2);
	return this->controller2->get_DefaultBackgroundColor(backgroundColor);
}
EXPORT HRESULT get_DefaultBackgroundColor(
	WebView2Connector* webview2,
	/* [retval][out] */ COREWEBVIEW2_COLOR* backgroundColor
) {
	return webview2->get_DefaultBackgroundColor(backgroundColor);
}

HRESULT WC::put_DefaultBackgroundColor(
	COREWEBVIEW2_COLOR backgroundColor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller2);
	return this->controller2->put_DefaultBackgroundColor(backgroundColor);
}
EXPORT HRESULT put_DefaultBackgroundColor(
	WebView2Connector* webview2,
	/* [in] */ COREWEBVIEW2_COLOR backgroundColor
) {
	return webview2->put_DefaultBackgroundColor(backgroundColor);
}

/*
* ICoreWebView2Controller3
*/

HRESULT WC::add_RasterizationScaleChanged(
	HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller3);
	return this->controller3->add_RasterizationScaleChanged(
		Callback<ICoreWebView2RasterizationScaleChangedEventHandler>(
			[callback](ICoreWebView2Controller* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_RasterizationScaleChanged(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_RasterizationScaleChanged(callback, token);
}

HRESULT WC::remove_RasterizationScaleChanged(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller3);
	return this->controller3->remove_RasterizationScaleChanged(token);
}
EXPORT HRESULT remove_RasterizationScaleChanged(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_RasterizationScaleChanged(token);
}


HRESULT WC::get_BoundsMode(COREWEBVIEW2_BOUNDS_MODE* boundsMode) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller3);
	return this->controller3->get_BoundsMode(boundsMode);
}
EXPORT HRESULT get_BoundsMode(
	WebView2Connector* webview2,
	/* [retval][out] */ COREWEBVIEW2_BOUNDS_MODE* boundsMode
) {
	return webview2->get_BoundsMode(boundsMode);
}

HRESULT WC::put_BoundsMode(COREWEBVIEW2_BOUNDS_MODE boundsMode) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller3);
	return this->controller3->put_BoundsMode(boundsMode);
}
EXPORT HRESULT put_BoundsMode(
	WebView2Connector* webview2,
	/* [in] */ COREWEBVIEW2_BOUNDS_MODE boundsMode
) {
	return webview2->put_BoundsMode(boundsMode);
}

HRESULT WC::get_RasterizationScale(double* scale) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller3);
	return this->controller3->get_RasterizationScale(scale);
}
EXPORT HRESULT get_RasterizationScale(
	WebView2Connector* webview2,
	/* [retval][out] */ double* scale
) {
	return webview2->get_RasterizationScale(scale);
}

HRESULT WC::put_RasterizationScale(double scale) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller3);
	return this->controller3->put_RasterizationScale(scale);
}
EXPORT HRESULT put_RasterizationScale(
	WebView2Connector* webview2,
	/* [in] */ double scale
) {
	return webview2->put_RasterizationScale(scale);
}

HRESULT WC::get_ShouldDetectMonitorScaleChanges(BOOL* value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller3);
	return this->controller3->get_ShouldDetectMonitorScaleChanges(value);
}
EXPORT HRESULT get_ShouldDetectMonitorScaleChanges(
	WebView2Connector* webview2,
	/* [retval][out] */ BOOL* value
) {
	return webview2->get_ShouldDetectMonitorScaleChanges(value);
}


HRESULT WC::put_ShouldDetectMonitorScaleChanges(
	BOOL value
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller3);
	return this->controller3->put_ShouldDetectMonitorScaleChanges(value);
}
EXPORT HRESULT put_ShouldDetectMonitorScaleChanges(
	WebView2Connector* webview2,
	/* [in] */ BOOL value
) {
	return webview2->put_ShouldDetectMonitorScaleChanges(value);
}

/*
* ICoreWebView2Controller4
*/

HRESULT WC::get_AllowExternalDrop(
	BOOL* value
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller4);
	return this->controller4->get_AllowExternalDrop(value);
}
EXPORT HRESULT get_AllowExternalDrop(
	WebView2Connector* webview2,
	/* [retval][out] */ BOOL* value
) {
	return webview2->get_AllowExternalDrop(value);
}

HRESULT WC::put_AllowExternalDrop(BOOL value) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(this->controller4);
	return this->controller4->put_AllowExternalDrop(value);
}
EXPORT HRESULT put_AllowExternalDrop(
	WebView2Connector* webview2,
	/* [in] */ BOOL value
) {
	return webview2->put_AllowExternalDrop(value);
}

#endif
