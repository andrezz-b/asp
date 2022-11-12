#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 100
#define MAX_TREE_STRING 100
#define MAX_NODES 100

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

template <typename T> struct Queue {
  int size;
  int head;
  int tail;
  T *array;

  Queue(int n) {
    size = n;
    head = 0;
    tail = 0;
    array = new T[size];
  }

  T front () {
    if (head == tail) return (T) - 1;

    return array[head];
  }

  int enqueue(T val) {
    if ((tail + 1) % size == head) return -1;

    array[tail] = val;
    tail = (tail + 1) % size;

    return 0;
  }

  int dequeue() {
    if (head == tail) return -1;

    head = (head + 1) % size;

    return 0;
  }
};
struct LcrsNode {
  int value;
  LcrsNode *parent;
  LcrsNode *child;
  LcrsNode *sibling;

  LcrsNode(int value) {
    this->value = value;
    parent = NULL;
    child = NULL;
    sibling = NULL;
  }
};
struct Node {
  int value;
  Node *parent;
  Node *left;
  Node *right;

  Node(int value) {
    this->value = value;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
};

struct BinTree {
  Node *root;

  BinTree() {
    root = NULL;
  }

  ~BinTree() {
    destroy_tree(root);
  }
  void destroy_tree(Node *n) {
    if (!n) return;

    destroy_tree(n->left);
    delete(n->left);
    destroy_tree(n->right);
    delete(n->right);
  }

  Node *add_node(Node *node, Node *parent, int value) {
    if (!node) {  // osnovni slucaj rekurzije
      node = new Node(value);
      node->parent = parent;
      return node;
    }

    if (value < node->value) {
      node->left = add_node(node->left, node, value);
    } else {
      node->right = add_node(node->right, node, value);
    }
    return node;
  }
  int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 7;

    if (!tree) return 0;
    sprintf(b, "(%02d:%02d)", tree->value, tree->parent ? tree->parent->value : 0);
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
};

struct LCRSTree {
  LcrsNode *root;

  LCRSTree() {
    root = NULL;
  }

  ~LCRSTree() {
    destroy_tree(root);
  }

  void destroy_tree(LcrsNode *n) {
    if (!n) return;

    destroy_tree(n->child);
    delete(n->child);
    destroy_tree(n->sibling);
    delete(n->sibling);
  }

  void print_lcrs_tree(LcrsNode *node, int level) {
    int i;

    if (!node) return;
    for (i = 0; i < level; i++) printf("--");
    printf("%d:%d\n", node->value, node->parent ? node->parent->value : 0);
    print_lcrs_tree(node->child, level + 1);
    print_lcrs_tree(node->sibling, level + 1);
  }
};

LcrsNode *bin_to_lcrs(Node *node, LcrsNode *parent) {
  if (!node) return NULL;

  LcrsNode *n = new LcrsNode(node->value);
  n->parent = parent;

  LcrsNode *child1 = bin_to_lcrs(node->left, n);
  LcrsNode *child2 = bin_to_lcrs(node->right, n);


  // Ako lijevo dijete postoji onda je to dijete
  // a child2 je sibling
  if (child1) {
    n->child = child1;
    n->sibling = child2;
  } else {
    n->child = child2; // Ako ne postoji child1 onda je child2 child
  }

  return n;
}

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int menu_choice, i, val;
  LCRSTree Lcrs_stablo;
  BinTree Binarno_stablo;
  char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];

  do {
    cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      Lcrs_stablo.root = bin_to_lcrs(Binarno_stablo.root, Lcrs_stablo.root);
      break;
    case 2:
      while (scanf("%d", &val) == 1) {
        if (val < 1 || val > 999) continue;
        Binarno_stablo.root = Binarno_stablo.add_node(Binarno_stablo.root, NULL, val);
      }
      while ((c = getchar()) != '\n' && c != EOF);
      break;
    case 3:
      Lcrs_stablo.print_lcrs_tree(Lcrs_stablo.root, 0);
      break;
    case 4:
      sprintf(print_format, "%%%ds", WIDTH - 1);
      for (i = 0; i < HEIGHT; i++)
        sprintf(s[i], print_format, " ");

      Binarno_stablo.print_tree(Binarno_stablo.root, 0, 0, 0, s);

      sprintf(empty_line, print_format, " ");
      for (i = 0; i < HEIGHT; i++) {
        if (strcmp(s[i], empty_line))
          printf("%s\n", s[i]);
      }
      break;
    case 5:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 5);
  return 0;
}