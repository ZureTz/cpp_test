#include <iostream>
#include <valarray>

int main(int argc, char const *argv[]) {
  int dimension;
  unsigned firstInputTimes, secondInputTimes;
  std::cin >> dimension >> firstInputTimes >> secondInputTimes;
  std::valarray<int> arr1(0, dimension), arr2(0, dimension);

  for (int i = 0; i < firstInputTimes; i++) {
    int index, value;
    std::cin >> index >> value;
    arr1[index - 1] = value;
  }

  for (int i = 0; i < secondInputTimes; i++) {
    int index, value;
    std::cin >> index >> value;
    arr2[index - 1] = value;
  }

  int sum = 0;
  for (int i = 0; i < dimension; i++) {
    sum += arr1[i] * arr2[i];
  }

  std::cout << sum;
  return 0;
}