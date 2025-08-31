import { DoublePointer } from './DoublePointer.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import {
  createStringPointer,
  utf16BufferToString,
  utf16PointerToString,
} from '../libs/convert.ts';

/**
 * Parses the headers from a WebView2 header pointer.
 * @param libs
 * @param webview2Header
 * @returns
 */
export function parseHeaders(
  libs: Webview2Funcs,
  webview2Header: Deno.PointerValue,
): Headers {
  const headers: Headers = new Headers();

  const callback = new Deno.UnsafeCallback(
    {
      parameters: [
        'pointer', // name
        'pointer', // value
      ],
      result: 'i32',
    },
    (
      name: Deno.PointerValue,
      value: Deno.PointerValue,
    ) => {
      headers.append(
        utf16PointerToString(name),
        utf16PointerToString(value),
      );
      return 0; // Continue iteration
    },
  );
  libs.symbols.HttpRequestHeaders_GetIterator(
    webview2Header,
    callback.pointer,
  );

  return headers;
}

export class WebView2Headers {
  static create(
    libs: Webview2Funcs,
    request: Deno.PointerValue,
  ): WebView2Headers {
    const headerPointer = new DoublePointer();

    const result = libs.symbols.WebResourceRequest_get_Headers(
      request,
      headerPointer.getPointer(),
    );

    if (result !== 0) {
      throw new Error(`Failed to get WebResourceRequest::Headers: ${result}`);
    }

    return new WebView2Headers(libs, headerPointer.getDoublePointer());
  }

  constructor(
    protected libs: Webview2Funcs,
    protected header: Deno.PointerValue,
  ) {
  }

  /**
   * Converts the WebView2 headers to a standard Headers object.
   * @returns A Headers object containing the parsed headers.
   */
  public convertHeaders(): Headers {
    return parseHeaders(this.libs, this.header);
  }

  /**
   * Checks if the request contains a specific header.
   * @param name The name of the header to check.
   * @returns True if the header exists, false otherwise.
   */
  public Contains(name: string): boolean {
    const contains = new Int32Array(1);
    this.libs.symbols.HttpRequestHeaders_Contains(
      this.header,
      createStringPointer(name),
      Deno.UnsafePointer.of(contains),
    );
    return contains[0] !== 0;
  }

  /**
   * Gets a header from the request.
   * @param name The name of the header.
   * @returns The value of the header.
   */
  public GetHeader(name: string): string {
    const namePointer = createStringPointer(name);
    const size = new BigUint64Array(1);
    const hresult = this.libs.symbols.HttpRequestHeaders_GetHeader(
      this.header,
      namePointer,
      null,
      Deno.UnsafePointer.of(size),
    );

    if (hresult !== 0) {
      throw new Error();
    }
    if (size[0] === 0n) {
      return '';
    }

    const buffer = new Uint16Array(Number(size[0]));
    const hresult2 = this.libs.symbols.HttpRequestHeaders_GetHeader(
      this.header,
      namePointer,
      Deno.UnsafePointer.of(buffer),
      null,
    );
    if (hresult2 !== 0) {
      throw new Error();
    }

    return utf16BufferToString(buffer);
  }

  /**
   * Gets the values of a header from the request.
   * @param name The name of the header.
   * @returns An array of header values.
   */
  public GetHeaders(name: string): string[] {
    const values: string[] = [];
    const callback = new Deno.UnsafeCallback(
      {
        parameters: [
          'pointer',
        ],
        result: 'i32',
      },
      (valuePtr: Deno.PointerValue) => {
        values.push(utf16PointerToString(valuePtr));
        return 0;
      },
    );

    this.libs.symbols.HttpRequestHeaders_GetHeaders(
      this.header,
      createStringPointer(name),
      callback.pointer,
    );

    return values;
  }

  /**
   * Removes a header from the request.
   * @param name The name of the header.
   */
  public RemoveHeader(name: string): void {
    const result = this.libs.symbols.HttpRequestHeaders_RemoveHeader(
      this.header,
      createStringPointer(name),
    );
    if (result !== 0) {
      throw new Error(`Failed to remove header ${name}: ${result}`);
    }
  }

  /**
   * Sets a header for the request.
   * @param name The name of the header.
   * @param value The value of the header.
   */
  public SetHeader(name: string, value: string): void {
    const result = this.libs.symbols.HttpRequestHeaders_SetHeader(
      this.header,
      createStringPointer(name),
      createStringPointer(value),
    );
    if (result !== 0) {
      throw new Error(`Failed to set header ${name}: ${result}`);
    }
  }
}
