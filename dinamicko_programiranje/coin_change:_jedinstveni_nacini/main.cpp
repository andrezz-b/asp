#include <iostream>
#include <vector>
#define MAX_L 100

using namespace std;


// Index - pokazuje koje su name sve denominacije dostupne
int calculate_ways(int value, int length, int index, int denominations[], std::vector<std::vector<int>> &memo) {

  if (value == 0) return 1;
  if (value < 0) return 0;
  if (memo[value][index] != 0) return memo[value][index];
  if (index >= length) return 0;

  // Koristimo denominaciju na indexu -> umanjujemo vrijednost index ostaje isti
  int useTheCoinAtIndex = calculate_ways(value - denominations[index], length, index, denominations, memo);

  // Preskačemo denominaciju na indexu -> ne umanjujemo vrijednost, ali taj novcic vise ne koristimo
  int dontUseTheCoinAtIndex = calculate_ways(value, length, index + 1, denominations, memo);  

  memo[value][index] = useTheCoinAtIndex + dontUseTheCoinAtIndex;

  return memo[value][index];
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, length;

  cin >> n >> length;

  int denominations[length];
  std::vector<std::vector<int>> memo(n + 1, std::vector<int>(length + 1, 0));


  for (int i = 0; i < length; ++i) {
    cin >> denominations[i];
  }

  cout << calculate_ways(n, length, 0, denominations, memo);


  return 0;
}