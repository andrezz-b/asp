#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define WIDTH 80
#define HEIGHT 10

typedef struct avl_node
{

  avl_node(const int &key)
    : key(key), height(0), parent(NULL), left(NULL), right(NULL)
  {}
  int key;
  int height;
  struct avl_node *parent;
  struct avl_node *left;
  struct avl_node *right;
} Node;

struct AVL
{
  Node *root;
  AVL()
  {
    root = NULL;
  }

  Node *add_node(Node *node, Node *parent, int key) {
    if (!node) {
      Node *n = new Node(key);
      n->parent = parent;
      return n;
    }

    if (key < node->key) {
      node->left = add_node(node->left, node, key);
    } else {
      node->right = add_node(node->right, node, key);
    }

    node->height = get_height(node);

    return node;
  }

  int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH])
  {
    char b[HEIGHT];
    int i, left, right, width = 5;

    if (!tree)
      return 0;

    sprintf(b, "(%03d)", tree->key);
    left = print_tree(tree->left, 1, offset, depth + 1, s);
    right = print_tree(tree->right, 0, offset + left + width, depth + 1, s);

    for (i = 0; i < width; i++)
      s[depth][offset + left + i] = b[i];

    if (depth)
    {
      if (is_left)
      {
        for (i = 0; i < width + right; i++)
          s[depth - 1][offset + left + width / 2 + i] = '-';
      }
      else
      {
        for (i = 0; i < left + width; i++)
          s[depth - 1][offset - width / 2 + i] = '-';
      }

      s[depth - 1][offset + left + width / 2] = '.';
    }

    return left + width + right;
  }

  int get_height(Node *node) {
    if (!node) return -1;
    return std::max((node->left ? node->left->height : -1), (node->right ? node->right->height : -1)) + 1;
  }

  int maksimalni_bf(Node *node) {
    if (!node) return 0;
    int lBalance = maksimalni_bf(node->left);
    int rBalance = maksimalni_bf(node->right);
    int maxChildBalance = abs(lBalance) > abs(rBalance) ? lBalance : rBalance;

    int currBalance = get_height(node->left) - get_height(node->right);
    return abs(currBalance) > abs(maxChildBalance) ? currBalance : maxChildBalance;

  }
};

int main()
{
  int i, menu_choice, val;
  char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  AVL *avl = new AVL();

  setbuf(stdout, NULL);
  do
  {
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      cout << avl->maksimalni_bf(avl->root) << "\n";
      break;
    case 2:
      while (cin >> val)
      {
        if (val < 1 || val > 999)
          continue;
        avl->root = avl->add_node(avl->root, NULL, val);
      }
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      cin.clear();
      break;
    case 3:
      sprintf(print_format, "%%%ds", WIDTH - 1);

      for (i = 0; i < HEIGHT; i++)
        sprintf(s[i], print_format, " ");

      avl->print_tree(avl->root, 0, 0, 0, s);

      sprintf(empty_line, print_format, " ");
      for (i = 0; i < HEIGHT; i++)
      {
        if (strcmp(s[i], empty_line))
          cout << s[i] << "\n";
      }
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