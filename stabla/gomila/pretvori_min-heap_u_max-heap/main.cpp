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

    int i = heap_size - 1;
    vals[i] = k;

    // Bubble Up
    while (i != 0 && vals[PARENT(i)] > vals[i]) {
      swap(&vals[i], &vals[PARENT(i)]);
      // cout << "mijenja " << vals[i] << " " << vals[PARENT(i)] << endl;
      i = PARENT(i);
    }

    return 0;
  }

  void min_heapify(int i) {
    int l = LEFT(i);
    int r = RIGHT(i);

    int smallest = i;

    if (l < heap_size && vals[l] < vals[smallest]) {
      smallest = l;
    }

    if (r < heap_size && vals[r] < vals[smallest]) {
      smallest = r;
    }

    if (smallest != i) {
      swap(&vals[i], &vals[smallest]);
      min_heapify(smallest);
    }
  }

  void print_heap() {
    for (int i = 0; i < heap_size; ++i) {
      cout << " " << vals[i];
    }
    cout << endl;
  }

  void MaxHeapify(int i) {
    int l = LEFT(i);
    int r = RIGHT(i);

    int largest = i;

    if (l < heap_size && vals[l] > vals[largest]) {
      largest = l;
    }

    if (r < heap_size && vals[r] > vals[largest]) {
      largest = r;
    }

    if (largest != i) {
      swap(&vals[i], &vals[largest]);
      MaxHeapify(largest);
    }
  }

  void convertMaxHeap() {
    // Bubble down sve roditelje
    for (int i = PARENT(heap_size - 1); i >= 0; --i) {
      MaxHeapify(i);
    }
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
      cout << "MinHeap: ";
      heap.print_heap();
      break;
    case 3:
      heap.convertMaxHeap();
      cout << "MaxHeap: ";
      heap.print_heap();
    case 4:
      break;
    }
  } while (menu_choice != 4);

  return 0;
}