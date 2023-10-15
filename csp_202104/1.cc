#include <iostream>
using std::cin;
using std::cout;

static int map[300] = {
    0,
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  int m, n, max;
  cin >> m >> n >> max;

  int temp;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> temp;
      ++map[temp];
    }
  }

  for (int i = 0; i < max; i++) {
    cout << map[i] << ' ';
  }

  return 0;
}