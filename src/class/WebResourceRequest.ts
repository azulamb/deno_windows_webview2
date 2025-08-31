import {
  createStringPointer,
  getString,
  utf16BufferToString,
} from '../libs/convert.ts';
import { WebView2Headers } from './Header.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import { DoublePointer } from './DoublePointer.ts';
import { IStream } from './IStream.ts';

export class WebResourceRequest {
  protected request: DoublePointer = new DoublePointer();
  constructor(
    protected libs: Webview2Funcs,
  ) {
  }

  public get pointer(): Deno.PointerValue {
    return this.request.getDoublePointer();
  }

  public get Content(): IStream {
    const stream = new IStream(this.libs);
    const result = this.libs.symbols.WebResourceRequest_get_Content(
      this.request.getPointer(),
      stream.getDoublePointer(),
    );
    if (result !== 0) {
      throw new Error(`Failed to get WebResourceRequest::Content: ${result}`);
    }
    return stream;
  }

  public set Content(stream: IStream) {
    const result = this.libs.symbols.WebResourceRequest_put_Content(
      this.request.getPointer(),
      stream.getDoublePointer(),
    );
    if (result !== 0) {
      throw new Error(`Failed to set WebResourceRequest::Content: ${result}`);
    }
  }

  public get Headers(): WebView2Headers {
    return WebView2Headers.create(
      this.libs,
      this.request.getPointer(),
    );
  }

  public get Method(): string {
    const method = new Uint16Array(8);
    const result = this.libs.symbols.WebResourceRequest_get_Method(
      this.request.getPointer(),
      Deno.UnsafePointer.of(method),
    );
    if (result !== 0) {
      throw new Error(`Failed to get WebResourceRequest::Method: ${result}`);
    }
    let size = 0;
    for (const char of method) {
      if (char === 0) {
        break;
      }
      size++;
    }
    if (size === 0) {
      return '';
    }
    return utf16BufferToString(method.subarray(0, size));
  }

  public set Method(value: string) {
    this.libs.symbols.WebResourceRequest_put_Method(
      this.request.getPointer(),
      createStringPointer(value),
    );
  }

  public get Uri(): string {
    return getString(
      this.request.getPointer(),
      this.libs.symbols.WebResourceRequest_get_Uri,
    );
  }

  public set Uri(value: string) {
    this.libs.symbols.WebResourceRequest_put_Uri(
      this.request.getPointer(),
      createStringPointer(value),
    );
  }
}
