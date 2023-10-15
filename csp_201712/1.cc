#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;
  std::vector<int> arr(n);
  for (int &num : arr) {
    cin >> num;
  }
  std::sort(arr.begin(), arr.end(), [](int a, int b) { return a < b; });

  int min = INT_MAX;
  for (std::vector<int>::const_iterator it = arr.begin() + 1; it != arr.end();
       it++) {
    min = std::min(min, it[0] - it[-1]);
  }

  cout << min;
  return 0;
}