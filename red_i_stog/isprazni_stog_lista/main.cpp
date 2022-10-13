#include <iostream>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

struct Node {
  int val;
  Node *next;

  Node(const int &val)
    : val(val), next(NULL)
  {}
};

int push(Node **top, const int &val) {
  Node *n = new Node(val);
  n->next = *top;
  *top = n;
  return 0;
}

int pop(Node **top) {
  if (*top == NULL) return -1;

  Node *tmp = *top;
  *top = (*top)->next;

  delete tmp;

  return 0;
}

int print(Node *top) {
  if (!top) return -1;

  for (Node *curr = top; curr != NULL; curr = curr->next) {
    std::cout << curr->val << " ";
  }
  std::cout << "\n";
  return 0;
}

void isprazni(Node **top) {
  while (*top != NULL) {
    pop(top);
  }

}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  //definirati cvor top
  Node *top = NULL;
  int menu_choice, val, ret_val;

  do {
    menu_choice = 0;
    std::cin >> menu_choice;
    switch (menu_choice) {
    case 1:
      isprazni(&top);
      break;
    case 2:
      std::cin >> val;
      ret_val = push(&top, val);
      if (ret_val == -1)
        DEBUG("Alokacija nije uspjela.");
      break;
    case 3:
      ret_val = pop(&top);
      if (ret_val == -1)
        DEBUG("Stog je prazan.");
      break;
    case 4:
      ret_val = print(top);
      if (ret_val == -1)
        DEBUG("Stog je prazan.");
      break;
    case 5:
      break;
    }
  } while (menu_choice != 5);

  return 0;
}