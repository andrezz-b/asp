#include <iostream>
#include <list>

#define SIZE 100

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

template <typename T> struct Stog {
  std::list<T> l;
  int top;
  int tt;

  std::list<T> getStog() {
    return l;
  }

  Stog()
    : top(-1), tt( 0)
  {}

  int push(const T &val) {
    l.push_front(val);
    top++;

    tt = std::max((int) l.size(), tt);
    return 0;
  }

  int pop() {
    if (empty()) return -1;

    l.pop_front();
    top--;
    return 0;
  }

  int empty() {
    return top <= -1;
  }

  void clear() {
    l.clear();
    top = -1;
  }

  int print() {
    if (empty()) return -1;

    for (auto &val : l)
      std::cout << val << " ";
    /*
    for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
      std::cout << *it << " ";
    */
    std::cout << "\n";

    return 0;
  }
};

void top_topova(const Stog<int> &s) {
  std::cout << s.tt << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int val, ret_val, menu_choice;
  char c;

  Stog<int> s = Stog<int>();

  do {
    menu_choice = 0;

    //DEBUG("\n1 top topova (top_topova)");
    //DEBUG("\n2 dodaj (push)\n3 brisi (pop)\n4 ispis (print)\n5 izlaz\n");

    std::cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      top_topova(s);
      break;
    case 2:
      std::cin >> val;

      ret_val = s.push(val);
      if (ret_val == -1)
        DEBUG("Stog je pun.\n");

      break;
    case 3:
      ret_val = s.pop();
      if (ret_val == -1)
        DEBUG("Stog je prazan.\n");

      break;
    case 4:
      ret_val = s.print();
      if (ret_val == -1)
        DEBUG("Stog je prazan.\n");

      break;
    case 5:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 5);

  return 0;
}