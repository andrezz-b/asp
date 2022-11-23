#include <iostream>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

void print_array(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }

    cout << "\n";
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selection_sort(int *a, int n) {
    if (n <= 1) return;

    int min_pos = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[min_pos]) min_pos = i;
    }
    swap(a + min_pos, a);

    selection_sort(a + 1, n - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int a[n];

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    selection_sort(a, n);

    print_array(a, n);

    return 0;
}