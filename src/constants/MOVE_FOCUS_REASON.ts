// TODO: edit WebResourceRequestedEventArgs.ts
export const MOVE_FOCUS_REASON = {
  PROGRAMMATIC: 0,
  NEXT: 1,
  PREVIOUS: 2,
} as const;
export type MOVE_FOCUS_REASON_TYPES =
  typeof MOVE_FOCUS_REASON[keyof typeof MOVE_FOCUS_REASON];
