import {
  createStringBuffer,
  getWString,
  utf16BufferToString,
  utf16PointerToString,
} from '../src/libs/convert.ts';
import { copyAtomic } from '../tools/copy_file.ts';
import { CompletionCallbacks } from '../src/libs/completion_callbacks.ts';
import { toFileUrl } from '@std/path';

function equal(actual: unknown, expected: unknown): void {
  if (JSON.stringify(actual) !== JSON.stringify(expected)) {
    throw new Error(
      `Expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`,
    );
  }
}
Deno.test('UTF-16 conversion preserves Japanese, surrogate pairs and NUL termination', () => {
  const buffer = createStringBuffer('日本語😀');
  const pointer = Deno.UnsafePointer.of(buffer);
  equal(getWString(pointer), '日本語😀');
  equal(utf16PointerToString(pointer), '日本語😀');
  equal(utf16BufferToString(buffer), '日本語😀');
  equal(utf16BufferToString(new Uint16Array([65, 0, 66])), 'A');
  equal(utf16BufferToString(new Uint16Array([65, 66])), 'AB');
  equal(getWString(null), '');
});
Deno.test('completion shutdown waits for native completion and suppresses user callbacks', async () => {
  const manager = new CompletionCallbacks();
  let called = false, closed = false;
  const fn = manager.create(() => {
    called = true;
    return 0;
  });
  manager.close(() => {
    closed = true;
  });
  equal(closed, false);
  const native = new Deno.UnsafeFnPointer(fn.pointer, {
    parameters: ['i32', 'pointer'],
    result: 'i32',
  });
  equal(native.call(0, null), 0);
  equal(called, false);
  await Promise.resolve();
  equal(closed, true);
});
Deno.test('failed completion registration closes immediately', () => {
  const manager = new CompletionCallbacks();
  const fn = manager.create(() => 0);
  manager.cancel(fn);
  let closed = false;
  manager.close(() => {
    closed = true;
  });
  equal(closed, true);
});
Deno.test('DLL copy replaces a longer file and preserves it when a source fails', async () => {
  const directory = await Deno.makeTempDir();
  try {
    const source = `${directory}/source.dll`,
      destination = `${directory}/日本語 folder/output.dll`;
    await Deno.writeFile(source, new Uint8Array([1, 2, 3, 4]));
    await copyAtomic(destination, toFileUrl(source));
    await Deno.writeFile(source, new Uint8Array([9]));
    await copyAtomic(destination, toFileUrl(source));
    equal([...await Deno.readFile(destination)], [9]);
    let failed = false;
    try {
      await copyAtomic(destination, toFileUrl(`${directory}/missing.dll`));
    } catch {
      failed = true;
    }
    equal(failed, true);
    equal([...await Deno.readFile(destination)], [9]);
    equal(
      [...Deno.readDirSync(`${directory}/日本語 folder`)].map((entry) =>
        entry.name
      ),
      ['output.dll'],
    );
  } finally {
    await Deno.remove(directory, { recursive: true });
  }
});
