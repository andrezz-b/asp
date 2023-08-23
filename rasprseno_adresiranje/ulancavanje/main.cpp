#include <bits/stdc++.h>

using namespace std;

#define ALPHA 127

struct HashTable {
  vector< list< pair<string, int> > > table;
  int size;

  HashTable (int size) {
    table.resize(size);
    this->size = size;
  }

  int hsh(string &k) {
    int ret = 0;
    for (auto c : k) {
      ret += ret * ALPHA + (int)c;
      ret %= size;
    }
    return ret;
  }

  void insert(string &k, int v) {
    std::list<std::pair<std::string, int>> *tableList = &table[hsh(k)];

    // Ako postoje elementi u listi onda vidimo
    // ako već postoji naš ključ pa da zamijenimo vrijednost
    for (auto &listElement : *tableList) {
      if (listElement.first == k) {
        listElement.second = v;
        return; 
      }
    }

   tableList->push_back({k, v});
  }

  pair<int, int> get(string &k) {

    std::list<std::pair<std::string, int>> *tableList = &table[hsh(k)];
    int index = 0, v = 0;
    for (auto listElement : *tableList) {
      index++;
      if (listElement.first == k) {
        v = listElement.second;
        return {index, v};
      }
    }

    return {0, 0};
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, q;
  cin >> n >> m;
  HashTable ht(m);

  for (int i = 0; i < n; ++i) {
    string k;
    int v;
    cin >> k >> v;

    ht.insert(k, v);
  }

  cin >> q;
  for (int i = 0; i < q; ++i) {
    string k;
    cin >> k;

    int pos, v;
    tie(pos, v) = ht.get(k);

    cout << v << " " << pos << "\n";
  }

  return 0;
}