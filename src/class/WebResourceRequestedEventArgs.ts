import type { Webview2Funcs } from '../webview2_types.ts';
import { Deferral } from './Deferral.ts';
import { WebResourceRequest } from './WebResourceRequest.ts';
import { WebResourceResponse } from './WebResourceResponse.ts';

type ICoreWebView2WebResourceRequestedEventArgs = Deno.PointerValue;

type WEB_RESOURCE_CONTEXT_TYPE_NAMES =
  | 'ALL'
  | 'DOCUMENT'
  | 'STYLESHEET'
  | 'IMAGE'
  | 'MEDIA'
  | 'FONT'
  | 'SCRIPT'
  | 'XML_HTTP_REQUEST'
  | 'FETCH'
  | 'TEXT_TRACK'
  | 'EVENT_SOURCE'
  | 'WEBSOCKET'
  | 'MANIFEST'
  | 'SIGNED_EXCHANGE'
  | 'PING'
  | 'CSP_VIOLATION_REPORT'
  | 'OTHER';

const WEB_RESOURCE_CONTEXT_TYPES: WEB_RESOURCE_CONTEXT_TYPE_NAMES[] = [
  'ALL', // 0
  'DOCUMENT', // 1
  'STYLESHEET', // 2
  'IMAGE', // 3
  'MEDIA', // 4
  'FONT', // 5
  'SCRIPT', // 6
  'XML_HTTP_REQUEST', // 7
  'FETCH', // 8
  'TEXT_TRACK', // 9
  'EVENT_SOURCE', // 10
  'WEBSOCKET', // 11
  'MANIFEST', // 12
  'SIGNED_EXCHANGE', // 13
  'PING', // 14
  'CSP_VIOLATION_REPORT', // 15
  'OTHER', // 16
];

/** Borrowed arguments for an intercepted WebView2 resource request. */
export class WebResourceRequestedEventArgs {
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    protected libs: Webview2Funcs,
    protected args: ICoreWebView2WebResourceRequestedEventArgs,
  ) {
  }

  /** Intercepted request. Close the returned owned request wrapper after use. */
  public get Request(): WebResourceRequest {
    const request = new WebResourceRequest(
      this.libs,
    );
    const result = this.libs.symbols.WebResourceRequestedEventArgs_get_Request(
      this.args,
      request.doublePointer,
    );
    if (result < 0) {
      throw new Error(`Failed to get WebResourceRequest: ${result}`);
    }
    return request;
  }

  /** Numeric WebView2 resource category. */
  public get ResourceContextCode(): number {
    const context = new Uint32Array(1);
    const hresult = this.libs.symbols
      .WebResourceRequestedEventArgs_get_ResourceContext(
        this.args,
        Deno.UnsafePointer.of(context),
      );
    if (hresult !== 0) {
      throw new Error(`Failed to get ResourceContext: ${hresult}`);
    }
    return context[0];
  }

  /** Resource category name, or UNKNOWN for an unrecognized native value. */
  public get ResourceContext(): WEB_RESOURCE_CONTEXT_TYPE_NAMES | 'UNKNOWN' {
    return WEB_RESOURCE_CONTEXT_TYPES[this.ResourceContextCode] || 'UNKNOWN';
  }

  /** Response assigned to this intercepted request. Close retrieved response wrappers after use. */
  public get Response(): WebResourceResponse {
    const response = new WebResourceResponse(
      this.libs,
    );
    const result = this.libs.symbols.WebResourceRequestedEventArgs_get_Response(
      this.args,
      response.doublePointer,
    );
    if (result !== 0) {
      throw new Error(`Failed to get WebResourceResponse: ${result}`);
    }
    return response;
  }

  /** Assign the intercepted response before completing a deferral. */
  public set Response(response: WebResourceResponse) {
    const result = this.libs.symbols.WebResourceRequestedEventArgs_put_Response(
      this.args,
      response.pointer,
    );
    if (result !== 0) {
      throw new Error(`Failed to set WebResourceResponse: ${result}`);
    }
  }

  /** Defer event processing. Complete and close the returned deferral after asynchronous work. */
  public getDeferral(): Deferral {
    const deferral = new Deferral(this.libs);
    const result = this.libs.symbols.WebResourceRequestedEventArgs_GetDeferral(
      this.args,
      deferral.getDoublePointer(),
    );
    if (result < 0) {
      throw new Error(`Failed to get Deferral: ${result}`);
    }
    return deferral;
  }
}
