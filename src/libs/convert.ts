/**
 * Converts a buffer of UTF-16 encoded characters to a JS string.
 * @param buffer The buffer containing UTF-16 encoded characters.
 * @returns The converted JS string.
 */
export function utf16BufferToString(buffer: Uint16Array): string {
  const nul = buffer.indexOf(0);
  const end = nul < 0 ? buffer.length : nul;
  let result = '';
  for (let offset = 0; offset < end; offset += 4096) {
    result += String.fromCharCode(
      ...buffer.subarray(offset, Math.min(end, offset + 4096)),
    );
  }
  return result;
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
  return getWString(pointer);
}

/**
 * Creates a pointer to a UTF-16 encoded string.
 * @param value The string to convert to a pointer.
 * @returns A pointer to the UTF-16 encoded string.
 */
export function createStringBuffer(value: string): Uint16Array<ArrayBuffer> {
  const buffer = new Uint16Array(value.length + 1);
  for (let i = 0; i < value.length; ++i) buffer[i] = value.charCodeAt(i);
  return buffer;
}

export function createStringPointer(value: string): Deno.PointerValue {
  return Deno.UnsafePointer.of(createStringBuffer(value));
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
  const view = new Deno.UnsafePointerView(pointer);
  let result = '';
  for (let offset = 0;; offset += 2) {
    const code = view.getUint16(offset);
    if (code === 0) {
      return result;
    }
    result += String.fromCharCode(code);
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
  ) => number,
): boolean {
  const data = new Int32Array([0]);
  const bool = Deno.UnsafePointer.of(data);
  const result = func(connector, bool);
  if (result < 0) throw new Error(`Boolean getter failed: ${result}`);
  return data[0] !== 0;
}
