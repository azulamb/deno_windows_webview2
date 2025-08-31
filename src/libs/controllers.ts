import type { Webview2Context } from './types.ts';
import type { Rect } from './winapi.ts';

export class Controllers {
  protected controllers!: Deno.PointerValue<unknown>;

  public get pointer(): Deno.PointerValue<unknown> {
    return this.controllers;
  }

  protected get symbols() {
    return this.context.lib.symbols;
  }

  constructor(protected context: Webview2Context) {
    this.controllers = context.lib.symbols.CreateControllers();
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
    this.symbols.put_Bounds(this.controllers, bounds.data);
  }

  /*readonly Close: {
    readonly parameters: ['pointer'];
    readonly result: 'i32';
  };

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
  };
  readonly MoveFocus: {
    readonly parameters: ['pointer', 'i32'];
    readonly result: 'i32';
  };
  readonly add_MoveFocusRequested: {
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
