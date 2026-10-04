import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool, getString } from '../libs/convert.ts';
import { Deferral } from './Deferral.ts';

/** Borrowed event arguments; valid during the callback. Retain a COM reference and use a deferral for asynchronous work. */
export class NewWindowRequestedEventArgs {
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  public get Uri(): string {
    return getString(
      this.pointer,
      this.libs.symbols.NewWindowRequestedEventArgs_get_Uri,
    );
  }
  public get IsUserInitiated(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NewWindowRequestedEventArgs_get_IsUserInitiated,
    );
  }
  public get Handled(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.NewWindowRequestedEventArgs_get_Handled,
    );
  }
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
