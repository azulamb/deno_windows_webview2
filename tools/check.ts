import * as checker from 'jsr:@azulamb/checker';
import { version } from '../mod.ts';
const VERSION = version.Deno.Webview2;

await checker.check(
  checker.createDenoVersionChecker(),
  checker.createVersionChecker(VERSION),
  checker.createJsrPublishChecker(),
);
