#include <iostream>

template <typename T> class Stog {
  T *array;
  int top;
  int size;

public:
  T *getStog() {
    return array;
  }

  Stog(const int &n)
    : array(new T[n]), top(-1), size(n)
  {}

  int push(const T &val) {
    if (top >= size) return -1;
    array[++top] = val;
    return 0;
  }

  T pop() {
    if (empty()) return (T) -1;
    T popped = array[top];
    top--;
    return popped;
  }

  T topValue() {
    if (empty()) return (T) -1;
    return array[top];
  }

  int empty() {
    return top == -1;
  }

  void clear() {
    top = -1;
  }

  int print() {
    if (empty()) return -1;
    for (int i = top; i >= 0; --i) {
      std::cout << array[i] << " ";
    }
    std::cout << "\n";
    return 0;
  }
};

int calculate(Stog<int> &s, const char &op) {
  int num1 = s.pop();
  int num2 = s.pop();
  

  std::cout << num1 << op << num2 << " = ";
  switch (op) {
    case '+':
    return num1 + num2;
    case '*':
    return num1 * num2;
    case '-':
    return num2 - num1;
  }
  return 0;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  //instancirati objekt razreda Stog
  Stog<int> s(n);
  const std::string operations = "*+-";

  for (int i = 0; i < n; i++) {
    char input;
    std::cin >> input;

    if (operations.find(input) == std::string::npos) {
      s.push(input - '0');
    } else {
      s.push(calculate(s, input));
      std::cout << s.topValue() << "\n";
      s.print();
    }
  }

  std::cout << s.topValue();

  return 0;
}