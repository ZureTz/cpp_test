#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
typedef long long ll;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;
  std::vector<int> arr(n);
  for (int &num : arr) {
    cin >> num;
  }
  std::sort(arr.begin(), arr.end());

  if (n % 2 == 0) {
    if ((ll(arr.at(n / 2)) + arr.at(n / 2 - 1)) % 2 != 0) {
      double median = double(arr.at(n / 2) + arr.at(n / 2 - 1)) / 2.0;
      cout << arr.back() << ' ' << std::fixed << std::setprecision(1) << median
           << ' ' << arr.front();
      return 0;
    }
    cout << arr.back() << ' ' << ((ll(arr.at(n / 2)) + arr.at((n / 2) - 1)) / 2)
         << ' ' << arr.front();
    return 0;
  }
  cout << arr.back() << ' ' << arr.at(n / 2) << ' ' << arr.front();

  return 0;
}