# Deno Windows Webview2

DLL acquisition is shared by the copy, compile and preparation helpers.
`ensureDLL(path, { signal, expectedVersion })` from `/copy` preserves existing
files and can verify their fixed Windows file version. `copy()` replaces files
atomically. Both support cancellation. `compile()` awaits DLL preparation and
returns `success` and `code` as well as its output; non-empty stderr alone does
not mean compilation failed. Command generation has no file-writing side
effects. `deno task version` updates the API, fixed resource and string resource
versions together while preserving the resource file's encoding.

- GitHub
  - https://github.com/azulamb/deno_windows_webview2
- JSR
  - https://jsr.io/@azulamb/webview2

## Develop

- Deno
  - `^2.9.7`

## DLL

### Versions

- Microsoft.Web.WebView2
  - `1.0.3351.48`
- Microsoft.Windows.ImplementationLibrary
  - `1.0.250325.1`

### File

`./webview2/x64/Debug/webview2.dll` or `./webview2/x64/Release/webview2.dll`

Copy command.

```sh
deno run --allow-read --allow-net --allow-write jsr:@azulamb/webview2@0.6.0/copy [--debug] path
```

- `--debug`
  - Copy from debug DLL.
- `path`
  - Destination directory path or file.
    - `directory/path/`
    - `directory/file_path.dll`
  - If directory, copy to `path/webview2.dll`

### Copy code.

TODO: change import path.

```ts
import { copy } from 'path/to/deno_windows_webview2/tools/copy.ts';

await copy({
  toFilePath: './webview2.dll',
});
```

### Build

Install Visual Studio 2022 or compatible Visual Studio Build Tools with Desktop
development with C++, MSVC v143, and a Windows SDK. The solution uses the `x64`
platform.

From the repository root, build either DLL configuration:

```powershell
deno task build:dll:debug
deno task build:dll:release
```

These tasks use `vswhere.exe` to locate MSBuild. You can also run the script
directly from a regular PowerShell terminal without Deno:

```powershell
powershell -NoProfile -File tools/build.ps1 -Configuration Debug
powershell -NoProfile -File tools/build.ps1 -Configuration Release
```

Add `-Rebuild` for a full rebuild. Use `-Configuration DebugWindow` to build the
C++ sample executable. The DLL outputs are `webview2/x64/Debug/webview2.dll` and
`webview2/x64/Release/webview2.dll`.

In a Visual Studio Developer PowerShell or Developer Command Prompt, you can
invoke MSBuild directly:

```powershell
msbuild webview2/webview2.sln /m /t:Build /p:Configuration=Debug /p:Platform=x64
msbuild webview2/webview2.sln /m /t:Build /p:Configuration=Release /p:Platform=x64
```

If `webview2/packages` has not been restored, install the NuGet CLI and run this
command before building:

```powershell
nuget restore webview2/webview2.sln -PackagesDirectory webview2/packages
```

See the
[NuGet restore command documentation](https://learn.microsoft.com/en-us/nuget/reference/cli-reference/cli-ref-restore).

### Resource ownership and shutdown

Keep all WebView2 and COM calls on the STA thread that created the control. Use
weapn's UI Worker API for messages between the main script and the native UI.
The exported raw pointers are borrowed handles on that same STA, not
transferable Worker objects.

Request, response, headers, stream and deferral objects returned by getters own
one COM reference. Release them with `close()` after use. Event argument objects
received by callbacks are borrowed for the duration of the callback; a deferral
and an explicitly retained reference are needed to use them later.

`WebResourceRequest.pointer` refers to the output-buffer pointer. Use
`doublePointer` for native output parameters and `nativePointer` for the request
interface itself. Response headers support `AppendHeader`; request headers
support `SetHeader` and `RemoveHeader`.

Unsubscribe events and close owned request/response/stream objects before
shutting down the control. Then call `webview.close()` and await
`webview.closed` while continuing to pump the STA message queue. Close is
idempotent and waits for pending native completions before freeing wrappers and
the library created by `createWebView2()`. A directly constructed
`WebView2(library)` borrows its DLL; its caller closes that library after
shutdown. Borrowed wrapper pointers are not destroyed by this instance.

JStream's native reference count is managed by the DLL. Its callbacks are closed
on the final Release; overriding AddRef or Release is rejected. For asynchronous
web responses, prefer native memory streams as used by weapn's UI Worker, so
native reads do not depend on JavaScript callbacks.

### Navigation and request events

`webview.core.navigateToString(html)` displays an HTML string without a server.
`addNavigationStarting()` and `addNavigationCompleted()` receive typed event
arguments. Starting arguments expose `Uri`, `NavigationId`, `IsUserInitiated`,
`IsRedirected` and writable `Cancel`. Completion arguments expose `IsSuccess`,
`WebErrorStatus` and `NavigationId`.

`addNewWindowRequested()` receives `Uri`, `IsUserInitiated`, writable `Handled`
and `getDeferral()`. `addPermissionRequested()` receives `Uri`,
`PermissionKind`, `IsUserInitiated`, writable `State` (0: default, 1: allow, 2:
deny) and `getDeferral()`. Each registration returns a token for its matching
`remove...()` method. Handlers run synchronously on the owning STA and return an
HRESULT.

```ts
const token = webview.core.addNavigationStarting((_sender, args) => {
  if (args.Uri.startsWith('https://blocked.example/')) args.Cancel = true;
  return 0;
});
webview.core.navigateToString('<h1>Hello</h1>');
// Before shutdown, or when the handler is no longer needed:
webview.core.removeNavigationStarting(token);
```

Event arguments are borrowed during the callback. New-window and permission
events support asynchronous handling with a deferral: keep an explicit COM
reference as well, complete and close the deferral, then release that reference
on the same STA. Navigation cancellation must be decided during the synchronous
callback. `WebView2.close()` removes outstanding event subscriptions automatically.

### API coverage report

`docs/dll.json` and `docs/index.html` catalog the stable SDK **1.0.4258.31**.
This catalog version is independent of the DLL build SDK in `src/version.ts`.
New SDK methods are listed even when their wrappers are not yet implemented. The
catalog includes COM interfaces, global functions, enums and structures; event
handler interfaces are excluded.

Run `deno task report` to recompute coverage from the current source without
network access. `defined` means a native exported function has a C++ definition;
`implemented` means the TypeScript implementation references that function.
Comments and generated FFI definitions do not count as implementations. These
flags describe method wrappers; enum and structure entries remain unmarked.

To import a newer stable SDK, download and extract its official
[NuGet package](https://www.nuget.org/packages/Microsoft.Web.WebView2), then
run:

```sh
deno task report --sdk-header ./path/to/build/native/include/WebView2.h --version 1.0.4258.31
```

The SDK header supplies the catalog directly, so this update does not depend on
documentation scraping or stale hand-maintained implementation flags.

### DLL preparation and verification

`prepareWebview2DLL(destination, { includePath: true })` copies the bundled DLL
to a real filesystem destination, including when it is embedded by
`deno compile`. Copies replace the destination atomically. A failed copy or
download preserves the existing destination. The default download URL uses this
module's release tag. Applications should resolve their destination relative to
the executable directory or another writable directory.

Run `deno task check:publish` for lint, unit tests, type checking and JSR
slow-type validation. On Windows, rebuild the DLL and run
`deno task test:native` for real WebView2 tests covering headers, long HTTP
methods, script results, event removal, the user data folder and repeated
shutdown. `deno task version` also generates `webview2/version.h` so the DLL
version getter stays in sync.
