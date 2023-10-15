#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
constexpr int ROWS = 55, COLS = 1010;

int n, m;
int tree[ROWS][26], count[ROWS], idx;
int q[ROWS], ne[ROWS];
struct Node {
  int row, next;
} g[26][ROWS];
int f[COLS][ROWS][ROWS];
std::vector<std::string> strs;

void insert(const std::string &str) {
  int p = 0;
  for (const char c : str) {
    int u = c - 'a';
    if (!tree[p][u])
      tree[p][u] = ++idx;
    p = tree[p][u];
  }
  count[p]++;
}

void createTree() {
  int hh = 0, tt = -1;
  for (int i = 0; i < 26; i++)
    if (tree[0][i])
      q[++tt] = tree[0][i];
  while (hh <= tt) {
    int t = q[hh++];
    for (int i = 0; i < 26; i++) {
      int p = tree[t][i];
      if (!p)
        tree[t][i] = tree[ne[t]][i];
      else {
        ne[p] = tree[ne[t]][i];
        count[p] += count[ne[p]];
        q[++tt] = p;
      }
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < 26; i++) {
    for (int j = 1; j <= n; j++) {
      std::string str;
      cin >> str;
      g[str[0] - 'a'][j] = {i, stoi(str.substr(1))};
    }
  }
  std::string str;
  while (cin >> str) {
    insert(str);
    strs.push_back(str);
  }

  createTree();

  f[0][0][1] = 1;
  for (int i = 0; i <= m; i++) {
    int sum = 0;
    for (int j = 0; j <= idx; j++)
      for (int k = 1; k <= n; k++) {
        if (!f[i][j][k]) {
          continue;
        }

        sum = (sum + f[i][j][k]);
        for (const auto &s : strs) {
          if (i + s.size() > m) {
            continue;
          }

          bool flag = true;
          int x = j, y = k;
          for (const auto c : s) {
            int u = c - 'a';
            auto &t = g[u][y];
            x = tree[x][t.row];
            if (count[x]) {
              flag = false;
              break;
            }
            y = t.next;
          }

          if (flag) {
            auto &v = f[i + s.size()][x][y];
            v = (v + f[i][j][k]);
          }
        }
      }
    if (i) {
      cout << sum << std::endl;
    }
  }
  return 0;
}