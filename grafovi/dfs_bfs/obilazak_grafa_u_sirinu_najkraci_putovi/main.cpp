#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

void bfs(std::vector<int> *graph, int *dist) {
  std::queue<int> q;
  bool visited[MAXN] = {};

  q.push(1);
  dist[1] = 0;
  visited[1] = true;

  while (!q.empty()) {
    int current = q.front();
    q.pop();
    for (auto const &el : graph[current]) {
      if (visited[el]) continue;

      // Udaljenost trenutnog je udaljenost od kojeg gledamo + 1
      dist[el] = dist[current] + 1;
      q.push(el);
      visited[el] = true;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  // n - broj vrhova, m - broj bridova
  int n{}, m{};
  std::cin >> n >> m;
  std::vector<int> graph[MAXN];


  for (int i = 1; i <= m; ++i) {
    int u{}, v{};

    std::cin >> u >> v;
    // neusmjeren graf u je susjed v i v je susjed u
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int dist[MAXN] = {};

  bfs(graph, dist);

  for (int i = 1; i <= n; ++i) {
    std::cout << dist[i] << "\n";
  }

  return 0;
}