import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool } from '../libs/convert.ts';

/** Borrowed callback arguments. Access only on the owning STA during the callback. */
export class AcceleratorKeyPressedEventArgs {
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  public get KeyEventKind(): number {
    const value = new Int32Array(1);
    const result = this.libs.symbols
      .AcceleratorKeyPressedEventArgs_get_KeyEventKind(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) {
      throw new Error(
        'AcceleratorKeyPressedEventArgs_get_KeyEventKind failed: ' + result,
      );
    }
    return value[0];
  }
  public get VirtualKey(): number {
    const value = new Uint32Array(1);
    const result = this.libs.symbols
      .AcceleratorKeyPressedEventArgs_get_VirtualKey(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) {
      throw new Error(
        'AcceleratorKeyPressedEventArgs_get_VirtualKey failed: ' + result,
      );
    }
    return value[0];
  }
  public get KeyEventLParam(): number {
    const value = new Int32Array(1);
    const result = this.libs.symbols
      .AcceleratorKeyPressedEventArgs_get_KeyEventLParam(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) {
      throw new Error(
        'AcceleratorKeyPressedEventArgs_get_KeyEventLParam failed: ' + result,
      );
    }
    return value[0];
  }
  public get Handled(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.AcceleratorKeyPressedEventArgs_get_Handled,
    );
  }
  public set Handled(value: boolean) {
    const result = this.libs.symbols.AcceleratorKeyPressedEventArgs_put_Handled(
      this.pointer,
      Number(value),
    );
    if (result < 0) {
      throw new Error(
        'AcceleratorKeyPressedEventArgs_put_Handled failed: ' + result,
      );
    }
  }
  public get PhysicalKeyStatus(): PhysicalKeyStatus {
    const value = new Uint32Array(6);
    const result = this.libs.symbols
      .AcceleratorKeyPressedEventArgs_get_PhysicalKeyStatus(
        this.pointer,
        Deno.UnsafePointer.of(value),
      );
    if (result < 0) throw new Error('PhysicalKeyStatus failed: ' + result);
    return {
      RepeatCount: value[0],
      ScanCode: value[1],
      IsExtendedKey: value[2] !== 0,
      IsMenuKeyDown: value[3] !== 0,
      WasKeyDown: value[4] !== 0,
      IsKeyReleased: value[5] !== 0,
    };
  }
}
export interface PhysicalKeyStatus {
  RepeatCount: number;
  ScanCode: number;
  IsExtendedKey: boolean;
  IsMenuKeyDown: boolean;
  WasKeyDown: boolean;
  IsKeyReleased: boolean;
}
