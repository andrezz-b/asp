#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

const float INF = 0x7f7f7f7f;

float h_func(int n, int D, map<int, pair<float, float>> &nodes) {
  float x1, y1, x2, y2;

  tie(x1, y1) = nodes[n];
  tie(x2, y2) = nodes[D];

  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void a_star(std::vector<std::vector<std::pair<int, int>>> &graph,
            std::vector<float> &minDistanceHeuristic,
            int S, int D,
            std::map<int, std::pair<float, float>> &nodes,
            std::vector<std::pair<float, float>> &minDistanceWeighted) {

  // spremamo {heruistička udaljenost, vrh}
  std::priority_queue< std::pair<float, int>,
      std::vector<std::pair<float, int>>,
      std::greater<std::pair<float, int>>
      > pq;

  minDistanceHeuristic[S] = 0;
  pq.push({0, S});

  minDistanceWeighted[S] = { -1, 0};

  while (!pq.empty()) {
    float heuristicDistanceToCurrent; // heuristička udaljenost do trenutnog
    int currentVertex; // vrh

    tie(heuristicDistanceToCurrent, currentVertex) = pq.top();
    pq.pop();

    // Ako smo pronasli cilj
    if (currentVertex == D) return;

    // Ako je udaljenost do gledanog vec najmanja
    if (minDistanceHeuristic[currentVertex] < heuristicDistanceToCurrent) continue;

    float minWegihtedDistanceToCurrent = minDistanceWeighted[currentVertex].second;

    for (auto const &edge : graph[currentVertex]) {
      int adjacentVertex; // susjedni vrh
      int edgeWeight; // udaljenost od trenutnog do susjeda (težinska)

      tie(adjacentVertex, edgeWeight) = edge;

      // Udaljenost od početka do susjeda, ovo se koristi kod dijkstre u if-u
      // u dijkstriu: minDistance[currentVertex] + edgeWeight
      // g(n) funkcija iz prezentacije
      float minWegihtedDistanceToAdjacent = minWegihtedDistanceToCurrent + edgeWeight;

      // težinska udaljenost i heuristika
      float f_func = minWegihtedDistanceToAdjacent + h_func(adjacentVertex, D, nodes);

      // isti if kao i kod dijsktre, ali ovdje uspoređujemo heurističke udaljenosti
      if (f_func < minDistanceHeuristic[adjacentVertex]) { 
        minDistanceHeuristic[adjacentVertex] = f_func;

        // ovo je previous iz main-a, zove se previous jer prvi element u paru je vrh koji
        // dolazi prije susjeda (koristi se kod ispisa), drugi element je minimalna težinska udaljenost
        minDistanceWeighted[adjacentVertex] = {currentVertex, minWegihtedDistanceToCurrent + edgeWeight};
        // u pq dodajemo heurističke
        pq.push({minDistanceHeuristic[adjacentVertex], adjacentVertex});
      }
    }
  }

}

void ispisi_put(int s, int d, vector<pair<float, float>> &previous,  vector<float> dist) {
  if (s == d) {
    cout << d << " " << dist[d] << endl;
    return;
  }

  ispisi_put(s, previous[d].first, previous, dist);
  cout << d << " " << dist[d] << endl;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m, S, D;
  std::cin >> n >> m >> S >> D;

  // Mapa čvorova i njihovih pozicija u prostoru (koordinatni sustav)
  std::map<int, std::pair<float, float>> nodes;

  for (int i = 1; i <= n; ++i) {
    float x, y;
    std::cin >> x >> y;
    nodes[i] = {x, y};
  }

  // Graf kao lista susjedstava, {vrh, težina brida}
  std::vector<std::vector<std::pair<int, int>>> graph(n + 1);

  for (int j = 0; j < m; ++j) {
    int u, v, w;
    std::cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  // vektor za heuristiku
  std::vector<float> minDistanceHeuristic(n + 1, INF);

  // vektor za prethodni i normalna (težinska) udaljenost do prethodnog
  // {prethodni vrh, težinska udaljenost do mene}
  // previous[5] = {vrh 3, 27 -> težinska udaljenost do 5} 
  std::vector<std::pair<float, float>> previous(n + 1, { -1, -1});

  a_star(graph, minDistanceHeuristic, S, D, nodes, previous);

  ispisi_put(S, D, previous, minDistanceHeuristic);

  return 0;
}