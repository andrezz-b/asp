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

  Node(int key) {
    this->key = key;
    parent = right = left = NULL;
  }
};

struct BST
{
  Node *root;

  BST()
  {
    root = NULL;
  }

  void add_node(int key)
  {
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

  int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH])
  {
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
};

#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define HEAP_ROOT 0
#define LINE_WIDTH 70
#define SIZE(x) (sizeof(x) / sizeof(x[0]))

struct Heap
{
  size_t size;   // broj elemenata u gomili
  size_t length; // broj elemenata u polju
  int *array;

  Heap() {}

  Heap(int s)
    : size(0), length(s), array(new int[s]) {}

  void print_heap()
  {
    int print_pos[size];
    int i, j, k, pos, current_pos = 1, level = 0;

    print_pos[HEAP_ROOT] = 0;

    for (i = 0, j = 1; i < (int)size; i++, j++)
    {
      pos = print_pos[PARENT(i)] + (i % 2 ? -1 : 1) * (LINE_WIDTH / (pow(2, level + 1)) + 1);

      for (k = 0; k < pos - current_pos; k++)
        cout << (i == 0 || i % 2 ? ' ' : '-');

      cout << array[i];
      print_pos[i] = current_pos = pos + 1;

      if (j == pow(2, level))
      {
        cout << "\n";
        level++;
        current_pos = 1;
        j = 0;
      }
    }

    cout << "\n";
    return;
  }
};

int tree_count(Node *n) {
  return n ? tree_count(n->left) + tree_count(n->right) + 1 : 0;
}

// Reverse in_order prolaz daje silazno sortirano polje baš kako treba u max heap
void reverse_in_order(Node *n, Heap *heap) {
  if (!n) return;
  reverse_in_order(n->right, heap);
  heap->array[heap->size] = n->key;
  heap->size += 1;
  reverse_in_order(n->left, heap);
}

Heap *stvori_gomilu(Node *root) {
  Heap *heap = new Heap(tree_count(root));

  reverse_in_order(root, heap);

  return heap;
}

int main()
{
  int i, menu_choice;
  char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  BST *bst = new BST();
  Heap *heap = new Heap();

  setbuf(stdout, NULL);
  do
  {
    //DEBUG("\n1 opis funkcije (ime_funkcije)");
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      heap = stvori_gomilu(bst->root);
      break;
    case 2:
      int val;
      while (cin >> val)
      {
        if (val < 1 || val > 999)
          continue;
        bst->add_node(val);
      }
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      cin.clear();
      break;
    case 3:
      sprintf(print_format, "%%%ds", WIDTH - 1);
      for (i = 0; i < HEIGHT; i++)
        sprintf(s[i], print_format, " ");

      bst->print_tree(bst->root, 0, 0, 0, s);

      sprintf(empty_line, print_format, " ");
      for (i = 0; i < HEIGHT; i++)
      {
        if (strcmp(s[i], empty_line))
          cout << s[i] << "\n";
      }
      break;
    case 4:
      if (heap)
        heap->print_heap();
      break;
    case 5:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF)
        ;
    }
  } while (menu_choice != 5);

  return 0;
}
