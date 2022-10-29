#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXN 8

// sirina i visina 2D polja koje se koristi za funkciju do_print_tree
#define WIDTH 80
#define HEIGHT 10

typedef struct node_struct {
  int val;
  struct node_struct *left;
  struct node_struct *right;
} Node;

int do_print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
  char b[HEIGHT];
  int i, left, right, width = 5;

  if (!tree) return 0;
  sprintf(b,"(%03d)",tree->val);
  left = do_print_tree(tree->left,1,offset,depth+1,s);
  right = do_print_tree(tree->right,0,offset+left+width,depth+1,s);
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

void print_tree(Node *root) {
  char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  sprintf(print_format, "%%%ds", WIDTH-1);
  for (int i = 0; i < HEIGHT; i++) {
    sprintf(s[i], print_format, " ");
  }
  do_print_tree(root, 0, 0, 0, s);
  sprintf(empty_line, print_format, " ");
  for (int i = 0; i < HEIGHT; i++) {
    if (strcmp(s[i], empty_line)) printf("%s\n", s[i]);
  }
}

Node *create_node(int val, Node *left, Node *right) {
  Node *node = (Node *) malloc(sizeof(Node));
  if (node==NULL) return NULL;
  node->val = val;
  node->left = left;
  node->right = right;
  return node;
}

Node *create_tree(Node **nodes, int n) {
  while (n >  1) {
    for (int i = 0, k = 0; i < n; i += 2, k++) {
      Node *newNode = create_node(nodes[i]->val + nodes[i + 1]->val, nodes[i], nodes[i + 1]);
      nodes[k] = newNode;
    }
    n /= 2;
  }

  return nodes[0];
}

int main() {
  int h, n;
  Node *nodes[MAXN];
  scanf("%d", &h);
  n = 1<<h;
  for (int i = 0; i < n; ++i) {
    int val;
    scanf("%d", &val);
    nodes[i] = create_node(val, NULL, NULL);
  }
  Node *root = create_tree(nodes, n);
  print_tree(root);
  return 0;
}
