#include <iostream>
#include <stack>
#include <string>

void print_reverse_words(std::stack<char> &wordStack) {
  while (!wordStack.empty()) {
    std::cout << wordStack.top();
    wordStack.pop();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;
  std::cin.ignore(n, '\n');

  std::stack<char> wordStack;

  for (int i = 0; i < n; ++i) {
    char c;
    std::cin.get(c);
    if (c == ' ') {
      print_reverse_words(wordStack);
      std::cout << ' ';
    } else {
      wordStack.push(c);
    }
  }

  print_reverse_words(wordStack);

  return 0;
}