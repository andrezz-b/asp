#include <iostream>
#include <ctime>

using namespace std;

#define PARENT(i) (i - 1) / 2
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2

void merge(int *array, int *temp, int lstart, int rp, int re) {
  int le = rp - 1;
  int lp = lstart;
  int tp = lstart;

  while ((lp <= le) && (rp <= re)) {
    // Ako je lp manji od rp njega stavi u polje i povecaj tp inace stavi rp
    if (array[lp] <= array[rp]) {
      temp[tp++] = array[lp++];
    } else {
      temp[tp++] = array[rp++];
    }
  }

  // Ako ostane nesto u lijevom to iskopriaj ako nema niceg nece uci u while
  while (lp <= le) {
    temp[tp++] = array[lp++];
  }

  // Ako ostane nesto u desnom to iskopiraj ako nema niceg nece uci u while
  while (rp <= re) {
    temp[tp++] = array[rp++];
  }

  // Nakon svih dodavanja rp ce pokazivat na 1 element iza zadnjeg
  // a mora pokazivati bas na zadnji element
  --rp;

  // Vrati sve iz pomocnog polja u pravo polje
  while (rp >= lstart) {
    array[rp] = temp[rp];
    --rp;
  }
}

void merge_sort(int *array, int *temp, int l, int r) {
  if (l < r) {
    int mid = (l + r) / 2;

    merge_sort(array, temp, l, mid);
    merge_sort(array, temp, mid + 1, r);

    merge(array, temp, l, mid + 1, r);
  }
}

int random_int(int lo, int hi) {
  // Returns random integer in range [lo, hi)
  return (abs((rand() << 16) + rand()) % (hi - lo)) + lo;
}

void quick_sort(int *array, int l, int r) {
  // int pivot = (r + l) / 2;

  // int pivot = l;
  // int pivot = r;
  int pivot = random_int(l, r + 1);

  int pivotValue = array[pivot];

  std::swap(array[pivot], array[r]);

  int i = l - 1;

  for (int j = l; j < r; ++j) {
    if (array[j] <= pivotValue)  {
      i++;
      std::swap(array[i], array[j]);
    }
  }

  std::swap(array[++i], array[r]);

  if (l < i) quick_sort(array, l, i - 1);
  if (i < r) quick_sort(array, i + 1, r);

}

void max_heapify(int *array, int i, int heap_size) {
  int l = LEFT(i);
  int r = RIGHT(i);

  int largest = i;

  if (l < heap_size && array[l] > array[largest]) {
    largest = l;
  }

  if (r < heap_size && array[r] > array[largest]) {
    largest = r;
  }

  if (largest != i) {
    swap(array[i], array[largest]);
    max_heapify(array, largest, heap_size);
  }
}

void heap_sort(int *array, int heap_size) {
  // Izrada gomile, bubble up
  for (int i = 0; i < heap_size; ++i) {
    int j = i;
    while (j != 0 && array[PARENT(j)] < array[j]) {
      std::swap(array[PARENT(j)], array[j]);
      j = PARENT(j);
    }
  }
  while (heap_size > 0) {
    // heap_size pokazuje na elemnt izvan niza
    heap_size--;
    // stavljamo prvi element na svoju poziciju na kraj
    std::swap(array[0], array[heap_size]);
    // novi element sa kraja moramo bubble down-at na dobru poziciju
    max_heapify(array, 0, heap_size);
  }
}

void print_array(int *array, int n) {
  for (int i = 0; i < n; ++i) {
    cout << array[i] << " ";
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  srand(time(NULL));

  int n, *array;

  std::cin >> n;

  array = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }

  // Merge sort implementation
  //int *temp = new int[n];
  //merge_sort(array, temp, 0, n - 1);
  //delete(temp);

  // Quick sort implementation
  // quick_sort(array, 0, n - 1);

  // Heap sort implementation
  heap_sort(array, n);

  print_array(array, n);

  delete(array);

  return 0;
}