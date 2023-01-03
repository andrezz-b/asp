#include <bits/stdc++.h>

using namespace std;

#define MAXV 100
#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define TRUE  1
#define FALSE 0

#define WHITE 0
#define GRAY  1
#define BLACK 2

typedef int color;

struct Graph {
  int adj[MAXV][MAXV];
  int nvertices;
  char labels[MAXV];
  int distances[MAXV];
  color colors[MAXV];

  int find_vertex_index(char label) {
    int u;

    for (u = 0; u < nvertices; u++) {
      if (labels[u] == label)
        return u;
    }
    return -1;
  }

  Graph() {
    int v;
    nvertices = 0;
    for (v = 0; v < nvertices; v++) {
      distances[v] = 0;
      colors[v] = WHITE;
    }
  }
  void initialize_attributes() {
    int v;

    for (v = 0; v < nvertices; v++) {
      distances[v] = 0;
      colors[v] = WHITE;
    }
  }
  void initialize_graph() {
    int u, v;

    nvertices = 0;
    for (u = 0; u < MAXV; u++) {
      for (v = 0; v < MAXV; v++) {
        adj[u][v] = 0;
      }
    }
  }

  void print_graph() {
    int u, v;

    for (u = 0; u < nvertices; u++) {
      cout << labels[u] << ": ";
      for (v = 0; v < nvertices; v++) {
        if (adj[u][v]) {
          cout << " " << labels[v];
        }
      }
      cout << "\n";
    }
  }

  int add_vertex(char label) {
    int u;

    u = nvertices++;
    labels[u] = label;
    return u;
  }

  void insert_edge_vertices() {
    char label;
    int u, v;

    cin >> label;

    u = find_vertex_index(label);

    if (u == -1) u = add_vertex(label);
    cin >> label;
    if (label == '/') return;
    v = find_vertex_index(label);
    if (v == -1) v = add_vertex(label);
    adj[u][v] = adj[v][u] = 1;
    //print_graph();
  }

  void read_graph() {
    int i, nedges;
    cin >> nedges;
    for (i = 0; i < nedges; i++) {
      insert_edge_vertices();

    }
  }

  void najudaljeniji_vrhovi_dijkstra(int u) {
    const int EDGE_WEIGHT = 1;
    for (auto &el : distances) {
      el = INT_MAX;
    }

    std::priority_queue<std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>> pq;
    int maxDist = 0;
    distances[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
      int currentVertex, distanceToCurrent;

      tie(distanceToCurrent, currentVertex) = pq.top();
      pq.pop();

      maxDist = std::max(distances[currentVertex], maxDist);

      if (distances[currentVertex] < distanceToCurrent) continue;

      for (int adjacent = 0; adjacent < nvertices; ++adjacent) {
        if (!adj[currentVertex][adjacent]) continue;

        if (distances[currentVertex] + EDGE_WEIGHT < distances[adjacent]) {
          distances[adjacent] = distanceToCurrent + EDGE_WEIGHT;
          pq.push({distances[adjacent], adjacent});
        }
      }
    }

    for (int vertex = 0; vertex < nvertices; ++vertex) {
      if (distances[vertex] >= maxDist) {
        std::cout << labels[vertex] << " ";
      } 
    }
    std::cout << "\n" << maxDist << "\n";
  }

  void najudaljeniji_vrhovi_bfs(int u) {
    std::queue<int> q;

    q.push(u);
    distances[u] = 0;
    colors[u] = GRAY;
    int maxDist = 0;

    while (!q.empty()) {
      int currentVertex = q.front();
      q.pop();

      maxDist = std::max(maxDist, distances[currentVertex]);

      for (int adjacent = 0; adjacent < nvertices; ++adjacent) {
        if (!adj[currentVertex][adjacent]) continue;
        if (colors[adjacent] != WHITE) continue;

        distances[adjacent] = distances[currentVertex] + 1;
        colors[adjacent] = GRAY;
        q.push(adjacent);
      } 
    }

    for (int vertex = 0; vertex < nvertices; ++vertex) {
      if (distances[vertex] >= maxDist) {
        std::cout << labels[vertex] << " ";
      } 
    }
    std::cout << "\n" << maxDist << "\n";
  }
};


int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  Graph *g = new Graph();
  int u, menu_choice;
  char label, c;

  do {
    cin >> menu_choice;
    switch (menu_choice) {
    case 1:
      cin >> label;
      u = g->find_vertex_index(label);
      if (u == -1) break;
      g->initialize_attributes();
      g->najudaljeniji_vrhovi_bfs(u);
      // g->najudaljeniji_vrhovi_dijkstra(u);
      break;
    case 2:
      g = new Graph();
      g->read_graph();
      break;
    case 3:
      g->print_graph();
      break;
    case 4:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 4);
  delete g;
  return 0;
}
