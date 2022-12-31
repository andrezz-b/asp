#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

void dijkstra(vector<vector<pair<int, int>>> &graph, vector<int> &minDistance, int S) {
  std::priority_queue<std::pair<int, int>,
      std::vector<std::pair<int, int>>,
      std::greater<std::pair<int, int>>> pq;

  pq.push({0, S});
  minDistance[S] = 0;

  while (!pq.empty()) {
    int distanceToCurrent, currentVertex;

    tie(distanceToCurrent, currentVertex) = pq.top();
    pq.pop();

    // Ako već imamo manju udaljenost do ovog vrha onda sve ostale
    // udaljenosti pomoću ove će sigurno biti manje
    if (minDistance[currentVertex] < distanceToCurrent) continue;

    for (auto const &edge : graph[currentVertex]) {
      int adjacentVertex, edgeWeight;
      tie(adjacentVertex, edgeWeight) = edge;

      // Ako je udaljenost preko nas do našeg susjeda manja od trenutno najmanje
      // stavljamo udaljenost preko nas kao najmanju do sada i dodajemo u red
      if (minDistance[currentVertex] + edgeWeight < minDistance[adjacentVertex]) {
        minDistance[adjacentVertex] = minDistance[currentVertex] + edgeWeight;
        pq.push({minDistance[adjacentVertex], adjacentVertex});
      }
    }
  }

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> graph(n + 1);

  int u, v, w;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  vector<int> dist(n + 1, INF);

  dijkstra(graph, dist, 1);

  for (int u = 1; u <= n; ++u) {
    cout << (dist[u] < INF ? dist[u] : -1) << endl;
  }

  return 0;
}