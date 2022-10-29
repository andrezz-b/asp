#include <iostream>
#include <cctype>
#include <stack>

using namespace std;

#define MAXN 1000000

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

  int push(T val) {
    if (is_full()) return -1;

    array[++top_ptr] = val;

    return 0;
  }

  int pop() {
    if (is_empty()) return -1;

    top_ptr--;

    return 0;
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

  Tree(string postfix) {
    Stack<Node *> stack(MAXN);
    Node *n;

    for (auto cp : postfix) {
      if (!cp) break;

      n = new Node(cp);

      if (is_operator(cp)) {
        n->right = stack.top();
        stack.pop();
        n->left = stack.top();
        stack.pop();
      }

      stack.push(n);
    }

    root = stack.top();
    stack.pop();
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

  void pre_order(Node *n) {
    if (!n) return;

    std::cout << n->val;
    pre_order(n->left);
    pre_order(n->right);
  }

  void post_order(Node *n) {
    if (!n) return;

    post_order(n->left);
    post_order(n->right);
    std::cout << n->val;
  }

  void in_order(Node *n) {
    if (!n) return;

    in_order(n->left);
    std::cout << n->val;
    in_order(n->right);
  }
};

int priority(char c) {
  if (c == '*' || c == '/' || c == '%') return 2;

  if (c == '+' || c == '-') return 1;

  return 0;
}

string infix2postfix(string infix) {
  std::string postfix;
  std::stack<char> s;

  for (auto c : infix) {
    if (isalpha(c)) {
      postfix += c;
    } else if (is_operator(c)) {
      while (!s.empty() && priority(s.top()) >= priority(c)) {
        postfix += s.top();
        s.pop();
      }
      s.push(c);
    } else if (c == '(') {
      s.push(c);
    } else if (c == ')') {
      while (s.top() != '(') {
        postfix += s.top();
        s.pop();
      }
      s.pop();
    }
  }

  while (!s.empty()) {
    postfix += s.top();
    s.pop();
  }

  return postfix;
}

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int n;
  string infix, postfix;

  cin >> n;
  cin >> infix;

  postfix = infix2postfix(infix);

  cout << "Postfix: ";
  cout << postfix << endl;

  Tree tree(postfix);

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
