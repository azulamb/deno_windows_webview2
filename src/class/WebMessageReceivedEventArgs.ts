import type { WEBVIEW2_FUNCS } from '../webview2_types.ts';

type ICoreWebView2WebMessageReceivedEventArgsPointer = Deno.PointerValue;

/**
 * ICoreWebView2WebMessageReceivedEventArgs wrapper.
 * https://learn.microsoft.com/ja-jp/microsoft-edge/webview2/reference/win32/icorewebview2webmessagereceivedeventargs
 */
export class WebMessageReceivedEventArgs {
  protected libs: Deno.DynamicLibrary<WEBVIEW2_FUNCS>;
  protected args: ICoreWebView2WebMessageReceivedEventArgsPointer;
  // TODO: cache results if success.
  // Ex: protected _source: string;

  /**
   * The raw pointer to the ICoreWebView2WebMessageReceivedEventArgs interface.
   */
  constructor(
    libs: Deno.DynamicLibrary<WEBVIEW2_FUNCS>,
    args: ICoreWebView2WebMessageReceivedEventArgsPointer,
  ) {
    this.libs = libs;
    this.args = args;
  }

  /**
   * Gets the source of the message.
   */
  public Source(): string {
    const size = new BigUint64Array(1);
    const hresult = this.libs.symbols.MessageReceivedEventArgs_get_Source(
      this.args,
      null,
      Deno.UnsafePointer.of(size),
    );
    if (hresult !== 0) {
      throw new Error(`Failed to get Source: ${hresult}`);
    }
    if (size[0] === 0n) {
      return '';
    }

    const buffer = new Uint16Array(Number(size[0]));
    const hresult2 = this.libs.symbols.MessageReceivedEventArgs_get_Source(
      this.args,
      Deno.UnsafePointer.of(buffer),
      null,
    );
    if (hresult2 !== 0) {
      throw new Error(`Failed to get Source: ${hresult2}`);
    }

    return new TextDecoder().decode(buffer);
  }

  /**
   * Gets the message as JSON.
   */
  public WebMessageAsJson<T>(): T | null {
    const size = new BigUint64Array(1);
    const hresult = this.libs.symbols
      .MessageReceivedEventArgs_get_WebMessageAsJson(
        this.args,
        null,
        Deno.UnsafePointer.of(size),
      );
    if (hresult !== 0) {
      throw new Error(`Failed to get WebMessageAsJson: ${hresult}`);
    }
    if (size[0] === 0n) {
      return null;
    }

    const buffer = new Uint16Array(Number(size[0]));
    const hresult2 = this.libs.symbols
      .MessageReceivedEventArgs_get_WebMessageAsJson(
        this.args,
        Deno.UnsafePointer.of(buffer),
        null,
      );
    if (hresult2 !== 0) {
      throw new Error(`Failed to get WebMessageAsJson: ${hresult2}`);
    }

    return JSON.parse(
      JSON.parse(
        String.fromCharCode.apply(null, Array.from(buffer.subarray(0, -1))),
      ),
    ) as T;
  }

  /**
   * Tries to get the web message as a string.
   * This method is failed if the message is not a string. (ex: JSON)
   * @returns The web message as a string, or null if it could not be retrieved.
   */
  public TryGetWebMessageAsString(): string | null {
    const size = new BigUint64Array(1);
    const hresult = this.libs.symbols
      .MessageReceivedEventArgs_TryGetWebMessageAsString(
        this.args,
        null,
        Deno.UnsafePointer.of(size),
      );
    console.log(size[0]);
    if (hresult !== 0) {
      throw new Error(`Failed to get StringMessage: ${hresult}`);
    }
    if (size[0] === 0n) {
      return null;
    }

    const buffer = new Uint16Array(Number(size[0]));
    const hresult2 = this.libs.symbols
      .MessageReceivedEventArgs_get_WebMessageAsJson(
        this.args,
        Deno.UnsafePointer.of(buffer),
        null,
      );
    if (hresult2 !== 0) {
      throw new Error(`Failed to get WebMessageAsJson: ${hresult2}`);
    }

    return String.fromCharCode.apply(null, Array.from(buffer.subarray(1, -1)));
  }
}
