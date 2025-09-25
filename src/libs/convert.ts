/**
 * Converts a buffer of UTF-16 encoded characters to a JS string.
 * @param buffer The buffer containing UTF-16 encoded characters.
 * @returns The converted JS string.
 */
export function utf16BufferToString(buffer: Uint16Array): string {
  return String.fromCharCode.apply(null, Array.from(buffer.subarray(0, -1)));
}

/**
 * Converts a pointer to a UTF-16 encoded string to a JS string.
 * @param pointer The pointer to the UTF-16 encoded string.
 * @returns The converted JS string.
 */
export function utf16PointerToString(
  pointer: Deno.PointerValue,
): string {
  if (!pointer) {
    return '';
  }
  // TODO: Wcharに対応してないのでなんとかする。
  return Deno.UnsafePointerView.getCString(pointer);
}

/**
 * Creates a pointer to a UTF-16 encoded string.
 * @param value The string to convert to a pointer.
 * @returns A pointer to the UTF-16 encoded string.
 */
export function createStringPointer(value: string) {
  const buffer = new Uint16Array(
    <number[]> [].map.call(value + '\0', (c: string) => {
      return c.charCodeAt(0);
    }),
  );
  return Deno.UnsafePointer.of(buffer);
}

/**
 * Gets a string from a pointer using a specified function.
 * @param pointer The pointer to the string.
 * @param func The function to call to get the string.
 * @returns The retrieved string.
 */
export function getString(
  pointer: Deno.PointerValue,
  func: (
    pointer: Deno.PointerValue,
    buffer: Deno.PointerValue,
    size: Deno.PointerValue,
  ) => number,
): string {
  const size = new BigUint64Array(1);
  const hresult = func(
    pointer,
    null,
    Deno.UnsafePointer.of(size),
  );

  if (hresult !== 0) {
    throw new Error();
  }
  if (size[0] === 0n) {
    return '';
  }

  const buffer = new Uint16Array(Number(size[0]));
  const hresult2 = func(
    pointer,
    Deno.UnsafePointer.of(buffer),
    null,
  );
  if (hresult2 !== 0) {
    throw new Error();
  }

  return utf16BufferToString(buffer);
}

export function getWString(pointer: Deno.PointerValue): string {
  if (!pointer) {
    return '';
  }
  let size = 0;
  while (true) {
    const view = Deno.UnsafePointerView.getArrayBuffer(pointer, 1024);
  }
}

/**
 * Gets a boolean value from a WebView2 function.
 * @param connector The pointer to the WebView2 function.
 * @param func The function to call to get the boolean value.
 * @returns The retrieved boolean value.
 */
export function getBool(
  connector: Deno.PointerValue,
  func: (
    connector: Deno.PointerValue,
    bool: Deno.PointerValue,
  ) => unknown,
): boolean {
  const data = new Int32Array([0]);
  const bool = Deno.UnsafePointer.of(data);
  func(connector, bool);
  return data[0] !== 0;
}
