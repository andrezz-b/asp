#include <iostream>
#include <vector>

int calculateSteps(int n, std::vector<int> &memo, int possibleSteps) {
  if (n == 0) return 1;
  if (n < 0) return 0;

  if (memo[n] != 0) return memo[n];

  for (int step = 1; step <= possibleSteps; ++step) {
    memo[n] += calculateSteps(n - step, memo, possibleSteps);
  }

  return memo[n];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, k;
  std::cin >> n >> k;
  std::vector<int> memo(n + 1, 0);

  std::cout << calculateSteps(n, memo, k); 
  return 0;
}
