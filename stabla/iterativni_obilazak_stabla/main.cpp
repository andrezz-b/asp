#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

#define MAXN 1000
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

template <typename T> struct Stack {
  int size;
  int top_ptr;
  T *array;

  Stack(int n) {
    size = n;
    top_ptr = -1;
    array = new T[size];
  }

  ~Stack() {
    delete(array);
  }

  bool is_empty() {
    if (top_ptr <= -1) return true;

    return false;
  }

  bool is_full() {
    if (top_ptr >= size - 1) return true;

    return false;
  }

  T top() {
    if (is_empty()) return (T) - 1;

    return array[top_ptr];
  }

  void push(T val) {
    if (is_full()) return;

    array[++top_ptr] = val;


  }

  void pop() {
    if (is_empty()) return;

    top_ptr--;


  }
};


bool is_operator(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') return true;

  return false;
}

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
  Node *trenutni, *parent;
  int i;
  Tree(string tree_string) {
    root = NULL;
    create_tree(tree_string);
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
    root = NULL;

    Queue<Node *> queue(MAXN);
    trenutni = parent = NULL;

    for (i = 0; i < (int) tree_string.size(); i++)
    { //dodavanje u stablo koristeći red, auditorne vježbe su koristile stog
      if (tree_string[i] != ';')
      {
        if (tree_string[i] == '-')
          continue;

        trenutni = new Node(tree_string[i]);
        if (!root) root = trenutni;

        queue.enqueue(trenutni);

        if (parent && tree_string[i - 1] == ';')
        {
          parent->left = trenutni;
        }
        else if (i > 0)
        {
          parent->right = trenutni;
        }
      }
      else
      {
        parent = queue.front();
        queue.dequeue();
      }
    }
  }

  int sprint_tree(Node *root, int is_left, int offset, int depth, char s[HEIGHT][WIDTH])
  {
    char b[HEIGHT];
    int i, left, right, width = 3;

    if (!root)
      return 0;

    sprintf(b, "(%c)", root->val);
    left = sprint_tree(root->left, 1, offset, depth + 1, s);
    right = sprint_tree(root->right, 0, offset + left + width, depth + 1, s);

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
  void ispisi_stablo()
  {
    char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    int i;

    sprintf(print_format, "%%%ds", WIDTH - 1);

    for (i = 0; i < HEIGHT; i++)
      sprintf(s[i], print_format, " ");

    sprint_tree(root, 0, 0, 0, s);

    sprintf(empty_line, print_format, " ");
    for (i = 0; i < HEIGHT; i++)
    {
      if (strcmp(s[i], empty_line))
        cout << s[i] << "\n";
    }

  }

  void pre_order(Node *n) {
    if (!n) return;

    Stack<Node *> s(MAXN);
    s.push(n);

    while (!s.is_empty()) {
      Node *tmp = s.top();
      s.pop();
      std::cout << tmp->val;

      if (tmp->right) {
        s.push(tmp->right);
      }

      if (tmp->left) {
        s.push(tmp->left);
      }
    }

  }

  void post_order(Node *n) {
    if (!n) return;

    Stack<Node *> s1(MAXN), s2(MAXN);

    Node *curr = n;

    while (curr || !s1.is_empty()) {

      while (curr) {
        s1.push(curr);
        s2.push(curr);
        curr = curr->right;
      }
      curr = s1.top();
      s1.pop();
      curr = curr->left;
    }
    while (!s2.is_empty()) {
      std::cout << s2.top()->val;
      s2.pop();
    }

  }

  void in_order(Node *n) {
    if (!n) return;

    Stack<Node *> s(MAXN);

    Node *curr = n;

    while (curr || !s.is_empty()) {

      while (curr) {
        s.push(curr);
        curr = curr->left;
      }

      curr = s.top();
      s.pop();
      std::cout << curr->val;
      curr = curr->right;
    }

  }
};



int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  string tree_string;
  cin >> tree_string;

  Tree tree(tree_string);
  tree.ispisi_stablo();

  cout << "Pre-order: ";
  tree.pre_order(tree.root);
  cout << endl;

  cout << "In-order: ";
  tree.in_order(tree.root);
  cout << endl;

  cout << "Post-order: ";
  tree.post_order(tree.root);
  cout << endl;

  return 0;
}