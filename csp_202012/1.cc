#include <algorithm>
#include <iostream>
using std::cin;
using std::cout;

// 定义ReLU函数
inline int ReLU(int x) { return std::max(0, x); }

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nFactor, w, score;
  // 输入n种因素
  cin >> nFactor;
  // 得分总和：
  int sum = 0;
  for (int i = 0; i < nFactor; i++) {
    // 对每个因素，输入重要程度和分数
    cin >> w >> score;
    sum += w * score;
  }

  // 输出结果
  cout << ReLU(sum);
  return 0;
}