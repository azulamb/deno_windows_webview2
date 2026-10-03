import type { Webview2Funcs } from '../webview2_types.ts';
import { DoublePointer } from './DoublePointer.ts';

/** Owns one COM reference. Use on the apartment that owns the object. */
export class ComPointer extends DoublePointer {
  private disposed: boolean = false;
  constructor(protected libs: Webview2Funcs) {
    super();
  }
  public close(): void {
    if (this.disposed) return;
    const pointer = this.getPointer();
    if (pointer) this.libs.symbols.COM_Release(pointer);
    this.setPointer(null);
    this.disposed = true;
  }
  public override getPointer<T>(): Deno.PointerValue<T> {
    if (this.disposed) throw new Error('COM object is closed.');
    return super.getPointer<T>();
  }
  public override getDoublePointer(): Deno.PointerValue {
    if (this.disposed) throw new Error('COM object is closed.');
    return super.getDoublePointer();
  }
}
