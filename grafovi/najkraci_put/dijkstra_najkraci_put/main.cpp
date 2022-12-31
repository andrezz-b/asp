#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

// Dovoljno veliki broj 1061109567 pogodan za memset jer su mu sva 4 byte-a ista
const int INF = 0x3f3f3f3f;

void dijkstra(const std::vector<std::pair<int, int>> graph[MAXN], std::vector<int> &minDistance, int start) {
  std::priority_queue<std::pair<int, int>,
      std::vector<std::pair<int, int>>,
      std::greater<std::pair<int, int>>> pq;

  minDistance[start] = 0;
  pq.push({0, start});

  while (!pq.empty()) {
    int currentVertex, distanceToCurrent;

    tie(distanceToCurrent, currentVertex) = pq.top();
    pq.pop();

    if (minDistance[currentVertex] < distanceToCurrent) continue;

    for (auto const &edge : graph[currentVertex]) {
      int adjacentVertex, edgeWeight;
      tie(adjacentVertex, edgeWeight) = edge;

      if (minDistance[currentVertex] + edgeWeight < minDistance[adjacentVertex]) {
        minDistance[adjacentVertex] = minDistance[currentVertex] + edgeWeight;
        pq.push({minDistance[adjacentVertex], adjacentVertex});
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m, s;
  std::vector<pair<int, int>> g[MAXN];

  std::cin >> n >> m >> s;

  for (int i = 0; i < m; ++i) {
    int vertex, adjacentVertex, edgeWeight;

    std::cin >> vertex >> adjacentVertex >> edgeWeight;

    g[vertex].push_back({adjacentVertex, edgeWeight});
    g[adjacentVertex].push_back({vertex, edgeWeight});
  }

  std::vector<int> minDistance(n + 1, INF);

  dijkstra(g, minDistance, s);

  for (int i = 1; i <= n; ++i) {
    std::cout << (minDistance[i] != INF ? minDistance[i] : -1) << "\n";
  }


  return 0;
}