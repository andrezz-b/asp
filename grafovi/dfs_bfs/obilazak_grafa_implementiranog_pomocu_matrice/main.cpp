#include <bits/stdc++.h>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define TRUE  1
#define FALSE 0
#define MAXV 100

#define WHITE 0
#define GRAY  1 // trenutno se obraduje
#define BLACK 2

typedef int color;

struct Graph {
  int adj[MAXV][MAXV]; // matrica susjedstava
  int nvertices; // broj vrhova
  char labels[MAXV]; // polje oznaka (redovi u matrici)
  color colors[MAXV];

  Graph() {
  }


  // svi vrhovi pobojani u bijelo
  void initialize_attributes() {
    int v;

    for (v = 0; v < nvertices; v++) {
      colors[v] = WHITE;
    }
  }
  // inicijalizacija matrice susjedstava
  void initialize_graph() {
    int u, v;

    nvertices = 0;
    for (u = 0; u < MAXV; u++) {
      for (v = 0; v < MAXV; v++) {
        adj[u][v] = 0;
      }
    }
    initialize_attributes();
  }
  int find_vertex_index(char label) {
    int u;

    for (u = 0; u < nvertices; u++) {
      if (labels[u] == label)
        return u;
    }
    return -1;
  }
  void process_vertex(int u) {
    cout << "Obradjujem vrh " << labels[u] << "\n";
  }

  void process_edge(int u, int v) {
    cout << "Obradjujem brid (" << labels[u] << "," << labels[v] << ")\n";
  }

  void print_graph() {
    int u, v;
    // ispisi sve labele grafa
    for (u = 0; u < nvertices; u++) {
      cout << labels[u] << ": ";
      for (v = 0; v < nvertices; v++) { // ispisi sve susjede
        if (adj[u][v])
          cout << " " << labels[v];
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
  }

  void read_graph() {
    int i, nedges;

    // DEBUG("Unesite broj bridova: ");
    cin >> nedges;
    for (i = 0; i < nedges; i++) {
      // DEBUG("Unesite oznake vrhova brida %d ", i + 1);
      insert_edge_vertices();
    }
  }

  void bfs(int u) {
    std::queue<int> q;

    q.push(u);
    colors[u] = GRAY;


    while (!q.empty()) {
      int u = q.front();
      q.pop();

      process_vertex(u);

      // po stupcima
      for (int v = 0; v < nvertices; ++v) {
        if (adj[u][v] && colors[v] == WHITE) {
          colors[v] = GRAY;
          q.push(v);
          process_edge(u, v);
        }
      }
      colors[u] = BLACK;
    }
  }

  void dfs_rec(int u) {
    colors[u] = GRAY;

    for (int v = 0; v < nvertices; ++v) {
      if (adj[u][v] && colors[v] == WHITE) {
        process_edge(u, v);
        dfs_rec(v);
      }
    }

    process_vertex(u);
    colors[u] = BLACK;
  }

  void dfs(int u) {
    stack<int> stack;
    int v;

    colors[u] = GRAY;
    stack.push(u);  // push

    while (!stack.empty()) {
      u = stack.top();

      // prolazimo po susjedima od 'u' u matricu susjedstava
      for (v = 0; v < nvertices; v++) {

        // Ako je v nas susjed i ne obrađuje se dodajemo ga na stack
        // i njega obrađujemo
        if (adj[u][v]) {
          if (colors[v] == WHITE) {
            process_edge(u, v);
            colors[v] = GRAY;
            stack.push(v);  // push
            // Breakamo jer moramo odmah v ići obrađivati kako je ovo DFS
            break;
          }
        }
      }
      // ovo se izvrašava jedino kad prođemo kroz sve susjede
      // odnosno svi naši susjedi se obrađuju već ili ih nemamo
      // tada ono što je na vrhu stoga je gotovo s obrađivanjem
      // jer nema više gdje ići pa ga stavljamo u Black
      if (v == nvertices) {
        u = stack.top();
        stack.pop();
        process_vertex(u);
        colors[u] = BLACK;
      }
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Graph g;
  int u, menu_choice;
  char label, c;

  do {
    // DEBUG("\n1.Unos grafa\n");
    // DEBUG("2.Ispisi\n");
    // DEBUG("3.BFS\n");
    // DEBUG("4.DFS\n");
    // DEBUG("5.DFS rekurzivno\n");
    // DEBUG("6.Izlaz\n");
    // DEBUG("Odabir:\t");
    cin >> menu_choice;
    switch (menu_choice) {
    case 1:
      g.initialize_graph();
      g.read_graph();
      break;
    case 2:
      // DEBUG("\nIspis grafa:\n");
      g.print_graph();
      break;
    case 3:
      // DEBUG("\nUnesite oznaku vrha:\n");
      cin >> label;
      u = g.find_vertex_index(label);
      if (u == -1) break;
      g.initialize_attributes();
      // DEBUG("\nPretrazivanje prvo u sirinu:\n");
      g.bfs(u);
      break;
    case 4:
      // DEBUG("\nUnesite oznaku vrha:\n");
      cin >> label;
      u = g.find_vertex_index(label);
      if (u == -1) break;
      g.initialize_attributes();
      // DEBUG("\nPretrazivanje prvo u dubinu:\n");
      g.dfs(u);
      break;
    case 5:
      // DEBUG("\nUnesite oznaku vrha:\n");
      cin >> label;
      u = g.find_vertex_index(label);
      if (u == -1) break;
      g.initialize_attributes();
      // DEBUG("\nRekurzivno pretrazivanje prvo u dubinu:\n");
      g.dfs_rec(u);
      break;
    case 6:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 6);
  return 0;
}
