import { version } from '../mod.ts';
const VERSION = version.Deno.Webview2;

async function Exec(command: string[]) {
  const { stdout, stderr } = await new Deno.Command(
    command.shift() as string,
    {
      args: command,
    },
  ).output();

  return {
    stdout: new TextDecoder().decode(stdout),
    stderr: new TextDecoder().decode(stderr),
  };
}

function Exit(message: string) {
  console.error(`%c[Error] ${message}`, 'color: red');
  Deno.exit(1);
}

function Start(name: string) {
  console.log(`== ${name} `.padEnd(80, '='));
}

function Complete(message: string) {
  console.log(`%c${message}`, 'color: green');
}

function VersionCheck(nowTag: string, noeVer: string) {
  const v1 = nowTag.split('.').map((v) => {
    return parseInt(v);
  });
  const v2 = noeVer.split('.').map((v) => {
    return parseInt(v);
  });
  for (let i = 0; i < 3; ++i) {
    if (v1[i] < v2[i]) {
      return true;
    }
  }
  return false;
}

const list: {
  name: string;
  command?: string[];
  after: (result: { stdout: string; stderr: string }) => Promise<string | void>;
}[] = [
  {
    name: 'Deno version check',
    command: ['deno', 'upgrade', '--dry-run'],
    after: (result) => {
      let version = '';
      result.stderr.split('\n').forEach((line) => {
        line = line.trim();
        const v = line.replace(
          /^Found latest stable version .*v([0-9.]+).*$/,
          '$1',
        );
        if (v !== line && !v.match(/[^0-9.]/)) {
          version = v;
        }
      });
      if (!version) {
        return Promise.resolve('This deno version is latest');
      }
      return Promise.reject(
        new Error(`Found latest version: ${version}\nExec \`deno upgrade\``),
      );
    },
  },
  {
    name: 'VERSION check',
    command: ['git', 'describe', '--tags', '--abbrev=0'],
    after: (result) => {
      return Promise.resolve(result.stdout.replace(/\s/g, '')).then((tag) => {
        console.log(`Now tag: ${tag} Now ver: ${VERSION}`);
        if (!VersionCheck(tag, VERSION)) {
          throw new Error(
            'VERSION is not updated. Update deno.json & deno task version',
          );
        }
      });
    },
  },
];

for (const check of list) {
  Start(check.name);
  const p = check.command
    ? Exec(check.command).then(check.after)
    : check.after({ stdout: '', stderr: '' });
  await p.then((msg) => {
    Complete(`OK ... ${check.name}${msg ? ': ' + msg : ''}`);
  }).catch((error) => {
    Exit(error.message);
  });
}
