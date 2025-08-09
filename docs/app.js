document.addEventListener('DOMContentLoaded', () => {
  const lang = {
    ja: 'ja-jp',
  }[window.navigator.language] || 'en-us';

  let total = 0;
  let implemented = 0;
  let defined = 0;
  const table = document.getElementById('list');
  for (const group of DATA.list) {
    const tbody = document.createElement('tbody');
    table.appendChild(tbody);
    const link = document.createElement('a');
    link.target = '_blank';
    link.rel = 'noopener noreferrer';
    link.href = group.url;
    link.textContent = group.class;
    const td = document.createElement('td');
    td.colSpan = 2;
    td.appendChild(link);
    const tr = document.createElement('tr');
    tr.appendChild(td);
    tbody.appendChild(tr);

    for (const item of group.members) {
      ++total;
      const check = document.createElement('input');
      check.type = 'checkbox';
      check.readOnly = true;
      const tdImplemented = document.createElement('td');
      tdImplemented.appendChild(check);
      const tdMember = document.createElement('td');
      tdMember.textContent = item.name;
      if (item.implemented) {
        ++implemented;
        tdMember.classList.add('exists');
      }
      if (item.defined) {
        ++defined;
        check.checked = true;
      }
      if (item.name.match(/^(add|put|get)_/)) {
        tdMember.classList.add('space3');
      } else if (!item.name.match(/^remove_/)) {
        tdMember.classList.add('space7');
      }
      const tr = document.createElement('tr');
      tr.appendChild(tdImplemented);
      tr.appendChild(tdMember);
      tbody.appendChild(tr);
    }
  }
  document.getElementById('total').textContent = total.toString();
  document.getElementById('implemented').textContent = implemented.toString();
  document.getElementById('implemented_rate').textContent = ((implemented / total) * 100).toFixed(2);
  document.getElementById('defined').textContent = defined.toString();
  document.getElementById('defined_rate').textContent = ((defined / total) * 100).toFixed(2);
});
