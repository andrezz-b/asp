#include <iostream>
#include <string.h>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

struct Node
{
  int val;
  Node *left;
  Node *right;

  Node (int key) {
    this->val = key;
    right = left = NULL;
  }
};

int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH])
{
  int i, left, right, width = 5;
  char b[width + 1];

  if (!tree)
    return 0;

  sprintf(b, "(%03d)", tree->val);
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

Node *polje_u_stablo(int *a, int start, int end)
{
  if (start > end) return NULL;
  int half = (start + end) / 2;
  Node *root = new Node(a[half]);
  root->left = polje_u_stablo(a, start, half - 1);
  root->right = polje_u_stablo(a, half + 1, end);
  return root;
}

int main()
{
  int i, n, a[100];
  char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  Node *root = NULL;

  cin >> n;
  for (i = 0; i < n; ++i)
  {
    cin >> a[i];
  }

  root = polje_u_stablo(a, 0, n - 1);

  // ispis stabla
  sprintf(print_format, "%%%ds", WIDTH - 1);
  for (i = 0; i < HEIGHT; i++)
    sprintf(s[i], print_format, " ");

  print_tree(root, 0, 0, 0, s);

  sprintf(empty_line, print_format, " ");
  for (i = 0; i < HEIGHT; i++)
  {
    if (strcmp(s[i], empty_line))
      cout << s[i] << "\n";
  }

  return 0;
}