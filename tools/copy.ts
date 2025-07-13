import { isAbsolute, join } from 'jsr:@std/path@^1.0.8';
import { createDLLPath } from './dll_path.ts';

export function copy(
  toFilePath: string,
  option?: {
    isDebug?: boolean; // Copy Debug DLL.
    log?: boolean; // Output log.
  },
): Promise<void> {
  const fromFilePath = createDLLPath(option?.isDebug);

  if (option?.log) {
    console.log(`Module dir: ${import.meta.dirname}`);
    console.log(`From: ${fromFilePath.toString()}`);
    console.log(`To: ${toFilePath}`);
  }

  if (!fromFilePath.toString().match(/^https:\/\//)) {
    // File copy.
    return Deno.copyFile(fromFilePath, toFilePath);
  }

  // Download file.
  return fetch(fromFilePath).then((response) => {
    if (!response.ok) {
      throw new Error(
        `Failed to fetch ${fromFilePath}: ${response.statusText}`,
      );
    }
    return response.arrayBuffer();
  }).then((buffer) => {
    return Deno.writeFile(toFilePath, new Uint8Array(buffer));
  });
}

if (import.meta.main) {
  let isDebug = false;
  let dest = '';

  for (const arg of Deno.args) {
    if (arg === '--debug') {
      isDebug = true;
      continue;
    }
    dest = arg;
    break;
  }

  if (!dest) {
    console.error('Usage: deno task copy [--debug] <dest dir path>');
    Deno.exit(1);
  }

  try {
    const stat = await Deno.stat(dest);
    if (!stat.isDirectory) {
      throw new Error();
    }
  } catch (_error) {
    console.error(`"${dest}" is not a directory`);
    Deno.exit(1);
  }

  dest = join(dest, 'webview2.dll');
  if (!isAbsolute(dest)) {
    dest = join(Deno.cwd(), dest);
  }

  if (confirm(`Copy webview2.dll?\n${dest}`)) {
    console.log('Copying...');
    await copy(dest, {
      isDebug: isDebug,
      log: true,
    });
  }
  console.log('Done');
}
