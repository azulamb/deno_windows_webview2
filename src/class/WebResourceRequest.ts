import { createStringPointer, getString } from '../libs/convert.ts';
import { WebView2Headers } from './Header.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import { DoublePointer } from './DoublePointer.ts';
import { IStream } from './IStream.ts';

export class WebResourceRequest {
  protected request: DoublePointer = new DoublePointer();
  private disposed: boolean = false;
  protected get lib(): Webview2Funcs {
    if (this.disposed) throw new Error('COM object is closed.');
    return this.libs;
  }
  constructor(
    protected libs: Webview2Funcs,
  ) {
  }

  /** @deprecated This is the output buffer; prefer doublePointer or nativePointer explicitly. */
  public get pointer(): Deno.PointerValue {
    return this.request.getDoublePointer();
  }

  public get doublePointer(): Deno.PointerValue {
    return this.request.getDoublePointer();
  }
  public get nativePointer(): Deno.PointerValue {
    return this.request.getPointer();
  }

  /** Releases the owned request reference. */
  public close(): void {
    if (this.disposed) return;
    this.lib.symbols.COM_Release(this.request.getPointer());
    this.request.setPointer(null);
    this.disposed = true;
  }

  public get Content(): IStream {
    const stream = new IStream(this.lib);
    const result = this.lib.symbols.WebResourceRequest_get_Content(
      this.request.getPointer(),
      stream.getDoublePointer(),
    );
    if (result !== 0) {
      throw new Error(`Failed to get WebResourceRequest::Content: ${result}`);
    }
    return stream;
  }

  public set Content(stream: IStream) {
    const result = this.lib.symbols.WebResourceRequest_put_Content(
      this.request.getPointer(),
      stream.getPointer(),
    );
    if (result < 0) {
      throw new Error(`Failed to set WebResourceRequest::Content: ${result}`);
    }
  }

  public get Headers(): WebView2Headers {
    return WebView2Headers.create(
      this.lib,
      this.request.getPointer(),
    );
  }

  public get Method(): string {
    return getString(
      this.request.getPointer(),
      this.lib.symbols.WebResourceRequest_get_Method,
    );
  }

  public set Method(value: string) {
    const result = this.lib.symbols.WebResourceRequest_put_Method(
      this.request.getPointer(),
      createStringPointer(value),
    );
    if (result < 0) {
      throw new Error(`WebResourceRequest setter failed: ${result}`);
    }
  }

  public get Uri(): string {
    return getString(
      this.request.getPointer(),
      this.lib.symbols.WebResourceRequest_get_Uri,
    );
  }

  public set Uri(value: string) {
    const result = this.lib.symbols.WebResourceRequest_put_Uri(
      this.request.getPointer(),
      createStringPointer(value),
    );
    if (result < 0) throw new Error(`Failed to set Uri: ${result}`);
  }
}
