const definition = { parameters: ['i32', 'pointer'], result: 'i32' } as const;
type Completion = Deno.UnsafeCallback<typeof definition>;

/** Keeps completion callbacks and their buffers alive until native completion. */
export class CompletionCallbacks {
  private pending: Map<Completion, unknown[]> = new Map();
  private closing: boolean = false;
  private idle?: () => void;
  public create(
    callback: (result: number, pointer: Deno.PointerValue) => number,
    keepAlive: unknown[] = [],
  ): Completion {
    if (this.closing) throw new Error('WebView2 is closing.');
    const fn: Completion = new Deno.UnsafeCallback(
      definition,
      (result, pointer) => {
        try {
          return this.closing ? 0 : callback(result, pointer);
        } catch (error) {
          console.error(error);
          return -2147467259; // E_FAIL
        } finally {
          queueMicrotask(() => this.cancel(fn));
        }
      },
    );
    // Strong ownership is explicit; it does not depend on closure optimization.
    this.pending.set(fn, keepAlive);
    return fn;
  }
  public cancel(fn: Completion): void {
    if (!this.pending.delete(fn)) return;
    fn.close();
    if (this.closing && this.pending.size === 0) this.idle?.();
  }
  public beginClose(): void {
    this.closing = true;
  }
  public close(whenIdle: () => void): void {
    this.closing = true;
    this.idle = whenIdle;
    if (this.pending.size === 0) whenIdle();
  }
}
