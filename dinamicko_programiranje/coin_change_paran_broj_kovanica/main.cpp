#include <iostream>
#include <vector>
#define MAX_L 100

using namespace std;

int calculate_ways(int n, int even, int size,  int denominations[]) {

  vector<vector<int>> ways(n + 1, vector<int>(2));
  ways[0][0] = 0;
  ways[0][1] = 1;

  for (int i = 1; i < n + 1; ++i) {

    for (int j = 0; j < 2; ++j) {


      // Prolazi korz sve denominacije novaca
      for (int k = 0; k < size; ++k) {
        if (i - denominations[k] < 0) continue;
        if ((i - denominations[k]) >= 0) {
          ways[i][j] += ways[i - denominations[k]][1 - j];
        }
        printf("\ni: %d, j: %d k: %d\n", i, j, i - denominations[k]);

        for (auto row : ways) {
          for (auto el : row) {
            printf("%d ", el);
          }
          printf("\n");
        }
      }
    }
  }



  return ways[n][even];
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, length;
  int denominations[MAX_L];

  cin >> n >> length;

  for (int i = 0; i < length; ++i)
    cin >> denominations[i];

  cout << calculate_ways(n, 1, length, denominations);

  //ako na mjesto drugog argumenta proslijedimo 0,
  //dobit ćemo rješenje zadatka za neparan broj kovanica

  return 0;
}