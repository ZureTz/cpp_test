#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using std::cin;
using std::cout;

inline int distanceSquareSum(const std::pair<int, int> &point1,
                             const std::pair<int, int> &point2) {
  return ((point1.first - point2.first) * (point1.first - point2.first)) +
         ((point1.second - point2.second) * (point1.second - point2.second));
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  std::pair<int, int> residentPos;
  cin >> n >> residentPos.first >> residentPos.second;

  std::vector<std::pair<int, std::pair<int, int>>> checkPoints(n);
  // for (auto &pair : checkPoints) {
  //   cin >> pair.first >> pair.second;
  // }
  for (int i = 0; i < n; i++) {
    checkPoints[i].first = i + 1;
    cin >> checkPoints[i].second.first >> checkPoints[i].second.second;
  }

  auto sortPriority =
      [&residentPos](const std::pair<int, std::pair<int, int>> &p1,
                     const std::pair<int, std::pair<int, int>> &p2) {
        const int dist1 = distanceSquareSum(residentPos, p1.second);
        const int dist2 = distanceSquareSum(residentPos, p2.second);
        if (dist1 == dist2) {
          return p1.first < p2.first;
        }
        return dist1 < dist2;
      };
  std::stable_sort(checkPoints.begin(), checkPoints.end(), sortPriority);

  for (int i = 0; i < 3; i++) {
    cout << checkPoints[i].first << std::endl;
  }
  // cout << "Residence: " << residentPos.first << ' ' << residentPos.second
  //      << std::endl;
  // for (const auto &pair : checkPoints) {
  //   cout << pair.first << ": " << pair.second.first << ' ' << pair.second.second <<", dist: "<< distanceSquareSum(residentPos, pair.second)
  //        << std::endl;
  // }

  return 0;
}