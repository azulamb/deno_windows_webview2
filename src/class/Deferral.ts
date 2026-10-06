import type { HRESULT } from '../libs/winapi.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import { ComPointer } from './ComPointer.ts';

/** Owned COM deferral that delays completion of a native event. */
export class Deferral extends ComPointer {
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    libs: Webview2Funcs,
    pointer?: Deno.PointerValue,
  ) {
    super(libs);
    if (pointer) {
      this.setPointer(pointer);
    }
  }

  /** Finish deferred event processing and return the native HRESULT. */
  public complete(): HRESULT {
    return this.libs.symbols.Deferral_Complete(this.getPointer());
  }
}
