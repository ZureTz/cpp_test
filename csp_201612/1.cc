#include <functional>
#include <iostream>
#include <iterator>
#include <set>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;
  std::multiset<int, std::greater<int>> set;
  {
    int temp;
    for (int i = 0; i < n; i++) {
      cin >> temp;
      set.insert(temp);
    }
  }

  for (const auto &num : set) {
    if (std::distance(set.begin(), set.lower_bound(num)) ==
        std::distance(set.upper_bound(num), set.end())) {
      cout << num;
      return 0;
    }
  }
  cout << -1;
  return 0;
}