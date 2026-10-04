import {
  catalogFromHeader,
  type Report,
  updateCoverage,
} from './report_data.ts';

function argument(name: string): string | undefined {
  const index = Deno.args.indexOf(name);
  if (index < 0) return undefined;
  const value = Deno.args[index + 1];
  if (!value || value.startsWith('--')) {
    throw new Error(`Missing value for ${name}`);
  }
  return value;
}

const jsonURL = new URL('../docs/dll.json', import.meta.url);
const previous: Report = JSON.parse(await Deno.readTextFile(jsonURL));
const headerPath = argument('--sdk-header');
const version = argument('--version');
if (Boolean(headerPath) !== Boolean(version)) {
  throw new Error('Use --sdk-header and --version together.');
}
const report = headerPath && version
  ? catalogFromHeader(await Deno.readTextFile(headerPath), version)
  : previous;

async function sources(directory: URL, extension: string): Promise<string[]> {
  const result: string[] = [];
  for await (const entry of Deno.readDir(directory)) {
    const url = new URL(entry.name + (entry.isDirectory ? '/' : ''), directory);
    if (entry.isDirectory) result.push(...await sources(url, extension));
    else if (entry.name.endsWith(extension)) {
      result.push(await Deno.readTextFile(url));
    }
  }
  return result;
}

updateCoverage(
  report,
  await sources(new URL('../webview2/source/', import.meta.url), '.cpp'),
  await sources(new URL('../src/', import.meta.url), '.ts'),
);
await Deno.writeTextFile(jsonURL, JSON.stringify(report, null, 2) + '\n');
const template = await Deno.readTextFile(
  new URL('./template.html', import.meta.url),
);
await Deno.writeTextFile(
  new URL('../docs/index.html', import.meta.url),
  template
    .replace(
      '<script></script>',
      `<script>const DATA=${JSON.stringify(report)}</script>`,
    )
    .replace(
      '<dd id="version"></dd>',
      `<dd id="version">${report.version}</dd>`,
    ),
);
console.log(
  `API catalog ${report.version}: ${report.list.length} groups, ${
    report.list.flatMap((group) => group.members).length
  } members`,
);
