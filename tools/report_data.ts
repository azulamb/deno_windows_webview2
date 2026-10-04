export interface Report {
  /** SDK version used for the API catalog, independent of the DLL build SDK. */
  version: string;
  list: {
    class: string;
    url: string;
    members: { name: string; defined: boolean; implemented: boolean }[];
  }[];
}

export function withoutComments(source: string): string {
  return source.replace(/\/\*[\s\S]*?\*\//g, '').replace(/^\s*\/\/.*$/gm, '');
}

/** Parse the C++ interface declarations from an official stable SDK header. */
export function catalogFromHeader(header: string, version: string): Report {
  if (!/^\d+\.\d+\.\d+\.\d+$/.test(version)) {
    throw new Error('Specify a stable SDK version.');
  }
  const list: Report['list'] = [];
  for (
    const match of header.matchAll(
      /MIDL_INTERFACE\("[^"]+"\)\s+(ICoreWebView2\w*)\s*:\s*public\s+\w+\s*\{([\s\S]*?)\n\s*\};/g,
    )
  ) {
    const name = match[1];
    if (name.endsWith('Handler')) continue;
    const members = [
      ...withoutComments(match[2]).matchAll(
        /virtual\s+\w+\s+STDMETHODCALLTYPE\s+(\w+)\s*\(/g,
      ),
    ].map((m) => ({ name: m[1], defined: false, implemented: false }));
    list.push({
      class: name,
      url:
        `https://learn.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/${name.toLowerCase()}?view=webview2-${version}`,
      members,
    });
  }
  if (!list.some((group) => group.class === 'ICoreWebView2')) {
    throw new Error('No WebView2 interfaces found in SDK header.');
  }
  const plain = withoutComments(header);
  list.unshift({
    class: 'Globals',
    url:
      `https://learn.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/webview2-idl?view=webview2-${version}`,
    members: [...plain.matchAll(/STDAPI\s+(\w+)\s*\(/g)].map((m) => ({
      name: m[1],
      defined: false,
      implemented: false,
    })),
  });
  for (
    const match of plain.matchAll(
      /typedef\s+enum\s+(COREWEBVIEW2_\w+)\s*\{([\s\S]*?)\}\s*\w+\s*;/g,
    )
  ) {
    list.push({
      class: match[1],
      url:
        `https://learn.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/webview2-idl?view=webview2-${version}`,
      members: [...match[2].matchAll(/\b(COREWEBVIEW2_\w+)\s*=/g)].map((m) => ({
        name: m[1],
        defined: false,
        implemented: false,
      })),
    });
  }
  for (
    const match of plain.matchAll(
      /typedef\s+struct\s+(COREWEBVIEW2_\w+)\s*\{([\s\S]*?)\}\s*\w+\s*;/g,
    )
  ) {
    list.push({
      class: match[1],
      url:
        `https://learn.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/${
          match[1].toLowerCase()
        }?view=webview2-${version}`,
      members: [...match[2].matchAll(/\b(\w+)\s*;/g)].map((m) => ({
        name: m[1],
        defined: false,
        implemented: false,
      })),
    });
  }
  return { version, list };
}

/** Recompute both flags from native definitions and active TypeScript symbol references. */
export function updateCoverage(
  report: Report,
  nativeSources: string[],
  typescriptSources: string[],
): void {
  const native = new Set<string>();
  for (const source of nativeSources) {
    for (
      const match of withoutComments(source).matchAll(
        /EXPORT\s+\w+\s+(\w+)\s*\([\s\S]*?\)\s*\{/g,
      )
    ) native.add(match[1]);
  }
  const used = new Set<string>();
  for (const source of typescriptSources) {
    for (
      const match of withoutComments(source).matchAll(/\.symbols\s*\.\s*(\w+)/g)
    ) used.add(match[1]);
  }
  for (const group of report.list) {
    let prefix = group.class.replace(/^ICoreWebView2/, '').replace(
      /(?:_\d+|\d+)$/,
      '',
    );
    if (!prefix) prefix = 'WebView2';
    else if (prefix === 'Controller') prefix = 'Controllers';
    else if (prefix === 'Environment') prefix = 'Environments';
    else if (group.class === 'Globals') prefix = 'Global';
    for (const member of group.members) {
      const symbol = `${prefix}_${member.name}`;
      member.defined = native.has(symbol);
      member.implemented = member.defined && used.has(symbol);
    }
  }
}
