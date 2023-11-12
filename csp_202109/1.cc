#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n; // 输入 B 的长度

  // 初始化最大 sum，最小 sum，以及当前和上个元素
  int sumMax(0), sumMin(0), prev, now;
  // 先输入第 1 个元素
  cin >> prev;
  // 特殊情况特殊考虑
  if (n == 1) {
    cout << prev << '\n' << prev;
    return 0;
  }

  // 两个和都加上第 1 个元素
  sumMax += prev;
  sumMin += prev;
  // 进入循环，输入后续元素
  for (int i = 1; i < n; i++, prev = now) {
    cin >> now;
    // 最大 sum：加入所有输入的元素
    sumMax += now;
    if (now == prev) {
      continue;
    }
    // 最小sum：只在当前元素与上个元素不同的时候相加，其他的时候假设当前A_i为0
    sumMin += now;
  }
  cout << sumMax << '\n' << sumMin;
  return 0;
}