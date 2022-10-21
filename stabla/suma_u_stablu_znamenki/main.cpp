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

// najmanja i najveca dopustena vrijednost u stablu
#define MIN_VAL 0
#define MAX_VAL 9

#define MAX_TREE_STRING 100
#define MAX_NODES 100

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

struct Node {
  char val;
  Node *left, *right;
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
  int i, size;

  Node *root;

  int print_tree(Node *root, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 5;

    if (!root) return 0;
    sprintf(b, "(%03d)", root->val);
    left = print_tree(root->left, 1, offset, depth + 1, s);
    right = print_tree(root->right, 0, offset + left + width, depth + 1, s);
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

  Node *add_child(Node *parent, int key, int is_left) {
    Node *novi;

    novi = new Node(key);
    if (parent) {
      if (is_left == 1) parent->left = novi;
      else parent->right = novi;
    }
    return novi;
  }

  void create_tree(string tree_string) {
    int i = 0, j = 0, n, ns;
    size = tree_string.size();
    unsigned int key = 0;
    Node *parent, *dodavani;
    Queue<Node *> queue(MAX_NODES);
    root = NULL;
    dodavani = parent = NULL;

    while (i < size) {
      ns = sscanf(&(tree_string[i]), " %u;%n", &key, &n);
      if (ns == 1 && key >= MIN_VAL && key <= MAX_VAL && (parent || j == 0))
        dodavani = add_child(parent, key, j % 2);
      queue.enqueue(dodavani);
      if (!root) root = dodavani;
      if (j % 2 == 0) {
        if (queue.head >= queue.tail) break;
        parent = queue.front();
        queue.dequeue();
      }
      i += ns == 1 ? n : 1;
      j++;
    }
  }

  int suma(Node *node, int val) {
    if (!node) return 0;
    if (!node->left && !node->right) return val * 10 + node->val;
    int lTotal = suma(node->left, val * 10 + node->val);
    int rTotal = suma(node->right, val * 10 + node->val);
    return rTotal + lTotal;
  }

};

int main()
{
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int menu_choice, i;
  char c;
  char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  string tree_string;
  Stablo stablo;
  do
  {
    menu_choice = 0;
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      std::cout << stablo.suma(stablo.root, 0) << "\n";
      break;
    case 2:
      cin >> tree_string;
      stablo.create_tree(tree_string); //kreiranje stabla
      break;
    case 3:
      sprintf(print_format, "%%%ds", WIDTH - 1);
      for (i = 0; i < HEIGHT; i++)
        sprintf(s[i], print_format, " ");

      stablo.print_tree(stablo.root, 0, 0, 0, s);

      sprintf(empty_line, print_format, " ");
      for (i = 0; i < HEIGHT; i++) {
        if (strcmp(s[i], empty_line))
          printf("%s\n", s[i]);
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