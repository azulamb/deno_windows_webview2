/** Bit flags selecting which document/Worker resource requests are intercepted. */
export enum WebResourceRequestSourceKinds {
  None = 0,
  Document = 1,
  SharedWorker = 2,
  ServiceWorker = 4,
  All = 7,
}
