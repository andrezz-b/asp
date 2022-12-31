#include <bits/stdc++.h>

using namespace std;
const int INF = 0x3f3f3f3f;

#define MAXN 101

std::string mapa[MAXN];
bool bio[MAXN][MAXN] = {};

int dx[] = {1,  0, -1, 0};
int dy[] = {0, -1,  0, 1};

void markBio(int i, int j) {
  bio[i][j] = true;
}

void markBio(std::pair<int, int> location) {
  markBio(location.first, location.second);
}

bool isOutOfBounds(int i, int j, int n, int m) {
  return i < 0 || i >= n || j < 0 || j >= m;
}

int findFinish(const std::pair<int, int> &start, const int &n, const int &m) {
  std::queue<std::pair<std::pair<int, int>, int>> q;
  markBio(start);
  q.push({start, 0});

  while (!q.empty()) {
    int dist;
    std::pair<int, int> poz;
    tie(poz, dist) = q.front();
    q.pop();

    for (int di = 0; di < 4; ++di) {

      int I = poz.first + dx[di];
      int J = poz.second + dy[di];

      if (isOutOfBounds(I, J, n, m)) continue;
      if (mapa[I][J] == '#') continue;
      if (bio[I][J]) continue;
      if (mapa[I][J] == 'F') return dist + 1;

      markBio(I, J);
      q.push({{I, J}, dist + 1});
    }
  }
  return 0;
}

int findFinishDijkstra(const std::pair<int, int> &start, const int &n, const int &m) {
  std::priority_queue<std::pair<int, std::pair<int, int>>,
      std::vector<std::pair<int, std::pair<int, int>>>,
      std::greater<std::pair<int, std::pair<int, int>>>> pq;

  std::vector<std::vector<int>> minDistance(n + 1, std::vector<int>(m + 1, INF));

  minDistance[start.first][start.second] = 0;
  pq.push({0, start});

  while (!pq.empty()) {
    int distance;
    std::pair<int, int> position;

    tie(distance, position) = pq.top();
    pq.pop();

    markBio(position);
    if (minDistance[position.first][position.second] < distance) continue;

    for (int di = 0; di < 4; ++di) {
      int rowMoved = position.first + dx[di];
      int columnMoved = position.second + dy[di];

      if (isOutOfBounds(rowMoved, columnMoved, n, m)) continue;
      if (bio[rowMoved][columnMoved]) continue;
      if (mapa[rowMoved][columnMoved] == '#') continue;
      if (mapa[rowMoved][columnMoved] == 'F') return distance + 1;


      if (minDistance[position.first][position.second] + 1 < minDistance[rowMoved][columnMoved]) {
        minDistance[rowMoved][columnMoved] = minDistance[position.first][position.second] + 1;
        pq.push({minDistance[rowMoved][columnMoved], {rowMoved, columnMoved}});
      }
    }
  }

  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  int ans_udaljenost = 0;
  std::pair<int, int> start;


  std::cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    std::cin >> mapa[i];

    for (int j = 0; j < m; ++j) {
      if (mapa[i][j] == 'S') {
        // postavljanje para
        start = {i, j};
      }
    }
  }

  // pozicije definiramo {{i, j}, dist} par između parova pozicija i udaljenosti
  ans_udaljenost = findFinishDijkstra(start, n, m);

  std::cout << ans_udaljenost << "\n";


  return 0;
}