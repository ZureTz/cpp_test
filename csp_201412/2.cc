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

  int nDim;
  cin >> nDim;
  Matrix matrix(nDim);
  for (auto &vec : matrix.matrix) {
    for (int &element : vec) {
      cin >> element;
    }
  }

  for (int i = 0; i < nDim; ++i) {
    int index1, index2;
    if (i % 2 == 0) {
      index1 = i;
      index2 = 0;
      for (int j = 0; j <= i; j++, index1--, index2++) {
        cout << matrix.matrix[index1][index2] << ' ';
      }
    } else {
      index1 = 0;
      index2 = i;
      for (int j = 0; j <= i; j++, index1++, index2--) {
        cout << matrix.matrix[index1][index2] << ' ';
      }
    }
  }

  int iterations = 2 * (nDim - 1);
  for (int i = nDim; i <= iterations; ++i) {
    int index1, index2;
    if (i % 2 == 0) {
      index1 = nDim - 1;
      index2 = i - nDim + 1;
      for (int j = 0; j <= 2 * nDim - i - 2; j++, index1--, index2++) {
        cout << matrix.matrix[index1][index2] << ' ';
      }
    } else {
      index1 = i - nDim + 1;
      index2 = nDim - 1;
      for (int j = 0; j <= 2 * nDim - i - 2; j++, index1++, index2--) {
        cout << matrix.matrix[index1][index2] << ' ';
      }
    }
  }

  return 0;
}