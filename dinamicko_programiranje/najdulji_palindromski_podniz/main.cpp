#include <iostream>
#include <vector>
#include <string>

int LPS(std::string s) {
  if (!s.length()) return 0;

  int len = s.length();

  std::vector<std::vector<int>> dp(len + 1, std::vector<int>(len));

  for (int i = 0; i < len; ++i) {
    dp[i][i] = 1;
  }

  for (int dist = 1; dist < len; dist++) {
    for (int first = 0; first < len - dist; ++first) {
      int second = first + dist;
      // if (second >= len) break;

      // Ako su jednaki, duljina + 2, i duljina i + 1, j - 1 -> duljina palindroma unutar njih
      if (s[first] == s[second]) {
        dp[first][second] = 2 + dp[first + 1][second - 1];
      } else {
        // Ako su razliciti, onda trazimo max od lijevog i desnog palindroma 
        // odnosno odbacujemo desno slovo pa gledamo unutra ili odbacujemo lijevo slovo
        // pa gledamo unutra
        dp[first][second] = std::max(dp[first][second - 1], dp[first + 1][second]);
      }

    }
  }

  return dp[0][len - 1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string word;
  std::cin >> word;

  std::cout << LPS(word);

  return 0;
}