/**
 * Converts a buffer of UTF-16 encoded characters to a JS string.
 * @param buffer The buffer containing UTF-16 encoded characters.
 * @returns The converted JS string.
 */
export function utf16BufferToString(buffer: Uint16Array): string {
  return String.fromCharCode.apply(null, Array.from(buffer.subarray(0, -1)));
}
