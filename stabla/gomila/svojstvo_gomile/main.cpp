#include <iostream>

using namespace std;

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define PARENT(i) ((i-1) / 2)
/*
 * Varijable min i max oznacavaju da li su vrijednosti u polju u skladu sa
 * svojstvom min odnosno max gomile. Na pocetku su 1 i cim ih barem jedna
 * provjera opovrgne postavljaju se na 0. Funkcija ide redom od zadnjeg do
 * prvog elementa polja i provjerava odnos izmedju djeteta i roditelja.
 * U ovisnosti o vrijednosti min i max varijable tijekom i na kraju provjera
 * moze se donijeti zakljucak i ispisati poruku ispisati.
*/
void dali_je_gomila(int *array, int len) {
  bool min = true;
  bool max = true;

  for (int i = len - 1; i >= 0; --i) {
    // Roditelj manji od djeteta, nije max heap
    if (array[i] > array[PARENT(i)]) {
      max = false;
    }
    // Roditelj veći od djeteta, nije min heap
    if (array[i] < array[PARENT(i)]) {
      min = false;
    }
  }
  if (!min && !max)
    std::cout << "NO-HEAP\n";
  else if (min && max)
    std::cout << "HEAP\n";
  else if (min && !max)
    std::cout << "MIN-HEAP\n";
  else
    std::cout << "MAX-HEAP\n";
}

int main() {
  int menu_choice, i, num, len = 0, *array = NULL;
  char c;

  setbuf(stdout, NULL);
  do {
    cin >> menu_choice;
    switch (menu_choice) {
    case 1:
      dali_je_gomila(array, len);
      break;
    case 2:
      cin >> len;
      if (array) free(array);
      array = new int[len];
      for (i = 0; i < len; i++) {
        cin >> num;
        array[i] = num;
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