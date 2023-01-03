#include <bits/stdc++.h>

using namespace std;

#define MAXV 100
#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

struct Graph {
  int adj[MAXV][MAXV];
  int nvertices;
  char labels[MAXV];

  int find_vertex_index(char label) {
    int u;

    for (u = 0; u < nvertices; u++) {
      if (labels[u] == label)
        return u;
    }
    return -1;
  }

  Graph() {
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

  bool dfs(int u, vector<bool> &visited, vector<pair<bool, int>> &currentPath, int count) {
    if (visited[u]) return false;

    visited[u] = true;
    currentPath[u] = {true, count};

    for (int v = 0; v < nvertices; ++v) {
      if (!adj[u][v]) continue;

      // Ako je susjed već u trenutnom putu i udaljenost između nas i susjeda je 2
      // onda to tvori ciklus od 3 vrha
      if (currentPath[v].first && currentPath[u].second - currentPath[v].second == 2) return true;

      if (visited[v]) continue;
      if (dfs(v, visited, currentPath, count + 1)) return true;
    }

    // Kada se maknemo sa vrha mičemo ga s trenutnog puta 
    currentPath[u] = {false, 0};
    return false;
  }

  bool triangle_exists() {
    for (int u = 0; u < nvertices; ++u) {
      std::vector<bool> visited(nvertices + 1, false);
      // Spremamo vrhove koji su u trenutnom putu i njihove udaljenosti od pocetka puta
      std::vector<std::pair<bool, int>> currentPath(nvertices + 1, {false, 0});

      if (dfs(u, visited, currentPath, 0)) return true;
    }

    return false;
  }
};

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);
  Graph *g = new Graph();
  int menu_choice;
  char c;

  do {
    cin >> menu_choice;
    switch (menu_choice) {
    case 1:
      std::cout << (g->triangle_exists() ? "Y" : "N") << "\n";
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
  return 0;
}
