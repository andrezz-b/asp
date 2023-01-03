#include <bits/stdc++.h>
#include <string.h>

using namespace std;

#define MAXV 100
#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef int colors;

#define QUEUESIZE 1000

#define MAXV 100
#define MAXLABEL 10
#define INITDIST INT_MAX

struct Edge;
typedef struct Vertex {
  char label[MAXLABEL];
  struct Edge *edges;
  // opcionalni atributi
  int distance;
  colors color;
} vertex;
typedef struct Edge
{
  struct Vertex* u;
  struct Vertex* v;
  struct Edge* next;
  // opcionalni atributi
  int weight;
} edge;

struct Graph
{
  vertex* vertices[MAXV];
  bool directed;
  bool weighted;
  int nvertices;

  int find_vertex_index(vertex* v)
  {
    int i;

    for (i = 0; i < nvertices; i++)
    {
      if (vertices[i] == v)
        return i;
    }
    return -1;
  }

  vertex* find_vertex(char label[])
  {
    int i;

    for (i = 0; i < nvertices; i++)
    {
      if (!strcmp(vertices[i]->label, label))
        return vertices[i];
    }
    return NULL;
  }

  Graph(bool directed, bool weighted)
  {
    directed = directed;
    weighted = weighted;
    nvertices = 0;
  }

  vertex* add_vertex(char label[])
  {
    int i;
    vertex* v;

    if (nvertices >= MAXV)
    {
      return NULL;
    }
    for (i = 0; i < nvertices; i++)
    {
      v = vertices[i];
      if (!strcmp(v->label, label))
      {
        return NULL;
      }
    }
    v = (vertex*)malloc(sizeof(vertex));
    strcpy(v->label, label);
    v->edges = NULL;
    v->distance = INITDIST;
    v->color = WHITE;


    vertices[nvertices++] = v;
    return v;
  }

  void clear_edges_list(edge* e)
  {
    if (!e)
      return;
    clear_edges_list(e->next);
    free(e);
  }
  void delete_vertex(vertex* u)
  {
    int i;

    for (i = 0; i < nvertices; i++)
      delete_edge(vertices[i], u, true);
    i = find_vertex_index(u);
    if (i == -1)
      return;
    clear_edges_list(u->edges);
    free(u);
    for (; i < nvertices - 1; i++)
      vertices[i] = vertices[i + 1];
    nvertices--;
  }

  void add_edge(vertex* u, vertex* v, bool directed, int weight)
  {
    edge *e, *ue;

    if (!u || !v)
      return;
    e = (edge*)malloc(sizeof(vertex));
    e->u = u;
    e->v = v;
    e->next = NULL;
    e->weight = weight;

    ue = u->edges;
    if (ue)
    {
      for (; ue->next; ue = ue->next)
      {
        if (ue->v == e->v)
        {
        }
      }
      ue->next = e;
    }
    else
    {
      u->edges = e;
    }

    if (!directed)
      add_edge(v, u, true, weight);
  }

  void delete_edge(vertex* u, vertex* v, bool directed)
  {
    edge *e, *e_prev = NULL;

    if (!u || !v)
      return;
    for (e = u->edges; e; e = e->next)
    {
      if (e->v == v)
      {
        if (e_prev)
          e_prev->next = e->next;
        else
          u->edges = e->next;
        free(e);
      }
      e_prev = e;
    }

    if (!directed)
      delete_edge(v, u, true);
  }

  void empty_graph()
  {
    int i;

    for (i = nvertices - 1; i >= 0; i--)
    {
      delete_vertex(vertices[i]);
    }
  }

  void insert_edge_vertices()
  {
    char label[MAXLABEL];
    vertex *u, *v;
    int weight;

    cin >> label;
    u = find_vertex(label);
    if (!u)
      u = add_vertex(label);
    cin >> label;
    if (!strcmp(label, "/"))
      return;
    v = find_vertex(label);
    if (!v)
      v = add_vertex(label);
    if (weighted)
      cin >> weight;
    else
      weight = 1;
    add_edge(u, v, directed, weight);
  }

  void read_graph()
  {
    int i, nedges;

    empty_graph();

    cin >> nedges;

    for (i = 0; i < nedges; i++)
    {
      insert_edge_vertices();
    }
  }

  void print_graph()
  {
    vertex* v;
    edge* e;
    int i;

    for (i = 0; i < nvertices; i++)
    {
      v = vertices[i];
      cout << v->label;
      for (e = v->edges; e; e = e->next)
      {
        cout << e->v->label;
        if (weighted)
          cout << "(" << e->weight << ")";
      }
      cout << "\n";
    }
  }

  void initialize_attributes()
  {
    vertex* v;
    int i;

    for (i = 0; i < nvertices; i++)
    {
      v = vertices[i];
      v->distance = INITDIST;
      v->color = WHITE;
    }
  }

  int broj_putova(vertex *u, vertex *v) {
    if (u->color == GRAY) return 0;
    if (u == v) return 1;
    int sum = 0;
    u->color = GRAY;

    for (edge* currEdge = u->edges; currEdge != NULL; currEdge = currEdge->next) {
      vertex* adjacent = currEdge->v;
      if (adjacent->color == GRAY) continue;
      sum += broj_putova(adjacent, v);
    }

    u->color = WHITE;
    return sum;
  }
};

int main()
{
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);
  Graph* g;
  vertex *u, *v;
  int menu_choice;
  char c, label[MAXLABEL];

  g = new Graph(false, false);
  do
  {
    cin >> menu_choice;
    switch (menu_choice)
    {
    case 1:
      cin >> label;
      u = g->find_vertex(label);
      cin >> label;
      v = g->find_vertex(label);
      if (!u || !v) break;

      std::cout << g->broj_putova(u, v) << "\n";
      break;
    case 2:

      g->read_graph();
      break;
    case 3:

      g->print_graph();
      break;
    case 4:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF)
        ;
    }
  } while (menu_choice != 4);
  return 0;
}
