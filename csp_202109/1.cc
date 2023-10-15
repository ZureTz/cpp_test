#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;

  int sumMax(0), sumMin(0), prev, now;
  cin >> prev;
  if (n == 1) {
    cout << prev << '\n' << prev;
    return 0;
  }

  sumMax += prev;
  sumMin += prev;
  for (int i = 1; i < n; i++, prev = now) {
    cin >> now;
    sumMax += now;
    if (now == prev) {
      continue;
    }
    sumMin += now;
  }

  cout << sumMax << '\n' << sumMin;
  return 0;
}