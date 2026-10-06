/**
 * Generate Deno compile arguments or compile an application and prepare its WebView2 DLL.
 * Supports embedded files, executable icons and console visibility options.
 * @module
 */

import { createDllFile } from './webview2.ts';

/** Executable compilation and bundled DLL preparation options. */
export interface COMPILE_OPTION {
  /** ICO path passed to deno compile's --icon option. */
  icon?: string;
  /** Destination DLL path to prepare and embed. */
  dllPath?: string;
  /** Use the bundled debug DLL instead of the release DLL. */
  isDebug?: boolean;
  // version?: string; // Deno Windows Webview2 version(tag)
  /** Additional files or directories embedded with --include. */
  includes?: string[];
  /** When true, omit the default --no-terminal option and preserve supplied terminal arguments. */
  disableTerminal?: boolean;
}

function createCompileArgs(
  main: string,
  output: string,
  option?: COMPILE_OPTION,
  args?: string[],
) {
  const includes = [...(option?.includes ?? [])];
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
    commandArgs.push(
      ...includes.map((file) => {
        return ['--include', file];
      }).flat(),
    );
  }

  commandArgs.push('--output', output, main);

  return commandArgs;
}

/**
 * Create the command line arguments for the Deno compile command.
 * @param mainSource The main source file.
 * @param output The output file.
 * @param option Options for the compile operation.
 * @param args Additional arguments for the compile operation.
 * @returns The command line arguments for the Deno compile command.
 */
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

/**
 * Create the command line arguments for the Deno compile command.
 * @param mainSource The main source file.
 * @param output The output file.
 * @param args Additional arguments for the compile operation.
 * @param option Options for the compile operation.
 * @returns The command line arguments for the Deno compile command.
 */
export async function compile(
  mainSource: string,
  output: string,
  args?: string[],
  option?: COMPILE_OPTION,
): Promise<{
  command: string[];
  stdout: string;
  stderr: string;
  success: boolean;
  code: number;
}> {
  if (option?.dllPath) await createDllFile(option.dllPath, option.isDebug);
  const commandArgs = createCompileArgs(mainSource, output, option, args);
  const { stdout, stderr, success, code } = await new Deno.Command(
    Deno.execPath(),
    {
      args: commandArgs,
    },
  ).output();

  return {
    command: ['deno', ...commandArgs],
    stdout: new TextDecoder().decode(stdout),
    stderr: new TextDecoder().decode(stderr),
    success,
    code,
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
