#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define MAXNM 100
#define vec vector<pair<int, int>>

int dp[MAXNM][MAXNM] = {{ 0 }};
vec path;

void find_max_profit(int n, int m, int coins[][MAXNM]) {
  if (n <= 0 || m <= 0) return;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {

      dp[i][j] = coins[i][j];

      if (i > 0 && j > 0) {
        dp[i][j] += std::max(dp[i][j - 1], dp[i - 1][j]);
      } else if (i > 0) {
        dp[i][j] += dp[i - 1][j];
      } else if (j > 0) {
        dp[i][j] += dp[i][j - 1];
      }
    }
  }

  std::cout << dp[n - 1][m - 1] << "\n";
}

void reconstruct_best_path(int i, int j) {

  if (i == 0 && j == 0) {

    path.push_back(make_pair(i, j));
    return;

  } else if (i == 0) {

    reconstruct_best_path(i, j - 1);

  } else if (j == 0) {

    reconstruct_best_path(i - 1, j);

  } else {

    if (dp[i - 1][j] >= dp[i][j - 1])

      reconstruct_best_path(i - 1, j);

    else

      reconstruct_best_path(i, j - 1);
  }

  path.push_back(make_pair(i, j));
  return;
}

void print_best_path(int n, int m) {

  if (n <= 0 || m <= 0) return;

  reconstruct_best_path(n - 1, m - 1);

  for (int i = 0; i < (int)path.size(); ++i) {

    cout << "{" << path[i].first << "," << path[i].second << "}" << " ";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  int coins[MAXNM][MAXNM];

  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> coins[i][j];
    }
  }

  find_max_profit(n, m, coins);
  print_best_path(n, m);
  return 0;
}
