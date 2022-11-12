#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10
#define PARENT(i)      ((i-1) / 2)
#define LEFT(i)        (2*(i) + 1)
#define RIGHT(i)       (2*(i) + 2)
#define HEAP_ROOT      0
#define LINE_WIDTH     70
#define SIZE(x)        (sizeof(x) / sizeof(x[0]))

struct Node {
  int key;
  Node *parent;
  Node *left;
  Node *right;

  Node(const int &value)
    : key(value), parent(NULL), left(NULL), right(NULL)
  {}
};

struct Heap {
  size_t size;
  int *array;

  Heap()
    : size(0)
  {}

  ~Heap() {
    delete(array);
  }
  void print_heap() {
    int print_pos[size];
    int i, j, k, pos, current_pos = 1, level = 0;


    print_pos[HEAP_ROOT] = 0;
    for (i = 0, j = 1; i < (int)size; i++, j++) {
      pos = print_pos[PARENT(i)] + (i % 2 ? - 1 : 1) * (LINE_WIDTH / (pow(2, level + 1)) + 1);
      for (k = 0; k < pos - current_pos; k++) cout << (i == 0 || i % 2 ? ' ' : '-');
      cout << array[i];
      print_pos[i] = current_pos = pos + 1;
      if (j == pow(2, level)) {
        cout << "\n";
        level++;
        current_pos = 1;
        j = 0;
      }
    }
    cout << "\n";
    return;
  }

  int is_max_heap(int *array, int len) {
    int i;

    for (i = len - 1; i > 0; i--) {
      if (array[i] > array[PARENT(i)]) {
        return 0;
      }
    }
    return 1;
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
  int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 7;

    if (!tree) return 0;
    sprintf(b, "(%02d:%02d)", tree->key, tree->parent ? tree->parent->key : 0);
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

Node *heap_to_tree(Heap *heap, Node *parent, int j) {
  if (j >= (int) heap->size) return NULL;

  Node *n = new Node(heap->array[j]);
  n->parent = parent;

  n->left = heap_to_tree(heap, n, LEFT(j));
  n->right = heap_to_tree(heap, n, RIGHT(j));

  return n;
}

int main() {
  int i, menu_choice, len, val;
  char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  BinTree binarno_stablo;
  Heap *heap = NULL;

  heap = new Heap();
  setbuf(stdout, NULL);
  do {

    cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      binarno_stablo.root = heap_to_tree(heap, NULL, 0);
      break;
    case 2:

      cin >> len;
      if (heap->array) free(heap->array);
      heap->array = new int[len];
      heap->size = len;
      while (len > 0) {
        cin >> val;
        if (val < 1 || val > 99) continue;
        heap->array[heap->size - len] = val;
        len--;
      }
      if (!heap->is_max_heap(heap->array, heap->size)) {

        free(heap->array);
      }
      break;
    case 3:
      sprintf(print_format, "%%%ds", WIDTH - 1);
      for (i = 0; i < HEIGHT; i++)
        sprintf(s[i], print_format, " ");

      binarno_stablo.print_tree(binarno_stablo.root, 0, 0, 0, s);

      sprintf(empty_line, print_format, " ");
      for (i = 0; i < HEIGHT; i++) {
        if (strcmp(s[i], empty_line))
          cout << s[i] << endl;
      }
      break;
    case 4:
      heap->print_heap();
      break;
    case 5:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 5);
  return 0;
}