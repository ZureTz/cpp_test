#include <array>
#include <cmath>
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;

constexpr double PI_4 = 0.785398163397448309615660845819875721;
constexpr int matLength = 8;

double inline alpha(int u) { return u != 0 ? 1.0 : (sqrt(2.0) / 2.0); }

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::array<std::array<int, matLength>, matLength> Qmat;
  for (auto &arr : Qmat) {
    for (int &num : arr) {
      cin >> num;
    }
  }

  std::array<std::array<int, matLength>, matLength> Mmat;
  for (auto &arr : Mmat) {
    std::fill(arr.begin(), arr.end(), 0);
  }
  int tempLength, operationType;
  cin >> tempLength >> operationType;
  std::array<int, 64> tempArray;
  std::fill(tempArray.begin(), tempArray.end(), 0);
  for (int i = 0; i < tempLength; i++) {
    cin >> tempArray[i];
  }

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

  if (operationType == 0) {
    for (const auto &arr : Mmat) {
      for (const int num : arr) {
        cout << num << ' ';
      }
      cout << std::endl;
    }
    return 0;
  }

  for (int i = 0; i < matLength; i++) {
    for (int j = 0; j < matLength; j++) {
      Mmat[i][j] *= Qmat[i][j];
    }
  }

  if (operationType == 1) {
    for (const auto &arr : Mmat) {
      for (const int num : arr) {
        cout << num << ' ';
      }
      cout << std::endl;
    }
    return 0;
  }

  std::array<std::array<double, matLength>, matLength> resMat;
  for (auto &arr : resMat) {
    std::fill(arr.begin(), arr.end(), 0.0);
  }
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