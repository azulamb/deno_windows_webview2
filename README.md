# deno_windows_webview2

* GitHub
  * https://github.com/azulamb/deno_windows_webview2
* JSR
  * https://jsr.io/@azulamb/webview2

## Develop

* Deno
  * `2.1.9`

## DLL

### File

`./webview2/x64/Debug/webview2.dll` or `./webview2/x64/Release/webview2.dll`

Copy command.

```sh
deno task copy [--debug] directory/path
```

* `--debug`
  * Copy from debug DLL.
* `directory/path`
  * Destination directory path.

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
