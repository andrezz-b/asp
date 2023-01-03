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

    for (v = 0; v < nvertices; v++) {
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
  void initialize_attributes() {
    int v;

    for (v = 0; v < nvertices; v++) {
      colors[v] = WHITE;
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

  void dfs(int u) {
    int v;

    colors[u] = GRAY;
    for (v = 0; v < nvertices; v++) {
      if (adj[u][v]) {
        if (colors[v] == WHITE) {
          dfs(v);
        }
      }
    }
    colors[u] = BLACK;
  }

  int num_edges() {
    int u, v, sum = 0;
    for (u = 0; u < nvertices; u++) {
      for (v = 0; v < nvertices; v++) {
        sum += adj[u][v];
      }
    }
    return sum / 2;
  }

  bool is_connected() {
    int u;

    initialize_attributes();
    dfs(0);
    for (u = 0; u < nvertices; u++) {
      if (colors[u] != BLACK) return false;
    }
    initialize_attributes();
    return true;
  }

  int obrisi_bridove(int u) {
    if (colors[u] == GRAY) return 0;

    colors[u] = GRAY;
    int sum = 0;

    for (int v = 0; v < nvertices; v++) {
      if (!adj[u][v]) continue;
      if (colors[v] == GRAY) continue;

      int ret = obrisi_bridove(v);
      if (ret % 2 == 0) {
        adj[u][v] = adj[v][u] = 0;
      } else {
        sum += ret;
      }

    }
    return sum + 1;
  }

};

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  Graph *g = new Graph();
  int menu_choice;
  char c;

  setbuf(stdout, NULL);
  do {
    cin >> menu_choice;
    switch (menu_choice) {
    case 1:
      g->initialize_attributes();
      //obrisi bridove
      g->obrisi_bridove(0);
      break;
    case 2:
      do {
        g = new Graph();
        g->read_graph();
      } while (g->nvertices % 2 || !g->is_connected() || g->num_edges() != g->nvertices - 1);
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
