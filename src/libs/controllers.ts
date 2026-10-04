import type { MOVE_FOCUS_REASON_TYPES } from '../constants/MOVE_FOCUS_REASON.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import type { Webview2Context } from './types.ts';
import type { HRESULT, Rect } from './winapi.ts';

/** WebView2 background channels. Alpha supports only 0 (transparent) or 255 (opaque). */
export interface BackgroundColor {
  alpha: 0 | 255;
  red: number;
  green: number;
  blue: number;
}

export class Controllers {
  public get defaultBackgroundColor(): BackgroundColor {
    const bytes = new Uint8Array(4);
    const result = this.libs.symbols.Controllers_get_DefaultBackgroundColor(
      this.controllers,
      Deno.UnsafePointer.of(bytes),
    );
    if (result < 0) throw new Error(`Get background color failed: ${result}`);
    return {
      alpha: bytes[0] as 0 | 255,
      red: bytes[1],
      green: bytes[2],
      blue: bytes[3],
    };
  }
  public set defaultBackgroundColor(color: BackgroundColor) {
    if (
      (color.alpha !== 0 && color.alpha !== 255) ||
      ![color.red, color.green, color.blue].every((value) =>
        Number.isInteger(value) && value >= 0 && value <= 255
      )
    ) {
      throw new TypeError('Invalid background color channels.');
    }
    const bytes = new Uint8Array([
      color.alpha,
      color.red,
      color.green,
      color.blue,
    ]);
    const result = this.libs.symbols.Controllers_put_DefaultBackgroundColor(
      this.controllers,
      new DataView(bytes.buffer).getUint32(0, true),
    );
    if (result < 0) throw new Error(`Set background color failed: ${result}`);
  }
  protected controllers!: Deno.PointerValue<unknown>;

  public get pointer(): Deno.PointerValue<unknown> {
    return this.controllers;
  }

  protected get libs(): Webview2Funcs {
    return this.context.lib;
  }

  constructor(
    protected context: Webview2Context,
    controllers?: Deno.PointerValue<unknown>,
  ) {
    this.controllers = controllers ?? context.lib.symbols.Controllers_Create();
  }

  /*readonly add_AcceleratorKeyPressed: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_AcceleratorKeyPressed: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_Bounds: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };*/

  /**
   * Sets the bounds of the WebView2 control.
   * @param bounds The new bounds for the control.
   */
  public set bounds(bounds: Rect) {
    this.libs.symbols.Controllers_put_Bounds(this.controllers, bounds.data);
  }

  public close(): HRESULT {
    return this.libs.symbols.Controllers_Close(this.controllers);
  }

  /*
  readonly add_GotFocus: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_GotFocus: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_IsVisible: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_IsVisible: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly add_LostFocus: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_LostFocus: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };*/

  /**
   * Focus and set the reason.
   * @param reason The reason for moving focus.
   */
  public set moveFocus(reason: MOVE_FOCUS_REASON_TYPES) {
    this.libs.symbols.Controllers_MoveFocus(this.controllers, reason);
  }

  /*readonly add_MoveFocusRequested: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_MoveFocusRequested: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly NotifyParentWindowPositionChanged: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };
  readonly get_ParentWindow: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_ParentWindow: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly SetBoundsAndZoomFactor: {
    readonly parameters: ['pointer', 'buffer', 'f64'];
    readonly result: 'i32';
  };
  readonly get_ZoomFactor: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_ZoomFactor: {
    readonly parameters: ['pointer', 'f64'];
    readonly result: 'i32';
  };
  readonly add_ZoomFactorChanged: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_ZoomFactorChanged: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_DefaultBackgroundColor: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_DefaultBackgroundColor: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly add_RasterizationScaleChanged: {
    readonly parameters: ['pointer', 'function', 'pointer'];
    readonly result: 'i32';
  };
  readonly remove_RasterizationScaleChanged: {
    readonly parameters: ['pointer', 'buffer'];
    readonly result: 'i32';
  };
  readonly get_BoundsMode: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_BoundsMode: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly get_RasterizationScale: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_RasterizationScale: {
    readonly parameters: ['pointer', 'f64'];
    readonly result: 'i32';
  };
  readonly get_ShouldDetectMonitorScaleChanges: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_ShouldDetectMonitorScaleChanges: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly get_AllowExternalDrop: {
    readonly parameters: ['pointer', 'pointer'];
    readonly result: 'i32';
  };
  readonly put_AllowExternalDrop: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };*/
}
