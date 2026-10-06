import type { Webview2Funcs } from '../webview2_types.ts';
import { getBool } from '../libs/convert.ts';

/** Borrowed callback arguments. Access only on the owning STA during the callback. */
export class SourceChangedEventArgs {
  /** Wrap a native WebView2 object or event using its DLL and pointer. */
  constructor(
    private libs: Webview2Funcs,
    public readonly pointer: Deno.PointerValue,
  ) {}
  /** Whether the source changed to a new document. */
  public get IsNewDocument(): boolean {
    return getBool(
      this.pointer,
      this.libs.symbols.SourceChangedEventArgs_get_IsNewDocument,
    );
  }
}
