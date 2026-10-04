#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

EXPORT HRESULT ProcessFailedEventArgs_get_ProcessFailedKind(ICoreWebView2ProcessFailedEventArgs* args, COREWEBVIEW2_PROCESS_FAILED_KIND* value) { CHECK(args); return args->get_ProcessFailedKind(value); }
EXPORT HRESULT AcceleratorKeyPressedEventArgs_get_KeyEventKind(ICoreWebView2AcceleratorKeyPressedEventArgs* args, COREWEBVIEW2_KEY_EVENT_KIND* value) { CHECK(args); return args->get_KeyEventKind(value); }
EXPORT HRESULT AcceleratorKeyPressedEventArgs_get_VirtualKey(ICoreWebView2AcceleratorKeyPressedEventArgs* args, UINT32* value) { CHECK(args); return args->get_VirtualKey(value); }
EXPORT HRESULT AcceleratorKeyPressedEventArgs_get_KeyEventLParam(ICoreWebView2AcceleratorKeyPressedEventArgs* args, INT* value) { CHECK(args); return args->get_KeyEventLParam(value); }
EXPORT HRESULT AcceleratorKeyPressedEventArgs_get_Handled(ICoreWebView2AcceleratorKeyPressedEventArgs* args, BOOL* value) { CHECK(args); return args->get_Handled(value); }
EXPORT HRESULT AcceleratorKeyPressedEventArgs_put_Handled(ICoreWebView2AcceleratorKeyPressedEventArgs* args, BOOL value) { CHECK(args); return args->put_Handled(value); }
EXPORT HRESULT AcceleratorKeyPressedEventArgs_get_PhysicalKeyStatus(ICoreWebView2AcceleratorKeyPressedEventArgs* args, COREWEBVIEW2_PHYSICAL_KEY_STATUS* value) { CHECK(args); return args->get_PhysicalKeyStatus(value); }
EXPORT HRESULT SourceChangedEventArgs_get_IsNewDocument(ICoreWebView2SourceChangedEventArgs* args, BOOL* value) { CHECK(args); return args->get_IsNewDocument(value); }
EXPORT HRESULT WebView2_AddWebResourceRequestedFilterWithRequestSourceKinds(WebView2* webview2, LPCWSTR uri, COREWEBVIEW2_WEB_RESOURCE_CONTEXT context, COREWEBVIEW2_WEB_RESOURCE_REQUEST_SOURCE_KINDS kinds) {
  CHECK(webview2); CHECK(webview2->webview1);
  auto extended = webview2->webview1.try_query<ICoreWebView2_22>();
  if (!extended) return E_NOINTERFACE;
  return extended->AddWebResourceRequestedFilterWithRequestSourceKinds(uri, context, kinds);
}
EXPORT HRESULT WebView2_RemoveWebResourceRequestedFilterWithRequestSourceKinds(WebView2* webview2, LPCWSTR uri, COREWEBVIEW2_WEB_RESOURCE_CONTEXT context, COREWEBVIEW2_WEB_RESOURCE_REQUEST_SOURCE_KINDS kinds) {
  CHECK(webview2); CHECK(webview2->webview1);
  auto extended = webview2->webview1.try_query<ICoreWebView2_22>();
  if (!extended) return E_NOINTERFACE;
  return extended->RemoveWebResourceRequestedFilterWithRequestSourceKinds(uri, context, kinds);
}
#endif

