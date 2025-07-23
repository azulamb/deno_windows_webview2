import * as checker from 'jsr:@azulamb/checker@1.2.0';
import { version } from '../mod.ts';
const VERSION = version.Deno.Webview2;
const DLL_VERSION = version.Dll;

await checker.check(
  {
    name: 'DLL version check',
    command: ['git', 'diff', '--name-status'],
    after: async (result) => {
      const list = result.stdout.split(/\r\n|\r|\n/g).map((file) => {
        return file.trim().split(/\t/)[1];
      }).filter((file) => {
        return file && file.match(/webview2\.dll$/);
      }).map((file) => {
        return file.replace(/^.+(Debug|Release).+$/, '$1');
      });
      if (list.length <= 0) {
        const dllVersion = (await checker.exec(
          ['powershell', './tools/dllver.ps1', 'Release'],
        )).stdout.trim();
        console.log(
          `Now version: ${DLL_VERSION} Now dll version: ${dllVersion}`,
        );
        if (DLL_VERSION !== dllVersion) {
          return Promise.reject(
            new Error(
              `Dll version invalid: Update deno.json & deno task version`,
            ),
          );
        }
        return Promise.resolve(
          'No DLL changes detected, skipping version check.',
        );
      }
      const versions = await Promise.all(list.map((mode) => {
        return checker.exec(
          ['powershell', './tools/dllver.ps1', mode],
        ).then((output) => {
          return {
            mode: mode,
            version: output.stdout.trim(),
          };
        });
      }));

      if (
        versions.length !== 2 || versions[0].version !== versions[1].version
      ) {
        console.error('DLL versions do not match for Debug and Release modes.');
        return Promise.reject(
          new Error(
            `DLL version mismatch: ${
              versions.map((v) => `${v.mode}: ${v.version}`).join(', ')
            }`,
          ),
        );
      }
      const dllVersion = versions[0].version;

      console.log(`Now version: ${DLL_VERSION} Now dll version: ${dllVersion}`);
      if (!checker.isUpdatedVersion(DLL_VERSION, dllVersion)) {
        return Promise.reject(
          new Error(
            `Dll version invalid: ${dllVersion} Need update version in dll.`,
          ),
        );
      }

      return Promise.resolve(
        `Dll version updated ${DLL_VERSION} -> ${dllVersion}`,
      );
    },
  },
  checker.createDenoVersionChecker(),
  checker.createVersionChecker(VERSION, {
    isNotUpdated:
      'VERSION is not updated. Update deno.json & deno task version',
  }),
  checker.createJsrPublishChecker(),
);
