#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

void topsort_dfs(int u, vector<vector<int>> &graph, vector<int> &sorted, vector<bool> &visited) {
  if (visited[u]) return;
  visited[u] = true;

  for (auto const &adjacentVertex : graph[u]) {
    if (visited[adjacentVertex]) continue;
    topsort_dfs(adjacentVertex, graph, sorted, visited);
  }

  sorted.push_back(u);
}

// Topolosko sortiranje - Modificirani DFS
void topsort1(vector<vector<int>> &graph, vector<int> &sorted, int n) {
  std::vector<bool> visited(n + 1, false);

  for (int i = 1; i <= n; ++i) {
    topsort_dfs(i, graph, sorted, visited);
  }

}

// Topolosko sortiranje - Khanov algoritam
void topsort2(vector<vector<int>> &graph, vector<int> &indegree, vector<int> &sorted, int n) {
  std::queue<int> q;

  for (int currentVertex = 1; currentVertex <= n; ++currentVertex) {
    if (!indegree[currentVertex]) q.push(currentVertex);
  }

  while (!q.empty()) {
    int currentVertex = q.front();
    q.pop();

    sorted.push_back(currentVertex);

    for (auto const &adjacentVertex : graph[currentVertex]) {
      indegree[adjacentVertex]--;
      if (!indegree[adjacentVertex]) {
        q.push(adjacentVertex);
      }
    }
  }

  std::reverse(sorted.begin(), sorted.end());
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> graph(n + 1);
  vector<int> indegree(n + 1);

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;

    graph[u].push_back(v);
    indegree[v]++;
  }

  vector<int> sorted;

  // topsort1(graph, sorted, n);
  topsort2(graph, indegree, sorted, n);

  for (auto u : sorted) {
    cout << u << " ";
  }
  cout << endl;

  return 0;
}