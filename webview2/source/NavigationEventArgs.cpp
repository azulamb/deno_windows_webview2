#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

EXPORT HRESULT NavigationStartingEventArgs_get_Uri(ICoreWebView2NavigationStartingEventArgs* args, LPWSTR value, rsize_t* size) {
  wil::unique_cotaskmem_string data;
  HRESULT result = args->get_Uri(&data);
  if (FAILED(result)) { if (size) *size = 0; return result; }
  CopyString(data.get(), size, value);
  return result;
}
EXPORT HRESULT NavigationStartingEventArgs_get_IsUserInitiated(ICoreWebView2NavigationStartingEventArgs* args, BOOL* value) { return args->get_IsUserInitiated(value); }
EXPORT HRESULT NavigationStartingEventArgs_get_IsRedirected(ICoreWebView2NavigationStartingEventArgs* args, BOOL* value) { return args->get_IsRedirected(value); }
EXPORT HRESULT NavigationStartingEventArgs_get_Cancel(ICoreWebView2NavigationStartingEventArgs* args, BOOL* value) { return args->get_Cancel(value); }
EXPORT HRESULT NavigationStartingEventArgs_put_Cancel(ICoreWebView2NavigationStartingEventArgs* args, BOOL value) { return args->put_Cancel(value); }
EXPORT HRESULT NavigationStartingEventArgs_get_NavigationId(ICoreWebView2NavigationStartingEventArgs* args, UINT64* value) { return args->get_NavigationId(value); }
EXPORT HRESULT NavigationCompletedEventArgs_get_IsSuccess(ICoreWebView2NavigationCompletedEventArgs* args, BOOL* value) { return args->get_IsSuccess(value); }
EXPORT HRESULT NavigationCompletedEventArgs_get_WebErrorStatus(ICoreWebView2NavigationCompletedEventArgs* args, COREWEBVIEW2_WEB_ERROR_STATUS* value) { return args->get_WebErrorStatus(value); }
EXPORT HRESULT NavigationCompletedEventArgs_get_NavigationId(ICoreWebView2NavigationCompletedEventArgs* args, UINT64* value) { return args->get_NavigationId(value); }
EXPORT HRESULT NewWindowRequestedEventArgs_get_Uri(ICoreWebView2NewWindowRequestedEventArgs* args, LPWSTR value, rsize_t* size) {
  wil::unique_cotaskmem_string data;
  HRESULT result = args->get_Uri(&data);
  if (FAILED(result)) { if (size) *size = 0; return result; }
  CopyString(data.get(), size, value);
  return result;
}
EXPORT HRESULT NewWindowRequestedEventArgs_get_IsUserInitiated(ICoreWebView2NewWindowRequestedEventArgs* args, BOOL* value) { return args->get_IsUserInitiated(value); }
EXPORT HRESULT NewWindowRequestedEventArgs_get_Handled(ICoreWebView2NewWindowRequestedEventArgs* args, BOOL* value) { return args->get_Handled(value); }
EXPORT HRESULT NewWindowRequestedEventArgs_put_Handled(ICoreWebView2NewWindowRequestedEventArgs* args, BOOL value) { return args->put_Handled(value); }
EXPORT HRESULT NewWindowRequestedEventArgs_GetDeferral(ICoreWebView2NewWindowRequestedEventArgs* args, ICoreWebView2Deferral** value) { return args->GetDeferral(value); }
EXPORT HRESULT PermissionRequestedEventArgs_get_Uri(ICoreWebView2PermissionRequestedEventArgs* args, LPWSTR value, rsize_t* size) {
  wil::unique_cotaskmem_string data;
  HRESULT result = args->get_Uri(&data);
  if (FAILED(result)) { if (size) *size = 0; return result; }
  CopyString(data.get(), size, value);
  return result;
}
EXPORT HRESULT PermissionRequestedEventArgs_get_PermissionKind(ICoreWebView2PermissionRequestedEventArgs* args, COREWEBVIEW2_PERMISSION_KIND* value) { return args->get_PermissionKind(value); }
EXPORT HRESULT PermissionRequestedEventArgs_get_IsUserInitiated(ICoreWebView2PermissionRequestedEventArgs* args, BOOL* value) { return args->get_IsUserInitiated(value); }
EXPORT HRESULT PermissionRequestedEventArgs_get_State(ICoreWebView2PermissionRequestedEventArgs* args, COREWEBVIEW2_PERMISSION_STATE* value) { return args->get_State(value); }
EXPORT HRESULT PermissionRequestedEventArgs_put_State(ICoreWebView2PermissionRequestedEventArgs* args, COREWEBVIEW2_PERMISSION_STATE value) { return args->put_State(value); }
EXPORT HRESULT PermissionRequestedEventArgs_GetDeferral(ICoreWebView2PermissionRequestedEventArgs* args, ICoreWebView2Deferral** value) { return args->GetDeferral(value); }
#endif

