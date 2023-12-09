#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

struct mmp {
  int num;
  bool flag;
};

std::queue<mmp> str[10005];
inline void clear(std::queue<mmp> &q) {
  std::queue<mmp> empty;
  swap(empty, q);
}

int main() {
  int t, n;
  (std::cin >> t >> n).get();
  while (t--) {
    for (int i = 0; i < n; i++) {
      clear(str[i]);
    }

    std::string line;

    for (int i = 0; i < n; ++i) {
      getline(std::cin, line);
      std::stringstream ss(line);
      std::string tmp;
      mmp temp;
      while (ss >> tmp) {
        temp.flag = tmp.substr(0, 1) == "S" ? true : false;
        temp.num = stoi(tmp.substr(1));
        str[i].push(temp);
      }
    }

    int v[10005] = {0};
    bool is_change = true;
    while (is_change) {
      int p = 0, q;
      std::fill(v, v + 10005, 0);
      is_change = false;
      while (p < n && str[p].empty()) {
        p++;
      }
      if (p == n) {
        break;
      }
      q = str[p].front().num;
      while (!is_change && !v[q] && !str[q].empty()) {
        v[q] = 1;
        if (str[q].front().num == p &&
            str[p].front().flag != str[q].front().flag) {
          is_change = true;
          str[p].pop();
          str[q].pop();
          break;
        }
        p = q;
        q = str[p].front().num;
      }
    }

    bool res = true;
    for (int i = 0; i < n; ++i) {
      if (!str[i].empty()) {
        res = false;
        break;
      }
    }
    if (res) {
      std::cout << 0 << std::endl;
      continue;
    }
    std::cout << 1 << std::endl;
  }

  return 0;
}
/*
3 2
R1 S1
S0 R0
R1 S1
R0 S0
R1 R1 R1 R1 S1 S1 S1 S1
S0 S0 S0 S0 R0 R0 R0 R0
*/
