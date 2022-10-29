#include <iostream>
#include <string.h>

using namespace std;

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

struct Stablo {

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

  Node *root;


  void add_node(int key) {
    Node *new_node, *trenutni, *prethodni = NULL;

    new_node = new Node(key);

    trenutni = root;
    while (trenutni != NULL) {
      prethodni = trenutni;
      if (new_node->key < trenutni->key)
        trenutni = trenutni->left;
      else
        trenutni = trenutni->right;
    }

    new_node->parent = prethodni;
    if (prethodni == NULL) {
      root = new_node;
    } else if (new_node->key < prethodni->key) {
      prethodni->left = new_node;
    } else {
      prethodni->right = new_node;
    }
  }


  Node *najnizi_zajednicki_predak(Node *node, int k1, int k2) {
    if (!node) return NULL;

    const int min = std::min(k1, k2);
    const int max = std::max(k1, k2);

    if (node->key < min) {
      return najnizi_zajednicki_predak(node->right, k1, k2);
    } else if (node->key > max) {
      return najnizi_zajednicki_predak(node->left, k1, k2);
    }

    return node;
  } 

  int udaljenost_do_nasljednika(Node *node, int k) {
    if (!node) return 0;
    if (node->key == k) return 0;

    if (node->key < k) {
      return udaljenost_do_nasljednika(node->right, k) + 1;
    } else {
      return udaljenost_do_nasljednika(node->left, k) + 1;
    }
  }

  int udaljenost_u_stablu(int k1, int k2) {
    Node *ancestor = najnizi_zajednicki_predak(root, k1, k2);
    return udaljenost_do_nasljednika(ancestor, k1) + udaljenost_do_nasljednika(ancestor, k2);
  }

};

int main()
{
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int i, n, q, key, k1, k2;

  Stablo stablo;
  cin >> n;
  for (i = 0; i < n; ++i) {
    cin >> key;
    stablo.add_node(key);
  }

  cin >> q;
  for (i = 0; i < q; ++i) {
    cin >> k1;
    cin >> k2;
    cout << stablo.udaljenost_u_stablu(k1, k2) << endl;
  }
  return 0;
}