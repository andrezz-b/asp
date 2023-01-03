#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

struct Node
{
  int key;
  Node *parent;
  Node *left;
  Node *right;

  Node (int key) {
    this->key = key;
    parent = right = left = NULL;
  }
};

struct BST
{
  Node *root;
  BST() {
    root = NULL;
  }

  void add_node(int key) {
    Node *new_node, *trenutni, *prethodni = NULL;

    new_node = new Node(key);

    trenutni = root;
    while (trenutni != NULL)
    {
      prethodni = trenutni;
      if (new_node->key < trenutni->key)
      {
        trenutni = trenutni->left;
      }
      else
      {
        trenutni = trenutni->right;
      }
    }

    new_node->parent = prethodni;
    if (prethodni == NULL)
    {
      root = new_node;
    }
    else if (new_node->key < prethodni->key)
    {
      prethodni->left = new_node;
    }
    else
    {
      prethodni->right = new_node;
    }
  }

  int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    int i, left, right, width = 5;
    char b[width + 1];

    if (!tree)
      return 0;
    sprintf(b, "(%03d)", tree->key);
    left = print_tree(tree->left, 1, offset, depth + 1, s);
    right = print_tree(tree->right, 0, offset + left + width, depth + 1, s);
    for (i = 0; i < width; i++)
    {
      s[depth][offset + left + i] = b[i];
    }
    if (depth)
    {
      if (is_left)
      {
        for (i = 0; i < width + right; i++)
        {
          s[depth - 1][offset + left + width / 2 + i] = '-';
        }
      }
      else
      {
        for (i = 0; i < left + width; i++)
        {
          s[depth - 1][offset - width / 2 + i] = '-';
        }
      }
      s[depth - 1][offset + left + width / 2] = '.';
    }
    return left + width + right;
  }

  void print_graph(int **g, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++)
        cout << g[i][j] << " ";
      cout << "\n";
    }
  }

  void stablo_u_graf(Node *node, int **g) {
    if (!node) return;

    if (node->left) {
      g[node->key][node->left->key] = 1;
      g[node->left->key][node->key] = 1;
    }

    if (node->right) {
      g[node->key][node->right->key] = 1;
      g[node->right->key][node->key] = 1;
    }

    stablo_u_graf(node->left, g);
    stablo_u_graf(node->right, g);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int i, n, val;
  char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  BST stablo;

  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::cin >> val;
    stablo.add_node(val);
  }


  sprintf(print_format, "%%%ds", WIDTH - 1);
  for (i = 0; i < HEIGHT; i++)
    sprintf(s[i], print_format, " ");

  stablo.print_tree(stablo.root, 0, 0, 0, s);

  sprintf(empty_line, print_format, " ");
  for (i = 0; i < HEIGHT; i++) {
    if (strcmp(s[i], empty_line)) {
      cout << s[i] << "\n";
    }
  }
  int **g = new int*[n];
  for (int i = 0; i < n; ++i) {
    g[i] = new int[n];
  }

  std::cout << "\n";

  stablo.stablo_u_graf(stablo.root, g);
  stablo.print_graph(g, n);

  for (int i = 0; i < n; ++i) {
    delete[] g[i];
  }
  delete[] g;

  return (0);
}