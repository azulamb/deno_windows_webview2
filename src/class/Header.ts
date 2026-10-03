import type { Webview2Funcs } from '../webview2_types.ts';
import { DoublePointer } from './DoublePointer.ts';
import { createStringPointer, getString, getWString } from '../libs/convert.ts';

function check(result: number): void {
  if (result < 0) throw new Error(`Header operation failed: ${result}`);
}

/** Enumerates borrowed request or response header pointers synchronously. */
export function parseHeaders(
  libs: Webview2Funcs,
  pointer: Deno.PointerValue,
  response = false,
): Headers {
  const headers = new Headers();
  const callback = new Deno.UnsafeCallback({
    parameters: ['pointer', 'pointer'],
    result: 'i32',
  }, (name, value) => {
    headers.append(getWString(name), getWString(value));
    return 0;
  });
  try {
    check(
      (response
        ? libs.symbols.HttpResponseHeaders_GetIterator
        : libs.symbols.HttpRequestHeaders_GetIterator)(
          pointer,
          callback.pointer,
        ),
    );
    return headers;
  } finally {
    callback.close();
  }
}

/** Owns the COM reference returned by a request or response Headers getter. */
export class WebView2Headers {
  static create(
    libs: Webview2Funcs,
    request: Deno.PointerValue,
  ): WebView2Headers {
    return this.acquire(libs, request, false);
  }
  static createResponse(
    libs: Webview2Funcs,
    response: Deno.PointerValue,
  ): WebView2Headers {
    return this.acquire(libs, response, true);
  }
  private static acquire(
    libs: Webview2Funcs,
    owner: Deno.PointerValue,
    response: boolean,
  ): WebView2Headers {
    const out = new DoublePointer();
    check(
      (response
        ? libs.symbols.WebResourceResponse_get_Headers
        : libs.symbols.WebResourceRequest_get_Headers)(
          owner,
          out.getDoublePointer(),
        ),
    );
    return new WebView2Headers(libs, out.getPointer(), response);
  }
  constructor(
    protected libs: Webview2Funcs,
    protected header: Deno.PointerValue,
    private response: boolean = false,
  ) {}
  private get pointer(): Deno.PointerValue {
    if (!this.header) throw new Error('Headers are closed.');
    return this.header;
  }
  public close(): void {
    if (this.header) this.libs.symbols.COM_Release(this.header);
    this.header = null;
  }
  public convertHeaders(): Headers {
    return parseHeaders(this.libs, this.pointer, this.response);
  }
  public Contains(name: string): boolean {
    const contains = new Int32Array(1);
    check(
      (this.response
        ? this.libs.symbols.HttpResponseHeaders_Contains
        : this.libs.symbols.HttpRequestHeaders_Contains)(
          this.pointer,
          createStringPointer(name),
          Deno.UnsafePointer.of(contains),
        ),
    );
    return contains[0] !== 0;
  }
  public GetHeader(name: string): string {
    const namePointer = createStringPointer(name);
    const getter = this.response
      ? this.libs.symbols.HttpResponseHeaders_GetHeader
      : this.libs.symbols.HttpRequestHeaders_GetHeader;
    return getString(
      this.pointer,
      (pointer, buffer, size) => getter(pointer, namePointer, buffer, size),
    );
  }
  public GetHeaders(name: string): string[] {
    const values: string[] = [];
    const callback = new Deno.UnsafeCallback({
      parameters: ['pointer'],
      result: 'i32',
    }, (value) => {
      values.push(getWString(value));
      return 0;
    });
    try {
      check(
        (this.response
          ? this.libs.symbols.HttpResponseHeaders_GetHeaders
          : this.libs.symbols.HttpRequestHeaders_GetHeaders)(
            this.pointer,
            createStringPointer(name),
            callback.pointer,
          ),
      );
      return values;
    } finally {
      callback.close();
    }
  }
  public RemoveHeader(name: string): void {
    if (this.response) {
      throw new Error('Response headers do not support RemoveHeader.');
    }
    check(
      this.libs.symbols.HttpRequestHeaders_RemoveHeader(
        this.pointer,
        createStringPointer(name),
      ),
    );
  }
  public SetHeader(name: string, value: string): void {
    if (this.response) {
      throw new Error('Use AppendHeader for response headers.');
    }
    check(
      this.libs.symbols.HttpRequestHeaders_SetHeader(
        this.pointer,
        createStringPointer(name),
        createStringPointer(value),
      ),
    );
  }
  public AppendHeader(name: string, value: string): void {
    if (!this.response) throw new Error('Use SetHeader for request headers.');
    check(
      this.libs.symbols.HttpResponseHeaders_AppendHeader(
        this.pointer,
        createStringPointer(name),
        createStringPointer(value),
      ),
    );
  }
}
