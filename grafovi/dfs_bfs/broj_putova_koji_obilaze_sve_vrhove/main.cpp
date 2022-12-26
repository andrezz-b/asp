#include <bits/stdc++.h>

#define MAXN 9

void dfs(std::vector<int> graph[],
         std::vector<bool> &visited,
         int n, int u, int &count, int &ans) {

  // dolazimo na novi vrh, označujemo da smo ga posjetili
  // i povećavamo broj vrhova koji smo posjetili
  visited[u] = true;
  count++;

  // kako je ovo dfs, kada dođemo do n vrhova to je jedan
  // specifičan put koji prolazi sve vrhove pa povećavamo rezultat
  if (count == n) ans++;

  for (auto const &v : graph[u]) {
    if (visited[v]) continue;
    dfs(graph, visited, n, v, count, ans);
  }

  // kada završimo s trenutnim vrhom stavljamo ga da nije posjećen
  // i umanjujemo broj posjećenih za 1 jer se vraćamo unazad
  // ovo nam pomaže da dođemo do svih mogućnosti jer sada možemo provjeriti ako
  // pomoću drugog vrha možemo opet doći do ovoga i time dobijemo još jedan put
  // koji prolazi svim vrhovima točno 1
  visited[u] = false;
  count--;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> graph[MAXN];

  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;

    graph[u].push_back(v);
    graph[v].push_back(u);
  }


  int count = 0;
  int ans = 0;
  std::vector<bool> visited(n + 1, false);

  dfs(graph, visited, n, 1, count, ans);

  std::cout << ans << "\n";

  return 0;
}