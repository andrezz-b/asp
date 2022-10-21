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

struct Node {
    char val;
    Node *left, *right;
};

struct Stablo{
     Node *trenutni, *parent, *parents_queue[MAX_NODES];
     int tail, head, i, size;
    Node *root;
    Stablo(){
        root = NULL;
    }
   int sprint_tree(Node *root, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 5;

    if (!root) return 0;
    sprintf(b,"(%03d)",root->val);
    left = sprint_tree(root->left, 1, offset, depth + 1, s);
    right = sprint_tree(root->right, 0, offset + left + width, depth + 1, s);
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
        s[depth-1][offset + left + width / 2] = '.';
    }
    return left + width + right;
}

Node *read_tree(int n) {
  
  int val;

  trenutni = parent = NULL;
  parents_queue[0] = NULL;
  tail = head = -1;

  for (i = 0; i < n; i++) {
    cin >> val;
    if (val >= 0) {
      trenutni = (Node*) malloc(sizeof(Node));
      trenutni->val = val;
      trenutni->left = trenutni->right = NULL;
      if (parent) {
        if (i % 2) parent->left = trenutni;
        else parent->right = trenutni;
      }
      parents_queue[++tail] = trenutni;
    }
    if (i % 2 == 0) {
      if (head == tail) break;
      parent = parents_queue[++head];
    }
  }
  root = parents_queue[0];
  return NULL;
}
void ispisi_stablo(Node *root) {
  char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  int i;
  sprintf(print_format, "%%%ds", WIDTH-1);
  for (i = 0; i < HEIGHT; i++)
    sprintf(s[i], print_format, " ");

  sprint_tree(root, 0, 0, 0, s);

  sprintf(empty_line, print_format, " ");
  for (i = 0; i < HEIGHT; i++) {
    if (strcmp(s[i], empty_line))
      cout << s[i] << endl;
  }
}

int suma_listova(Node *node) {
  if (!node) return 0;
  if (!node->left && !node->right) return node->val;
  return suma_listova(node->left) + suma_listova(node->right);
   }
};

int main()
{
    ios_base::sync_with_stdio(true);
    cin.tie(NULL);
 
    int n;
  
    cin >> n;
    Stablo stablo;
    stablo.read_tree(n);
    stablo.ispisi_stablo(stablo.root);
    cout << stablo.suma_listova(stablo.root);
    return 0;
} 