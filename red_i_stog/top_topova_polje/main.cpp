#include<iostream>
#include <algorithm>

#define SIZE 100

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

struct Stog {
  int *array;
  int top;
  int size;
  int tt;

  int *getStog() {
    return array;
  }

  Stog(const int &n)
    : array(new int[n]), top(-1), size(n), tt(-1)
  {}

  int push(const int &val) {
    array[++top] = val;
    tt = std::max(tt, top);
    return 0;
  }

  int pop() {
    if (empty()) return -1;
    top--;
    return 0;
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
      std::cout << array[i];
    }
    return 0;
  }
};

void top_topova(const Stog &s) {
  std::cout << s.tt + 1 << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int val, ret_val, menu_choice;
  char c;

  //definirati stog
  Stog stack(SIZE);

  do {
    menu_choice = 0;

    //DEBUG("\n1 top topova (top_topova)");
    //DEBUG("\n2 dodaj (push)\n3 brisi (pop)\n4 ispis (print)\n5 izlaz\n");

    std::cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      top_topova(stack);
      break;
    case 2:
      std::cin >> val;

      //pozvati funkciju push
      ret_val = stack.push(val);
        if (ret_val == -1) DEBUG("Stog je pun.\n");

      break;
    case 3:
      //pozvati funkciju pop
      ret_val = stack.pop();
      if (ret_val == -1) DEBUG("Stog je prazan.\n");

      break;
    case 4:
      //ispisati stog
      ret_val = stack.print();
      if (ret_val == -1) DEBUG("Stog je prazan.\n");

      break;
    case 5:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 5);

  return 0;
}