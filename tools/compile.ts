import { createDllFile } from './webview2.ts';

interface COMPILE_OPTION {
  icon?: string;
  dllPath?: string;
  isDebug?: boolean;
  // version?: string; // Deno Windows Webview2 version(tag)
  includes?: string[];
  disableTerminal?: boolean;
}

function createCompileArgs(
  main: string,
  output: string,
  option?: COMPILE_OPTION,
  args?: string[],
) {
  const includes = option?.includes || [];
  const commandArgs = [
    'compile',
    '--allow-ffi',
  ];

  if (!option?.disableTerminal) {
    commandArgs.push('--no-terminal');
  }

  if (option?.icon) {
    commandArgs.push('--icon', option?.icon);
  }

  if (option?.dllPath) {
    const dllPath = option?.dllPath;
    createDllFile(dllPath, option?.isDebug).toString();
    commandArgs.push(`--allow-write=${dllPath}`);
    includes.push(dllPath);
  }

  if (args && 0 < args.length) {
    if (!option?.disableTerminal) {
      commandArgs.push(...args.filter((arg) => {
        return arg !== '--no-terminal';
      }));
    } else {
      commandArgs.push(...args);
    }
  }
  if (includes.length > 0) {
    commandArgs.push('--include', ...includes);
  }

  commandArgs.push('--output', output, main);

  return commandArgs;
}

export function createCompileCommand(
  mainSource: string,
  output: string,
  option?: COMPILE_OPTION,
  args?: string[],
): string {
  return `deno ${
    createCompileArgs(mainSource, output, option, args).join(' ')
  }`;
}

export async function compile(
  mainSource: string,
  output: string,
  args?: string[],
  option?: COMPILE_OPTION,
): Promise<{
  command: string[];
  stdout: string;
  stderr: string;
}> {
  const commandArgs = createCompileArgs(mainSource, output, option, args);
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
  const option: COMPILE_OPTION = {};
  let main = '';
  let output = '';

  const args: string[] = [];
  for (const arg of Deno.args) {
    if (arg.startsWith('--icon=')) {
      option.icon = arg.split('=')[1];
      continue;
    }
    if (arg.startsWith('--dll=')) {
      option.dllPath = arg.split('=')[1];
      continue;
    }
    if (arg === '--debug') {
      option.isDebug = true;
      continue;
    }
    if (arg.startsWith('--main=')) {
      main = arg.split('=')[1];
      continue;
    }
    if (arg.startsWith('--output=')) {
      output = arg.split('=')[1];
      continue;
    }
    args.push(arg);
  }

  if (!main) {
    console.error('Error: --main=MAIN_SOURCE argument is required');
    Deno.exit(1);
  }
  if (!output) {
    console.error('Error: --output=OUTPUT argument is required');
    Deno.exit(1);
  }

  console.log(createCompileCommand(main, output, option, args));
}
