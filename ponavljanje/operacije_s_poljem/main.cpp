#include <iostream>

#define SIZE 8

using namespace std;

struct Polje {
  int *array;
  int size;

  Polje(int n) {
    array = new int[n];
    size = 0;
  }

  int insert_element(int pos, int val) {
    if (size == SIZE) return -1;
    if (size < pos - 1) return -2;
    for (int i = size; i >= pos; --i) {
      array[i] = array[i - 1];
    }
    array[pos - 1] = val;
    ++size;
    return 0;
  }

  int delete_element(int pos) {
    if (!size) return -1;
    if (size < pos) return -2;
    int j = 0;
    for (int i = 0; i < size; ++i) {
      if (pos - 1 != i) {
        array[j] = array[i];
        ++j;
      }
    }
    --size;
    return 0;
  }

  int print_array() {
    if (!size) return -1;
    cout << "Polje: ";
    for (int i = 0; i < size; ++i) {
      cout << array[i] << " ";
    }
    cout << endl;
    return 0;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  //definirati objekt Polja
  Polje polje(SIZE);

  char menu_choice;
  int val, retval, pos;
  do {
    cin >> menu_choice;
    switch (menu_choice) {

    case 'd':
      cin >> pos;
      cin >> val;
      //dodati u polje
      retval = polje.insert_element(pos, val);
      if (retval == -1) cout << "Polje je puno.\n";
      if (retval == -2) cout << "Nije moguce dodati element na poziciju " << pos << ".\n";
      break;
    case 'b':
      cin >> pos;
      //brisi iz polja
      retval = polje.delete_element(pos);
      if (retval == -1) cout << "Polje je prazno.\n";
      if (retval == -2) cout << "Nije moguce obrisati element na poziciji " << pos << ". \n";
      break;
    case 'i':
      //ispis polja
      retval = polje.print_array();
      if (retval == -1) cout << "Polje je prazno.\n";
      break;
    }
  } while (menu_choice != 'e');

  return 0;
}

