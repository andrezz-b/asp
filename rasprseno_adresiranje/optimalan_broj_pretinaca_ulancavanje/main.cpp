#include <bits/stdc++.h>

using namespace std;

#define MAXN 100
#define ALPHA 127

struct HashTable {
  vector<list<string>> table;
  int size;
  explicit HashTable (int size) : size(size) {
    table.resize(size);
  }

  int hsh(string &k) {
    int ret = 0;
    for (auto c : k) {
      ret += ret * ALPHA + (int)c;
      ret %= size;
    }
    return ret;
  }

  int insert(string &k) {
    for (auto &el : table[hsh(k)]) {
      if (el == k) return 0;
    }
    table[hsh(k)].push_back(k);
    return table[hsh(k)].size();
  }

  bool get(string &k) {
    for (auto &el : table[hsh(k)]) {
      if (el == k) return true;
    }
    return false;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int query, mlo, mhi;

  std::cin >> query >> mlo >> mhi;
  std::vector<std::string> words(query);

  for (int i = 0; i < query; ++i) {
    std::cin >> words[i];
  }

  int minListLength = INT_MAX;
  int optimalSize = mhi;

  for (int currentSize = mlo; currentSize <= mhi; ++currentSize) {
    HashTable ht(currentSize);
    int listLenghtCurrent = 0;

    for (auto &word : words) {
      listLenghtCurrent += ht.insert(word);
    }

    if (listLenghtCurrent < minListLength) {
      optimalSize = currentSize;
      minListLength = listLenghtCurrent;
    }
  }

  std::cout << optimalSize;

  return 0;
}