export class DoublePointer {
  protected rawPointer: BigUint64Array = BigUint64Array.from([0n]);
  protected pointer = Deno.UnsafePointer.of(this.rawPointer);

  /**
   * Gets the double pointer.
   * @returns The double pointer.
   */
  public getDoublePointer(): Deno.PointerValue {
    return this.pointer;
  }

  /**
   * Gets the pointer.
   * @returns The pointer.
   */
  public getPointer<T>(): Deno.PointerValue<T> {
    return Deno.UnsafePointer.create(this.rawPointer[0]);
  }

  public setPointer(pointer: Deno.PointerValue): void {
    if (pointer) {
      this.rawPointer[0] = Deno.UnsafePointer.value(pointer);
    } else {
      this.rawPointer[0] = 0n;
    }
  }
}
