#include <bits/stdc++.h>

std::vector<int> g[26];
int bio[26], can[26][26];

void dfs(int s, int u) {
  bio[u] = 1;

  can[s][u] = 1;

  for (auto const &v : g[u]) {
    if (bio[v]) continue;
    dfs(s, v);
  }
}

bool tryEncrypt(std::string first, std::string second) {
  // Različite duljine
  if (first.length() != second.length()) return false;

  for (unsigned i = 0; i < first.length(); ++i) {
    // Ako odmah možemo, prelazimo na drugo slovo
    if (can[first[i] - 'a'][second[i] - 'a']) continue;

    // Resetriaj bio da možemo proći sve opet
    memset(bio, 0, sizeof(bio));
    dfs(first[i] - 'a', first[i] - 'a');

    // Ako nakon pretrage opet ne možemo onda sigurno ne možemo
    if (!can[first[i] - 'a'][second[i] - 'a']) return false;
  }

  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;

  std::cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    char u, v;
    std::cin >> u >> v;

    g[u - 'a'].push_back(v - 'a');
    can[u - 'a'][v - 'a'] = 1;
  }

  for (int i = 0; i < m; ++i) {
    std::string first, second;
    std::cin >> first >> second;

    std::cout << (tryEncrypt(first, second) ? "yes" : "no") << "\n";
  }

  return 0;
}