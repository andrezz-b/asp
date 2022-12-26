#include <bits/stdc++.h>

using namespace std;

#define MAXN 101

std::string mapa[MAXN];
bool bio[MAXN][MAXN] = {};

int dx[] = {1,  0, -1, 0};
int dy[] = {0, -1,  0, 1};

void markBio(std::pair<int, int> location) {
  bio[location.first][location.second] = true;
}

void markBio(int i, int j) {
  bio[i][j] = true;
}

bool isOutOfBounds(int i, int j, int n, int m) {
  return i < 0 || i >= n || j < 0 || j >= m;
}

void findFinish(const std::pair<int, int> &start, int &ans_udaljenost, const int &n, const int &m) {
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
      if (mapa[I][J] == 'F') {
        ans_udaljenost = dist + 1;
        return;
      }

      markBio(I, J);
      q.push({{I, J}, dist + 1});
    }
  }
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
  findFinish(start, ans_udaljenost, n, m);

  std::cout << ans_udaljenost << "\n";


  return 0;
}