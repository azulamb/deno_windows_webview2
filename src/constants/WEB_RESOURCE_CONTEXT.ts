// TODO: edit WebResourceRequestedEventArgs.ts
/** WebView2 resource category flags for request filters. */
export const WEB_RESOURCE_CONTEXT = {
  ALL: 0,
  DOCUMENT: 1,
  STYLESHEET: 2,
  IMAGE: 3,
  MEDIA: 4,
  FONT: 5,
  SCRIPT: 6,
  XML_HTTP_REQUEST: 7,
  FETCH: 8,
  TEXT_TRACK: 9,
  EVENT_SOURCE: 10,
  WEBSOCKET: 11,
  MANIFEST: 12,
  SIGNED_EXCHANGE: 13,
  PING: 14,
  CSP_VIOLATION_REPORT: 15,
  OTHER: 16,
} as const;
/** Names of resource categories in WEB_RESOURCE_CONTEXT. */
export type WEB_RESOURCE_CONTEXT_TYPES =
  typeof WEB_RESOURCE_CONTEXT[keyof typeof WEB_RESOURCE_CONTEXT];
