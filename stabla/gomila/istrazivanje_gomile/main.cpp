#include <iostream>

using namespace std;

#define PARENT(i) ((i-1) / 2)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

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

int is_max_heap(int *array, int len) {
  int i;

  for (i = len - 1; i > 0; i--) {
    if (array[i] > array[PARENT(i)]) {
      return 0;
    }
  }
  return 1;
}

int istrazi(int *heap, int n, int k, int x) {
  int counter = 0, i;
  Stack<int> stog(k);
  stog.push(0);
  // Iterativni obilazak stabla
  while (!stog.is_empty()) {
    i = stog.top();
    stog.pop();
    // Ako je trenutni element veći od x povećacamo brojač
    // i dodajemo njegovu djecu u stog (ako je ima)
    if (heap[i] > x) {
      counter++;
      if (counter >= k) return 1;
      if (RIGHT(i) < n) stog.push(RIGHT(i));
      if (LEFT(i) < n) stog.push(LEFT(i));
    }
  }
  return 0;
}

int main() {
  int menu_choice, i, num, len = 0, k, x, *heap = NULL;
  char c;

  setbuf(stdout, NULL);
  do {
    cin >> menu_choice;
    switch (menu_choice) {
    case 1:
      do {
        cin >> k;
      } while (k < 1 || k >= len);
      std::cin >> x;
      //ovdje pozovi funkciju
      std::cout << (istrazi(heap, len, k, x) ? "Y" : "N") << "\n";
      break;
    case 2:
      cin >> len;
      if (heap) delete(heap);
      heap = new int[len];
      for (i = 0; i < len; i++) {
        cin >> num;
        heap[i] = num;
      }
      if (!is_max_heap(heap, len)) {
        delete heap;
        heap = NULL;
      }
      break;
    case 3:
      break;
    default:
      while ((c = getchar()) != '\n' && c != EOF);
    }
  } while (menu_choice != 3);
  return 0;
}
