import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool } from '../libs/convert.ts';

/** Borrowed callback arguments. Access only on the owning STA during the callback. */
export class SourceChangedEventArgs {
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  public get IsNewDocument(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.SourceChangedEventArgs_get_IsNewDocument,
    );
  }
}
