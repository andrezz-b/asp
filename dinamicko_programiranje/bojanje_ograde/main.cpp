#include <iostream>
#include <vector>

using namespace std;

int totalWays(int n) {
  std::vector<int> dp(n + 1, 0);

  dp[1] = 2;
  dp[2] = 4;

  for (int i = 3; i <= n; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;

  std::cin >> n;

  std::cout << totalWays(n);

  return 0;
}