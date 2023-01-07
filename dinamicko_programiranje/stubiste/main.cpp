#include <iostream>
#include <vector>

const int possibleSteps[3] = {1, 2, 3};

int calculateSteps(int n, std::vector<int> &memo) {
  if (n == 0) return 1;
  if (n < 0) return 0;

  if (memo[n] != 0) return memo[n];

  for (auto const &step : possibleSteps) {
    memo[n] += calculateSteps(n - step, memo);
  }

  return memo[n];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::vector<int> memo(n + 1, 0);

  std::cout << calculateSteps(n, memo); 

  return 0;
}