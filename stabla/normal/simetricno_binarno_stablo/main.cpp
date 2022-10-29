#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAX_TREE_STRING 100
#define MAX_NODES 100
// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 16

typedef struct node {
  int val;
  struct node *left;
  struct node *right;
} Node;


int sprint_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
  char b[HEIGHT];
  int i, left, right, width = 5;

  if (!tree) return 0;
  sprintf(b, "(%03d)", tree->val);
  left = sprint_tree(tree->left, 1, offset, depth+1, s);
  right = sprint_tree(tree->right, 0, offset+left+width, depth+1, s);
  for (i=0; i<width; i++)
    s[depth][offset+left+i] = b[i];
  if (depth) {
    if (is_left) {
      for (i=0; i<width+right; i++)
        s[depth-1][offset+left+width/2+i] = '-';
    } else {
      for (i=0; i<left+width; i++)
        s[depth-1][offset-width/2+i] = '-';
    }
    s[depth-1][offset+left+width/2] = '.';
  }
  return left+width+right;
}

void ispisi_stablo(Node *root) {
  char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  int i;
  sprintf(print_format, "%%%ds", WIDTH-1);
  for (i=0; i<HEIGHT; i++)
    sprintf(s[i], print_format, " ");

  sprint_tree(root, 0, 0, 0, s);

  sprintf(empty_line, print_format, " ");
  for (i=0; i<HEIGHT; i++) {
    if (strcmp(s[i],empty_line))
      printf("%s\n", s[i]);
  }
}

Node *read_tree(int n) {
  Node *trenutni, *parent, *parents_queue[MAX_NODES];
  int tail, head, val;

  trenutni = parent = NULL;
  parents_queue[0] = NULL;
  tail = head = -1;

  for (int i = 0; i < n; ++i) {
    scanf("%d", &val);
    if (val>=0) {
      trenutni = (Node *)malloc(sizeof(Node));
      trenutni->val = val;
      trenutni->left = trenutni->right = NULL;
      if (parent) {
        if (i%2) parent->left = trenutni;
        else parent->right = trenutni;
      }
      parents_queue[++tail] = trenutni;
    }
    if (i%2==0) {
      if (head==tail) break;
      parent = parents_queue[++head];
    }
  }
  return parents_queue[0];
}

int isMirror(Node *node1, Node *node2) {
  // Ako su oba prazna onda je to dobro, isti su
  if (!node1 && !node2) return 1;
  // Ako je samo 1 prazan onda nisu isti
  if (!node1 || !node2) return 0;
  return node1->val == node2->val
         && isMirror(node1->left, node2->right)
         && isMirror(node1->right, node2->left);
}

int provjeri_simetriju(Node *node) {
  return isMirror(node, node);
}

int main () {
  int n;
  Node *root=NULL;

  scanf("%d", &n);
  root = read_tree(n);
  ispisi_stablo(root);
  if (provjeri_simetriju(root)) {
    printf("Y\n");
  } else {
    printf("N\n");
  }
  return 0;
}
