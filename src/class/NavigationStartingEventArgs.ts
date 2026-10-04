import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool, getString } from '../libs/convert.ts';

/** Borrowed event arguments; valid during the callback. Retain a COM reference and use a deferral for asynchronous work. */
export class NavigationStartingEventArgs {
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  public get Uri(): string {
    return getString(
      this.pointer,
      this.libs.symbols.NavigationStartingEventArgs_get_Uri,
    );
  }
  public get IsUserInitiated(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NavigationStartingEventArgs_get_IsUserInitiated,
    );
  }
  public get IsRedirected(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NavigationStartingEventArgs_get_IsRedirected,
    );
  }
  public get Cancel(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NavigationStartingEventArgs_get_Cancel,
    );
  }
  public set Cancel(value: boolean) {
    const result = this.libs.symbols.NavigationStartingEventArgs_put_Cancel(
      this.pointer,
      Number(value),
    );
    if (result < 0) {
      throw new Error(
        'NavigationStartingEventArgs_put_Cancel failed: ' + result,
      );
    }
  }
  public get NavigationId(): bigint {
    const value = new BigUint64Array(1);
    const result = this.libs.symbols
      .NavigationStartingEventArgs_get_NavigationId(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) {
      throw new Error(
        'NavigationStartingEventArgs_get_NavigationId failed: ' + result,
      );
    }
    return value[0];
  }
}
