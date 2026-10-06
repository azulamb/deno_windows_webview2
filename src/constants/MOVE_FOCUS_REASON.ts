// TODO: edit WebResourceRequestedEventArgs.ts
/** Reasons for moving focus into WebView2: programmatic, next or previous control. */
export const MOVE_FOCUS_REASON = {
  PROGRAMMATIC: 0,
  NEXT: 1,
  PREVIOUS: 2,
} as const;
/** Names of focus movement reasons in MOVE_FOCUS_REASON. */
export type MOVE_FOCUS_REASON_TYPES =
  typeof MOVE_FOCUS_REASON[keyof typeof MOVE_FOCUS_REASON];
