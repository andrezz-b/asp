#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const int INF = 0x3f3f3f3f;

int bellmanford(vector<vector<pair<int, int>>> &graph, vector<int> &minDistance, int S, int n) {
  minDistance[S] = 0;

  // petlja po i -> n - 1 iteracija
  // idemo po n - 1 iteracija jer najkraći put nikada neće imati u sebi više vrhova
  // nego što ih je ukupno u grafu
  for (int i = 0; i < n - 1; ++i) {

    for (int currentVertex = 1; currentVertex <= n; ++currentVertex) {

      // Ako je udaljenost do trenutnog vrha beskonačno znači da
      // još do njega ne možemo doći pa idemo na slijedeći
      if (minDistance[currentVertex] == INF) continue;

      // Prolazimo po svim bridovima za trenutni
      for (auto const &edge : graph[currentVertex]) {
        int vertex, weight;
        tie(vertex, weight) = edge;

        // Kao i kod dijkstre samo bez dodavanja u red
        // Ako je udaljenost preko nas do našeg susjeda manja od trenutno najmanje
        // stavljamo udaljenost preko nas kao najmanju do sada
        minDistance[vertex] = std::min(minDistance[currentVertex] + weight, minDistance[vertex]);
      }
    }

  }

  for (int currentVertex = 0; currentVertex <= n; ++currentVertex) {
    // Ako je udaljenost do trenutnog vrha beskonačno znači da
    // do njega ne možemo doći pa idemo dalje
    // npr. ako nam naš početak nije povezan s nekim drugim grafom (nepovezani grafovi)
    if (minDistance[currentVertex] == INF) continue;
    for (auto const &edge : graph[currentVertex]) {
      int vertex, weight;
      tie(vertex, weight) = edge;

      // Kako nakon n - 1 prolaska po svim bridovima imamo sigurno najmanje udaljenosti
      // onda ako opet ovdje nalazimo manju udaljenost onda je to negativni ciklus
      if (minDistance[currentVertex] + weight < minDistance[vertex]) {
        return -1;
      }
    }
  }


  return 0;
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
  }

  vector<int> dist(n + 1, INF);

  int retval = bellmanford(graph, dist, 1, n);

  if (retval == -1) {
    cout << "Detektiran negativan ciklus." << endl;
  } else {
    for (int u = 1; u <= n; ++u) {
      cout << (dist[u] < INF ? dist[u] : -1) << endl;
    }
  }

  return 0;
}