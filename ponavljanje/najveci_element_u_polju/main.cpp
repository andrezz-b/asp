#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
  
//implementacija funkcije
float max(std::vector<float>& p) {
  float max = 0;

  for (float &num : p) {
    max = std::max(num, max);
  }
  return max;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
     
  std::vector<float> p;
  //pokazivac na polje
  for (int i = 0; i < 10; i++) {
    //unos pomocu pokazivac
    float val;
    std::cin >> val;
    p.push_back(val);
  }


    
  //ispisati
  std::cout << "Najveci broj niza je: " << std::fixed << std::setprecision(2) << max(p) ;

  return 0;
}