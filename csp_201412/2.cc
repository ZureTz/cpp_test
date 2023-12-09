#include <cmath>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;

struct Matrix {
  std::vector<std::vector<int>> matrix;

  Matrix(int length) {
    matrix.resize(length);
    for (auto &vector : matrix) {
      vector.resize(length);
    }
  }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // 输入矩阵的大小
  int nDim;
  cin >> nDim;

  // 依次输入矩阵中的每个元素
  Matrix matrix(nDim);
  for (auto &vec : matrix.matrix) {
    for (int &element : vec) {
      cin >> element;
    }
  }

  // step1: 输出左上角的部分
  for (int i = 0; i < nDim; ++i) {
    // 往右上角走
    if (i % 2 == 0) {
      int index1 = i;
      int index2 = 0;
      // 从数学上可以证明循环次数为i + 1次
      for (int j = 0; j <= i; j++, index1--, index2++) {
        cout << matrix.matrix[index1][index2] << ' ';
      }
      continue;
    }
    // 往左下角走
    int index1 = 0;
    int index2 = i;
    // 注意到反方向的循环次数也是一样的
    for (int j = 0; j <= i; j++, index1++, index2--) {
      cout << matrix.matrix[index1][index2] << ' ';
    }
  }

  // step2: 输出右下角的部分
  const int iterations = 2 * (nDim - 1);
  for (int i = nDim; i <= iterations; ++i) {
    if (i % 2 == 0) {
      int index1 = nDim - 1;
      int index2 = i - nDim + 1;
      // 注意到循环次数变为如下次数（数学方式可以证明）
      for (int j = 0; j <= 2 * nDim - i - 2; j++, index1--, index2++) {
        cout << matrix.matrix[index1][index2] << ' ';
      }
      continue;
    }
    // 同上
    int index1 = i - nDim + 1;
    int index2 = nDim - 1;
    for (int j = 0; j <= 2 * nDim - i - 2; j++, index1++, index2--) {
      cout << matrix.matrix[index1][index2] << ' ';
    }
  }

  return 0;
}