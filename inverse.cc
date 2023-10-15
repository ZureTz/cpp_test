#include <algorithm>
#include <iostream>
#include <type_traits>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  constexpr int length = 17;

  int num[length];
  for (int i = 0; i < length; i++) {
    num[i] = i;
  }

  auto front = num, back = num + length - 1;
  while (front < back) {
    cout << *front << ' ' << *back << std::endl;
    std::swap(*front, *back);
    ++front;
    --back;
  }

  for (int i = 0; i < length; i++) {
    cout << num[i] << ' ';
  }

  return 0;
}