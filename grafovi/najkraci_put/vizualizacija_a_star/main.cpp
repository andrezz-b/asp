#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <cmath>

using namespace std;

#define MAXN 101
#define EDGE_WEIGHT 1

const float INF = 0x7f7f7f7f; // Different "INF" for int and float
// Pomaci
const std::pair<int, int> dM[4] = { {1, 0}, {0, -1}, { -1, 0}, {0, 1} };

bool isOutOfBounds(const int &row, const int &column, const int &rowSize, const int &columnSize) {
  return (row < 0 || row >= rowSize || column < 0 || column >= columnSize);
}

float h_func(pair<int, int> C, pair<int, int> F) {
  return sqrt(pow(F.first - C.first, 2) + pow(F.second - C.second, 2));
  // return fabs(F.first - C.first) + fabs(F.second - C.second);
}

void a_star(char matrix[MAXN][MAXN],
            std::vector<std::vector<std::pair<int, int>>> &previous,
            int n, int m, std::pair<int, int> start, std::pair<int, int> finish) {

  // spremamo {heuristička udaljenost, {poz_x, poz_y}}
  std::priority_queue<std::pair<float, std::pair<int, int>>,
      std::vector<std::pair<float, std::pair<int, int>>>,
      std::greater<std::pair<float, std::pair<int, int>>>> pq;

  // spremamo heurističke udaljenosti npr. najmanja heur udalj za točku (3, 1) je 5.23
  // minDistanceHeuristic[3][1] = 5.23
  std::vector<std::vector<float>> minDistanceHeuristic(n + 1, std::vector<float>(m + 1, INF));
  minDistanceHeuristic[start.first][start.second] = 0;

  // previous sprema prethodni čvor npr. prethodni od (5, 2) jer (4, 2)
  // previous[5][2] = {4, 2}
  previous[start.first][start.second];
  pq.push({0, start});

  while (!pq.empty()) {
    std::pair<int, int> currentVertex;
    float heuristicDistanceToCurrent;

    tie(heuristicDistanceToCurrent, currentVertex) = pq.top();
    pq.pop();

    if (currentVertex == finish) return;
    if (minDistanceHeuristic[currentVertex.first][currentVertex.second] < heuristicDistanceToCurrent) continue;

    // Prolazimo sve smjerove kretanja
    for (int i = 0; i < 4; ++i) {
      int rowMoved = currentVertex.first + dM[i].first;
      int columnMoved = currentVertex.second + dM[i].second;

      // Ako smo izvan granica matrice preskačemo
      if (isOutOfBounds(rowMoved, columnMoved, n, m)) continue;

      // Kako je ovo matrica, težinska udaljenost do trenutnog vrha
      // je udaljenost od starta do trenutnog (ali ne smijemo ići u koso nego gore, dolje, lijevo, desno)
      int minWeightedDistanceToCurrent = abs(start.first - currentVertex.first) + abs(start.second - currentVertex.second);
      float f_func = minWeightedDistanceToCurrent + EDGE_WEIGHT + h_func({rowMoved, columnMoved}, finish);

      if (f_func < minDistanceHeuristic[rowMoved][columnMoved]) {
        minDistanceHeuristic[rowMoved][columnMoved] = f_func;
        previous[rowMoved][columnMoved] = currentVertex;
        pq.push({f_func, {rowMoved, columnMoved}});
      }

    }
  }

}

void ispisi_put(pair<int, int> S, pair <int, int> F, vector<vector<pair<int, int>>> previous) {
  if (S == F) {
    cout << F.first << " " << F.second << " " << endl;
    return;
  }
  ispisi_put(S, previous[F.first][F.second], previous);
  cout << F.first << " " << F.second << " " << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  char matrix[MAXN][MAXN];
  pair<int, int> S;
  pair<int, int> F;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> matrix[i][j];
      if (matrix[i][j] == 'S') {
        S = {i, j};
      } else if (matrix[i][j] == 'F') {
        F = {i, j};
      }
    }
  }

  std::vector<std::vector<std::pair<int, int>>> previous(n + 1, std::vector<std::pair<int, int>>(m + 1, { -1, -1}));

  a_star(matrix, previous, n, m, S, F);

  //vizualizirani ispis
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (matrix[i][j] != '.') {
        cout << matrix[i][j];
      } else if (previous[i][j] == make_pair(-1, -1)) {
        cout << "0";
      } else {
        cout << "1";
      }
      cout << " ";
    }
    cout << "\n";
  }


  cout << "\nIspis puta od ishodišta do cilja: \n";
  ispisi_put(S, F, previous);

  return 0;
}