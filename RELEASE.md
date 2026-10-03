# Release

* Build DLL.
  * Debug
  * Release
* `deno task version`
  * After edit version.
* `deno fmt`
* `deno task check`
  * Includes `deno task check:publish` (lint and JSR publish dry-run).
  * Use `deno task check:publish` alone for checks without Windows DLLs.
* Set tag `vX.Y.Z`
* Push.
* `deno publish`
  * The Publish workflow runs `deno task check:publish` before publishing.
