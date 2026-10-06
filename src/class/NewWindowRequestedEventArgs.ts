import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool, getString } from '../libs/convert.ts';
import { Deferral } from './Deferral.ts';

/** Borrowed event arguments; valid during the callback. Retain a COM reference and use a deferral for asynchronous work. */
export class NewWindowRequestedEventArgs {
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  /** URI of the resource or navigation. */
  public get Uri(): string {
    return getString(
      this.pointer,
      this.libs.symbols.NewWindowRequestedEventArgs_get_Uri,
    );
  }
  /** Whether WebView2 reports a user-initiated action. */
  public get IsUserInitiated(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NewWindowRequestedEventArgs_get_IsUserInitiated,
    );
  }
  /** Whether the host consumes the event instead of WebView2. Set during the event callback. */
  public get Handled(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NewWindowRequestedEventArgs_get_Handled,
    );
  }
  /** Mark the event as handled by the host during its callback. */
  public set Handled(value: boolean) {
    const result = this.libs.symbols.NewWindowRequestedEventArgs_put_Handled(
      this.pointer,
      Number(value),
    );
    if (result < 0) {
      throw new Error(
        'NewWindowRequestedEventArgs_put_Handled failed: ' + result,
      );
    }
  }
  /** Defer event processing. Complete and close the returned deferral after asynchronous work. */
  public getDeferral(): Deferral {
    const value = new Deferral(this.libs);
    const result = this.libs.symbols.NewWindowRequestedEventArgs_GetDeferral(
      this.pointer,
      value.getDoublePointer(),
    );
    if (result < 0) {
      value.close();
      throw new Error(
        'NewWindowRequestedEventArgs_GetDeferral failed: ' + result,
      );
    }
    return value;
  }
}
