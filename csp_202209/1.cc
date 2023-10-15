#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nQuestion, magicNumber;
  cin >> nQuestion >> magicNumber;
  std::vector<int> arr(nQuestion + 1);
  arr.front() = 1;
  for (auto it = arr.begin() + 1; it != arr.end(); it++) {
    cin >> *it;
    *it *= *(it - 1);
  }
  for (int i = 1; i < nQuestion + 1; i++) {
    cout << ((magicNumber % arr[i]) - (magicNumber % arr[i - 1])) / arr[i - 1]
         << ' ';
  }

  return 0;
}
