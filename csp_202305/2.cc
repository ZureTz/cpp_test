#include <iostream>
#include <vector>
using std::cin;
using std::cout;
typedef long long ll;

struct Matrix {
  std::vector<std::vector<ll>> mat;

  Matrix(int m, int n) {
    mat.resize(m);
    for (auto &vector : mat) {
      vector.resize(n);
    }
  }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // 输入矩阵大小
  int n, d;
  cin >> n >> d;
  Matrix Q(n, d), K(d, n), V(n, d);
  std::vector<ll> W(n);

  // 分别输入 Q, K, V
  for (auto &col : Q.mat) {
    for (ll &num : col) {
      cin >> num;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      cin >> K.mat[j][i];
    }
  }
  for (auto &col : V.mat) {
    for (ll &num : col) {
      cin >> num;
    }
  }
  for (ll &num : W) {
    cin >> num;
  }

#if false
  for (const auto &vect : Q.mat) {
    for (const ll num : vect) {
      (cout << num).put(' ');
    }
    cout << std::endl;
  }
  for (const auto &vect : K.mat) {
    for (const ll num : vect) {
      (cout << num).put(' ');
    }
    cout << std::endl;
  }
  for (const auto &vect : V.mat) {
    for (const ll num : vect) {
      (cout << num).put(' ');
    }
    cout << std::endl;
  }
#endif

  // 初始化最终的结果
  Matrix WQKT(n, d);
  // WQKT = W(Q * K^T) * V
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // 此处使用sum储存 W(Q*K^T) 避免使用新的矩阵，从而降低了时间复杂度
      ll sum = 0;
      for (int k = 0; k < d; k++) {
        sum += Q.mat[i][k] * K.mat[k][j];
      }
      sum *= W[i];
      for (int k = 0; k < d; k++) {
        WQKT.mat[i][k] += sum * V.mat[j][k];
      }
    }
  }

  // 最后输出结果即可
  for (const auto &vect : WQKT.mat) {
    for (const ll num : vect) {
      (cout << num).put(' ');
    }
    cout << std::endl;
  }
  return 0;
}