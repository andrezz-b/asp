#include <bits/stdc++.h>

using namespace std;

#define MAXN 100

int dx[8] = {1,  1,  0, -1, -1, -1,  0,  1};
int dy[8] = {0, -1, -1, -1,  0,  1,  1,  1};

bool isOutOfBounds(int i, int j, int n, int m) {
  return i < 0 || i >= n || j < 0 || j >= m;
}

void dfs(int i, int j, int n, int m, string matrix[MAXN],
         std::vector<std::vector<bool>> &visited) {
  if (visited[i][j] || matrix[i][j] != '#') return;

  visited[i][j] = true;

  for (int di = 0; di < 8; ++di) {
    int rowMoved = i + dx[di];
    int columnMoved = j + dy[di];

    if (isOutOfBounds(rowMoved, columnMoved, n, m)) continue;
    if (matrix[rowMoved][columnMoved] != '#') continue;
    if (visited[rowMoved][columnMoved]) continue;

    dfs(rowMoved, columnMoved, n, m, matrix, visited);

  }

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;
  std::string matrix[MAXN];

  for (int i = 0; i < n; ++i) {
    std::cin >> matrix[i];
  }

  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
  int islands = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (matrix[i][j] != '#' || visited[i][j]) continue;
      islands += 1;
      dfs(i, j, n, m, matrix, visited);
    }
  }

  std::cout << islands << "\n";
  return 0;
}
