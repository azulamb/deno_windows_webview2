import type { HRESULT } from '../libs/winapi.ts';
import type { Webview2Funcs } from '../webview2_types.ts';
import { ComPointer } from './ComPointer.ts';

export class Deferral extends ComPointer {
  constructor(
    libs: Webview2Funcs,
    pointer?: Deno.PointerValue,
  ) {
    super(libs);
    if (pointer) {
      this.setPointer(pointer);
    }
  }

  public complete(): HRESULT {
    return this.libs.symbols.Deferral_Complete(this.getPointer());
  }
}
