# Release

## 0.7.1

- Update the WinAPI dependency to `^0.4.0` to match Weapn.
- Accept the public RECT buffer in `Controllers.bounds`, avoiding class identity
  conflicts between compatible WinAPI package versions.
- Continue using DLL version `0.7.0.0`; no native changes are required.

## Release steps

- Build DLL.
  - Debug
  - Release
- `deno task version`
  - After edit version.
- `deno fmt`
- `deno task check`
  - Includes `deno task check:publish` (lint and JSR publish dry-run).
  - Use `deno task check:publish` alone for checks without Windows DLLs.
- Set tag `vX.Y.Z`
- Push.
- `deno publish`
  - The Publish workflow runs `deno task check:publish` before publishing.
