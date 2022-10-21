#include <iostream>
#include <string.h>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAX_TREE_STRING 100
#define MAX_NODES 100

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

class Node
{
public:
  int val;
  Node *left, *right;
};

int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH])
{
  char b[HEIGHT];
  int i, left, right, width = 3;

  if (!tree)
    return 0;

  sprintf(b, "(%c)", tree->val);
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

Node *create_tree(char *tree_string)
{
  Node *queue[MAX_NODES];
  Node *trenutni, *parent;
  int tail, head, i;

  tail = head = -1;
  trenutni = parent = NULL;

  for (i = 0; i < (int)strlen(tree_string); i++)
  {
    if (tree_string[i] != ';')
    {
      if (tree_string[i] == '-')
        continue;
      trenutni = (Node *)malloc(sizeof(Node));
      trenutni->val = tree_string[i];
      trenutni->left = trenutni->right = NULL;

      queue[++tail] = trenutni;

      if (parent && tree_string[i - 1] == ';')
      {
        parent->left = trenutni;
      }
      else if (i > 0)
      {
        parent->right = trenutni;
      }
    }
    else
    {
      parent = queue[++head];
    }
  }

  return queue[0];
}

int broj_blizanaca(Node *node) {
  if (!node) return 0;
  // Ako na trenutnom čvoru postoje lijevo i desno dijete
  // provjeri ako su jednaki, ako jesu nadodaj zbroju 1
  // i nastavi provjeravati ako možda njihova djeca imaju blizance
  // ako nisu jednaki ne dodaj ništa (add = 0)
  int add = node->right && node->left ? node->right->val == node->left->val : 0;
  return broj_blizanaca(node->left) + broj_blizanaca(node->right) + add;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Node *root = NULL;
  int i, menu_choice;
  char c, tree_string[MAX_TREE_STRING];
  char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];

  do
  {
    menu_choice = 0;
    DEBUG("1. Broj blizanaca\n");
    DEBUG("2. Kreiraj stablo\n");
    DEBUG("3. Ispis\n");
    DEBUG("4. Izlaz\n");
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      cout << broj_blizanaca(root) << "\n";
      break;
    case 2:
      DEBUG("Unesite stablo kao niz alfanumerickih znakova odvojenih sa znakom ;\n");
      cin >> tree_string;
      root = create_tree(tree_string);
      break;
    case 3:
      sprintf(print_format, "%%%ds", WIDTH - 1);
      for (i = 0; i < HEIGHT; i++)
        sprintf(s[i], print_format, " ");

      print_tree(root, 0, 0, 0, s);

      sprintf(empty_line, print_format, " ");
      for (i = 0; i < HEIGHT; i++)
        if (strcmp(s[i], empty_line))
          cout << s[i] << "\n";

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