#include <iostream>
#include <cstring>

#define MAXS 10001

struct Stog {
public:
  int *arr;
  int top;

  int *getStog() {
    return arr;
  }

  Stog(int n) {
    arr = new int[n];
    top = -1;
  }

  int stack_is_empty() {
    return top == -1;
  }

  void push(int val) {
    arr[++top] = val;
  }

  void pop() {
    if (stack_is_empty()) return;
    top--;
  }
  int getTop() {
    return arr[top];
  }
  void stack_clear() {
    top = -1;
  }
};

void relocate(Stog &s1, Stog &s2) {
  while (!s1.stack_is_empty()) {
    s2.push(s1.getTop());
    s1.pop();
  }

}

void enqueue(Stog &s1, Stog &s2, const int &val) {
  s1.push(val);
}

void dequeue(Stog &s1, Stog &s2) {
  s2.pop();
  relocate(s2, s1);
}

void print_head(Stog &s1, Stog &s2) {
  relocate(s1, s2);
  if (s2.stack_is_empty()) {
    std::cout << "buffering\n";
    return;
  }
  std::cout << s2.getTop() << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  //definirati dva stoga
  Stog first(MAXS);
  Stog second(MAXS);

  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    char op;
    std::cin >> op;
    if (op == 'e') {
      int x;
      std::cin >> x;
      enqueue(first, second, x);
    }
    else {
      print_head(first, second);
      dequeue(first, second);
    }
  }
  return 0;
}