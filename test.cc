#include <iostream>
#include <sys/_types/_size_t.h>
#include <unordered_map>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t n;
  cin >> n;
  for (size_t i = 0; i < n; ++i) {
    std::unordered_map<char, int> map;
    for (size_t j = 0; j < 4; j++) {
      char temp;
      cin >> temp;
      if (map.find(temp) == map.end()) {
        map[temp] = 1;
        continue;
      }
      map[temp]++;
    }

    auto isMatch = [&]() -> bool {
      for (const auto &pair : map) {
        if (pair.second == 3) {
          return true;
        }
      }
      return false;
    };

    cout << (isMatch() ? "Yes" : "No") << std::endl;
  }
  return 0;
}