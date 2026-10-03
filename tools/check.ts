import * as checker from '@azulamb/checker';
import data from '../deno.json' with { type: 'json' };
import { version } from '../mod.ts';
const VERSION = version.Deno.Webview2;
const DLL_VERSION = version.Dll;

async function exec(command: string[]): Promise<string> {
  const result = await checker.exec(command);
  if (result.code !== 0) {
    throw new Error(result.stderr.trim() || 'Command failed.');
  }
  return result.stdout.trim();
}

function isUpdatedDllVersion(previous: string, current: string): boolean {
  if (
    !/^\d+\.\d+\.\d+\.\d+$/.test(previous) ||
    !/^\d+\.\d+\.\d+\.\d+$/.test(current)
  ) {
    throw new Error(`Invalid DLL version: ${previous} -> ${current}`);
  }
  const before = previous.split('.').map(Number);
  const after = current.split('.').map(Number);
  for (let i = 0; i < before.length; ++i) {
    if (before[i] !== after[i]) {
      return before[i] < after[i];
    }
  }
  return false;
}

// Check publication before Windows-specific DLL and release version checks.
await checker.check({
  name: 'Lint and JSR public API check',
  command: ['deno', 'task', 'check:publish'],
  after: (result) => {
    if (result.code !== 0) {
      return Promise.reject(new Error(result.stderr || result.stdout));
    }
    console.log(result.stdout);
    return Promise.resolve();
  },
});

await checker.check(
  {
    name: 'DLL version check',
    after: async () => {
      const versions = await Promise.all(
        ['Debug', 'Release'].map(async (mode) => {
          return {
            mode,
            version: await exec([
              'powershell',
              '-NoProfile',
              '-ExecutionPolicy',
              'Bypass',
              '-File',
              './tools/dllver.ps1',
              mode,
            ]),
          };
        }),
      );
      if (versions[0].version !== versions[1].version) {
        throw new Error(
          `DLL version mismatch: ${
            versions.map((v) => `${v.mode}: ${v.version}`).join(', ')
          }`,
        );
      }
      const dllVersion = versions[0].version;
      console.log(`Now version: ${DLL_VERSION} Now dll version: ${dllVersion}`);
      if (DLL_VERSION !== data.dll_version || DLL_VERSION !== dllVersion) {
        throw new Error(
          'Dll version invalid: Update deno.json & deno task version, and rebuild DLLs.',
        );
      }

      // Compare against the last release, including staged and committed changes.
      const tag = await exec(['git', 'describe', '--tags', '--abbrev=0']);
      const previous: { dll_version: string } = JSON.parse(
        await exec(['git', 'show', `${tag}:deno.json`]),
      );
      if (typeof previous.dll_version !== 'string') {
        throw new Error(`Missing dll_version in ${tag}:deno.json`);
      }
      const changedDlls = await exec([
        'git',
        'diff',
        '--name-only',
        tag,
        '--',
        'webview2/x64/Debug/webview2.dll',
        'webview2/x64/Release/webview2.dll',
      ]);
      // Validate all four components even if the DLL files are unchanged.
      const updated = isUpdatedDllVersion(previous.dll_version, dllVersion);
      console.log(`Release ${tag} DLL version: ${previous.dll_version}`);
      if (!changedDlls) {
        return 'No DLL changes since the last release, skipping version update check.';
      }
      if (!updated) {
        throw new Error(
          `Dll version invalid: ${dllVersion} must be newer than ${tag} (${previous.dll_version}).`,
        );
      }
      return `Dll version updated ${previous.dll_version} -> ${dllVersion}`;
    },
  },
  checker.createDenoVersionChecker(),
  checker.createVersionChecker(VERSION, {
    isNotUpdated:
      'VERSION is not updated. Update deno.json & deno task version',
  }),
);
