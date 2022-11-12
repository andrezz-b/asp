#include <iostream>

using namespace std;

#define MAXN 100

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

struct LCRSTree {
  struct Node {
    char val;
    Node *child;    // First child
    Node *sibling;  // Next sibling

    Node(char value) {
      val = value;
      child = NULL;
      sibling = NULL;
    }
  };
  Node *root;

  LCRSTree() {
    root = NULL;
  }

  ~LCRSTree() {
    destroy_tree(root);
  }

  void destroy_tree(Node *n) {
    if (!n) return;

    destroy_tree(n->child);
    delete(n->child);
    destroy_tree(n->sibling);
    delete(n->sibling);
  }

  void create_tree(string tree_string) {
    destroy_tree(root);
    root = NULL;

    Queue<Node *> queue(MAXN);
    Node *parent = NULL;
    Node *prev_sibling = NULL;
    Node *n;

    for (unsigned i = 0; i < tree_string.length(); ++i) {
      if (tree_string[i] != ';') {
        n = new Node(tree_string[i]);

        if (!root) root = n;
        queue.enqueue(n);

        if (parent && tree_string[i - 1] == ';') {
          parent->child = n;
        } else if (prev_sibling) {
          prev_sibling->sibling = n;
        }

        prev_sibling = n;
      } else {
        parent = queue.front();
        queue.dequeue();
        prev_sibling = NULL;
      }
    }
  }

  char max_node(Node *n) {
    if (!n) return 0;
    char childMax = std::max(max_node(n->child), max_node(n->sibling));

    return std::max(n->val, childMax);
  }

  char min_node(Node *n) {
    if (!n) return 127;
    char childMin = std::min(min_node(n->child), min_node(n->sibling));

    return std::min(n->val, childMin);
  }

  int num_nodes(Node *n) {
    if (!n) return 0;
    return num_nodes(n->child) + num_nodes(n->sibling) + 1;
  }

  Node *find_node(Node *n, char node_name) {
    if (!n) return NULL;

    if (n->val == node_name) return n;

    Node *tmp = find_node(n->child, node_name);

    if (tmp) return tmp;

    return find_node(n->sibling, node_name);
  }

  int node_height(Node *n, bool fFirstCall) {
    if (!n) return -1;

    // Dohvati visinu podstabla prvog djeteta i uvecaj za jedan
    int height = node_height(n->child, false) + 1;

    // Ako je prvi poziv onda ne provjeravam svoje siblinge jer smo na istoj razini
    if (!fFirstCall) {
      // Ako nije prvi poziv, onda dohvacam visine siblinga, ali ih ne uvecavam za
      // jedan jer smo na istoj razini
      int sb_height = node_height(n->sibling, false);

      // Visina koju cemo proslijediti roditelju (ili prethodnom siblingu) je
      // najveca visina podstabla svakog od siblinga u nizu
      height = height > sb_height ? height : sb_height;
    }

    return height;
  }
};

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int menu_choice;
  string tree_string;
  char node_name;
  LCRSTree lcrs;

  do {
    cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      cin >> tree_string;
      lcrs.create_tree(tree_string);
      break;
    case 2:
      cout << lcrs.num_nodes(lcrs.root) << endl;
      break;
    case 3:
      cout << lcrs.min_node(lcrs.root) << endl;
      break;
    case 4:
      cout << lcrs.max_node(lcrs.root) << endl;
      break;
    case 5:
      cin >> node_name;
      cout << lcrs.node_height(lcrs.find_node(lcrs.root, node_name), true) << endl;
      break;
    case 6:
      break;
    }
  } while (menu_choice != 6);

  return 0;
}