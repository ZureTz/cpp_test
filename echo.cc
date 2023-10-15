#include <iostream>

int main(int argc, char const *argv[]) {
  for (int i = 1; i < argc - 1; i++) {
    std::cout << argv[i] << ' ';
  }
  std::cout << argv[argc - 1];
  return 0;
}