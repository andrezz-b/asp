#include <iostream>
#include <cstring>

using namespace std;

#define WIDTH 80
#define HEIGHT 10

struct Tree {
  struct Node {
    int key;
    int height;
    Node *left;
    Node *right;
    Node *parent;

    Node(int value) {
      key = value;
      height = 0;
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
    delete(n->left);
    destroy_tree(n->right);
    delete(n->right);
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

  Node *find(Node *curr, int key) {
    if (!curr) return NULL;

    if (key == curr->key) return curr;

    if (key < curr->key) {
      return find(curr->left, key);
    } else {
      return find(curr->right, key);
    }
  }

  /*
   * Rekurzivna funkcija koja dodaje cvor u binarno stablo pretrazivanja.
   */
  Node *add_node(Node *curr, Node *parent, int key) {

    if (!curr) {
      Node *n = new Node(key);
      n->parent = parent;
      return n;
    }

    if (key < curr->key) {
      curr->left = add_node(curr->left, curr, key);
    } else {
      curr->right = add_node(curr->right, curr, key);
    }
    return curr;
  }

  /*
   * Vraca faktor ravnoteze za cvor koristeci visinu njegove djece.
   * Ako cvor ne postoji vraca 0.
   * Slozenost O(1)
   */
  int calculate_balance_factor(Node *curr) {
    if (!curr) return 0;

    return (curr->left ? curr->left->height : -1) - (curr->right ? curr->right->height : -1);
  }

  /*
   * Postavlja visinu cvora za jedan vecu od visine viseg djeteta.
   * Ako cvor nema djece visina je 0.
   * Slozenost O(1)
   */
  void recalculate_node_height(Node *curr) {
    if (!curr) return;

    if (!curr->left && !curr->right) {
      curr->height = 0;
    } else if (!curr->left) {
      curr->height = curr->right->height + 1;
    } else if (!curr->right) {
      curr->height = curr->left->height + 1;
    } else {
      curr->height = std::max(curr->left->height, curr->right->height) + 1;
    }
  }

  /*
   * Postavlja visinu za sve cvorovekoristeci post order i
   * recalculate_node_height.
   * Slozenost O(logn)
   */
  void recalculate_all_heights(Node *curr) {
    if (!curr) return;

    recalculate_all_heights(curr->left);
    recalculate_all_heights(curr->right);
    recalculate_node_height(curr);
  }

  /*
   * Obavlja lijevu rotaciju i obnavlja visine za cvorove koji su promjenili
   * razinu koristeci funkciju recalculate_node_height. Vraca gornji cvor
   * odnosno y.
   * Slozenost O(1)
   */
  Node *left_rotate(Node *x) {
    if (!x->right) return x;

    Node *y = x->right;
    Node *beta = y->left;
    Node *pi = x->parent;

    x->right = beta;                                        // I

    if (beta) {
      beta->parent = x;                                     // II
    }

    y->parent = pi;                                         // III

    if (pi) {
      if (x == pi->left) {
        pi->left = y;                                       // IV
      } else {
        pi->right = y;                                      // IV
      }
    }

    y->left = x;                                            // V

    x->parent = y;                                          // VI

    recalculate_node_height(x);
    recalculate_node_height(y);

    return y;
  }

  /*
   * Obavlja desnu rotaciju i obnavlja visine za cvorove koji su promjenili
   * razinu koristeci funkciju recalculate_node_height. Vraca gornji cvor
   * odnosno x.
   * Slozenost O(1)
   */
  Node *right_rotate(Node *y) {
    if (!y->left) return y;

    Node *x = y->left;
    Node *beta = x->right;
    Node *pi = y->parent;

    y->left = beta;

    if (beta) beta->parent = y;

    x->parent = pi;

    if (pi && pi->left == y) {
      pi->left = x;
    } else if (pi && pi->right == y) {
      pi->right = x;
    }
    x->right = y;
    y->parent = x;

    recalculate_node_height(y);
    recalculate_node_height(x);

    return x;
  }

  /*
   * Balansira pojedini cvor koristeci rotacije. Izracunava novu visinu za cvor
   * koristeci funkciju recalculate_node_height.
   * Slozenost O(1)
   */
  Node *balance_node(Node *curr) {
    if (!curr) return NULL;
    const int balance = calculate_balance_factor(curr);
    // Ako je balance > 1 stablo je left heavy pa moramo napraviti
    // right rotate da izbalansiramo
    if (balance > 1) {
      // Ako je lijevo podstablo right heav odnosno balance < 0
      // onda prvo to stablo moramo napraviti left heavy (lijeva rotacija)
      // da uspjesno napravimo desnu rotaciju koja onda daje balansirano stablo
      if (curr->left && calculate_balance_factor(curr->left) < 0) {
        curr->left = left_rotate(curr->left);
      }
      curr = right_rotate(curr);
      // Ako je balance < -1 stablo je right heavy pa moramo napraviti
      // left rotate da izbalansiramo
    } else if (balance < -1 ) {
      // Ako je desno podstablo left heavy odnosno balance > 0
      // onda prvo to stablo moramo napraviti right heavy (desna rotacija)
      // da uspjesno napravimo lijevu rotaciju koja onda daje balansirano stablo
      if (curr->right && calculate_balance_factor(curr->right) > 0) {
        curr->right = right_rotate(curr->right);
      }
      curr = left_rotate(curr);
    }

    recalculate_node_height(curr);

    return curr;
  }

  /*
   * Rekurzivna funkcija koja dodaje cvor u balansirano stablo, vrlo slicna
   * funkciji add_node za nebalansirano stablo s tom razlikom da se nakon
   * dodavanja odnosno u povratku balansiraju svi preci dodanog cvora pozivom
   * funkcije balance_node.
   */
  Node *add_balanced_node(Node *curr, Node *parent, int key) {
    if (!curr) {
      Node *n = new Node(key);
      n->parent = parent;
      return n;
    }

    if (key < curr->key) {
      curr->left = add_balanced_node(curr->left, curr, key);
    } else {
      curr->right = add_balanced_node(curr->right, curr, key);
    }

    return balance_node(curr);
  }
};

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  char mode, c;
  int menu_choice, val;

  Tree::Node *x, *y;
  Tree avl;

  do {
    cin >> mode;
  } while (mode != 'n' && mode != 'b');

  do {
    cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      while (cin >> val) {
        if (val < 1 || val > 999) {
          continue;
        }

        if (mode == 'n') {
          avl.root = avl.add_node(avl.root, NULL, val);
        } else {
          avl.root = avl.add_balanced_node(avl.root, NULL, val);
        }
      }

      while ((c = getchar()) != '\n' && c != EOF);
      cin.clear();
      break;
    case 2:
      cin >> val;

      if (mode == 'n') {
        avl.recalculate_all_heights(avl.root);
      }

      cout << avl.calculate_balance_factor(avl.find(avl.root, val)) << endl;
      break;
    case 3:
      cin >> val;

      x = avl.find(avl.root, val);
      y = avl.left_rotate(x);

      if (x == avl.root) {
        avl.root = y;
      }
      break;
    case 4:
      cin >> val;

      y = avl.find(avl.root, val);
      x = avl.right_rotate(y);

      if (y == avl.root) {
        avl.root = x;
      }
      break;
    case 5:
      avl.print();
      break;
    case 6:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 6);

  return 0;
}
