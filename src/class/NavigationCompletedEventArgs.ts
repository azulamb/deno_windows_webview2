import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool } from '../libs/convert.ts';

/** Borrowed event arguments; valid during the callback. Retain a COM reference and use a deferral for asynchronous work. */
export class NavigationCompletedEventArgs {
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  public get IsSuccess(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NavigationCompletedEventArgs_get_IsSuccess,
    );
  }
  public get WebErrorStatus(): number {
    const value = new Int32Array(1);
    const result = this.libs.symbols
      .NavigationCompletedEventArgs_get_WebErrorStatus(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) {
      throw new Error(
        'NavigationCompletedEventArgs_get_WebErrorStatus failed: ' + result,
      );
    }
    return value[0];
  }
  public get NavigationId(): bigint {
    const value = new BigUint64Array(1);
    const result = this.libs.symbols
      .NavigationCompletedEventArgs_get_NavigationId(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) {
      throw new Error(
        'NavigationCompletedEventArgs_get_NavigationId failed: ' + result,
      );
    }
    return value[0];
  }
}
