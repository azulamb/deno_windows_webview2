#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

/**
* ICoreWebView2
*/

/* Development */

HRESULT WC::CallDevToolsProtocolMethod(
	LPCWSTR methodName,
	LPCWSTR parametersAsJson,
	HRESULT(*callback)(HRESULT, LPCWSTR)
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->CallDevToolsProtocolMethod(
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
EXPORT HRESULT CallDevToolsProtocolMethod(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR methodName,
	/* [in] */ LPCWSTR parametersAsJson,
	/* [in] */ HRESULT(*callback)(/* [in] */ HRESULT, /* [in] */ LPCWSTR)
) {
	return webview2->CallDevToolsProtocolMethod(methodName, parametersAsJson, callback);
}

HRESULT WC::GetDevToolsProtocolEventReceiver(
	LPCWSTR eventName,
	ICoreWebView2DevToolsProtocolEventReceiver** receiver
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->GetDevToolsProtocolEventReceiver(eventName, receiver);
}
EXPORT HRESULT GetDevToolsProtocolEventReceiver(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR eventName,
	/* [retval][out] */ ICoreWebView2DevToolsProtocolEventReceiver** receiver
) {
	return webview2->GetDevToolsProtocolEventReceiver(eventName, receiver);
}

HRESULT WC::OpenDevToolsWindow(void) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->OpenDevToolsWindow();
}
EXPORT HRESULT OpenDevToolsWindow(WebView2Connector* webview2) {
	return webview2->OpenDevToolsWindow();
}

/* Document */

HRESULT WC::add_DocumentTitleChanged(
	HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_DocumentTitleChanged(
		Callback<ICoreWebView2DocumentTitleChangedEventHandler>(
			[callback](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_DocumentTitleChanged(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(/* [in] */ ICoreWebView2*, /* [in] */ IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_DocumentTitleChanged(callback, token);
}

HRESULT WC::remove_DocumentTitleChanged(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_DocumentTitleChanged(token);
}
EXPORT HRESULT remove_DocumentTitleChanged(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_DocumentTitleChanged(token);
}

HRESULT WC::get_DocumentTitle(
	LPWSTR* title
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->get_DocumentTitle(title);
}
EXPORT HRESULT get_DocumentTitle(
	WebView2Connector* webview2,
	/* [retval][out] */ LPWSTR* title
) {
	return webview2->get_DocumentTitle(title);
}

/* History */

HRESULT WC::add_HistoryChanged(
	HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_HistoryChanged(
		Callback<ICoreWebView2HistoryChangedEventHandler>(
			[callback](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_HistoryChanged(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_HistoryChanged(callback, token);
}

HRESULT WC::remove_HistoryChanged(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_HistoryChanged(token);
}
EXPORT HRESULT remove_HistoryChanged(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_HistoryChanged(token);
}

/* Message */

HRESULT WC::PostWebMessageAsJson(LPCWSTR webMessageAsJson) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->PostWebMessageAsJson(webMessageAsJson);
}
EXPORT HRESULT PostWebMessageAsJson(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR webMessageAsJson
	// TODO: sender. if null, default.
) {
	return webview2->PostWebMessageAsJson(webMessageAsJson);
}


HRESULT WC::PostWebMessageAsString(LPCWSTR webMessageAsString) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->PostWebMessageAsString(webMessageAsString);
}
EXPORT HRESULT PostWebMessageAsString(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR webMessageAsString
	// TODO: sender. if null, default.
) {
	return webview2->PostWebMessageAsString(webMessageAsString);
}

HRESULT WC::add_WebMessageReceived(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebMessageReceivedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_WebMessageReceived(
		Callback<ICoreWebView2WebMessageReceivedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_WebMessageReceived(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebMessageReceivedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_WebMessageReceived(callback, token);
}

HRESULT WC::remove_WebMessageReceived(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_WebMessageReceived(token);
}
EXPORT HRESULT remove_WebMessageReceived(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_WebMessageReceived(token);
}

/* Navigation */

HRESULT WC::Navigate(LPCWSTR uri) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->Navigate(uri);
}
EXPORT HRESULT Navigate(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR uri
) {
	return webview2->Navigate(uri);
}

HRESULT WC::add_NavigationCompleted(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_NavigationCompleted(
		Callback<ICoreWebView2NavigationCompletedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_NavigationCompleted(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_NavigationCompleted(callback, token);
}

HRESULT WC::remove_NavigationCompleted(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_NavigationCompleted(token);
}
EXPORT HRESULT remove_NavigationCompleted(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_NavigationCompleted(token);
}

HRESULT WC::add_NavigationStarting(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_NavigationStarting(
		Callback<ICoreWebView2NavigationStartingEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_NavigationStarting(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_NavigationStarting(callback, token);
}

HRESULT WC::remove_NavigationStarting(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_NavigationStarting(token);
}
EXPORT HRESULT remove_NavigationStarting(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_NavigationStarting(token);
}

HRESULT WC::NavigateToString(LPCWSTR htmlContent) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->NavigateToString(htmlContent);
}
EXPORT HRESULT NavigateToString(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR htmlContent
) {
	return webview2->NavigateToString(htmlContent);
}

HRESULT WC::add_FrameNavigationCompleted(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_FrameNavigationCompleted(
		Callback<ICoreWebView2NavigationCompletedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_FrameNavigationCompleted(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationCompletedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_FrameNavigationCompleted(callback, token);
}


HRESULT WC::remove_FrameNavigationCompleted(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_FrameNavigationCompleted(token);
}
EXPORT HRESULT remove_FrameNavigationCompleted(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_FrameNavigationCompleted(token);
}

HRESULT WC::add_FrameNavigationStarting(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_FrameNavigationStarting(
		Callback<ICoreWebView2NavigationStartingEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_FrameNavigationStarting(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NavigationStartingEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_FrameNavigationStarting(callback, token);
}


HRESULT WC::remove_FrameNavigationStarting(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_FrameNavigationStarting(token);
}
EXPORT HRESULT remove_FrameNavigationStarting(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_FrameNavigationStarting(token);
}

/* Permission */

HRESULT WC::add_PermissionRequested(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2PermissionRequestedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_PermissionRequested(
		Callback<ICoreWebView2PermissionRequestedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2PermissionRequestedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_PermissionRequested(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2PermissionRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_PermissionRequested(callback, token);
}

HRESULT WC::remove_PermissionRequested(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_PermissionRequested(token);
}
EXPORT HRESULT remove_PermissionRequested(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_PermissionRequested(token);
}

/* Script */

HRESULT WC::add_ScriptDialogOpening(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ScriptDialogOpeningEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_ScriptDialogOpening(
		Callback<ICoreWebView2ScriptDialogOpeningEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2ScriptDialogOpeningEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_ScriptDialogOpening(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ScriptDialogOpeningEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_ScriptDialogOpening(callback, token);
}

HRESULT WC::remove_ScriptDialogOpening(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_ScriptDialogOpening(token);
}
EXPORT HRESULT remove_ScriptDialogOpening(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_ScriptDialogOpening(token);
}

HRESULT WC::AddScriptToExecuteOnDocumentCreated(
	LPCWSTR javaScript,
	HRESULT(*callback)(HRESULT, LPCWSTR)
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->AddScriptToExecuteOnDocumentCreated(
		javaScript,
		Callback<ICoreWebView2AddScriptToExecuteOnDocumentCreatedCompletedHandler>(
			[callback](HRESULT errorCode, LPCWSTR id) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(errorCode, id);
			}
		).Get()
	);
}
EXPORT HRESULT AddScriptToExecuteOnDocumentCreated(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR javaScript,
	/* [in] */ HRESULT(*callback)(HRESULT, LPCWSTR)
) {
	return webview2->AddScriptToExecuteOnDocumentCreated(javaScript, callback);
}

HRESULT WC::RemoveScriptToExecuteOnDocumentCreated(
	LPCWSTR id
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->RemoveScriptToExecuteOnDocumentCreated(id);
}
EXPORT HRESULT RemoveScriptToExecuteOnDocumentCreated(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR id
) {
	return webview2->RemoveScriptToExecuteOnDocumentCreated(id);
}

HRESULT WC::ExecuteScript(
	LPCWSTR javaScript,
	HRESULT(*callback)(HRESULT, LPCWSTR)
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->ExecuteScript(
		javaScript,
		Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
			[callback](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(errorCode, resultObjectAsJson);
			}
		).Get()
	);
}
EXPORT HRESULT ExecuteScript(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR javaScript,
	/* [in] */ HRESULT(*callback)(HRESULT, LPCWSTR)
) {
	return webview2->ExecuteScript(javaScript, callback);
}

HRESULT WC::AddHostObjectToScript(
	LPCWSTR name,
	VARIANT* object
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->AddHostObjectToScript(name, object);
}
EXPORT HRESULT AddHostObjectToScript(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR name,
	/* [in] */ VARIANT* object
) {
	return webview2->AddHostObjectToScript(name, object);
}

HRESULT WC::RemoveHostObjectFromScript(
	LPCWSTR name
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->RemoveHostObjectFromScript(name);
}
EXPORT HRESULT RemoveHostObjectFromScript(
	WebView2Connector* webview2,
	/* [in] */ LPCWSTR name
) {
	return webview2->RemoveHostObjectFromScript(name);
}

/* Source */

HRESULT WC::get_Source(
	LPWSTR* uri
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->get_Source(uri);
}
EXPORT HRESULT get_Source(
	WebView2Connector* webview2,
	/* [retval][out] */ LPWSTR* uri
) {
	return webview2->get_Source(uri);
}

HRESULT WC::add_SourceChanged(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2SourceChangedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_SourceChanged(
		Callback<ICoreWebView2SourceChangedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2SourceChangedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_SourceChanged(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2SourceChangedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_SourceChanged(callback, token);
}

HRESULT WC::remove_SourceChanged(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_SourceChanged(token);
}
EXPORT HRESULT remove_SourceChanged(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_SourceChanged(token);
}

/* Operation */

HRESULT WC::Reload(void) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->Reload();
}
EXPORT HRESULT Reload(WebView2Connector* webview2) {
	return webview2->Reload();
}

HRESULT WC::get_CanGoBack(
	BOOL* canGoBack
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->get_CanGoBack(canGoBack);
}
EXPORT HRESULT get_CanGoBack(
	WebView2Connector* webview2,
	/* [retval][out] */ BOOL* canGoBack
) {
	return webview2->get_CanGoBack(canGoBack);
}

HRESULT WC::get_CanGoForward(
	BOOL* canGoForward
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->get_CanGoForward(canGoForward);
}
EXPORT HRESULT get_CanGoForward(
	WebView2Connector* webview2,
	/* [retval][out] */ BOOL* canGoForward
) {
	return webview2->get_CanGoForward(canGoForward);
}

HRESULT WC::GoBack(void) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->GoBack();
}
EXPORT HRESULT GoBack(WebView2Connector* webview2) {
	return webview2->GoBack();
}

HRESULT WC::GoForward(void) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->GoForward();
}
EXPORT HRESULT GoForward(WebView2Connector* webview2) {
	return webview2->GoForward();
}

HRESULT WC::Stop(void) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->Stop();
}
EXPORT HRESULT Stop(WebView2Connector* webview2) {
	return webview2->Stop();
}

/* Other */

HRESULT WC::add_ContentLoading(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ContentLoadingEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_ContentLoading(
		Callback<ICoreWebView2ContentLoadingEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2ContentLoadingEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_ContentLoading(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ContentLoadingEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_ContentLoading(callback, token);
}

HRESULT WC::remove_ContentLoading(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_ContentLoading(token);
}
EXPORT HRESULT remove_ContentLoading(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_ContentLoading(token);
}

HRESULT WC::add_ProcessFailed(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ProcessFailedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_ProcessFailed(
		Callback<ICoreWebView2ProcessFailedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2ProcessFailedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_ProcessFailed(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2ProcessFailedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_ProcessFailed(callback, token);
}

HRESULT WC::remove_ProcessFailed(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_ProcessFailed(token);
}
EXPORT HRESULT remove_ProcessFailed(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_ProcessFailed(token);
}

HRESULT WC::get_Settings() {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->get_Settings(&(this->settings1));
}
EXPORT HRESULT get_Settings(WebView2Connector* webview2) {
	return webview2->get_Settings();
}

HRESULT WC::CapturePreview(
	COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT imageFormat,
	IStream* imageStream,
	HRESULT(*callback)(HRESULT errorCode)
) {
	Log(__FUNCTIONW__ L"\n");
	// TODO: imageStream
	return this->webview->CapturePreview(
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
EXPORT HRESULT CapturePreview(
	WebView2Connector* webview2,
	/* [in] */ COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT imageFormat,
	/* [in] */ IStream* imageStream,
	/* [in] */ HRESULT(*callback)(HRESULT errorCode)
) {
	// TODO: imageStream
	return webview2->CapturePreview(imageFormat, imageStream, callback);
}

HRESULT WC::get_BrowserProcessId(
	UINT32* value
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->get_BrowserProcessId(value);
}
EXPORT HRESULT get_BrowserProcessId(
	WebView2Connector* webview2,
	/* [retval][out] */ UINT32* value
) {
	return webview2->get_BrowserProcessId(value);
}

HRESULT WC::add_NewWindowRequested(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NewWindowRequestedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_NewWindowRequested(
		Callback<ICoreWebView2NewWindowRequestedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2NewWindowRequestedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_NewWindowRequested(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2NewWindowRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_NewWindowRequested(callback, token);
}

HRESULT WC::remove_NewWindowRequested(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_NewWindowRequested(token);
}
EXPORT HRESULT remove_NewWindowRequested(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_NewWindowRequested(token);
}

HRESULT WC::add_ContainsFullScreenElementChanged(
	HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_ContainsFullScreenElementChanged(
		Callback<ICoreWebView2ContainsFullScreenElementChangedEventHandler>(
			[callback](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_ContainsFullScreenElementChanged(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_ContainsFullScreenElementChanged(callback, token);
}

HRESULT WC::remove_ContainsFullScreenElementChanged(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_ContainsFullScreenElementChanged(token);
}
EXPORT HRESULT remove_ContainsFullScreenElementChanged(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_ContainsFullScreenElementChanged(token);
}

HRESULT WC::get_ContainsFullScreenElement(
	BOOL* containsFullScreenElement
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->get_ContainsFullScreenElement(containsFullScreenElement);
}
EXPORT HRESULT get_ContainsFullScreenElement(
	WebView2Connector* webview2,
	/* [retval][out] */ BOOL* containsFullScreenElement
) {
	return webview2->get_ContainsFullScreenElement(containsFullScreenElement);
}

HRESULT WC::add_WebResourceRequested(
	HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceRequestedEventArgs*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_WebResourceRequested(
		Callback<ICoreWebView2WebResourceRequestedEventHandler>(
			[callback](ICoreWebView2* sender, ICoreWebView2WebResourceRequestedEventArgs* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_WebResourceRequested(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, ICoreWebView2WebResourceRequestedEventArgs*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_WebResourceRequested(callback, token);
}

HRESULT WC::remove_WebResourceRequested(
	EventRegistrationToken token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_WebResourceRequested(token);
}
EXPORT HRESULT remove_WebResourceRequested(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_WebResourceRequested(token);
}

HRESULT WC::AddWebResourceRequestedFilter(
	const LPCWSTR uri,
	const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->AddWebResourceRequestedFilter(uri, resourceContext);
}
EXPORT HRESULT AddWebResourceRequestedFilter(
	WebView2Connector* webview2,
	/* [in] */ const LPCWSTR uri,
	/* [in] */ const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
) {
	// TODO: Add arg 3.
	// https://learn.microsoft.com/en-us/dotnet/api/microsoft.web.webview2.core.corewebview2.addwebresourcerequestedfilter?view=webview2-dotnet-1.0.3351.48
	return webview2->AddWebResourceRequestedFilter(uri, resourceContext);
}

HRESULT WC::RemoveWebResourceRequestedFilter(
	const LPCWSTR uri,
	const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->RemoveWebResourceRequestedFilter(uri, resourceContext);
}
EXPORT HRESULT RemoveWebResourceRequestedFilter(
	WebView2Connector* webview2,
	/* [in] */ const LPCWSTR uri,
	/* [in] */ const COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext
) {
	return webview2->RemoveWebResourceRequestedFilter(uri, resourceContext);
}

HRESULT WC::add_WindowCloseRequested(
	HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	EventRegistrationToken* token
) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->add_WindowCloseRequested(
		Callback<ICoreWebView2WindowCloseRequestedEventHandler>(
			[callback](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				Log(__FUNCTIONW__ L"\n");
				return callback(sender, args);
			}
		).Get(),
		token
	);
}
EXPORT HRESULT add_WindowCloseRequested(
	WebView2Connector* webview2,
	/* [in] */ HRESULT(*callback)(ICoreWebView2*, IUnknown*),
	/* [out] */ EventRegistrationToken* token
) {
	return webview2->add_WindowCloseRequested(callback, token);
}

HRESULT WC::remove_WindowCloseRequested(EventRegistrationToken token) {
	Log(__FUNCTIONW__ L"\n");
	return this->webview->remove_WindowCloseRequested(token);
}
EXPORT HRESULT remove_WindowCloseRequested(
	WebView2Connector* webview2,
	/* [in] */ EventRegistrationToken token
) {
	return webview2->remove_WindowCloseRequested(token);
}

#endif
