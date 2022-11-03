#include <iostream>
#include <cstring>

#define MAXS 10001

template <typename T> struct Stog {
public:
  T *arr;
  int top;

  T *getStog() {
    return arr;
  }

  Stog(int n)
    : arr(new T[n]), top(-1) 
  {}

  int stack_is_empty() {
    return top == -1;
  }

  void push(T val) {
    arr[++top] = val;
  }

  void pop() {
    if (stack_is_empty()) return;
    top--;
  }
  T getTop() {
    return arr[top];
  }
  void stack_clear() {
    top = -1;
  }
};

void relocate(Stog<int> &s1, Stog<int> &s2) {
  while (!s1.stack_is_empty()) {
    s2.push(s1.getTop());
    s1.pop();
  }

}

void enqueue(Stog<int> &s1, Stog<int> &s2, const int &val) {
  s1.push(val);
}

void dequeue(Stog<int> &s1, Stog<int> &s2) {
  s2.pop();
  relocate(s2, s1);
}

void print_head(Stog<int> &s1, Stog<int> &s2) {
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
  Stog<int> first(MAXS);
  Stog<int> second(MAXS);

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