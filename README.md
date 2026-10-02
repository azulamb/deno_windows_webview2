# Deno Windows Webview2

* GitHub
  * https://github.com/azulamb/deno_windows_webview2
* JSR
  * https://jsr.io/@azulamb/webview2

## Develop

* Deno
  * `2.4.2`

## DLL

### Versions

* Microsoft.Web.WebView2
  * `1.0.3351.48`
* Microsoft.Windows.ImplementationLibrary
  * `1.0.250325.1`

### File

`./webview2/x64/Debug/webview2.dll` or `./webview2/x64/Release/webview2.dll`

Copy command.

```sh
deno run --allow-read --allow-net --allow-write jsr:@azulamb/webview2@0.2.4/copy [--debug] path
```

* `--debug`
  * Copy from debug DLL.
* `path`
  * Destination directory path or file.
    * `directory/path/`
    * `directory/file_path.dll`
  * If directory, copy to `path/webview2.dll`

### Copy code.

TODO: change import path.

```ts
import { copy } from 'path/to/deno_windows_webview2/tools/copy.ts';

await copy({
  toFilePath: './webview2.dll',
});
```

### Build

Install Visual Studio 2022 or compatible Visual Studio Build Tools with
Desktop development with C++, MSVC v143, and a Windows SDK.
The solution uses the `x64` platform.

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

Add `-Rebuild` for a full rebuild. Use `-Configuration DebugWindow` to build
the C++ sample executable. The DLL outputs are
`webview2/x64/Debug/webview2.dll` and `webview2/x64/Release/webview2.dll`.

In a Visual Studio Developer PowerShell or Developer Command Prompt,
you can invoke MSBuild directly:

```powershell
msbuild webview2/webview2.sln /m /t:Build /p:Configuration=Debug /p:Platform=x64
msbuild webview2/webview2.sln /m /t:Build /p:Configuration=Release /p:Platform=x64
```

If `webview2/packages` has not been restored, install the NuGet CLI and run
this command before building:

```powershell
nuget restore webview2/webview2.sln -PackagesDirectory webview2/packages
```

See the [NuGet restore command documentation](https://learn.microsoft.com/en-us/nuget/reference/cli-reference/cli-ref-restore).
