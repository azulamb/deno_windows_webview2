import { Microsoft_Web_WebView2 } from '../src/version.ts';
import { DOMParser, Element } from 'jsr:@b-fuze/deno-dom';

const BASEURL =
  'https://learn.microsoft.com/ja-jp/microsoft-edge/webview2/reference/win32/';
const URL = `${BASEURL}?view=webview2-${Microsoft_Web_WebView2}`;

const html = await fetch(URL).then((response) => {
  return response.text();
});

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
  if (a.name.match(/^ICoreWebView2_[0-9]+$/) && b.name.match(/^ICoreWebView2_[0-9]+$/)) {
    const aNum = Number(a.name.replace(/^ICoreWebView2_/, ''));
    const bNum = Number(b.name.replace(/^ICoreWebView2_/, ''));
    return aNum - bNum;
  }
  return a.name.localeCompare(b.name);
});
