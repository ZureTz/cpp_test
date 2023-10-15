#include <iostream>
int main(int argc, char const *argv[]){
  int iterations;
  double interest;

  double summary(0);
  std::cin >> iterations >> interest;
  interest += 1.0;

  for (int i = 0; i <= iterations; i++) {
    double temp_money;
    std::cin >> temp_money;
    for (int j = 0; j < i; j++) {
      temp_money /= interest;
    }
    summary += temp_money;
  }
  std::cout << summary;

  return 0;
}