import type { Webview2Funcs } from '../webview2_types.ts';

/** Borrowed callback arguments. Access only on the owning STA during the callback. */
export class ProcessFailedEventArgs {
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  /** Numeric WebView2 process failure category. */
  public get ProcessFailedKind(): number {
    const value = new Int32Array(1);
    const result = this.libs.symbols
      .ProcessFailedEventArgs_get_ProcessFailedKind(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) {
      throw new Error(
        'ProcessFailedEventArgs_get_ProcessFailedKind failed: ' + result,
      );
    }
    return value[0];
  }
}
