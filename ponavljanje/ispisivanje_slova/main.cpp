#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);


  for (int i = (int) 'a'; i <= (int) 'z'; ++i) {
    cout << (char) i;
  }

  for (int i = (int) 'A'; i <= (int) 'Z'; ++i) {
    cout << (char) i;
  }

  return 0;
}