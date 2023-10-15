#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;

struct Map {
  std::vector<std::string> map;
  int count;

  Map() : count(1) {
    map.resize(8);
    for (auto &str : map) {
      std::getline(cin, str);
    }
  }

  bool operator==(const Map &rhs) const {
    for (int i = 0; i < 8; i++) {
      if (map[i] != rhs.map[i]) {
        return false;
      }
    }
    return true;
  }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nMaps;
  (cin >> nMaps).get(); // 错误原因:少了个get!
  std::vector<Map> maps(nMaps);

  if (nMaps == 1) {
    cout << 1 << std::endl;
    return 0;
  }

  for (int i = 1; i < nMaps; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (maps[j] == maps[i]) {
        maps[i].count += maps[j].count;
        break;
      }
    }
  }

  for (const auto &map : maps) {
    cout << map.count << std::endl;
  }

  return 0;
}