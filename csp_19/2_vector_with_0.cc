#include <iostream>
#include <valarray>

int main(int argc, char const *argv[]) {
  unsigned long dimension;
  unsigned long firstInputTimes, secondInputTimes;
  std::cin >> dimension >> firstInputTimes >> secondInputTimes;
  long long *arr1 = new long long[dimension]();
  long long *arr2 = new long long[dimension]();

  for (unsigned long i = 0; i < firstInputTimes; i++) {
    unsigned long index;
    long long value;
    std::cin >> index >> value;
    arr1[index - 1] = value;
  }

  for (unsigned long i = 0; i < secondInputTimes; i++) {
    unsigned long index;
    long long value;
    std::cin >> index >> value;
    arr2[index - 1] = value;
  }

  long long sum = 0;
  for (unsigned long i = 0; i < dimension; i++) {
    sum += arr1[i] * arr2[i];
  }

  std::cout << sum;
  return 0;
}