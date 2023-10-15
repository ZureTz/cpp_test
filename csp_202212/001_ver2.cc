#include <cmath>
#include <iostream>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  int years;
  double interest;
  cin >> years >> interest;
  interest += 1.0;

  double totalProfit;
  for (int i = 0; i < years + 1; i++) {
    int currentProfit;
    cin >> currentProfit;
    totalProfit += currentProfit * pow(interest, -i);
  }

  cout << totalProfit;
  return 0;
}