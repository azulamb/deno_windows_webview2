import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool } from '../libs/convert.ts';

/** Borrowed callback arguments. Access only on the owning STA during the callback. */
export class AcceleratorKeyPressedEventArgs {
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  /** Native key event category: key-down, key-up or system key event. */
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
  /** Windows virtual-key code for the pressed or released key. */
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
  /** Packed Windows keyboard message lParam value. */
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
  /** Whether the host consumes the event instead of WebView2. Set during the event callback. */
  public get Handled(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.AcceleratorKeyPressedEventArgs_get_Handled,
    );
  }
  /** Mark the event as handled by the host during its callback. */
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
  /** Decoded repeat count, scan code and modifier state. */
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
/** Keyboard state decoded from WebView2's physical key status structure. */
export interface PhysicalKeyStatus {
  /** Number of key repetitions represented by the event. */
  RepeatCount: number;
  /** Hardware scan code for the key. */
  ScanCode: number;
  /** Whether this is an extended key. */
  IsExtendedKey: boolean;
  /** Whether Alt was held when the event occurred. */
  IsMenuKeyDown: boolean;
  /** Whether the key was already pressed before this event. */
  WasKeyDown: boolean;
  /** Whether the event releases the key. */
  IsKeyReleased: boolean;
}
