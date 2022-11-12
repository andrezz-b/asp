#include <iostream>

using namespace std;

#define MAXN 100
#define PARENT(i) (i - 1) / 2
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2

struct Heap {
  int capacity;
  int heap_size;
  int *vals;

  Heap(int size) {
    capacity = size;
    heap_size = 0;
    vals = new int[capacity];
  }

  ~Heap() {
    delete(vals);
  }

  void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
  }

  int insert_key(int k) {
    if (heap_size >= capacity) return -1;
    heap_size++;
    int index = heap_size - 1;
    vals[index] = k;
    while (index != 0 && vals[index] < vals[PARENT(index)]) {
      swap(&vals[index], &vals[PARENT(index)]);
      index = PARENT(index);
    }

    return 0;
  }

  void min_heapify(int i) {
    int index = i;
    while (LEFT(index) < heap_size) {
      int minChildIndex = vals[LEFT(index)] < vals[RIGHT(index)] ? LEFT(index) : RIGHT(index);

      if (vals[index] < vals[minChildIndex]) return;

      swap(&vals[index], &vals[minChildIndex]);

      index = minChildIndex;
    }

  }

  void min_heapify_recursive(int i) {
    int smallest = i;

    if (LEFT(i) < heap_size && vals[LEFT(i)] < vals[smallest]) {
      smallest = LEFT(i);
    }

    if (RIGHT(i) < heap_size && vals[RIGHT(i)] < vals[smallest]) {
      smallest = RIGHT(i);
    }

    if (smallest != i) {
      swap(&vals[i], &vals[smallest]);
      min_heapify_recursive(smallest);
    }
  }

  int delete_key(int i) {
    if (i >= heap_size || heap_size <= 0) return -1;
    vals[i] = vals[heap_size - 1];
    heap_size--;
    min_heapify(i);
    return 0;
  }

  void print_heap() {
    cout << "MinHeap:";
    for (int i = 0; i < heap_size; ++i) {
      cout << " " << vals[i];
    }
    cout << endl;
  }
};

int main() {
  ios_base::sync_with_stdio(true);
  cin.tie(NULL);

  int menu_choice;
  int val;
  Heap heap(MAXN);

  do {
    cin >> menu_choice;

    switch (menu_choice) {
    case 1:
      cin >> val;
      heap.insert_key(val);
      break;
    case 2:
      cin >> val;
      heap.delete_key(val);
      break;
    case 3:
      heap.print_heap();
      break;
    case 4:
      break;
    }
  } while (menu_choice != 4);

  return 0;
}