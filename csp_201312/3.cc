#include <algorithm>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // input
  int n;
  cin >> n;
  std::vector<int> arr(n + 2, 0);
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }

  // iterate and expansion
  int maxArea = 0;
  for (auto it = arr.begin() + 1; it + 1 != arr.end(); it++) {
    auto backIt = it, forwardIt = it;

    while (*backIt >= *it) {
      backIt--;
    }

    while (*forwardIt >= *it) {
      forwardIt++;
    }
    maxArea = std::max(maxArea, *it * (int(forwardIt - backIt) - 1));
  }

  cout << maxArea;

  return 0;
}