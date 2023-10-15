#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

#define DEBUG false

struct pairHash {
  std::size_t operator()(const pair<int, int> &pair) const {
    return hash<int>()(pair.first) ^ (hash<int>()(pair.second) << 1);
  }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  cout.tie(0);

  int nTrees, maxSizeA, maxSizeB;
  cin >> nTrees >> maxSizeA >> maxSizeB;

  unordered_map<pair<int, int>, bool, pairHash> mapA;
  mapA.reserve(nTrees);
  // input A
  {
    int tempX, tempY;
    for (int i = 0; i < nTrees; i++) {
      cin >> tempX >> tempY;
      mapA[make_pair(tempX, tempY)] = true;
    }
  }

#if DEBUG
  for (const auto &pair : mapA) {
    cout << pair.first.first << ' ' << pair.first.second << endl;
  }
  cout << endl;
#endif

  vector<vector<int>> mapB(maxSizeB + 1, vector<int>(maxSizeB + 1, 0));
  // input B
  {
    for (int i = maxSizeB; i >= 0; i--) {
      for (int j = 0; j <= maxSizeB; j++) {
        cin >> mapB[i][j];
      }
    }
  }

#if DEBUG
  for (const auto &arr : mapB) {
    for (const int num : arr) {
      cout << num << ' ';
    }
    cout << endl;
  }
  cout << endl;
#endif

  // find:
  int sum = 0;
  for (auto it = mapA.begin(); it != mapA.end(); ++it) {
    if (it->first.first + maxSizeB > maxSizeA ||
        it->first.second + maxSizeB > maxSizeA) {
      continue;
    }

    bool flag = true;
    for (int i = 0; i <= maxSizeB && flag; i++) {
      for (int j = 0; j <= maxSizeB && flag; j++) {
        auto itA =
            mapA.find(make_pair(it->first.first + i, it->first.second + j));
        // if not found
        if (itA == mapA.end()) {
          if (mapB[i][j] == 1) {
#if DEBUG
            cout << "not found, but [i][j] == 1, @(" << it->first.first << ", "
                 << it->first.second << ')' << '(' << i << ", " << j << ')'
                 << endl;
#endif
            flag = false;
          } // else map[i][j] == 0, corresbounds
          continue;
        }
        // if found
        if (mapB[i][j] == 0) {
#if DEBUG
          cout << "found, but [i][j] == 0, @(" << it->first.first << ", "
               << it->first.second << ')' << '(' << i << ", " << j << ')'
               << endl;
#endif
          flag = false;
        } // else map[i][j] == 1, corresbounds
      }
    }
    sum += flag ? 1 : 0;
  }
  cout << sum;

  return 0;
}