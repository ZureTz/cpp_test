#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  std::ofstream fibo;
  fibo.open("fibo.hpp", std::ios::out | std::ios::trunc);
  fibo << "static constexpr long long fiboList[] = { " << std::endl;

  std::vector<long long> list(93);
  list.at(0) = 0;
  list.at(1) = 1;
  for (int i = 2; i < 93; i++) {
    list.at(i) = list.at(i - 1) + list.at(i - 2);
  }

  for (const long long num : list) {
    fibo << '\t' << num << ", " << std::endl;
  }
  fibo << "};";
  fibo.close();

  return 0;
}