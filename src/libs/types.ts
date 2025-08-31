import type { Webview2Funcs } from '../webview2_types.ts';
import type { EventRegistrationToken } from '../webview2_types.ts';

export interface TokenManager<T> {
  create(): T;
  remove(token: T): void;
}

export interface Webview2Context {
  readonly lib: Webview2Funcs;
  readonly eventRegistrationToken: TokenManager<EventRegistrationToken>;
}
