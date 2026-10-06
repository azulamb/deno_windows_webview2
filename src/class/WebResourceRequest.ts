import { createStringPointer, getString } from '../libs/convert.ts';
import { WebView2Headers } from './Header.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import { DoublePointer } from './DoublePointer.ts';
import { IStream } from './IStream.ts';

/** Owned HTTP request with editable URI, method, body and headers. */
export class WebResourceRequest {
  /** Storage for the owned request pointer and its output address. */
  protected request: DoublePointer = new DoublePointer();
  private disposed: boolean = false;
  /** Native FFI library; access throws after the wrapper is disposed. */
  protected get lib(): Webview2Funcs {
    if (this.disposed) throw new Error('COM object is closed.');
    return this.libs;
  }
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    protected libs: Webview2Funcs,
  ) {
  }

  /**
   * Address of this request's COM output buffer.
   * @deprecated Prefer doublePointer or nativePointer explicitly.
   */
  public get pointer(): Deno.PointerValue {
    return this.request.getDoublePointer();
  }

  /** Address of native pointer storage, for COM output parameters. */
  public get doublePointer(): Deno.PointerValue {
    return this.request.getDoublePointer();
  }
  /** Native COM request pointer, not the address of its output storage. */
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

  /** Body stream. Close the returned owned stream after use. */
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

  /** Assign the body stream; the native object retains its own COM reference. */
  public set Content(stream: IStream) {
    const result = this.lib.symbols.WebResourceRequest_put_Content(
      this.request.getPointer(),
      stream.getPointer(),
    );
    if (result < 0) {
      throw new Error(`Failed to set WebResourceRequest::Content: ${result}`);
    }
  }

  /** HTTP headers. Close the returned owned headers wrapper after use. */
  public get Headers(): WebView2Headers {
    return WebView2Headers.create(
      this.lib,
      this.request.getPointer(),
    );
  }

  /** HTTP request method, such as GET or POST. */
  public get Method(): string {
    return getString(
      this.request.getPointer(),
      this.lib.symbols.WebResourceRequest_get_Method,
    );
  }

  /** Set the HTTP request method. */
  public set Method(value: string) {
    const result = this.lib.symbols.WebResourceRequest_put_Method(
      this.request.getPointer(),
      createStringPointer(value),
    );
    if (result < 0) {
      throw new Error(`WebResourceRequest setter failed: ${result}`);
    }
  }

  /** URI of the resource or navigation. */
  public get Uri(): string {
    return getString(
      this.request.getPointer(),
      this.lib.symbols.WebResourceRequest_get_Uri,
    );
  }

  /** Set the request URI. */
  public set Uri(value: string) {
    const result = this.lib.symbols.WebResourceRequest_put_Uri(
      this.request.getPointer(),
      createStringPointer(value),
    );
    if (result < 0) throw new Error(`Failed to set Uri: ${result}`);
  }
}
