import { createStringPointer, getString } from '../libs/convert.ts';
import { WebView2Headers } from './Header.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import { DoublePointer } from './DoublePointer.ts';
import { IStream } from './IStream.ts';

export class WebResourceResponse {
  private disposed: boolean = false;
  protected get lib(): Webview2Funcs {
    if (this.disposed) throw new Error('COM object is closed.');
    return this.libs;
  }
  constructor(
    protected libs: Webview2Funcs,
    protected response: DoublePointer = new DoublePointer(),
  ) {
  }

  public get doublePointer(): Deno.PointerValue {
    return this.response.getDoublePointer();
  }

  public get pointer(): Deno.PointerValue {
    return this.response.getPointer();
  }

  /** Releases this owned response reference. */
  public close(): void {
    if (this.disposed) return;
    this.lib.symbols.COM_Release(this.response.getPointer());
    this.response.setPointer(null);
    this.disposed = true;
  }

  public get Content(): IStream {
    const stream = new IStream(this.lib);
    const result = this.lib.symbols.WebResourceResponse_get_Content(
      this.response.getPointer(),
      stream.getDoublePointer(),
    );
    if (result !== 0) {
      throw new Error(`Failed to get WebResourceResponse::Content: ${result}`);
    }
    return stream;
  }

  public set Content(stream: IStream) {
    const result = this.lib.symbols.WebResourceResponse_put_Content(
      this.response.getPointer(),
      stream.getPointer(),
    );
    if (result !== 0) {
      throw new Error(`Failed to set WebResourceResponse::Content: ${result}`);
    }
  }

  public get Headers(): WebView2Headers {
    return WebView2Headers.createResponse(
      this.lib,
      this.response.getPointer(),
    );
  }

  public get ReasonPhrase(): string {
    return getString(
      this.response.getPointer(),
      this.lib.symbols.WebResourceResponse_get_ReasonPhrase,
    );
  }

  public set ReasonPhrase(value: string) {
    const result = this.lib.symbols.WebResourceResponse_put_ReasonPhrase(
      this.response.getPointer(),
      createStringPointer(value),
    );
    if (result !== 0) {
      throw new Error(
        `Failed to set WebResourceResponse::ReasonPhrase: ${result}`,
      );
    }
  }

  public get StatusCode(): number {
    const statusCode = new Int32Array(1);
    const result = this.lib.symbols.WebResourceResponse_get_StatusCode(
      this.response.getPointer(),
      Deno.UnsafePointer.of(statusCode),
    );
    if (result !== 0) {
      throw new Error(
        `Failed to get WebResourceResponse::StatusCode: ${result}`,
      );
    }
    return statusCode[0];
  }

  public set StatusCode(value: number) {
    const result = this.lib.symbols.WebResourceResponse_put_StatusCode(
      this.response.getPointer(),
      value,
    );
    if (result !== 0) {
      throw new Error(
        `Failed to set WebResourceResponse::StatusCode: ${result}`,
      );
    }
  }
}
