#include <bits/stdc++.h>

using namespace std;

#define MAXN 1001

const int MOD = 1e9 + 7;

/*
Krecemo od zadnje rijeci jer ako nađemo jedinstvenu
sve iznad možemo brisati, ako nije jedinstvena
ako imamo m(broj stupaca) hash vrijednosti imamo jedinstvene stupce
*/

long long hashFunc(char c, long long current) {
  return (current * 127 + c) % MOD;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  // Matrica
  std::string s[MAXN];

  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
  }

  // Hash tablica
  long long h[MAXN] = {0};

  for (int i = n - 1; i >= 0; --i) {

    std::set<int> S;

    for (int j = 0; j < m; ++j) {
      h[j] = hashFunc(s[i][j], h[j]);
      
      S.insert(h[j]);
    }

    if ((int) S.size() == m) {
      std::cout << i << "\n";
      return 0;
    }

  }

  return 0;
}