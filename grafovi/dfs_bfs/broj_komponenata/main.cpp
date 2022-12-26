#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

vector<int> graph[MAXN];
bool bio[MAXN];

void dfs(int u) {
  bio[u] = true;

  for (auto const &el : graph[u]) {
    if (bio[el]) continue;

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

  int count{};

  for (int u = 1; u <= n; ++u) {
    if (bio[u]) continue;
    dfs(u);
    count++;
  }

  std::cout << count << "\n";

  return 0;
}