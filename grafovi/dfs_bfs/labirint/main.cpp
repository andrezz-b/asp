#include <bits/stdc++.h>

std::pair<int, int> moves[4] = {{1, 0}, {0, -1}, { -1, 0}, {0, 1}};

bool isOutOfBounds(int i, int j, int n, int m) {
  return i < 0 || i >= n || j < 0 || j >= m;
}

bool bfs(std::vector<std::string> &matrix, int n, int m,
         std::pair<int, int> &S, std::pair<int, int> &F) {

  std::queue<std::pair<int, int>> q;
  std::vector<std::vector<bool>> visited(n + 1, std::vector<bool>(m + 1, false));
  q.push(S);
  visited[S.first][S.second] = true;

  while (!q.empty()) {
    std::pair<int, int> current = q.front();
    q.pop();

    if (current == F) return true;

    for(auto const &move : moves) {
      int i = current.first + move.first;
      int j = current.second + move.second;

      if (isOutOfBounds(i, j, n, m)) continue;
      if (visited[i][j]) continue;
      if (matrix[i][j] == '#') continue;

      q.push({i, j});
      visited[i][j] = true;
    }
  }

  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::pair<int, int> start, finish;

  std::vector<std::string> matrix(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> matrix[i];

    std::size_t startIndex = matrix[i].find('S');
    std::size_t finishIndex = matrix[i].find('F');

    if (startIndex != std::string::npos) start = {i, startIndex};
    if (finishIndex != std::string::npos) finish = {i, finishIndex};
  }

  std::cout << (bfs(matrix, n, m, start, finish) ? "Y" : "N");


  return 0;
}
