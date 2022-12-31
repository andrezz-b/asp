#include <bits/stdc++.h>

#define MAXN 101

//pomaci u susjeda

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

const int INF = 0x3f3f3f3f;

bool isOutOfBounds(const int &row, const int &column, const int &rowSize, const int &columnSize) {
  return (row < 0 || row >= rowSize || column < 0 || column >= columnSize);
}

bool isOutOfBounds(const std::pair<int, int> &position, const int &rowSize, const int &columnSize) {
  return isOutOfBounds(position.first, position.second, rowSize, columnSize);
}

void markVisited(int i, int j, bool posjeceni[MAXN][MAXN]) {
  posjeceni[i][j] = true;
}

void markVisited(std::pair<int, int> position, bool posjeceni[MAXN][MAXN]) {
  markVisited(position.first, position.second, posjeceni);
}

void ispisi_put_prolaska(bool posjeceni[MAXN][MAXN], int n, int m) {
  std::cout << "\n\n";
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (posjeceni[i][j]) {
        std::cout << "1 ";

      } else {
        std::cout << "0 ";
      }
    }
    std::cout << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  //koristit cemo BFs, znaci trebamo neki red i provjeru po susjedima
  int n, m;
  //visina i sirina mape
  std::cin >> n >> m;

  std::string mapa[MAXN];
  std::pair <int, int> start;
  bool posjeceni[MAXN][MAXN] = {{0}};
  int broj_k = 0;

  for (int i = 0; i < n; ++i)
  {
    std::cin >> mapa[i];
    for (int j = 0; j < m; ++j)
    {
      if (mapa[i][j] == 'S') {
        start = {i, j};
      }
    }
  }
  std::priority_queue<std::pair<int, std::pair<int, int>>,
      std::vector<std::pair<int, std::pair<int, int>>>,
      std::greater<std::pair<int, std::pair<int, int>>>
      > pq;

  pq.push({0, start});

  // svaki redak je vector koji inicijaliziramo na INF
  std::vector<std::vector<int>> minDistance(n + 1, std::vector<int>(m + 1, INF));
  minDistance[start.first][start.second] = 0;

  while (!pq.empty()) {
    int distance;
    std::pair<int, int> position;

    tie(distance, position) = pq.top();
    pq.pop();
    broj_k++;

    markVisited(position, posjeceni);

    if (mapa[position.first][position.second] == 'F') break;

    if (minDistance[position.first][position.second] < distance) continue;

    //iterirati po susjedima
    for (int di = 3; di >= 0; --di) {

      int rowMoved = position.first + dx[di];
      int columnMoved = position.second + dy[di];

      if (isOutOfBounds(rowMoved, columnMoved, n, m)) continue;
      if (posjeceni[rowMoved][columnMoved]) continue;

      if (minDistance[position.first][position.second] + 1 < minDistance[rowMoved][columnMoved]) {
        minDistance[rowMoved][columnMoved] = minDistance[position.first][position.second] + 1;
        pq.push({minDistance[rowMoved][columnMoved], {rowMoved, columnMoved}});
      }
    }

  }

  ispisi_put_prolaska(posjeceni, n, m);

  std::cout << broj_k << "\n";

  return 0;
}