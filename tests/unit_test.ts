import {
  createStringBuffer,
  getWString,
  utf16BufferToString,
  utf16PointerToString,
} from '../src/libs/convert.ts';
import { copyAtomic, dllVersion } from '../tools/copy_file.ts';
import { compile, createCompileCommand } from '../tools/compile.ts';
import { Dll } from '../src/version.ts';
import { updateVersionResource } from '../tools/resource_version.ts';
import { CompletionCallbacks } from '../src/libs/completion_callbacks.ts';
import { toFileUrl } from '@std/path';
import { catalogFromHeader, updateCoverage } from '../tools/report_data.ts';

Deno.test('report parses SDK interfaces and recomputes coverage without stale flags or comments', () => {
  const report = catalogFromHeader(
    `
    MIDL_INTERFACE("test") ICoreWebView2 : public IUnknown {
      virtual /* [propget] */ HRESULT STDMETHODCALLTYPE NavigateToString(LPCWSTR html) = 0;
      virtual HRESULT STDMETHODCALLTYPE Stop(void) = 0;
    };
    MIDL_INTERFACE("test2") ICoreWebView2_29 : public ICoreWebView2_28 {
      virtual HRESULT STDMETHODCALLTYPE NewMethod(void) = 0;
    };
  `,
    '1.0.4258.31',
  );
  report.list = report.list.filter((group) => group.class !== 'Globals');
  equal(report.list.map((group) => group.class), [
    'ICoreWebView2',
    'ICoreWebView2_29',
  ]);
  report.list[0].members[1].implemented = true;
  updateCoverage(report, [
    'EXPORT HRESULT WebView2_NavigateToString(WebView2* value) { return 0; }',
  ], [
    'libs.symbols.WebView2_NavigateToString(value); /* libs.symbols.WebView2_Stop(value); */',
  ]);
  equal(report.list[0].members, [
    { name: 'NavigateToString', defined: true, implemented: true },
    { name: 'Stop', defined: false, implemented: false },
  ]);
  equal(report.list[1].members[0].defined, false);
});

function equal(actual: unknown, expected: unknown): void {
  if (JSON.stringify(actual) !== JSON.stringify(expected)) {
    throw new Error(
      `Expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`,
    );
  }
}

Deno.test('DLL fixed version matches package version and mismatches preserve the destination', async () => {
  const source = new URL(
    '../webview2/x64/Release/webview2.dll',
    import.meta.url,
  );
  equal(dllVersion(await Deno.readFile(source)), Dll);
  const directory = await Deno.makeTempDir();
  try {
    const destination = `${directory}/output.dll`;
    await Deno.writeTextFile(destination, 'existing');
    let failed = false;
    try {
      await copyAtomic(destination, source, { expectedVersion: '999.0.0.0' });
    } catch {
      failed = true;
    }
    equal(failed, true);
    equal(await Deno.readTextFile(destination), 'existing');
  } finally {
    await Deno.remove(directory, { recursive: true });
  }
});
Deno.test('compile argument generation has no DLL writes or option mutations', async () => {
  const directory = await Deno.makeTempDir();
  try {
    const includes = ['assets'];
    const option = { dllPath: `${directory}/output.dll`, includes };
    const first = createCompileCommand('main.ts', 'app.exe', option);
    equal(createCompileCommand('main.ts', 'app.exe', option), first);
    equal(includes, ['assets']);
    equal([...Deno.readDirSync(directory)].length, 0);
  } finally {
    await Deno.remove(directory, { recursive: true });
  }
});
Deno.test('compile awaits DLL preparation and reports an unsuccessful process', async () => {
  const directory = await Deno.makeTempDir();
  try {
    const dllPath = `${directory}/webview2.dll`;
    const result = await compile(
      `${directory}/missing.ts`,
      `${directory}/app.exe`,
      [],
      { dllPath },
    );
    equal(result.success, false);
    equal(result.code !== 0, true);
    equal(dllVersion(await Deno.readFile(dllPath)), Dll);
  } finally {
    await Deno.remove(directory, { recursive: true });
  }
});
Deno.test('resource version generation preserves UTF-16 Japanese text and is idempotent', () => {
  const text =
    '// 日本語\r\nFILEVERSION 0,1,0,0\r\nPRODUCTVERSION 0,1,0,0\r\nVALUE "FileVersion", "0.1.0.0"\r\nVALUE "ProductVersion", "0.1.0.0"';
  const bytes = new Uint8Array((text.length + 1) * 2);
  const view = new DataView(bytes.buffer);
  view.setUint16(0, 0xFEFF, true);
  for (let index = 0; index < text.length; ++index) {
    view.setUint16((index + 1) * 2, text.charCodeAt(index), true);
  }
  const updated = updateVersionResource(bytes, '0.6.0.0');
  const decoded = new TextDecoder('utf-16le', { fatal: true }).decode(updated);
  equal(decoded.includes('// 日本語'), true);
  equal(decoded.includes('FILEVERSION 0,6,0,0'), true);
  equal(decoded.includes('"ProductVersion", "0.6.0.0"'), true);
  equal([...updateVersionResource(updated, '0.6.0.0')], [...updated]);
});
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
