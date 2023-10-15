#include <iostream>
#include <set>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::multiset<int> set{2, 7, 9, 5, 5, 5, 5, 4, 4, 4, 4,
                         4, 4, 4, 4, 4, 4, 4, 4, 5, 1, 3};
  for (auto it = set.begin(); it != set.end(); it++) {
    if (*it == 5 || *it == 4) {
      set.erase(it--);
    }
    cout << *it << ' ';
  }
  return 0;
}