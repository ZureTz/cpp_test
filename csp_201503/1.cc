#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  std::vector<std::vector<int>> mat(n);
  for (auto &vect : mat) {
    vect.resize(m);
    for (int &num : vect) {
      cin >> num;
    }
  }

  for (int i = m - 1; i >= 0; i--) {
    for (int j = 0; j < n; j++) {
      cout << mat[j][i] << ' ';
    }
    cout << std::endl;
  }

  return 0;
}