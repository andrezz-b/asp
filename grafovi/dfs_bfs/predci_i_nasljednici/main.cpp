#include <bits/stdc++.h>

#define MAXN 100001
#define MAXQ 500001

int n, ans[MAXQ];
std::vector<int> g[MAXN];
std::vector<std::pair<int, int>> upit[MAXN];
std::set<int> ancestors;


void dfs(int u, int p) {
  // kada dođemo na element dodajemo ga u pretke
  ancestors.insert(u);
  for (auto &up : upit[u]) {
    // up.first - index
    // up.second - element koji tražimo ako je predak
    ans[up.first] = ancestors.count(up.second);
  }
  for (auto v : g[u]) {
    // p - roditelj, da se ne vraćamo unazad
    if (v != p) {
      dfs(v, u);
    }
  }
  // kada završimo s trenutnim on više nije predak
  ancestors.erase(u);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int q;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    int t, u, v;
    std::cin >> t >> u >> v;

    // da li je vrh "u" nasljednik od vrha "v" ==  da li je vrh "v" predak od vrha "u"
    // Ako je t == 0 u je predak od v
    // i služi da ispisujemo po redu kasnije
    if (t == 0) {
      upit[v].push_back({i, u});
    }
    else {
      // Ako je t == 1 "v" je predak od "u"
      upit[u].push_back({i, v});
    }
  }

  dfs(1, 0);

  for (int i = 0; i < q; ++i) {
    std::cout << (ans[i] ? "YES" : "NO") << "\n";
  }
  
  return 0;
}

/* Dobro rješenje ali za svaki upit poziva dfs pa vremensko prekoračenje na zadnjim test caseovima
#include <bits/stdc++.h>

#define FOUND -1
#define MAXN 100005

bool dfs(std::vector<int> graph[], std::vector<bool> &visited,
         int predecessor, int successor, int u) {

  visited[u] = true;

  if (u == predecessor) {
    predecessor = FOUND;
  } else if (u == successor) {
    successor = FOUND;
  }

  if (successor == FOUND && predecessor != FOUND) return false;


  for (auto const &v : graph[u]) {
    if (visited[v]) continue;
    if (predecessor == FOUND && successor == v) return true;
    if (dfs(graph, visited, predecessor, successor, v)) return true;
  }

  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::vector<int> graph[MAXN];

  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;

    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int q;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    int type, u, v;

    std::cin >> type >> u >> v;
    // Uvijek tražimo da je u predak od v
    // tip 1 se možeo obrunto formulirat
    // da li je vrh "u" nasljednik od vrha "v" ==  da li je vrh "v" predak od vrha "u"
    if (type) std::swap(u, v);

    std::vector<bool> visited(n + 1, false);
    std::cout << (dfs(graph, visited, u, v, 1) ? "YES" : "NO") << "\n";
  }

  return 0;
}*/