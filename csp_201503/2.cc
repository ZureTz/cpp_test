#include <functional>
#include <iostream>
#include <map>
#include <utility>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;
  std::map<int, int> map;
  for (int i = 0; i < n; i++) {
    int tempNum;
    cin >> tempNum;
    auto it = map.find(tempNum);
    if (it == map.end()) {
      map.insert({tempNum, 1});
      continue;
    }
    (it->second)++;
  }

  std::multimap<int, int, std::greater<int>> multimap;
  for (auto const pair : map) {
    multimap.insert({pair.second, pair.first});
  }

  for (auto const &pair : multimap) {
    cout << pair.second << ' ' << pair.first << std::endl;
  }

  return 0;
}