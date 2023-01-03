#include <bits/stdc++.h>

using namespace std;
#define MAXV 100
#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

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
        nvertices = 0;
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

    int num_neighbors(int u) {
        int v, sum = 0;
        for (v = 0; v < nvertices; v++) {
            if (adj[u][v]) sum++;
        }
        return sum;
    }
    /*
    bool eulerov_put() {
        int oddCounter = 0;
        for (int i = 1; i <= nvertices; ++i) {
          oddCounter += num_neighbors(i) % 2;
        }
        
        return oddCounter == 2 || oddCounter == 0;
    }*/
    
    bool eulerov_put() {
        int odd, u;
        // -- Provjera ako su svi vrhovi koji imaju susjede medjusobno povezani
        // Pronadji prvi vrh koji ima susjeda
        for (u = 1; u < nvertices; u++) {
            if (num_neighbors(u) > 0) break;
        }
        // Ako nema bridova u grafu postoji trivijalan Eulerov put duljine 0
        if (u == nvertices) return true;

        dfs(u);
        // Provjeri da li su svi neposjeceni vrhovi izolirani
        for (u = 0; u < nvertices; u++) {
            if (colors[u] != BLACK) {
                if (num_neighbors(u) > 0) return false;
            }
        }

        // Pobroji vrhove s neparnim brojem susjeda
        odd = 0;
        for (u = 0; u < nvertices; u++) {
            if (num_neighbors(u) % 2) odd++;
        }

        // Ako ih je vise od 2 graf ne sadrzi Eulerov put
        // Ako je ih je 2 ili 0 postoji Eulerov put
        return (odd > 2) ? false : true;
        // Broj vrhova s neparnim susjedima ne moze biti 1 za neusmjereni graf
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
        std::cin >> menu_choice;
        switch (menu_choice) {
        case 1:
            //eulerov put
            std::cout << (g->eulerov_put() ? "Y" : "N");
            cout << "\n";
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
