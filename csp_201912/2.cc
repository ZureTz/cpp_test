#include <iostream>
#include <unordered_map>
#include <utility>
using std::cin;
using std::cout;

struct keyHasher {
  std::size_t operator()(const std::pair<int, int> &op) const {
    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:
    return std::hash<int>()(op.first) ^ (std::hash<int>()(op.second) << 1);
  }
};

bool isSatisfied(
    std::pair<int, int> pair,
    const std::unordered_map<std::pair<int, int>, bool, keyHasher> &map) {
  if (map.find({pair.first + 1, pair.second}) == map.end()) {
    return false;
  }
  if (map.find({pair.first - 1, pair.second}) == map.end()) {
    return false;
  }
  if (map.find({pair.first, pair.second + 1}) == map.end()) {
    return false;
  }
  if (map.find({pair.first, pair.second - 1}) == map.end()) {
    return false;
  }
  return true;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;
  std::unordered_map<std::pair<int, int>, bool, keyHasher> map;
  map.reserve(n);
  int countOfSatisfiedStations[5]{0, 0, 0, 0, 0};
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    map.insert({{x, y}, true});
  }

  for (const auto &pair : map) {
    if (!isSatisfied(pair.first, map)) {
      continue;
    }

    int count = 0;
    if (map.find({pair.first.first + 1, pair.first.second + 1}) != map.end()) {
      count++;
    }
    if (map.find({pair.first.first - 1, pair.first.second - 1}) != map.end()) {
      count++;
    }
    if (map.find({pair.first.first + 1, pair.first.second - 1}) != map.end()) {
      count++;
    }
    if (map.find({pair.first.first - 1, pair.first.second + 1}) != map.end()) {
      count++;
    }
    countOfSatisfiedStations[count]++;
  }

  for (const int num : countOfSatisfiedStations) {
    cout << num << std::endl;
  }

  return 0;
}

// #include <iostream>
// #include <vector>

// using namespace std;

// // 定义结构体表示垃圾的坐标
// struct Coordinate {

//   int x; // x坐标
//   int y; // y坐标

//   // 构造函数
//   Coordinate(int _x, int _y) : x(_x), y(_y) {}
// };

// // 检查给定坐标是否有垃圾
// bool hasGarbage(int x, int y,
//                 const vector<Coordinate> &garbage) { // 循环遍历所有垃圾点
//   for (const auto &point : garbage) {
//     if (point.x == x && point.y == y)
//       return true; // 如果找到匹配的垃圾点，返回true
//   }
//   return false; // 如果循环结束都没找到匹配的垃圾点，返回false
// }

// // 计算不同分数的合适地址的数量
// // 参数: garbage - 垃圾坐标的vector
// void countAddresses(const vector<Coordinate> &garbage) {
//   int count[] = {0, 0, 0, 0, 0};

//   // 遍历每个垃圾点
//   for (const auto &point : garbage) {
//     int x = point.x;
//     int y = point.y;

//     // 检查上下左右的位置是否有垃圾
//     if (!hasGarbage(x, y + 1, garbage))
//       continue; // 如果上方没有垃圾，跳过当前垃圾点，进入下一次循环
//     if (!hasGarbage(x, y - 1, garbage))
//       continue; // 如果下方没有垃圾，跳过当前垃圾点，进入下一次循环
//     if (!hasGarbage(x + 1, y, garbage))
//       continue; // 如果右侧没有垃圾，跳过当前垃圾点，进入下一次循环
//     if (!hasGarbage(x - 1, y, garbage))
//       continue; // 如果左侧没有垃圾，跳过当前垃圾点，进入下一次循环

//     int score = 0; // 检查斜对角位置是否有垃圾
//     if (hasGarbage(x + 1, y + 1, garbage))
//       score++; // 如果右上方存在垃圾，则分数加1
//     if (hasGarbage(x + 1, y - 1, garbage))
//       score++; // 如果右下方存在垃圾，则分数加1
//     if (hasGarbage(x - 1, y + 1, garbage))
//       score++; // 如果左上方存在垃圾，则分数加1
//     if (hasGarbage(x - 1, y - 1, garbage))
//       score++; // 如果左下方存在垃圾，则分数加1

//     count[score]++; // 增加对应分数的数量
//   }

//   for (int i = 0; i <= 4; i++) {
//     cout << count[i] << endl;
//   }
// }

// int main() {

//   int n;
//   cin >> n;
//   vector<Coordinate> garbage;

//   // 输入垃圾的坐标
//   for (int i = 0; i < n; i++) {
//     int x, y;
//     cin >> x >> y;
//     garbage.emplace_back(x, y); // 添加垃圾点到vector中
//   }
//   countAddresses(garbage);
//   return 0;
// }