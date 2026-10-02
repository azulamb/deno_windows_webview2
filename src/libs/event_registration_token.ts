import type { EventRegistrationToken as Token } from '../webview2_types.ts';
import type { Webview2Context } from './types.ts';

export class EventRegistrationToken {
  constructor(protected context: Webview2Context) {
  }

  /**
   * Creates an event registration token.
   * @returns The event registration token.
   */
  public create(): Token {
    return this.context.lib.symbols.EventRegistrationToken_Create();
  }

  /**
   * Removes an event registration token.
   * @param token The event registration token to remove.
   */
  public remove(token: Token): void {
    this.context.lib.symbols.EventRegistrationToken_Remove(token);
  }
}
