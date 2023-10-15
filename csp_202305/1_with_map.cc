#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nTables;
  (cin >> nTables).get();
  std::unordered_map<std::string, int> tableMap;
  for (int i = 0; i < nTables; i++) {
    std::string tempMap;
    for (int j = 0; j < 8; j++) {
      std::string tempStr;
      std::getline(cin, tempStr);
      tempMap.append(tempStr);
    }
    auto it = tableMap.find(tempMap);
    // if not found:
    if (it == tableMap.end()) {
      tableMap.insert(std::make_pair(tempMap, 1));
      cout << tableMap[tempMap] << std::endl;
      continue;
    }
    // otherwise: found (it != tableMap.end)
    cout << ++(it->second) << std::endl;
  }

  return 0;
}