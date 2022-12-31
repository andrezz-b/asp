#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

void floydwarshall(vector<vector<pair<int, int>>> &graph, vector<vector<int>> &dist, int S, int n) {
  for (int currentVertex = 1; currentVertex <= n; ++currentVertex) {
    dist[currentVertex][currentVertex] = 0;
    for (auto const &edge : graph[currentVertex]) {
      int adjacentVertex, edgeWeight;
      tie(adjacentVertex, edgeWeight) = edge;

      dist[currentVertex][adjacentVertex] = edgeWeight;
    }
  }

  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (dist[i][k] == INF || dist[k][j] == INF) continue;
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  char d;
  cin >> n >> m >> d;

  vector<vector<pair<int, int>>> graph(n + 1);

  int u, v, w;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w;
    graph[u].push_back({v, w});

    if (d == 'N') {
      graph[v].push_back({u, w});
    }
  }

  vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

  floydwarshall(graph, dist, 1, n);

  for (int u = 1; u <= n; ++u) {
    for (int v = 1; v <= n; ++v) {
      if (dist[u][v] < INF) {
        cout << dist[u][v];
      } else {
        cout << "-";
      }
      cout << " ";
    }
    cout << endl;
  }

  return 0;
}