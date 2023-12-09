#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // 输入人数，逗留的最长时间，以及每个人的数据量
  int nPerson, kMaxTime, tTimeAts;
  cin >> nPerson >> kMaxTime >> tTimeAts;

  // 输入风险区域的左下和右上的坐标
  std::pair<int, int> leftDown, rightUp;
  cin >> leftDown.first >> leftDown.second;
  cin >> rightUp.first >> rightUp.second;

  // 输入每个人，以及每个人相应的地理数据
  std::vector<std::vector<std::pair<int, int>>> civilians;
  civilians.resize(nPerson);
  for (auto &civilian : civilians) {
    civilian.resize(tTimeAts);
    for (auto &pair : civilian) {
      cin >> pair.first >> pair.second;
    }
  }

  // 判断当前坐标是否在风险区域内
  auto inArea = [leftDown, rightUp](const std::pair<int, int> &pair) {
    return (leftDown.first <= pair.first && pair.first <= rightUp.first) &&
           (leftDown.second <= pair.second && pair.second <= rightUp.second);
  };

  // 初始化计数：
  int peoplePassAreaCount(0), peopleStayedForAWhileInAreaCount(0);

  // 对于每个居民：
  for (const auto &civilian : civilians) {
    // 分别判断是否经过以及是否逗留超过最低风险时长
    bool isIn = false, isContinious = false;
    // 判断第一个数据是否在风险区域内
    if (inArea(civilian.front())) {
      isIn = true;
    }

    // 对于该居民的每一个数据：
    auto it = civilian.begin();
    while (it != civilian.end()) {
      // 如果经过风险区：判断经过的时长
      if (inArea(*it)) {
        isIn = true;
        auto temp = it;

        while ((temp < civilian.end()) && inArea(*temp)) {
          ++temp;
        }
        // 满足最短时长，则加入风险名单
        if (std::distance(it, temp) >= kMaxTime) {
          isContinious = true;
          break;
        }

        it = temp;
        continue;
      }

      ++it;
    }

    // 分别增加计数
    peoplePassAreaCount += isIn ? 1 : 0;
    peopleStayedForAWhileInAreaCount += isContinious ? 1 : 0;
  }

  // 最后输出即可
  cout << peoplePassAreaCount << std::endl
       << peopleStayedForAWhileInAreaCount << std::endl;
  return 0;
}