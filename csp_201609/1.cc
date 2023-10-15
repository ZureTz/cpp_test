#include <algorithm>
#include <iostream>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  int n, prev, now;
  // 读入n以及第一个数字
  cin >> n >> prev;

  // 初始化最大波动为0
  int maxDiff(0);
  for (int i = 1; i < n; i++, prev = now) {
    // 读入第2至第n-1个数字
    cin >> now;
    // 计算最大值
    maxDiff = std::max(maxDiff, abs(now - prev));
  }

  cout << maxDiff;
  return 0;
}