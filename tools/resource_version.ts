/** Updates Windows version resource fields while preserving UTF-16 or UTF-8 encoding. */
export function updateVersionResource(
  bytes: Uint8Array,
  version: string,
): Uint8Array {
  const utf16 = bytes[0] === 0xFF && bytes[1] === 0xFE;
  const text = new TextDecoder(utf16 ? 'utf-16le' : 'utf-8', { fatal: true })
    .decode(bytes);
  if (!/^\d+\.\d+\.\d+\.\d+$/.test(version)) {
    throw new TypeError('DLL version must have four numeric components.');
  }
  const updated = text.replace(
    /(FILEVERSION|PRODUCTVERSION)\s+\d+,\d+,\d+,\d+/g,
    (_match, key) => `${key} ${version.replaceAll('.', ',')}`,
  )
    .replace(
      /(VALUE "(?:FileVersion|ProductVersion)", ")[^"]+("?)/g,
      (_match, prefix, suffix) => `${prefix}${version}${suffix}`,
    );
  if (!utf16) {
    return new TextEncoder().encode(
      (bytes[0] === 0xEF ? '\uFEFF' : '') + updated,
    );
  }
  const output = new Uint8Array((updated.length + 1) * 2);
  const view = new DataView(output.buffer);
  view.setUint16(0, 0xFEFF, true);
  for (let index = 0; index < updated.length; ++index) {
    view.setUint16((index + 1) * 2, updated.charCodeAt(index), true);
  }
  return output;
}
