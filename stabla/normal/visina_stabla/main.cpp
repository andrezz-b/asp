#include <iostream>
#include <string.h>

using namespace std;

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

struct Stablo {
  struct Node {
    char val;
    Node *left;
    Node *right;

    Node(char value) {
      val = value;
      left = NULL;
      right = NULL;
    }
  };
  Stablo() {
    root = NULL;
  }

  ~Stablo() {
    destroy_tree(root);
  }

  void destroy_tree(Node *n) {
    if (!n) return;

    destroy_tree(n->left);
    delete(n->left);
    destroy_tree(n->right);
    delete(n->right);
  }
  Node *trenutni, *parent; //pokazivaci na parent i queue(sluzi za dodavanje u stablo)
  int i;

  Node *root;

  void create_tree(string tree_string) {
    destroy_tree(root);
    root = NULL;

    Queue<Node *> queue(MAX_NODES);
    trenutni = parent = NULL;

    for (i = 0; i < (int) tree_string.size(); i++)
    { //dodavanje u stablo koristeći red, auditorne vježbe su koristile stog
      if (tree_string[i] != ';')
      {
        if (tree_string[i] == '-')
          continue;

        trenutni = new Node(tree_string[i]);
        if (!root) root = trenutni;

        queue.enqueue(trenutni);

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
        parent = queue.front();
        queue.dequeue();
      }
    }
  }

  int sprint_tree(Node *root, int is_left, int offset, int depth, char s[HEIGHT][WIDTH])
  {
    char b[HEIGHT];
    int i, left, right, width = 3;

    if (!root)
      return 0;

    sprintf(b, "(%c)", root->val);
    left = sprint_tree(root->left, 1, offset, depth + 1, s);
    right = sprint_tree(root->right, 0, offset + left + width, depth + 1, s);

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
  void ispisi_stablo()
  {
    char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    int i;

    sprintf(print_format, "%%%ds", WIDTH - 1);

    for (i = 0; i < HEIGHT; i++)
      sprintf(s[i], print_format, " ");

    sprint_tree(root, 0, 0, 0, s);

    sprintf(empty_line, print_format, " ");
    for (i = 0; i < HEIGHT; i++)
    {
      if (strcmp(s[i], empty_line))
        cout << s[i] << "\n";
    }

  }
  //implementirati funkciju za izračun visine
  int visina(Node *node) {
    if (!node || (!node->left && !node->right)) return 0;

    int lHeight = visina(node->left);
    int rHeight = visina(node->right);

    return lHeight > rHeight ? lHeight + 1  : rHeight + 1;
  }
};

int main()
{
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int menu_choice;
  char c;
  string tree_string;
  Stablo stablo;
  do
  {
    menu_choice = 0;
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      //visina
        std::cout << stablo.visina(stablo.root) << "\n";
      break;
    case 2:
      cin >> tree_string;
      stablo.create_tree(tree_string); //kreiranje stabla
      break;
    case 3:
      stablo.ispisi_stablo();
      break;
    case 4:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 4);

  return 0;
}