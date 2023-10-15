#include <iostream>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  int nums;
  cin >> nums;

  int count(0);
  for (int i = 0, now = -1, prev = -1; i < nums; i++) {
    prev = now;
    cin >> now;
    if (prev != now) {
      count++;
    }
  }
  cout << count;

  return 0;
}