import { createDLLPath } from './dll_path.ts';

export function createCompileCommand(
  args: string[],
  option?: {
    isDebug?: boolean;
    // version?: string;
  },
) {
  return `deno compile --include ${createDLLPath(option?.isDebug)} ${
    args.join(' ')
  }`;
}

export async function compile(
  args: string[],
  option?: {
    isDebug?: boolean;
  },
) {
  const { stdout, stderr } = await new Deno.Command(
    'deno' as string,
    {
      args: [
        'compile',
        '--include',
        createDLLPath(option?.isDebug).toString(),
        ...args,
      ],
    },
  ).output();

  return {
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
