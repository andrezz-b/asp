#include <bits/stdc++.h>

using namespace std;

// Koristi se kod hashiranja znakovnih nizova
#define ALPHA 127

struct HashTable {
  vector< pair<string, int> > table;
  int size;
  int type;  // 1 - linearno, 2 - kvadratno

  HashTable (int size, int type) : size(size), type(type) {
    table.resize(size, {"", 0});
  }

  int hash(string &k) {
    int ret = 0;

    for (auto c : k) {
      ret += ret * ALPHA + (int) c;
      ret %= size;
    }

    return ret;
  }

  // Vraca adresu (indeks) pretinca koristeci funkciju hash i linearno ispitivanje
  int oahash_linear(string &key, int i) {
    return (hash(key) + i) % this->size;
  }

  // Vraca adresu (indeks) pretinca koristeci funkciju hash i kvadratno ispitivanje uz konstante c_1 = c_2 = 0.5

  int oahash_quadratic(string &key, int i) {
    return (hash(key) + (i + (long long) i * i) / 2) % size;
  }


  // U ovisnosti o tipu otvorenog adresiranja poziva odgovarajucu metodu.
  int oahash(string &key, int i) {
    if (this->type == 1) return oahash_linear(key, i);

    return oahash_quadratic(key, i);
  }

  /*
   * Upisuje element u tablicu koristeci kljuc i funkciju oahash.
   * Ukoliko su svi pretinci u nizu zauzeti vraca -1, a inace vraca indeks pretinca.
   */
  int insert(string &key, int &value) {


    for (int i = 0; i < size; ++i) {

      int slotIndex = oahash(key, i);

      // Ako je prazno mjesto tu stavljamo našu vrijednost
      if (table[slotIndex].first == "") {
        table[slotIndex] = { key, value};
        return slotIndex;
        // Ako smo pronašli isti naš ključ onda mijenjamo njegovu vrijednost
      } else if (table[slotIndex].first == key) {
        table[slotIndex].second = value;
        return slotIndex;
      }
    }

    return -1;
  }

  /*
   * Dohvaca element u tablici koristeci kljuc i funkciju oahash i vraca trazeni element
   * odnosno pair (kljuc, vrijednost).
   * Ukoliko element s trazenim kljucem ne postoji vraca pair s praznim kljucem i vrijednosti 0.
   */
  pair<string, int> get(string &k) {

    for (int i = 0; i < size; ++i) {

      int slotIndex = oahash(k, i);

      if (table[slotIndex].first == "") break;

      if (table[slotIndex].first == k) {
        return table[slotIndex];
      }
    }

    return {"", 0};
  }

  /*
   * Za svaki indeks u tablici ispisuje broj ispitivanja potreban za dohvat elementa
   * koji je zapisan u tom pretincu odnosno 0 ukoliko je pretinac prazan.
   */
  void print_usage() {
    for (int slot = 0; slot < size; ++slot) {

      int i = -1;

      if (table[slot].first != "") {
        for (i = 0; i < size; ++i) {

          // Ako je jednak pronasli smo slot
          if (oahash(table[slot].first, i) == slot) break;
        }
      }


      std::cout << slot << " " << i + 1 << "\n";
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, t, q;
  cin >> n >> m >> t;
  HashTable ht(m, t);

  for (int i = 0; i < n; ++i) {
    string k;
    int v;
    cin >> k >> v;

    int retval = ht.insert(k, v);
    if (retval == -1) cout << "Unos neuspjesan " << k << "\n";
  }

  cin >> q;
  for (int i = 0; i < q; ++i) {
    int t;
    cin >> t;

    if (t == 1) {
      string k;
      int i;
      cin >> k >> i;

      cout << ht.oahash(k, i) << "\n";
    } else if (t == 2) {
      string k, k2;
      int v;
      cin >> k;

      tie(k2, v) = ht.get(k);
      if (k2 != "") cout << k << " " << v << "\n";
      else cout << "Nije pronadjen " << k << "\n";
    } else if (t == 3) {
      ht.print_usage();
    }
  }

  return 0;
}