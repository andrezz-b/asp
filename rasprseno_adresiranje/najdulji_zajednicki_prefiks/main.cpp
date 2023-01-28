#include <bits/stdc++.h>

const int MOD = 1e9 + 7;

int binarySearch(int firstWord, int secondWord, const int &wordLength,
                 std::vector<std::vector<long long>> &hashTable) {
  int lo = -1;
  int hi = wordLength;

  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;

    if (hashTable[firstWord][mid] == hashTable[secondWord][mid]) {
      lo = mid;
    } else {
      hi = mid;
    }
  }


  return hi;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> words(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> words[i];
  }

  std::vector<std::vector<long long>> h(n, std::vector<long long>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      h[i][j] = j ? ((h[i][j - 1] * 127 + words[i][j]) % MOD) : words[i][0];
    }
  }

  int q;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    int firstWord, secondWord;

    std::cin >> firstWord >> secondWord;

    std::cout << binarySearch(firstWord - 1, secondWord - 1, m, h) << "\n";
  }

  return 0;
}