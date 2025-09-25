import type { HRESULT } from '../libs/winapi.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import { DoublePointer } from './DoublePointer.ts';

export class Deferral extends DoublePointer {
  constructor(
    protected libs: Webview2Funcs,
    pointer?: Deno.PointerValue,
  ) {
    super();
    if (pointer) {
      this.setPointer(pointer);
    }
  }

  public complete(): HRESULT {
    return this.libs.symbols.Deferral_Complete(this.getPointer());
  }
}
