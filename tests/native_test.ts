import { winApi } from '@azulamb/winapi';
import { fromFileUrl } from '@std/path';
import {
  createWebView2,
  IStream,
  JStream,
  version,
  WebResourceRequestedEventArgs,
} from '../mod.ts';

function equal(actual: unknown, expected: unknown): void {
  if (JSON.stringify(actual) !== JSON.stringify(expected)) {
    throw new Error(
      `Expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`,
    );
  }
}
function check(result: number): void {
  if (result < 0) throw new Error(`HRESULT: ${result}`);
}
async function timeout<T>(promise: Promise<T>): Promise<T> {
  let timer: ReturnType<typeof setTimeout> | undefined;
  try {
    return await Promise.race([
      promise,
      new Promise<never>((_, reject) => {
        timer = setTimeout(
          () => reject(new Error('Native test timed out')),
          15000,
        );
      }),
    ]);
  } finally {
    clearTimeout(timer);
  }
}
Deno.test({
  name:
    'native headers, long methods, script results, event removal and repeated disposal',
  ignore: Deno.build.os !== 'windows',
  sanitizeOps: false,
  sanitizeResources: false,
  async fn() {
    const ole = Deno.dlopen('ole32.dll', {
      CoInitializeEx: { parameters: ['pointer', 'u32'], result: 'i32' },
      CoUninitialize: { parameters: [], result: 'void' },
    });
    const shell = Deno.dlopen('shlwapi.dll', {
      SHCreateMemStream: { parameters: ['buffer', 'u32'], result: 'pointer' },
    });
    check(ole.symbols.CoInitializeEx(null, 2));
    const previous = Deno.env.get('WEBVIEW2_USER_DATA_FOLDER');
    Deno.env.delete('WEBVIEW2_USER_DATA_FOLDER');
    const profile = await Deno.makeTempDir({ prefix: 'webview2-native-' });
    const message = winApi.create.message();
    const pump = setInterval(() => {
      for (
        let count = 0;
        count < 64 && winApi.user.PeekMessage(message.pointer, null, 0, 0, 1);
        ++count
      ) {
        winApi.user.TranslateMessage(message.pointer);
        winApi.user.DispatchMessage(message.pointer);
      }
    }, 2);
    try {
      for (let iteration = 0; iteration < 3; ++iteration) {
        const klass = winApi.create.windowClassEx();
        klass.hInstance = winApi.kernel.GetModuleHandle();
        klass.setClassName(`WebView2-test-${crypto.randomUUID()}`);
        klass.setWindowProcedure((handle, msg, wparam, lparam) =>
          winApi.user.DefWindowProc(handle, msg, wparam, lparam)
        );
        if (!winApi.user.RegisterClassEx(klass.pointer)) {
          throw new Error('RegisterClassEx failed');
        }
        const handle = winApi.user.CreateWindowEx(
          0,
          klass.lpszClassName,
          winApi.create.stringPointer('WebView2 native test'),
          0x00cf0000,
          0,
          0,
          320,
          240,
        );
        if (!handle) throw new Error('CreateWindowEx failed');
        const webview = createWebView2(
          fromFileUrl(
            new URL('../webview2/x64/Release/webview2.dll', import.meta.url),
          ),
        );
        try {
          equal(webview.dllVersion, version.Dll);
          await timeout(
            new Promise<void>((resolve, reject) => {
              const result = webview.createCoreWebView2EnvironmentWithOptions(
                null,
                profile,
                null,
                (hr) => {
                  if (hr < 0) reject(new Error(`Environment failed: ${hr}`));
                  else resolve();
                  return 0;
                },
              );
              if (result < 0) {
                reject(new Error(`Environment start failed: ${result}`));
              }
            }),
          );
          await timeout(
            new Promise<void>((resolve, reject) => {
              const result = webview.createCoreWebView2Controller(
                handle,
                (hr) => {
                  if (hr < 0) reject(new Error(`Controller failed: ${hr}`));
                  else resolve();
                  return 0;
                },
              );
              if (result < 0) {
                reject(new Error(`Controller start failed: ${result}`));
              }
            }),
          );
          check(webview.getCoreWebView2());
          check(webview.getSettings());
          const bounds = winApi.create.rect();
          winApi.user.GetClientRect(handle, bounds.pointer);
          webview.controllers.bounds = bounds;
          winApi.user.ShowWindow(handle, 5);
          let removedCalled = false;
          const removed = webview.core.addWebMessageReceived(() => {
            removedCalled = true;
            return 0;
          });
          check(webview.core.removeWebMessageReceived(removed));
          let loaded!: () => void;
          const ready = new Promise<void>((resolve) => {
            loaded = resolve;
          });
          const receive = webview.core.addWebMessageReceived(() => {
            loaded();
            return 0;
          });
          const longMethod = 'CUSTOM_METHOD_LONGER_THAN_EIGHT';
          let requested!: () => void, failed!: (error: unknown) => void;
          const received = new Promise<void>((resolve, reject) => {
            requested = resolve;
            failed = reject;
          });
          check(
            webview.core.addWebResourceRequestedFilter('https://test.local/*'),
          );
          const token = webview.core.addWebResourceRequested(
            (_sender, pointer) => {
              const args = new WebResourceRequestedEventArgs(
                webview.lib,
                pointer,
              );
              const request = args.Request;
              try {
                const requestHeaders = request.Headers;
                try {
                  requestHeaders.SetHeader('X-Test', 'value');
                  equal(requestHeaders.GetHeader('X-Test'), 'value');
                  equal(requestHeaders.GetHeaders('X-Test'), ['value']);
                  equal(requestHeaders.convertHeaders().get('X-Test'), 'value');
                  requestHeaders.RemoveHeader('X-Test');
                  equal(requestHeaders.Contains('X-Test'), false);
                } finally {
                  requestHeaders.close();
                }
                const isFetch = request.Uri.endsWith('/fetch');
                if (isFetch) equal(request.Method, longMethod);
                // Exercise Content setter's IStream* ABI and getter's output pointer.
                const empty = new IStream(webview.lib);
                empty.setPointer(
                  shell.symbols.SHCreateMemStream(new Uint8Array([65]), 1),
                );
                try {
                  request.Content = empty;
                  request.Content.close();
                } finally {
                  empty.close();
                }
                const text = isFetch
                  ? 'ok'
                  : '<script>chrome.webview.postMessage("ready")</script>';
                const stream = new IStream(webview.lib);
                stream.setPointer(
                  shell.symbols.SHCreateMemStream(
                    new TextEncoder().encode(text),
                    new TextEncoder().encode(text).length,
                  ),
                );
                try {
                  const response = webview.createWebResourceResponse(
                    stream,
                    200,
                    'OK',
                    `Content-Type: ${
                      isFetch ? 'text/plain' : 'text/html'
                    }\r\nX-Response: one\r\nX-Response: two`,
                  );
                  try {
                    const headers = response.Headers;
                    try {
                      equal(headers.GetHeaders('X-Response'), ['one', 'two']);
                      equal(
                        headers.convertHeaders().get('X-Response'),
                        'one, two',
                      );
                      headers.AppendHeader('X-Extra', 'three');
                      equal(headers.GetHeader('X-Extra'), 'three');
                    } finally {
                      headers.close();
                    }
                    args.Response = response;
                  } finally {
                    response.close();
                  }
                } finally {
                  stream.close();
                }
                if (isFetch) requested();
              } catch (error) {
                failed(error);
              } finally {
                request.close();
              }
              return 0;
            },
          );
          check(webview.core.navigate('https://test.local/index'));
          await timeout(Promise.race([ready, received]));
          equal(removedCalled, false);
          const execute = (source: string) =>
            timeout(
              new Promise<string>((resolve, reject) => {
                const result = webview.core.executeScript(
                  source,
                  (hr, json) => {
                    if (hr < 0) {
                      reject(new Error(`ExecuteScript failed: ${hr}`));
                    } else resolve(json);
                    return 0;
                  },
                );
                if (result < 0) {
                  reject(new Error(`Script start failed: ${result}`));
                }
              }),
            );
          equal(JSON.parse(await execute('"日本語😀"')), '日本語😀');
          await execute(`void fetch('/fetch', { method: '${longMethod}' })`);
          await timeout(received);
          check(webview.core.removeWebResourceRequested(token));
          check(webview.core.removeWebMessageReceived(receive));
          // Native JStream reference counting frees its callbacks on the final Release.
          const js = JStream.create(new JStream(webview.lib));
          js.close();
          await Promise.resolve();
        } finally {
          webview.close();
          await timeout(webview.closed);
          webview.close(); // Idempotent.
          winApi.user.DestroyWindow(handle);
          if (
            winApi.user.UnregisterClass(klass.lpszClassName, klass.hInstance)
          ) klass.closeWindowProcedure();
        }
      }
      if (!(await Deno.stat(`${profile}/EBWebView`)).isDirectory) {
        throw new Error('userDataFolder was not used');
      }
    } finally {
      clearInterval(pump);
      if (previous === undefined) Deno.env.delete('WEBVIEW2_USER_DATA_FOLDER');
      else Deno.env.set('WEBVIEW2_USER_DATA_FOLDER', previous);
      ole.symbols.CoUninitialize();
      ole.close();
      shell.close();
      await removeProfile(profile);
    }
  },
});

async function removeProfile(profile: string): Promise<void> {
  // Runtime processes may briefly retain the profile after controller disposal.
  for (let attempt = 0; attempt < 30; ++attempt) {
    try {
      await Deno.remove(profile, { recursive: true });
      break;
    } catch (error) {
      if (attempt === 29) throw error;
      await new Promise((resolve) => setTimeout(resolve, 100));
    }
  }
}
