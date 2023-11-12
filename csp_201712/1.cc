#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // 输入n和数字
  int n;
  cin >> n;
  std::vector<int> arr(n);
  for (int &num : arr) {
    cin >> num;
  }
  // 排序
  std::sort(arr.begin(), arr.end(), [](int a, int b) { return a < b; });

  // 计算最小差值
  int min = INT_MAX;
  for (std::vector<int>::const_iterator it = arr.begin() + 1; it != arr.end();
       it++) {
    min = std::min(min, it[0] - it[-1]);
  }
  // 输出最终的结果
  cout << min;
  return 0;
}