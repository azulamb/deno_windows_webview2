#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/*
* ICoreWebView2Controller
*/

EXPORT HRESULT add_AcceleratorKeyPressed(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2AcceleratorKeyPressedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->add_AcceleratorKeyPressed(
		Callback<ICoreWebView2AcceleratorKeyPressedEventHandler>(
			[callback](ICoreWebView2Controller* sender, ICoreWebView2AcceleratorKeyPressedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_AcceleratorKeyPressed(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->remove_AcceleratorKeyPressed(token);
}

EXPORT HRESULT get_Bounds(
	Controllers* controllers,
	/* [retval][out] */ RECT* bounds
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->get_Bounds(bounds);
}

EXPORT HRESULT put_Bounds(
	Controllers* controllers,
	/* [in] */ RECT bounds
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->put_Bounds(bounds);
}

EXPORT HRESULT Close(Controllers* controllers) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->Close();
}

EXPORT HRESULT get_CoreWebView2(Controllers* controllers, WebView2* webview2) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	HRESULT result = controllers->controller1->get_CoreWebView2(&webview2->webview1);
	InitWebView2(webview2);

	return result;
}

EXPORT HRESULT add_GotFocus(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->add_GotFocus(
		Callback<ICoreWebView2FocusChangedEventHandler>(
			[callback](ICoreWebView2Controller* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_GotFocus(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->remove_GotFocus(token);
}

EXPORT HRESULT get_IsVisible(
	Controllers* controllers,
	/* [retval][out] */ BOOL* isVisible
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->get_IsVisible(isVisible);
}

EXPORT HRESULT put_IsVisible(
	Controllers* controllers,
	/* [in] */ BOOL isVisible
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->put_IsVisible(isVisible);
}

EXPORT HRESULT add_LostFocus(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->add_LostFocus(
		Callback<ICoreWebView2FocusChangedEventHandler>(
			[callback](ICoreWebView2Controller* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_LostFocus(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->remove_LostFocus(token);
}

EXPORT HRESULT MoveFocus(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_MOVE_FOCUS_REASON reason
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->MoveFocus(reason);
}

EXPORT HRESULT add_MoveFocusRequested(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, ICoreWebView2MoveFocusRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->add_MoveFocusRequested(
		Callback<ICoreWebView2MoveFocusRequestedEventHandler>(
			[callback](ICoreWebView2Controller* sender, ICoreWebView2MoveFocusRequestedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_MoveFocusRequested(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->remove_MoveFocusRequested(token);
}

EXPORT HRESULT NotifyParentWindowPositionChanged(Controllers* controllers) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->NotifyParentWindowPositionChanged();
}

EXPORT HRESULT get_ParentWindow(
	Controllers* controllers,
	/* [retval][out] */ HWND* parentWindow
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->get_ParentWindow(parentWindow);
}

EXPORT HRESULT put_ParentWindow(
	Controllers* controllers,
	/* [in] */ HWND parentWindow
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->put_ParentWindow(parentWindow);
}

EXPORT HRESULT SetBoundsAndZoomFactor(
	Controllers* controllers,
	/* [in] */ RECT bounds,
	/* [in] */ double zoomFactor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->SetBoundsAndZoomFactor(bounds, zoomFactor);
}

EXPORT HRESULT get_ZoomFactor(
	Controllers* controllers,
	/* [retval][out] */ double* zoomFactor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->get_ZoomFactor(zoomFactor);
}

EXPORT HRESULT put_ZoomFactor(
	Controllers* controllers,
	/* [in] */ double zoomFactor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->put_ZoomFactor(zoomFactor);
}

EXPORT HRESULT add_ZoomFactorChanged(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->add_ZoomFactorChanged(
		Callback<ICoreWebView2ZoomFactorChangedEventHandler>(
			[callback](ICoreWebView2Controller* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_ZoomFactorChanged(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller1);
	return controllers->controller1->remove_ZoomFactorChanged(token);
}

/*
* ICoreWebView2Controller2
*/

EXPORT HRESULT get_DefaultBackgroundColor(
	Controllers* controllers,
	/* [retval][out] */ COREWEBVIEW2_COLOR* backgroundColor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller2);
	return controllers->controller2->get_DefaultBackgroundColor(backgroundColor);
}

EXPORT HRESULT put_DefaultBackgroundColor(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_COLOR backgroundColor
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller2);
	return controllers->controller2->put_DefaultBackgroundColor(backgroundColor);
}

/*
* ICoreWebView2Controller3
*/

EXPORT HRESULT add_RasterizationScaleChanged(
	Controllers* controllers,
	/* [in] */ HRESULT(*callback)(ICoreWebView2Controller*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller3);
	return controllers->controller3->add_RasterizationScaleChanged(
		Callback<ICoreWebView2RasterizationScaleChangedEventHandler>(
			[callback](ICoreWebView2Controller* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_RasterizationScaleChanged(
	Controllers* controllers,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller3);
	return controllers->controller3->remove_RasterizationScaleChanged(token);
}


EXPORT HRESULT get_BoundsMode(
	Controllers* controllers,
	/* [retval][out] */ COREWEBVIEW2_BOUNDS_MODE* boundsMode
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller3);
	return controllers->controller3->get_BoundsMode(boundsMode);
}

EXPORT HRESULT put_BoundsMode(
	Controllers* controllers,
	/* [in] */ COREWEBVIEW2_BOUNDS_MODE boundsMode
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller3);
	return controllers->controller3->put_BoundsMode(boundsMode);
}

EXPORT HRESULT get_RasterizationScale(
	Controllers* controllers,
	/* [retval][out] */ double* scale
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller3);
	return controllers->controller3->get_RasterizationScale(scale);
}

EXPORT HRESULT put_RasterizationScale(
	Controllers* controllers,
	/* [in] */ double scale
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller3);
	return controllers->controller3->put_RasterizationScale(scale);
}

EXPORT HRESULT get_ShouldDetectMonitorScaleChanges(
	Controllers* controllers,
	/* [retval][out] */ BOOL* value
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller3);
	return controllers->controller3->get_ShouldDetectMonitorScaleChanges(value);
}

EXPORT HRESULT put_ShouldDetectMonitorScaleChanges(
	Controllers* controllers,
	/* [in] */ BOOL value
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller3);
	return controllers->controller3->put_ShouldDetectMonitorScaleChanges(value);
}

/*
* ICoreWebView2Controller4
*/

EXPORT HRESULT get_AllowExternalDrop(
	Controllers* controllers,
	/* [retval][out] */ BOOL* value
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller4);
	return controllers->controller4->get_AllowExternalDrop(value);
}

EXPORT HRESULT put_AllowExternalDrop(
	Controllers* controllers,
	/* [in] */ BOOL value
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(controllers->controller4);
	return controllers->controller4->put_AllowExternalDrop(value);
}

#endif
