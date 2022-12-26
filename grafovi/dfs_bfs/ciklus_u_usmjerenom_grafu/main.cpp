#include <bits/stdc++.h>

#define MAXN 100001

std::vector<int> g[MAXN];
bool bio[MAXN], trenutno[MAXN];

bool dfs(int u) {
  bool ret = false;
  bio[u] = trenutno[u] = true;

  // Polje trenutno sadržava sve elemente koji su
  // u našem trenutnom putu

  for (auto const &v : g[u]) {
    // Ako dođemo na element iz trenutnog puta vraćamo true
    // jer smo napravili ciklus
    if (trenutno[v]) return true;
    if (bio[v]) continue;
    ret |= dfs(v);
  }

  // Kada se vraćamo iz elementa mičemo ga iz trenutnog puta
  trenutno[u] = false;
  return ret;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;

    g[u].push_back(v);
  }

  bool cycle = false;

  for (int i = 1; i <= n; ++i) {
    cycle = dfs(i);
    if (cycle) break;
  }

  std::cout << (cycle ? "Y" : "N") << "\n";

  return 0;
}