#include <bits/stdc++.h>

#define MAXN 100001

void dfs(int u, std::vector<bool> &visited, const std::vector<std::vector<int>> &graph, std::vector<int> &sorted) {
  if (visited[u]) return;

  visited[u] = true;

  for (auto const &vertex : graph[u]) {
    if (visited[vertex]) continue;

    dfs(vertex, visited, graph, sorted);
  }

  sorted.push_back(u);
}

void topsort_dfs(const std::vector<std::vector<int>> &graph, std::vector<int> &sorted, const int &n) {
  std::vector<bool> visited(n + 1, false);
  for (int i = 1; i <= n; ++i) {
    dfs(i, visited, graph, sorted);
  }

  std::reverse(sorted.begin(), sorted.end());
}

void topsort_khan(const std::vector<std::vector<int>> &graph, std::vector<int> &sorted, std::vector<int> &indegree, const int &n) {
  std::queue<int> q;
  for (int vertex = 1; vertex <= n; ++vertex) {
    if (!indegree[vertex]) q.push(vertex);
  }

  while (!q.empty()) {
    int currentVertex = q.front();
    q.pop();

    sorted.push_back(currentVertex);

    for (auto const &adjacentVertex : graph[currentVertex]) {
      indegree[adjacentVertex]--;
      if (!indegree[adjacentVertex]) q.push(adjacentVertex);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n + 1);
  std::vector<int> indegree(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;

    indegree[u]++;
    graph[v].push_back(u);
  }
  std::vector<int> sorted;

  //topsort_khan(graph, sorted, indegree, n);
  topsort_dfs(graph, sorted, n);

  for (auto const &el : sorted) {
    std::cout << el << " ";
  }
  
  return 0;
}