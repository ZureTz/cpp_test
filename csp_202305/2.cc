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

  int n, d;
  cin >> n >> d;
  Matrix Q(n, d), K(d, n), V(n, d);
  std::vector<ll> W(n);

  // input Q, K, V
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

  // simplified algorithm
  Matrix WQKT(n, d);
  // WQKT = W(Q * K(T)) * V
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ll sum = 0;
      for (int k = 0; k < d; k++) {
        sum += Q.mat[i][k] * K.mat[k][j];
      }
      sum *= W[i];
      for (int l = 0; l < d; l++) {
        WQKT.mat[i][l] += sum * V.mat[j][l];
      }
    }
  }

  for (const auto &vect : WQKT.mat) {
    for (const ll num : vect) {
      (cout << num).put(' ');
    }
    cout << std::endl;
  }
  return 0;
}