#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
const int EDGE_WEIGHT = 1;

void floydwarshall(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &minDistance, int n) {
  for (int currentVertex = 1; currentVertex <= n; ++currentVertex) {
    minDistance[currentVertex][currentVertex] = 0;
    for (auto const &vertex : graph[currentVertex]) {
      minDistance[vertex][currentVertex] = minDistance[currentVertex][vertex] = EDGE_WEIGHT;
    }
  }


  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (minDistance[i][k] == INF || minDistance[k][j] == INF) continue;

        if (minDistance[i][k] + minDistance[k][j] < minDistance[i][j]) {
          minDistance[i][j] = minDistance[i][k] + minDistance[k][j];
        }
      }
    }
  }

}

int countElements(std::vector<int> container, int maxValue) {
  // Najmanja udaljenost između elemenata može biti 1
  const int MIN_VALUE = 1;
  int sum = 0;

  for (auto const &el : container) {
    sum += el <= maxValue && el >= MIN_VALUE ? 1 : 0;
  }
  return sum;
}

void ans_floydwarshall(std::vector<std::vector<int>> &graph, int maxRange, int n) {
  std::vector<std::vector<int>> minDistance(n + 1, std::vector<int>(n + 1, INF));

  floydwarshall(graph, minDistance, n);

  for (int u = 1; u <= n; ++u) {
    std::cout << countElements(minDistance[u], maxRange) << "\n";
  }
}

int bfs(std::vector<std::vector<int>> &graph, int startVertex, int maxRange) {
  std::queue<int> q;
  std::vector<bool> visited(graph.size(), false);
  std::vector<int> dist(graph.size(), 0);

  q.push(startVertex);
  dist[startVertex] = 0;
  visited[startVertex] = true;

  int verticesInRange = 0;

  while (!q.empty()) {
    int currentVertex = q.front();
    q.pop();

    for (auto const &adjacent : graph[currentVertex]) {
      if (visited[adjacent]) continue;

      visited[adjacent] = true;
      dist[adjacent] = dist[currentVertex] + 1;
      verticesInRange += dist[adjacent] <= maxRange;
      q.push(adjacent);
    }

  }

  return verticesInRange;
}

void ans_bfs(std::vector<std::vector<int>> &graph, int maxRange, int n) {
  for (int u = 1; u <= n; ++u) {
    std::cout << bfs(graph, u, maxRange) << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m, d;
  std::cin >> n >> m >> d;

  std::vector<std::vector<int>> graph(n + 1);

  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;

    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  // Koristi se bfs jer je netežinski graf pa prvi način
  // kako dođemo do vrha je i najkraći
  ans_bfs(graph, d, n);

  // Prekoračenje memorije radi veličine polja, ali radi
  // ans_floydwarshall(graph, d, n);


  return 0;
}
