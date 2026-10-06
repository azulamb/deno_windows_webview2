import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool, getString } from '../libs/convert.ts';
import { Deferral } from './Deferral.ts';

/** Borrowed event arguments; valid during the callback. Retain a COM reference and use a deferral for asynchronous work. */
export class PermissionRequestedEventArgs {
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  /** URI of the resource or navigation. */
  public get Uri(): string {
    return getString(
      this.pointer,
      this.libs.symbols.PermissionRequestedEventArgs_get_Uri,
    );
  }
  /** Numeric permission category requested by the document. */
  public get PermissionKind(): number {
    const value = new Int32Array(1);
    const result = this.libs.symbols
      .PermissionRequestedEventArgs_get_PermissionKind(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) {
      throw new Error(
        'PermissionRequestedEventArgs_get_PermissionKind failed: ' + result,
      );
    }
    return value[0];
  }
  /** Whether WebView2 reports a user-initiated action. */
  public get IsUserInitiated(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.PermissionRequestedEventArgs_get_IsUserInitiated,
    );
  }
  /** Permission decision: 0 is default, 1 allows and 2 denies. */
  public get State(): number {
    const value = new Int32Array(1);
    const result = this.libs.symbols.PermissionRequestedEventArgs_get_State(
      this.pointer,
      Deno.UnsafePointer.of(value),
    );
    if (result < 0) {
      throw new Error(
        'PermissionRequestedEventArgs_get_State failed: ' + result,
      );
    }
    return value[0];
  }
  /** Set the permission decision: default (0), allow (1) or deny (2). */
  public set State(value: number) {
    const result = this.libs.symbols.PermissionRequestedEventArgs_put_State(
      this.pointer,
      value,
    );
    if (result < 0) {
      throw new Error(
        'PermissionRequestedEventArgs_put_State failed: ' + result,
      );
    }
  }
  /** Defer event processing. Complete and close the returned deferral after asynchronous work. */
  public getDeferral(): Deferral {
    const value = new Deferral(this.libs);
    const result = this.libs.symbols.PermissionRequestedEventArgs_GetDeferral(
      this.pointer,
      value.getDoublePointer(),
    );
    if (result < 0) {
      value.close();
      throw new Error(
        'PermissionRequestedEventArgs_GetDeferral failed: ' + result,
      );
    }
    return value;
  }
}
