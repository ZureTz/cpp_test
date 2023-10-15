#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nPerson, kMaxTime, tTimeAts;
  cin >> nPerson >> kMaxTime >> tTimeAts;
  std::pair<int, int> leftDown, rightUp;
  cin >> leftDown.first >> leftDown.second;
  cin >> rightUp.first >> rightUp.second;

  std::vector<std::vector<std::pair<int, int>>> civilians;
  civilians.resize(nPerson);
  for (auto &civilian : civilians) {
    civilian.resize(tTimeAts);
    for (auto &pair : civilian) {
      cin >> pair.first >> pair.second;
    }
  }

  auto inArea = [leftDown, rightUp](const std::pair<int, int> &pair) {
    return (leftDown.first <= pair.first && pair.first <= rightUp.first) &&
           (leftDown.second <= pair.second && pair.second <= rightUp.second);
  };

  int peoplePassAreaCount(0), peopleStayedForAWhileInAreaCount(0);
  for (const auto &civilian : civilians) {
    bool isIn = false, isContinious = false;
    if (inArea(civilian.front())) {
      isIn = true;
    }

    auto it = civilian.begin();
    while (it != civilian.end()) {
      if (inArea(*it)) {
        isIn = true;
        auto temp = it;

        while ((temp < civilian.end()) && inArea(*temp)) {
          ++temp;
        }
        if (std::distance(it, temp) >= kMaxTime) {
          isContinious = true;
          break;
        }

        it = temp;
        continue;
      }

      ++it;
    }

    peoplePassAreaCount += isIn ? 1 : 0;
    peopleStayedForAWhileInAreaCount += isContinious ? 1 : 0;
  }

  cout << peoplePassAreaCount << std::endl
       << peopleStayedForAWhileInAreaCount << std::endl;
  return 0;
}