import * as checker from 'jsr:@azulamb/checker';
import { version } from '../mod.ts';
const VERSION = version.Deno.Webview2;
const DLL_VERSION = version.Dll;

await checker.check(
  checker.createDenoVersionChecker(),
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
        return Promise.resolve();
      }
      const versions = (await Promise.all(list.map((mode) => {
        return checker.exec(
          ['powershell', './tools/dllver.ps1', mode],
        ).then((output) => {
          return {
            mode: mode,
            version: output.stdout.trim(),
          };
        });
      }))).filter((result) => {
        return result.version !== DLL_VERSION;
      });

      if (versions.length <= 0) {
        return Promise.resolve();
      }

      return Promise.reject(
        versions.map((result) => {
          return `Dll version invalid[${result.mode}]: ${result.version}`;
        }).join('\n'),
      );
    },
  },
  checker.createVersionChecker(VERSION),
  checker.createJsrPublishChecker(),
);
