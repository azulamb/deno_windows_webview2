import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool, getString } from '../libs/convert.ts';

/** Borrowed event arguments; valid during the callback. Retain a COM reference and use a deferral for asynchronous work. */
export class NavigationStartingEventArgs {
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  /** URI of the resource or navigation. */
  public get Uri(): string {
    return getString(
      this.pointer,
      this.libs.symbols.NavigationStartingEventArgs_get_Uri,
    );
  }
  /** Whether WebView2 reports a user-initiated action. */
  public get IsUserInitiated(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NavigationStartingEventArgs_get_IsUserInitiated,
    );
  }
  /** Whether this navigation is an HTTP redirect. */
  public get IsRedirected(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NavigationStartingEventArgs_get_IsRedirected,
    );
  }
  /** Whether to cancel this navigation. Set during the navigation-starting callback. */
  public get Cancel(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NavigationStartingEventArgs_get_Cancel,
    );
  }
  /** Cancel or allow the pending navigation during its callback. */
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
  /** Identifier shared by related navigation-starting and completed events. */
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
