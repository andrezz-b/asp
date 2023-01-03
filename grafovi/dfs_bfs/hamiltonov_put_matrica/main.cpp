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
  int next[MAXV];
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
      next[v] = -1;
      colors[v] = WHITE;
    }
  }
  void initialize_attributes() {
    int v;

    for (v = 0; v < nvertices; v++) {
      next[v] = -1;
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

  bool hamiltonov_put(int u, int distance) {
    colors[u] = GRAY;

    if (distance == nvertices - 1) return true;

    for (int vertex = 0; vertex < nvertices; ++vertex) {
      if (!adj[u][vertex]) continue;
      if (colors[vertex] == GRAY) continue;

      if (hamiltonov_put(vertex, distance + 1)) return true;
    }

    colors[u] = WHITE;
    return false;
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
      cout << (g->hamiltonov_put(u, 0) ? 'Y' : 'N') << "\n";
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
