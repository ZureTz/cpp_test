#include <cstdarg>
#include <cstddef>
#include <iostream>

template <typename T> void printSum(size_t argCount, ...) {
  va_list args;
  va_start(args, argCount);

  T sum = 0;
  for (size_t i = 0; i < argCount; ++i) {
    sum += va_arg(args, T);
  }
  
  va_end(args);
}

int main(int argc, char const *argv[]) {
  printSum<double>(5, 2.5, 5.7, 114.15, -225.12, 55.3);
  printSum<int>(5, 2, 57, 11415, -22512, 553);
  return 0;
}