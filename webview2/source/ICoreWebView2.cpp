#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2
*/

/* Development */

EXPORT HRESULT CallDevToolsProtocolMethod(
	WebView2* webview2,
	/* [in] */ LPCWSTR methodName,
	/* [in] */ LPCWSTR parametersAsJson,
	/* [in] */ HRESULT(*callback)(/* [in] */ HRESULT, /* [in] */ LPCWSTR)
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->CallDevToolsProtocolMethod(
		methodName,
		parametersAsJson,
		Callback<ICoreWebView2CallDevToolsProtocolMethodCompletedHandler>(
			[callback](HRESULT result, LPCWSTR returnObjectAsJson) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(result, returnObjectAsJson);
			}
		).Get()
	);
}

EXPORT HRESULT GetDevToolsProtocolEventReceiver(
	WebView2* webview2,
	/* [in] */ LPCWSTR eventName,
	/* [retval][out] */ ICoreWebView2DevToolsProtocolEventReceiver** receiver
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->GetDevToolsProtocolEventReceiver(eventName, receiver);
}

EXPORT HRESULT OpenDevToolsWindow(WebView2* webview2) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->OpenDevToolsWindow();
}

/* Document */

EXPORT HRESULT add_DocumentTitleChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(/* [in] */ ICoreWebView2*, /* [in] */ IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_DocumentTitleChanged(
		Callback<ICoreWebView2DocumentTitleChangedEventHandler>(
			[callback](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_DocumentTitleChanged(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_DocumentTitleChanged(token);
}

EXPORT HRESULT get_DocumentTitle(
	WebView2* webview2,
	/* [retval][out] */ LPWSTR* title
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->get_DocumentTitle(title);
}

/* History */

EXPORT HRESULT add_HistoryChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_HistoryChanged(
		Callback<ICoreWebView2HistoryChangedEventHandler>(
			[callback](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_HistoryChanged(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_HistoryChanged(token);
}

/* Message */

EXPORT HRESULT PostWebMessageAsJson(
	WebView2* webview2,
	/* [in] */ LPCWSTR webMessageAsJson
	// TODO: sender. if null, default.
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->PostWebMessageAsJson(webMessageAsJson);
}

EXPORT HRESULT PostWebMessageAsString(
	WebView2* webview2,
	/* [in] */ LPCWSTR webMessageAsString
	// TODO: sender. if null, default.
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->PostWebMessageAsString(webMessageAsString);
}

EXPORT HRESULT add_WebMessageReceived(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebMessageReceivedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_WebMessageReceived(
		Callback<ICoreWebView2WebMessageReceivedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_WebMessageReceived(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_WebMessageReceived(token);
}

/* Navigation */

EXPORT HRESULT Navigate(
	WebView2* webview2,
	/* [in] */ LPCWSTR uri
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->Navigate(uri);
}

EXPORT HRESULT add_NavigationCompleted(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_NavigationCompleted(
		Callback<ICoreWebView2NavigationCompletedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_NavigationCompleted(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_NavigationCompleted(token);
}

EXPORT HRESULT add_NavigationStarting(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_NavigationStarting(
		Callback<ICoreWebView2NavigationStartingEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_NavigationStarting(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_NavigationStarting(token);
}

EXPORT HRESULT NavigateToString(
	WebView2* webview2,
	/* [in] */ LPCWSTR htmlContent
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->NavigateToString(htmlContent);
}

EXPORT HRESULT add_FrameNavigationCompleted(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_FrameNavigationCompleted(
		Callback<ICoreWebView2NavigationCompletedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_FrameNavigationCompleted(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_FrameNavigationCompleted(token);
}

EXPORT HRESULT add_FrameNavigationStarting(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_FrameNavigationStarting(
		Callback<ICoreWebView2NavigationStartingEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_FrameNavigationStarting(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_FrameNavigationStarting(token);
}

/* Permission */

EXPORT HRESULT add_PermissionRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2PermissionRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_PermissionRequested(
		Callback<ICoreWebView2PermissionRequestedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2PermissionRequestedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_PermissionRequested(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_PermissionRequested(token);
}

/* Script */

EXPORT HRESULT add_ScriptDialogOpening(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ScriptDialogOpeningEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_ScriptDialogOpening(
		Callback<ICoreWebView2ScriptDialogOpeningEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2ScriptDialogOpeningEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_ScriptDialogOpening(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_ScriptDialogOpening(token);
}

EXPORT HRESULT AddScriptToExecuteOnDocumentCreated(
	WebView2* webview2,
	/* [in] */ LPCWSTR javaScript,
	/* [in] */ HRESULT(*callback)(HRESULT, LPCWSTR)
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->AddScriptToExecuteOnDocumentCreated(
		javaScript,
		Callback<ICoreWebView2AddScriptToExecuteOnDocumentCreatedCompletedHandler>(
			[callback](HRESULT errorCode, LPCWSTR id) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(errorCode, id);
			}
		).Get()
	);
}

EXPORT HRESULT RemoveScriptToExecuteOnDocumentCreated(
	WebView2* webview2,
	/* [in] */ LPCWSTR id
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->RemoveScriptToExecuteOnDocumentCreated(id);
}

EXPORT HRESULT ExecuteScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR javaScript,
	/* [in] */ HRESULT(*callback)(HRESULT, LPCWSTR)
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->ExecuteScript(
		javaScript,
		Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
			[callback](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(errorCode, resultObjectAsJson);
			}
		).Get()
	);
}

EXPORT HRESULT AddHostObjectToScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR name,
	/* [in] */ VARIANT* object
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->AddHostObjectToScript(name, object);
}

EXPORT HRESULT RemoveHostObjectFromScript(
	WebView2* webview2,
	/* [in] */ LPCWSTR name
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->RemoveHostObjectFromScript(name);
}

/* Source */

EXPORT HRESULT get_Source(
	WebView2* webview2,
	/* [retval][out] */ LPWSTR* uri
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->get_Source(uri);
}

EXPORT HRESULT add_SourceChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2SourceChangedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_SourceChanged(
		Callback<ICoreWebView2SourceChangedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2SourceChangedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_SourceChanged(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_SourceChanged(token);
}

/* Operation */

EXPORT HRESULT Reload(WebView2* webview2) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->Reload();
}

EXPORT HRESULT get_CanGoBack(
	WebView2* webview2,
	/* [retval][out] */ BOOL* canGoBack
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->get_CanGoBack(canGoBack);
}

EXPORT HRESULT get_CanGoForward(
	WebView2* webview2,
	/* [retval][out] */ BOOL* canGoForward
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->get_CanGoForward(canGoForward);
}

EXPORT HRESULT GoBack(WebView2* webview2) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->GoBack();
}

EXPORT HRESULT GoForward(WebView2* webview2) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->GoForward();
}

EXPORT HRESULT Stop(WebView2* webview2) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->Stop();
}

/* Other */

EXPORT HRESULT add_ContentLoading(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ContentLoadingEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_ContentLoading(
		Callback<ICoreWebView2ContentLoadingEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2ContentLoadingEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_ContentLoading(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_ContentLoading(token);
}

EXPORT HRESULT add_ProcessFailed(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ProcessFailedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_ProcessFailed(
		Callback<ICoreWebView2ProcessFailedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2ProcessFailedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_ProcessFailed(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_ProcessFailed(token);
}

EXPORT HRESULT get_Settings(WebView2* webview2, Settings* settings) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	HRESULT result = webview2->webview1->get_Settings(&(settings->settings1));
	InitSettings(settings);

	return result;
}

EXPORT HRESULT CapturePreview(
	WebView2* webview2,
	/* [in] */ COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT imageFormat,
	/* [in] */ IStream* imageStream,
	/* [in] */ HRESULT(*callback)(HRESULT errorCode)
) {
	// TODO: imageStream
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	// TODO: imageStream
	return webview2->webview1->CapturePreview(
		imageFormat,
		imageStream,
		Callback<ICoreWebView2CapturePreviewCompletedHandler>(
			[callback](HRESULT errorCode) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(errorCode);
			}
		).Get()
	);
}

EXPORT HRESULT get_BrowserProcessId(
	WebView2* webview2,
	/* [retval][out] */ UINT32* value
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->get_BrowserProcessId(value);
}

EXPORT HRESULT add_NewWindowRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NewWindowRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_NewWindowRequested(
		Callback<ICoreWebView2NewWindowRequestedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NewWindowRequestedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_NewWindowRequested(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_NewWindowRequested(token);
}

EXPORT HRESULT add_ContainsFullScreenElementChanged(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_ContainsFullScreenElementChanged(
		Callback<ICoreWebView2ContainsFullScreenElementChangedEventHandler>(
			[callback](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_ContainsFullScreenElementChanged(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_ContainsFullScreenElementChanged(token);
}

EXPORT HRESULT get_ContainsFullScreenElement(
	WebView2* webview2,
	/* [retval][out] */ BOOL* containsFullScreenElement
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->get_ContainsFullScreenElement(containsFullScreenElement);
}

EXPORT HRESULT add_WebResourceRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_WebResourceRequested(
		Callback<ICoreWebView2WebResourceRequestedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2WebResourceRequestedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_WebResourceRequested(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_WebResourceRequested(token);
}

EXPORT HRESULT AddWebResourceRequestedFilter(
	WebView2* webview2,
	/* [in] */ const LPCWSTR uri,
	/* [in] */ const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	// TODO: Add arg 3.
	// https://learn.microsoft.com/en-us/dotnet/api/microsoft.web.webview2.core.corewebview2.addwebresourcerequestedfilter?view=webview2-dotnet-1.0.3351.48
	return webview2->webview1->AddWebResourceRequestedFilter(uri, resourceContext);
}

EXPORT HRESULT RemoveWebResourceRequestedFilter(
	WebView2* webview2,
	/* [in] */ const LPCWSTR uri,
	/* [in] */ const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->RemoveWebResourceRequestedFilter(uri, resourceContext);
}

EXPORT HRESULT add_WindowCloseRequested(
	WebView2* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->add_WindowCloseRequested(
		Callback<ICoreWebView2WindowCloseRequestedEventHandler>(
			[callback](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}

EXPORT HRESULT remove_WindowCloseRequested(
	WebView2* webview2,
	/* [in] */ EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	CHECK(webview2->webview1);
	return webview2->webview1->remove_WindowCloseRequested(token);
}

#endif
