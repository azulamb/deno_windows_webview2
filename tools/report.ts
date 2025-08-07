import { Microsoft_Web_WebView2 } from '../src/version.ts';
import { DOMParser } from 'jsr:@b-fuze/deno-dom';
import { params } from '../src/webview2_params.ts';
import dll from '../docs/dll.json' with { type: 'json' };

interface DLL_JSON {
  version: string;
  list: {
    class: string;
    url: string;
    members: {
      name: string;
      implemented: boolean;
    }[];
  }[];
}

const BASEURL =
  'https://learn.microsoft.com/ja-jp/microsoft-edge/webview2/reference/win32/';

function createCachePath(path?: string) {
  if (!path) {
    return new URL(import.meta.resolve('./.cache'));
  }
  return new URL(import.meta.resolve(`./.cache/${path}`));
}

if ((<DLL_JSON> dll).version !== Microsoft_Web_WebView2) {
  const cacheDir = createCachePath();
  try {
    console.log('Creating cache directory:', cacheDir);
    await Deno.mkdir(cacheDir, {});
  } catch (error) {
    console.error(error);
    if (error instanceof Deno.errors.AlreadyExists) {
      // Directory already exists, ignore
    } else {
      console.error('Error creating cache directory:', error);
    }
  }
  // Cache clear.
  for await (const entry of Deno.readDir(cacheDir)) {
    if (!entry.isFile) {
      continue;
    }
    Deno.remove(createCachePath(entry.name));
  }
}

const implemented: { [keys: string]: true } = {};
if ((<DLL_JSON> dll).list) {
  for (const group of (<DLL_JSON> dll).list) {
    for (const item of group.members) {
      if (item.implemented) {
        implemented[
          [group.class, item.name].join('::')
        ] = true;
      }
    }
  }
}

function loadHTML(url: string, file: string) {
  return Deno.readTextFile(createCachePath(file))
    .catch(() => {
      return fetch(url).then((response) => {
        return response.text();
      }).then(async (html) => {
        await Deno.writeTextFile(createCachePath(file), html);
        // Wait for next download.
        await new Promise((resolve) => {
          setTimeout(resolve, 1000);
        });
        return html;
      });
    });
}

const html = await loadHTML(
  `${BASEURL}?view=webview2-${Microsoft_Web_WebView2}`,
  'index.html',
);

const document = new DOMParser().parseFromString(html, 'text/html');
const list = [...document.querySelectorAll('.content li > a')].map((link) => {
  return {
    name: link.textContent,
    url: `${BASEURL}${link.getAttribute('href')}`,
    isHandler: link.textContent.endsWith('Handler'),
  };
});

list.sort((a, b) => {
  if (a.isHandler !== b.isHandler) {
    return a.isHandler ? 1 : -1;
  }
  if (
    a.name.match(/^ICoreWebView2_[0-9]+$/) &&
    b.name.match(/^ICoreWebView2_[0-9]+$/)
  ) {
    const aNum = Number(a.name.replace(/^ICoreWebView2_/, ''));
    const bNum = Number(b.name.replace(/^ICoreWebView2_/, ''));
    return aNum - bNum;
  }
  const aResult = a.name.match(/^(.+[^0-9])([0-9]+)$/);
  const bResult = b.name.match(/^(.+[^0-9])([0-9]+)$/);
  if (aResult && bResult) {
    if (aResult[1] === bResult[1]) {
      return Number(aResult[2]) - Number(bResult[2]);
    }
  }
  return a.name.localeCompare(b.name);
});

const json: DLL_JSON = {
  version: Microsoft_Web_WebView2,
  list: [],
};

const functionNameCount: { [key: string]: number } = {};

for (const item of list) {
  if (item.isHandler) {
    continue; // Skip handlers.
  }

  const html = await loadHTML(item.url, `${item.name}.html`);
  const document = new DOMParser().parseFromString(html, 'text/html');
  json.list.push({
    class: item.name,
    url: item.url,
    members: [
      ...document.querySelectorAll('h2#summary + table tr td:first-child > a'),
    ]
      .map((link) => {
        const name = link.textContent;
        if (functionNameCount[name]) {
          ++functionNameCount[name];
        } else {
          functionNameCount[name] = 1;
        }
        return {
          name,
          implemented: implemented[`${item.name}::${name}`] === true,
        };
      }),
  });
}

for (const group of json.list) {
  for (const item of group.members) {
    if (item.implemented || !(item.name in params)) {
      continue;
    }
    if (functionNameCount[item.name] === 1) {
      item.implemented = true;
    } else {
      console.warn(`Implemented check: ${group.class}::${item.name}`);
    }
  }
}

await Deno.writeTextFile(
  new URL(import.meta.resolve('../docs/dll.json')),
  JSON.stringify(json, null, 2) + '\n',
);
await Deno.readTextFile(new URL(import.meta.resolve('./template.html'))).then(
  (html) => {
    html = html.replace(
      '<script></script>',
      `<script>const DATA=${JSON.stringify(json)}</script>`,
    ).replace(
      '<dd id="version"></dd>',
      `<dd id="version">${json.version}</dd>`,
    );
    return Deno.writeTextFile(
      new URL(import.meta.resolve('../docs/index.html')),
      html,
    );
  },
);
