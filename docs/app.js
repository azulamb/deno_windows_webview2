document.addEventListener('DOMContentLoaded', () => {
  const lang = {
    ja: 'ja-jp',
  }[window.navigator.language] || 'en-us';

  let total = 0;
  let implemented = 0;
  const tbody = document.getElementById('list');
  for (const group of DATA.list) {
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
      const td = document.createElement('td');
      td.textContent = item.name;
      if (item.implemented) {
        ++implemented;
        td.classList.add('exists');
      }
      const tr = document.createElement('tr');
      tr.appendChild(document.createElement('td'));
      tr.appendChild(td);
      tbody.appendChild(tr);
    }
  }
  document.getElementById('total').textContent = total.toString();
  document.getElementById('implemented').textContent = implemented.toString();
  document.getElementById('implemented_rate').textContent = ((implemented / total) * 100).toFixed(2);
});
