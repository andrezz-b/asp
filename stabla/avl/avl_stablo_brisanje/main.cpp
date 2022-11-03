#include <iostream>
#include <cstring>
using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define WIDTH 80
#define HEIGHT 10

struct Node {
  int key;
  int height;  // trenutna visina cvora
  Node *parent;
  Node *left;
  Node *right;

  Node(int key) {
    this->key = key;
    height = 0;
    parent = left = right = NULL;
  }
};

struct Avl_tree {
  Node *root;
  Avl_tree() {
    root = NULL;
  }

  int get_bf(Node *node) {
    return ((node->left) ? node->left->height + 1 : 0) - ((node->right) ? node->right->height + 1 : 0);
  }

  void recalculate_height(Node *node) {
    node->height = 0;
    if (node->left && (node->left->height > node->height)) {
      node->height = node->left->height;
    }
    if (node->right && (node->right->height > node->height)) {
      node->height = node->right->height;
    }
    if (node->left || node->right) {
      node->height += 1;
    }
  }

  Node* left_rotate(Node *x) {
    Node *y;

    y = x->right;
    x->right = y->left;  // I
    if (y->left) {
      y->left->parent = x;  // II
    }
    y->parent = x->parent;  // III
    if (x->parent) {
      if (x == x->parent->left) {
        x->parent->left = y;  // IV
      } else {
        x->parent->right = y;  // IV
      }
    }
    y->left = x;  // V
    x->parent = y;  // VI
    recalculate_height(x);
    recalculate_height(y);
    return y;
  }

  Node* right_rotate(Node *y) {
    Node *x;

    x = y->left;
    y->left = x->right;
    if (x->right) {
      x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent) {
      if (y == y->parent->left) {
        y->parent->left = x;
      } else {
        y->parent->right = x;
      }
    }
    x->right = y;
    y->parent = x;
    recalculate_height(y);
    recalculate_height(x);
    return x;
  }

  Node* balance(Node *node) {
    int bf;

    if (!node) return NULL;
    bf = get_bf(node);
    if (bf > 1) {
      if (get_bf(node->left) < 0) {
        node->left = left_rotate(node->left); // lr -> ll
      }
      node = right_rotate(node); // ll -> b
    } else if (bf < -1) {
      if (get_bf(node->right) > 0) {
        node->right = right_rotate(node->right); // rl -> rr
      }
      node = left_rotate(node); // rr -> b
    }
    recalculate_height(node);
    return node;
  }

  Node* avl_add_node(Node *node, Node *parent, int key) {
    if (!node) { // osnovni slucaj rekurzije
      node = new Node(key);
      node->parent = parent;
      return node;
    }

    if (key < node->key) {
      node->left = avl_add_node(node->left, node, key);
    } else {
      node->right = avl_add_node(node->right, node, key);
    }
    return balance(node);
  }

  Node *minimum(Node *node) {
    if (!node) return NULL;

    while (node->left != NULL)
      node = node->left;
    return node;
  }

  // na mjesto cvora node1 postavi cvor node2
  void transplant(Node *node1, Node *node2) {
    if (!node1->parent) {
      root = node2;
    } else if (node1 == (node1->parent)->left) {
      (node1->parent)->left = node2;
    } else {
      (node1->parent)->right = node2;
    }
    if (node2) {
      node2->parent = node1->parent;
    }
  }

  Node *delete_node(Node *node) {
    Node *node2, *ret = NULL;

    if (!node) return NULL;
    if (!node->left) {
      ret = node->right ? node->right : node->parent;
      transplant(node, node->right);
    } else if (!node->right) {
      ret = node->left;
      transplant(node, node->left);
    } else {
      node2 = minimum(node->right);
      ret = node2;
      if (node2->parent != node) {
        ret = node2->right ? node2->right : node2->parent;
        transplant(node2, node2->right);
        node2->right = node->right;
        (node2->right)->parent = node2;
      }
      transplant(node, node2);
      node2->left = node->left;
      (node2->left)->parent = node2;
    }
    free(node);
    return ret;
  }

  Node *search(Node *node, int key) {
    while (node != NULL && key != node->key) {
      if (key < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return node;
  }

  int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 5;

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

  int avl_delete(Node *node) {
    if (!node) return 0;

    Node *n = delete_node(node);

    while (n != root) {
      n = balance(n)->parent;
    }
    root = balance(n);
    return 1;
  }
};


int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int i, menu_choice, val;
  char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  Avl_tree avl_stablo;

  do {
    cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      while (scanf("%d", &val) == 1) {
        if (val < 1 || val > 999) continue;
        avl_stablo.root = avl_stablo.avl_add_node(avl_stablo.root, NULL, val);
      }
      while ((c = getchar()) != '\n' && c != EOF);
      break;
    case 2:
      cin >> val;
      avl_stablo.avl_delete(avl_stablo.search(avl_stablo.root, val));
      break;
    case 3:
      sprintf(print_format, "%%%ds", WIDTH - 1);
      for (i = 0; i < HEIGHT; i++)
        sprintf(s[i], print_format, " ");

      avl_stablo.print_tree(avl_stablo.root, 0, 0, 0, s);

      sprintf(empty_line, print_format, " ");
      for (i = 0; i < HEIGHT; i++) {
        if (strcmp(s[i], empty_line))
          cout <<  s[i];
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
