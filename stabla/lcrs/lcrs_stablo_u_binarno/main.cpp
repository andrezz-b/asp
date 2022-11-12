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
  char value;
  LcrsNode *parent;
  LcrsNode *child;
  LcrsNode *sibling;

  LcrsNode(char value) {
    this->value = value;
    parent = NULL;
    child = NULL;
    sibling = NULL;
  }
};
struct Node {
  char value;
  Node *parent;
  Node *left;
  Node *right;

  Node(char value) {
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

  int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH])
  {
    char b[HEIGHT];
    int i, left, right, width = 5;

    if (!tree)
      return 0;

    sprintf(b, "(%c:%c)", tree->value, tree->parent ? tree->parent->value : '0');
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
  void ispisi_binarno_stablo()
  {
    if (!root) return;
    char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    int i;

    sprintf(print_format, "%%%ds", WIDTH - 1);
    for (i = 0; i < HEIGHT; i++)
      sprintf(s[i], print_format, " ");

    print_tree(root, 0, 0, 0, s);

    sprintf(empty_line, print_format, " ");
    for (i = 0; i < HEIGHT; i++)
      if (strcmp(s[i], empty_line))
        cout << s[i] << "\n";
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
  void create_tree(string stablo) {
    Queue<LcrsNode *> queue(MAX_NODES);
    LcrsNode *trenutni, *prethodni, *roditelj;

    trenutni = prethodni = roditelj = NULL;

    for (int i = 0; i < (int) stablo.size(); i++)
    {
      if (stablo[i] != ';')
      {
        trenutni = new LcrsNode(stablo[i]);
        trenutni->parent = roditelj;
        trenutni->child = trenutni->sibling = NULL;

        if (!root) root = trenutni;
        queue.enqueue(trenutni);

        if (roditelj && stablo[i - 1] == ';')
        { // trenutni je prvo dijete
          roditelj->child = trenutni;
        }
        else if (prethodni)
        { // trenutni je sibling
          prethodni->sibling = trenutni;
        }
        prethodni = trenutni;
      }
      else
      {
        roditelj = queue.front();
        queue.dequeue();
      }
    }
  }
  void print_lcrs_tree(LcrsNode *node, int level) {
    int i;

    if (!node) return;
    for (i = 0; i < level; i++) cout << "\t";
    cout << node->value << endl;
    print_lcrs_tree(node->child, level + 1);
    print_lcrs_tree(node->sibling, level);
  }
};

Node *lcrs_to_bin(LcrsNode *lcrs_node, Node *previous, int is_first_sibling) {
    if (!lcrs_node) return NULL;

    Node *node = new Node(lcrs_node->value);

    node->left = lcrs_to_bin(lcrs_node->child, node, 1);

    if (is_first_sibling) {
        node->parent = previous;
        if (previous) {
            previous->right = lcrs_to_bin(lcrs_node->sibling, node, 0);
        }
    } else {
        if (previous) {
            node->parent = previous->parent;
        }
    }
    return node;
}

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int menu_choice;
  char c;
  string tree_string;
  BinTree Binarno_stablo;
  LCRSTree Lcrs_stablo;

  do
  {
    menu_choice = 0;
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      Binarno_stablo.root = lcrs_to_bin(Lcrs_stablo.root, NULL, 1);

      break;
    case 2:
      cin >> tree_string;
      Lcrs_stablo.create_tree(tree_string); //kreiranje stabla
      break;
    case 3:
      Lcrs_stablo.print_lcrs_tree(Lcrs_stablo.root, 0);
      break;
    case 4:
      Binarno_stablo.ispisi_binarno_stablo() ;
      break;
    case 5:

      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 5);

  return 0;
}