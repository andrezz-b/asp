#include <iostream>
#include <iomanip>
using namespace std;


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  do {
    cin >> n;
  } while (n < 1);

  float *p = (float *) malloc(n * sizeof(float));

  for (int i = 0; i < n; ++i) {
    cin >> p[i];
    cout << (i + 1) << ". broj je " << fixed << setprecision(2) << p[i] << endl;
  }

  free(p);

  return 0;
}
