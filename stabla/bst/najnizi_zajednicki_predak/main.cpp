#include <iostream>
#include <ctype.h>
#include <string.h>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

struct Node {
  int key;
  Node *parent;
  Node *left;
  Node *right;

  Node(int key) {
    this->key = key;
    parent = right = left = NULL;
  }
};

struct BST {
  Node *root;

  BST() {
    root = NULL;
  }
  void add_node(int key) {
    Node *new_node, *trenutni, *prethodni = NULL;

    new_node = new Node(key);

    trenutni = root;
    while (trenutni != NULL) {
      prethodni = trenutni;
      if (new_node->key < trenutni->key)
        trenutni = trenutni->left;
      else
        trenutni = trenutni->right;
    }

    new_node->parent = prethodni;
    if (prethodni == NULL)
      root = new_node;
    else if (new_node->key < prethodni->key)
      prethodni->left = new_node;
    else
      prethodni->right = new_node;
  }

  int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    int i, left, right, width = 5;
    char b[width + 1];

    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->key);
    left = print_tree(tree->left, 1, offset, depth + 1, s);
    right = print_tree(tree->right, 0, offset + left + width, depth + 1, s);
    for (i = 0; i < width; i++)
      s[depth][offset + left + i] = b[i];
    if (depth) {
      if (is_left) {
        for (i = 0; i < width + right; i++)
          s[depth - 1][offset + left + width / 2 + i] = '-';
      } else {
        for (i = 0; i < left + width; i++)
          s[depth - 1][offset - width / 2 + i] = '-';
      }
      s[depth - 1][offset + left + width / 2] = '.';
    }
    return left + width + right;
  }

  Node *search(int key) {
    if (!root) return NULL;
    Node *curr = root;

    while (curr) {
      if (curr->key == key) return curr;

      if (key < curr->key) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    return curr;
  }
  /* Iterativno *//*
  int najnizi_zajednicki_predak(Node *node, const int &n1, const int &n2) {
    if (!node) return 0;
    const int min = std::min(n1, n2);
    const int max = std::max(n1, n2);

    while (min < node->key || node->key < max) {
      // Ako je unutar intervala [min, max] onda je definitvno
      // min negdje lijevo od njega a max negdje desno
      if (min <= node->key && node->key <= max) return node->key;
      // Ako je trenutni manji od min onda smo negdje previše lijevo pa moramo ići desno
      if (node->key < min) {
        node = node->right;
      } else {
        // Inače je trenutni veći od max pa samo negdje previše desno pa moramo ići lijevo
        node = node->left;
      }
    }
    return 0;

  }*/

  /* Rekurzivno */
  int najnizi_zajednicki_predak(Node *node, const int &n1, const int &n2) {
    if (!node) return 0;
    const int min = std::min(n1, n2);
    const int max = std::max(n1, n2);
    int key = node->key;
    if (node->key < min) {
      key = najnizi_zajednicki_predak(node->right, n1, n2);
    } else if (node->key > max){
      key = najnizi_zajednicki_predak(node->left, n1, n2);
    }

    return key;
  }
};

int main() {
  int menu_choice, val, n1, n2, i;
  char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  BST *bst = new BST();

  do {
    scanf("%d", &menu_choice);

    switch (menu_choice) {
    case 1:
      do {
        cin >> n1;
      } while (!bst->search(n1));
      do {
        cin >> n2;
      } while (!bst->search(n2));
      cout << bst->najnizi_zajednicki_predak(bst->root, n1, n2) << endl;
      break;
    case 2:
      int val;
      while (cin >> val) {
        if (val < 1 || val > 999) continue;
        bst->add_node(val);
      }
      while ((c = getchar()) != '\n' && c != EOF);
      cin.clear();
      break;
    case 3:
      sprintf(print_format, "%%%ds", WIDTH - 1);
      for (i = 0; i < HEIGHT; i++)
        sprintf(s[i], print_format, " ");

      bst->print_tree(bst->root, 0, 0, 0, s);

      sprintf(empty_line, print_format, " ");
      for (i = 0; i < HEIGHT; i++) {
        if (strcmp(s[i], empty_line))
          cout <<  s[i] << endl;
      }
      break;
    case 4:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 4);
  return 0;
}

