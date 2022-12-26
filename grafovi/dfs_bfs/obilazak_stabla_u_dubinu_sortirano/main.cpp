#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

vector<int> graph[MAXN], ans;
bool visited[MAXN];

// u - pocetni vrh
void dfs(int u) {
  visited[u] = true;
  ans.push_back(u);

  std::sort(graph[u].begin(), graph[u].end());

  for (auto const &el : graph[u]) {
    if (visited[el]) continue;

    dfs(el);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n{}, m{};
  std::cin >> n >> m;


  for (int i = 1; i <= m; ++i) {
    int u{}, v{};

    std::cin >> u >> v;

    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs(1);

  for (auto const &i : ans) {
    std::cout << i << "\n";
  }

  return 0;
}