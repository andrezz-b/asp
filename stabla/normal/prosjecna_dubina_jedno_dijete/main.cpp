#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAX_TREE_STRING 100
#define MAX_NODES 100

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

struct Node
{
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

int sum_depth(Node *node, int depth, int *num)
{
  int h = 0;

  if (!node)
    return 0;

  if ((node->left && !node->right) || (!node->left && node->right))
  {
    // Ako čvor ima 1 dijete zapamti njegovu dubinu
    // i povećvaj ukupni broj čvorova s 1 djetetom
    h = depth;
    (*num)++;
  }
  // Ako čvor na kojem smo sad ima samo 1 dijete njegovu dubinu smo zapamtili u h
  // i povećavamo ukupan zbroj za h, ako ima 2 ili 0 djece h će biti 0
  return sum_depth(node->left, depth + 1, num) + sum_depth(node->right, depth + 1, num) + h;
}

void prosjecna_dubina(Node *root)
{
  // Poseban slučaj kad nemamo korijen ili imamo samo korijen
  // dubina će biti 0, ali također i broj čvorova s 1 djetetom će biti
  // 0 te ćemo onda za prosjek dijeliti 0 / 0
  if (!root || (!root->left && !root->right)) {
    std::cout << "0.00\n";
    return;
  }
  int size = 0;
  int depth = sum_depth(root, 0, &size);
  std::cout << std::fixed << std::setprecision(2) << depth / (float) size << "\n";

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
    DEBUG("\n1 Prosjecna dubina cvorova s jednim djetetom (prosjecna_dubina)");
    DEBUG("\n2 Kreiraj stablo \n3 Ispis \n4 Izlaz\n");
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      prosjecna_dubina(root);
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