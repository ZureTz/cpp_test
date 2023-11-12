#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
constexpr int N = 1005;
using std::cin;
using std::cout;

std::vector<int> blockZonesInMemory[N];
std::multiset<int> nodeInMemory[N];

int nNodes, mAvailableBlockZones, gSetOfTasks;
std::vector<int> results, tempResults;

void checkFirstTime(int aTaskIndex, int na, int pa) {
  if (!na && !pa) {
    for (int i = 1; i <= nNodes; i++) {
      results.push_back(i);
    }
    return;
  }

  if (!na && pa) {
    for (int i = 1; i <= mAvailableBlockZones; i++) {
      bool flag = false;
      for (int j = 0; j < blockZonesInMemory[i].size(); j++) {
        if (nodeInMemory[blockZonesInMemory[i][j]].count(pa) != 0) {
          flag = true;
        }
      }
      if (flag) {
        for (int j = 0; j < blockZonesInMemory[i].size(); j++) {
          results.push_back(blockZonesInMemory[i][j]);
        }
      }
    }
    return;
  }

  if (na && !pa) {
    for (int i = 0; i < blockZonesInMemory[na].size(); i++) {
      results.push_back(blockZonesInMemory[na][i]);
    }
    return;
  }

  bool flag = false;
  for (int j = 0; j < blockZonesInMemory[na].size(); j++) {
    if (nodeInMemory[blockZonesInMemory[na][j]].count(pa) != 0) {
      flag = true;
    }
  }
  if (flag) {
    for (int j = 0; j < blockZonesInMemory[na].size(); j++) {
      results.push_back(blockZonesInMemory[na][j]);
    }
  }
}

void checkSecondTime(int a, int paa) {
  for (int i = 0; i < results.size(); i++) {
    if (nodeInMemory[results[i]].count(paa) == 0) {
      tempResults.push_back(results[i]);
    }
  }
}

int main(int argc, char const *argv[]) {
  cin >> nNodes >> mAvailableBlockZones;
  for (int i = 1; i <= nNodes; i++) {
    int l;
    cin >> l;
    blockZonesInMemory[l].push_back(i);
  }
  cin >> gSetOfTasks;
  while (gSetOfTasks-- > 0) {
    int fTasks, aTaskIndex, na, pa, paa, paar;
    std::vector<int> answers;
    cin >> fTasks >> aTaskIndex >> na >> pa >> paa >> paar;
    while (fTasks-- > 0) {
      results.clear();
      tempResults.clear();
      checkFirstTime(aTaskIndex, na, pa);
      if (results.empty()) {
        int count = fTasks + 1;
        while (count-- > 0) {
          answers.push_back(0);
        }
        break;
      }
      checkSecondTime(aTaskIndex, paa);
      if (tempResults.empty()) {
        if (paar) {
          int count = fTasks + 1;
          while (count-- > 0) {
            answers.push_back(0);
          }
          break;
        }
      } else {
        results = tempResults;
      }

      sort(results.begin(), results.end(), [&](const int n1, const int n2) {
        if (::nodeInMemory[n1].size() != ::nodeInMemory[n2].size()) {
          return ::nodeInMemory[n1].size() < ::nodeInMemory[n2].size();
        }
        return n1 < n2;
      });

      answers.push_back(results[0]);
      nodeInMemory[results[0]].insert(aTaskIndex);
    }

    for (int i = 0; i < answers.size(); i++) {
      cout << answers[i] << ' ';
    }
    cout << std::endl;
  }
  return 0;
}