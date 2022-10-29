#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 100
#define WIDTH 80
#define HEIGHT 6

struct Tree {
  struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    Node(int value) {
      key = value;
      left = NULL;
      right = NULL;
      parent = NULL;
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
    delete (n->left);
    destroy_tree(n->right);
    delete (n->right);
  }

  int sprint_tree(Node *n, bool is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    if (!n) return 0;

    int width = 5;

    int left = sprint_tree(n->left, true, offset, depth + 1, s);
    int right = sprint_tree(n->right, false, offset + left + width, depth + 1, s);

    char b[width + 1];
    sprintf(b, "(%03d)", n->key);
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

  void add_node(int key) {
    Node *n = new Node(key);

    if (!root) {
      root = n;
      return;
    }

    Node *curr = root;
    Node *prev = NULL;

    while (curr) {
      prev = curr;
      if (key < curr->key) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    if (key < prev->key) {
      prev->left = n;
    } else {
      prev->right = n;
    }
    n->parent = prev;
  }

  Node *maximum(Node *curr) {
    if (!curr) return NULL;

    while (curr->right) curr = curr->right;

    return curr;
  }

  Node *minimum(Node *curr) {
    if (!curr) return NULL;

    while (curr->left) curr = curr->left;

    return curr;
  }

  Node *find(int key) {
    Node *found = NULL;
    Node *curr = root;
    while (!found && curr) {
      if (curr->key == key) found = curr;
      if (key < curr->key) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    return found;
  }

  int count(int key) {
    int sum = 0;

    Node *curr = root;

    while (curr) {
      sum += curr->key == key;

      if (key < curr->key) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    return sum;
  }

  Node *predecessor(Node *curr) {
    if (!curr) return NULL;

    if (curr->left) return maximum(curr->left);

    while (curr->parent) {
      if (curr->parent->right == curr) return curr->parent;
      curr = curr->parent;
    }

    return NULL;
  }

  Node *successor(Node *curr) {
    if (!curr) return NULL;

    if (curr->right) return minimum(curr->right);

    while (curr->parent) {
      if (curr->parent->left == curr) return curr->parent;
      curr = curr->parent;
    }
    return NULL;
  }

  // Transplant postavlja da roditelj od n1 sada pokazuje na n2
  // te ako n2 postoji postaljva da je njegov roditelj sada roditelj od n1
  // ovime efektivno povezujemo roditelja od n1 i n2 te izbacujemo n1
  void transplant(Node *n1, Node *n2) {
    if (!n1->parent) root = n2;

    if (n1->parent && n1->parent->left == n1) {
      n1->parent->left = n2;
    } else if (n1->parent) {
      n1->parent->right = n2;
    }

    if (n2) {
      n2->parent = n1->parent;
    }

  }

  int delete_node(Node *curr) {
    if (!curr) return 0;

    if (!curr->left) {
      transplant(curr, curr->right);
    } else if (!curr->right) {
      transplant(curr, curr->left);
    } else {
      Node *successorNode = minimum(curr->right);
      // Nasljednik će uvijek biti lijevi list, te ovdje može imati 1 ili 0 djece
      // rješavamo problem tako stavljamo njegovo desno dijete na njegovo mjesto
      // ako nema desno dijete osigurali smo da roditelj od successorNode pokazuje na NULL
      // jer smo ustvari successorNode izbrisali, ako desno dijete postoji uspješno smo
      // ga povezali s novim roditeljem
      transplant(successorNode, successorNode->right);

      // Ako successorNode nije dijete curr spajamo successorNode s curr-ovim desnim djetetom

      // U slučaju da bi successorNode bio roditelj curr, zbog načina na kojeg tražimo
      // successorNode on će uvijek biti curr-ovo desno dijete, odnosno curr->right == successorNode
      // te bi se onda successorNode kružno povezao odnosno
      // successorNode->right == successorNode i successorNode->parent == successorNode
      if (successorNode->parent != curr) {
        successorNode->right = curr->right;
        curr->right->parent = successorNode;
      }

      // Transplant rješava povezivanje successorNodea s curr-ovim roditeljem
      // nama preostaje samo spajanje njegovog lijevo djeteta, jer znamo da postoji
      // kako je ovo slučaj brisanja s 2 djece

      transplant(curr, successorNode);
      successorNode->left = curr->left;
      curr->left->parent = successorNode;
    }

    delete curr;

    return 1;
  }
};

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(nullptr);

  int n, key;
  string ins;
  Tree::Node *element;

  Tree bst;

  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> ins;
    cout << ins;

    if (!(ins == "max" || ins == "min" || ins == "prn")) {
      cin >> key;
      cout << "(" << key << ")";
    }

    cout << ": ";

    if (ins == "add") {
      bst.add_node(key);
      cout << "Y\n";
    } else if (ins == "max") {
      element = bst.maximum(bst.root);
      if (element) {
        cout << element->key << "\n";
      } else {
        cout << "-\n";
      }
    } else if (ins == "min") {
      element = bst.minimum(bst.root);
      if (element) {
        cout << element->key << "\n";
      } else {
        cout << "-\n";
      }
    } else if (ins == "fnd") {
      element = bst.find(key);
      if (element) {
        cout << "Y\n";
      } else {
        cout << "N\n";
      }
    } else if (ins == "cnt") {
      cout << bst.count(key) << endl;
    } else if (ins == "pre") {
      element = bst.predecessor(bst.find(key));
      if (element) {
        cout << element->key << "\n";
      } else {
        cout << "-\n";
      }
    } else if (ins == "suc") {
      element = bst.successor(bst.find(key));
      if (element) {
        cout << element->key << "\n";
      } else {
        cout << "-\n";
      }
    } else if (ins == "del") {
      if (bst.delete_node(bst.find(key))) {
        cout << "Y\n";
      } else {
        cout << "N\n";
      }
    } else if (ins == "prn") {
      cout << endl;
      bst.print();
    }
  }

  return 0;
}
