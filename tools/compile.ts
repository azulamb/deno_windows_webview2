import { createDllFile } from './webview2.ts';

interface COMPILE_OPTION {
  dllPath?: string;
  isDebug?: boolean;
  // version?: string;
}

function createCompileArgs(
  args: string[],
  option?: COMPILE_OPTION,
) {
  const commandArgs = [
    'compile',
    '--allow-ffi',
  ];
  if (option?.dllPath) {
    const dllPath = option?.dllPath;
    createDllFile(dllPath, option?.isDebug).toString(),

    commandArgs.push(
      `--allow-write=${dllPath}`,
      '--include',
      dllPath,
    );
  }
  commandArgs.push(...args);
  return commandArgs;
}

export function createCompileCommand(
  args: string[],
  option?: COMPILE_OPTION,
): string {
  return `deno ${createCompileArgs(args, option).join(' ')}`;
}

export async function compile(
  args: string[],
  option?: COMPILE_OPTION,
): Promise<{
  command: string[];
  stdout: string;
  stderr: string;
}> {
  const commandArgs = createCompileArgs(args, option);
  const { stdout, stderr } = await new Deno.Command(
    'deno',
    {
      args: commandArgs,
    },
  ).output();

  return {
    command: ['deno', ...commandArgs],
    stdout: new TextDecoder().decode(stdout),
    stderr: new TextDecoder().decode(stderr),
  };
}

if (import.meta.main) {
  let isDebug = false;

  for (const arg of Deno.args) {
    if (arg === '--debug') {
      isDebug = true;
      continue;
    }
  }

  console.log(createCompileCommand(Deno.args, { isDebug: isDebug }));
}
