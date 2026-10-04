import type { Webview2Funcs } from '../webview2_types.ts';
import type { Webview2Context } from './types.ts';
import type { HRESULT, LPVOID } from './winapi.ts';

export class Environments {
  protected environments!: Deno.PointerValue<unknown>;

  public get pointer(): Deno.PointerValue<unknown> {
    return this.environments;
  }

  protected get libs(): Webview2Funcs {
    return this.context.lib;
  }

  constructor(
    protected context: Webview2Context,
    environments?: Deno.PointerValue<unknown>,
  ) {
    this.environments = environments ??
      context.lib.symbols.Environments_Create();
  }

  /**
   * Creates a CoreWebView2Environment.
   * @param callback The callback to invoke when the operation completes.
   * @returns The HRESULT of the operation.
   */
  public create(
    callback: (result: HRESULT, env: LPVOID) => HRESULT, // HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
  ): HRESULT {
    const func = this.context.completions.create(callback);
    const result = this.libs.symbols.Global_CreateCoreWebView2Environment(
      this.environments,
      func.pointer,
    );
    if (result < 0) this.context.completions.cancel(func);
    return result;
  }
}
