#include <iostream>
#include <vector>

// https://www.youtube.com/watch?v=cjWnW0hdF1Y&list=PLot-Xpze53lcvx_tjrr_m2lgD2NsRHlNO&index=13
int longestSubsequence(int n, std::vector<int> &nums) {
  std::vector<int> list(n, 1);

  int maxLen = 0;

  for (int i = n - 2; i >= 0; --i) {
    for (int j = i; j < n; ++j) {
      if (nums[i] < nums[j]) {
        list[i] = std::max(list[i], 1 + list[j]);
      }
    }
    maxLen = std::max(maxLen, list[i]);
  }

  return maxLen;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;
  std::vector<int> nums;

  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    nums.push_back(x);
  }

  std::cout <<(n ? longestSubsequence(n, nums) : 0);

  return 0;
}