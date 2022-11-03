#include <iostream>
#include <string>

template <typename T> struct Cvor {
  T val;
  Cvor<T> *next;

  Cvor()
    : next(NULL)
  {}

  Cvor(const T &val)
    : val(val), next(NULL)
  {}
};

template <typename T> struct Stog {
  Cvor<T> *top;

  Stog()
    : top(NULL)
  {}

  int push(const T &val) {
    Cvor<T> *p = new Cvor<T>(val);
    p->next = top;
    top = p;
    return 0;
  }

  int pop() {
    if (top == NULL) return -1;
    Cvor<T> *drugi;

    drugi = top->next;
    delete top;
    top = drugi;
    return 0;
  }

  int empty() {
    if (top == NULL) return 1;
    return 0;
  }

  T rtop() {
    if (empty()) return (T) 0;

    return top->val;
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::string op;

  Stog<int> stack;

  Stog<int> maxStack;

  for (int i = 0; i < n; ++i) {
    std::cin >> op;

    if (op == "max") {
      if (stack.empty()) {
        std::cout << "-\n";
      } else {
        std::cout << maxStack.rtop() << "\n";
      }

    } else if (op == "pop") {
      // Ako je trenutni koji smo izbacili isti kao u maxStacku onda smo maknuli
      // trenutni max pa ga mičemo i iz maxStack
      if (stack.rtop() == maxStack.rtop()) {
        maxStack.pop();
      }
      stack.pop();

    } else if (op == "push") {
      int x;
      std::cin >> x;
      stack.push(x);
      // U maxStack spremamo svaki novi element koji je veći ili jednak od top u maxStack
      // jer će top u maxStack uvijek biti najveći element normalnog stacka
      // koristimo veće ili jednako jer ako dodajemo više istih brojeva onda bi trebali
      // pamtiti koliko istih smo dodali, a to možemo izbjeći samo da iste dodajemo u oba stacka
      if (x >= maxStack.rtop()) {
        maxStack.push(x);
      }
    }
  }

  return 0;
}