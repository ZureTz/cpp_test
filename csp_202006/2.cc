#include <iostream>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
typedef long long ll;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nDim, aNon0, bNon0;
  cin >> nDim >> aNon0 >> bNon0;
  std::vector<std::pair<int, int>> aVect(aNon0), bVect(bNon0);
  for (auto &pair : aVect) {
    cin >> pair.first >> pair.second;
  }
  for (auto &pair : bVect) {
    cin >> pair.first >> pair.second;
  }

  ll result = 0ll;
  auto itA = aVect.begin(), itB = bVect.begin();
  while (itA < aVect.end() && itB < bVect.end()) {
    if (itA->first == itB->first) {
      result += (ll)itA->second * (ll)itB->second;
      itA++;
      itB++;
      continue;
    }
    if (itA->first < itB->first) {
      itA++;
      continue;
    }
    itB++;
  }
  cout << result;
  return 0;
}