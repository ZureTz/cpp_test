#include <iostream>
using namespace std;
typedef long long ll;

inline int abs(int num) { return num < 0 ? -num : num; }

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  cout.tie(0);

  int n, N;
  cin >> n >> N;
  const int r = N / (n + 1);
  auto g = [=](int x) { return x / r; };

  int index = 0;
  int prev = 0, next = 0;
  ll sum = 0;
  for (int i = 0; i < n; ++i, prev = next) {
    cin >> next;
    while (index < N && prev <= index && index < next) {
      // cout << i << ' ' << g(index) << ' ' << abs(i - g(index)) << endl;
      sum += abs(g(index) - i); // i == f(index)
      index++;
    }
  }
  // i == n, break the cycle
  while (index < N) {
    if (next <= index) {
      // cout << n << ' ' << g(index) << ' ' << abs(n - g(index)) << endl;
      sum += abs(g(index) - n);
    }
    index++;
  }

  cout << sum;
  return 0;
}