#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
using std::cin;
using std::cout;

// 定义 PI / 4
constexpr double PI_4 = 0.785398163397448309615660845819875721;
// 定义矩阵的大小
constexpr int matLength = 8;

// 定义alpha函数
inline double alpha(int u) { return u != 0 ? 1.0 : (sqrt(2.0) / 2.0); }

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // 初始化并输入量化矩阵Q
  std::array<std::array<int, matLength>, matLength> Qmat;
  for (auto &arr : Qmat) {
    for (int &num : arr) {
      cin >> num;
    }
  }

  // 初始化矩阵M
  std::array<std::array<int, matLength>, matLength> Mmat;
  for (auto &arr : Mmat) {
    std::fill(arr.begin(), arr.end(), 0);
  }

  // 读入扫描数据，以及任务类型
  int tempLength, operationType;
  cin >> tempLength >> operationType;
  std::array<int, 64> tempArray;
  std::fill(tempArray.begin(), tempArray.end(), 0);
  for (int i = 0; i < tempLength; i++) {
    cin >> tempArray[i];
  }

  // 填充扫描数据到M（参考矩阵的zigzag扫描）
  auto tempArrIt = tempArray.begin();
  for (int i = 0, index1, index2; i < matLength; i++) {
    if (i % 2 == 0) {
      index1 = i;
      index2 = 0;
      for (int j = 0; j <= i; j++, tempArrIt++) {
        Mmat[index1 - j][index2 + j] = *tempArrIt;
      }
      continue;
    }
    index1 = 0;
    index2 = i;
    for (int j = 0; j <= i; j++, tempArrIt++) {
      Mmat[index1 + j][index2 - j] = *tempArrIt;
    }
  }
  const int iterations = 2 * (matLength - 1);
  for (int i = matLength, index1, index2; i <= iterations; i++) {
    if (i % 2 == 0) {
      index1 = matLength - 1;
      index2 = i - matLength + 1;
      for (int j = 0; j <= 2 * matLength - i - 2; j++, tempArrIt++) {
        Mmat[index1 - j][index2 + j] = *tempArrIt;
      }
      continue;
    }
    index1 = i - matLength + 1;
    index2 = matLength - 1;
    for (int j = 0; j <= 2 * matLength - i - 2; j++, tempArrIt++) {
      Mmat[index1 + j][index2 - j] = *tempArrIt;
    }
  }

  // 当任务类型为0: 输出扫描输入后的M，并退出
  if (operationType == 0) {
    for (const auto &arr : Mmat) {
      for (const int num : arr) {
        cout << num << ' ';
      }
      cout << std::endl;
    }
    return 0;
  }

  // M与Q点乘，结果放进M
  for (int i = 0; i < matLength; i++) {
    for (int j = 0; j < matLength; j++) {
      Mmat[i][j] *= Qmat[i][j];
    }
  }

  // 当任务类型为1: 输出点乘后的结果，并退出
  if (operationType == 1) {
    for (const auto &arr : Mmat) {
      for (const int num : arr) {
        cout << num << ' ';
      }
      cout << std::endl;
    }
    return 0;
  }

  // 初始化离散余弦逆变换的结果矩阵
  std::array<std::array<double, matLength>, matLength> resMat;
  for (auto &arr : resMat) {
    std::fill(arr.begin(), arr.end(), 0.0);
  }
  // 计算离散余弦逆变换
  for (int i = 0; i < matLength; i++) {
    for (int j = 0; j < matLength; j++) {
      for (int u = 0; u < matLength; u++) {
        for (int v = 0; v < matLength; v++) {
          resMat[i][j] += 0.25 * alpha(u) * alpha(v) * Mmat[u][v] *
                          cos(0.5 * PI_4 * (double(i) + 0.5) * double(u)) *
                          cos(0.5 * PI_4 * (double(j) + 0.5) * double(v));
        }
      }
    }
  }

  // 将每个元素加上128，并取整数(按照题目要求)
  // 然后将结果输出即可
  for (const auto &arr : resMat) {
    for (const double num : arr) {
      int temp = round(num + 128.0);
      if (temp > 255) {
        cout << 255 << ' ';
        continue;
      }
      if (temp < 0) {
        cout << 0 << ' ';
        continue;
      }
      cout << temp << ' ';
    }
    cout << std::endl;
  }

  return 0;
}