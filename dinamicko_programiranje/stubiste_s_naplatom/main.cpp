#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int calculate_ways(std::vector<int> &prices, int n, int k, std::vector<int> &path) {
  int dp[n + 1];
  dp[0] = 0;


  for (int i = 1; i <= n; ++i) {
    dp[i] = 0x3f3f;
    for (int step = 1; step <= k; ++step) {
      if (i - step < 0) break;

      dp[i] = std::min(prices[i] + dp[i - step], dp[i]);
    }
  }

  int index = n;
  path.push_back(index);

  while (index > 0) {
    int value = dp[index] - prices[index];

    for (int i = index - 1; i >= 0; --i){
      if (dp[i] == value) {
        index = i;
        break;
      }
    }
    path.push_back(index);
  }

  std::reverse(path.begin(), path.end());


  return dp[n];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, k;

  std::cin >> n >> k;

  std::vector<int> prices(n + 1);
  for (int i = 0; i <= n; ++i) {
    std::cin >> prices[i];
  }
  std::vector<int> path;

  std::cout << calculate_ways(prices, n, k, path) << "\n";
  for (auto step : path) {
    std::cout << step << " ";
  }

  return 0;
}