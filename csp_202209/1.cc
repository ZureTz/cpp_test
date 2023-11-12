#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // 输入题目的数量，以及神秘数字
  int nQuestion, magicNumber;
  cin >> nQuestion >> magicNumber;
  // 数组c（长度为 nQuestion + 1）
  std::vector<int> arr(nQuestion + 1);
  // 记 c_0 = 1
  arr.front() = 1;
  for (auto it = arr.begin() + 1; it != arr.end(); it++) {
    // 输入a_i的同时，计算 c_i
    cin >> *it;
    *it *= *(it - 1);
  }

  // 按照题目给的提示，输出公式即可
  for (int i = 1; i < nQuestion + 1; i++) {
    cout << ((magicNumber % arr[i]) - (magicNumber % arr[i - 1])) / arr[i - 1]
         << ' ';
  }

  return 0;
}
