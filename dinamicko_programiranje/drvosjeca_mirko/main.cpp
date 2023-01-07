#include <iostream>
#include <vector>

int maxPrice(int len, int value, std::vector<int> &memo, std::vector<int> price) {
  if (len == 0) return value;
  if (len < 0) return 0;

  if (memo[len]) return memo[len] + value;

  for (int i = 1; i <= len; ++i) {
    memo[len] = std::max(maxPrice(len - i, price[i], memo, price), memo[len]);
  }

  return memo[len] + value;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int d;
  std::cin >> d;

  std::vector<int> price(d + 1);
  for (int i = 1; i <= d; ++i) {
    std::cin >> price[i];
  }

  std::vector<int> memo(d + 1, 0);

  std::cout << maxPrice(d, 0, memo, price) << "\n";

  return 0;
}