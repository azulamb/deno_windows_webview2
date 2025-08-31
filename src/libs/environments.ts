import type { Webview2Context } from './types.ts';
import type { HRESULT, LPVOID } from './winapi.ts';

export class Environments {
  protected environments!: Deno.PointerValue<unknown>;

  public get pointer(): Deno.PointerValue<unknown> {
    return this.environments;
  }

  protected get symbols() {
    return this.context.lib.symbols;
  }

  constructor(protected context: Webview2Context) {
    this.environments = context.lib.symbols.CreateEnvironments();
  }

  /**
   * Creates a CoreWebView2Environment.
   * @param callback The callback to invoke when the operation completes.
   * @returns The HRESULT of the operation.
   */
  public create(
    callback: (result: HRESULT, env: LPVOID) => HRESULT, // HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
  ): HRESULT {
    const func = new Deno.UnsafeCallback(
      {
        parameters: [
          'i32', // HRESULT
          'pointer', // LPVOID
        ],
        result: 'i32', // HRESULT
      },
      callback,
    );
    return this.symbols.CreateCoreWebView2Environment(
      this.environments,
      func.pointer,
    );
  }
}
