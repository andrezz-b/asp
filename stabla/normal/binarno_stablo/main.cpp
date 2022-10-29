#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 100
#define WIDTH 80
#define HEIGHT 6

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

struct Tree {
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
  Node *root;

  Tree() {
    root = NULL;
  }

  ~Tree() {
    destroy_tree(root);
  }

  void destroy_tree(Node *n) {
    if (!n) return;

    destroy_tree(n->left);
    delete(n->left);
    destroy_tree(n->right);
    delete(n->right);
  }

  void create_tree(string tree_string) {
    destroy_tree(root);
    Queue<Node *> q(MAXN);
    Node *n = NULL;

    for (int i = 0; i < (int)tree_string.size(); ++i) {
      Node *curr = q.front();
      if (tree_string[i + 1] == ';') q.dequeue();

      if (tree_string[i] == '-' || tree_string[i] == ';') continue;

      n = new Node(tree_string[i]);
      q.enqueue(n);

      if (i == 0) {
        root = n;
        continue;
      }

      if (tree_string[i - 1] == ';') {
        curr->left = n;
      } else {
        curr->right = n;
      }


    }
  }

  int sprint_tree(Node *n, bool is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    if (!n) return 0;

    int width = 5;

    int left = sprint_tree(n->left, true, offset, depth + 1, s);
    int right = sprint_tree(n->right, false, offset + left + width, depth + 1, s);

    char b[HEIGHT];
    sprintf(b, "( %c )", n->val);
    for (int i = 0; i < width; ++i) {
      s[depth][offset + left + i] = b[i];
    }

    if (depth) {
      if (is_left) {
        for (int i = 0; i < width + right; ++i) {
          s[depth - 1][offset + left + width / 2 + i] = '-';
        }
      } else {
        for (int i = 0; i < left + width; ++i) {
          s[depth - 1][offset - width / 2 + i] = '-';
        }
      }

      s[depth - 1][offset + left + width / 2] = '.';
    }

    return left + width + right;
  }

  void print() {
    char print_format[6];
    sprintf(print_format, "%%%ds", WIDTH - 1);

    char s[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; ++i) {
      sprintf(s[i], print_format, " ");
    }

    sprint_tree(root, 0, 0, 0, s);

    char empty_line[WIDTH];
    sprintf(empty_line, print_format, " ");
    for (int i = 0; i < HEIGHT; ++i) {
      if (strcmp(s[i], empty_line)) {
        cout << s[i] << endl;
      }
    }
  }

  char max_node(Node *n) {
    if (!n) return 0;

    return std::max(std::max(max_node(n->left), max_node(n->right)), n->val);
  }

  char min_node(Node *n) {
    if (!n) return 127;
    return std::min(std::min(min_node(n->left), min_node(n->right)), n->val);
  }

  int num_nodes(Node *n) {
    if (!n) return 0;
    return num_nodes(n->left) + num_nodes(n->right) + 1;
  }

  void mirror_tree(Node *n) {
    if (!n) return;
    Node *tmp = n->left;
    n->left = n->right;
    n->right = tmp;
    mirror_tree(n->left);
    mirror_tree(n->right);
  }

  bool equal_tree(Node *n1, Node *n2) {
    if (!n1 && !n2) return true;
    if (!n1 || !n2) return false;
    return equal_tree(n1->left, n2->left) && equal_tree(n1->right, n2->right) && n1->val == n2->val;
  }
};

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int menu_choice;
  string tree_string;
  Tree tree;
  Tree tree2;

  do {
    cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      cin >> tree_string;
      tree.create_tree(tree_string);
      break;
    case 2:
      tree.print();
      break;
    case 3:
      cout << tree.max_node(tree.root) << endl;
      break;
    case 4:
      cout << tree.min_node(tree.root) << endl;
      break;
    case 5:
      cout << tree.num_nodes(tree.root) << endl;
      break;
    case 6:
      tree.mirror_tree(tree.root);
      break;
    case 7:
      cin >> tree_string;
      tree2.create_tree(tree_string);
      cout << (tree.equal_tree(tree.root, tree2.root) ? "Y" : "N") << endl;
      break;
    case 8:
      break;
    }
  } while (menu_choice != 8);

  return 0;
}
