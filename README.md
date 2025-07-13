# Deno Windows Webview2

* GitHub
  * https://github.com/azulamb/deno_windows_webview2
* JSR
  * https://jsr.io/@azulamb/webview2

## Develop

* Deno
  * `2.4.1`

## DLL

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

VisualStudio 2022

* Debug
* Release
* DebugWindow
  * Sample C++ code.
