#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
constexpr long long MAX = 3e3;
// constexpr long long MAX = 20;
bool output[MAX];
std::vector<long long> graph[MAX];
std::pair<std::string, std::vector<long long>> device[MAX];
long long degree[MAX];
long long ni, qi, mi, ki, si;
std::vector<long long> top;
// 求拓扑序列
bool topSort() {
  std::queue<long long> q;              // 储存入度为0的顶点
  for (long long i = 1; i <= ni; ++i) { // 将入度为零的顶点放入队列中
    if (degree[i] == 0) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    long long p = q.front();
    q.pop();
    top.push_back(p);
    for (long long i : graph[p]) { // 遍历该结点的邻接顶点
      if (--degree[i] == 0) { // 减少邻接顶点的入度，如果入度为零
        q.push(i);            // 压入队列
      }
    }
  }
  return top.size() == ni;
}
// 按input输入，求出所有器件的输出
void getResult(std::vector<long long> &input) {
  for (long long i : top) {
    if (device[i].first == "NOT") {
      long long j = device[i].second[0];
      output[i] = !(j > 0 ? output[j] : input[-j]);
    } else if (device[i].first == "AND") {
      output[i] = true;
      for (long long j : device[i].second) {
        output[i] &= j > 0 ? output[j] : input[-j];
      }
    } else if (device[i].first == "OR") {
      output[i] = false;
      for (long long j : device[i].second) {
        output[i] |= j > 0 ? output[j] : input[-j];
      }
    } else if (device[i].first == "XOR") {
      output[i] = false;
      for (long long j : device[i].second) {
        output[i] ^= j > 0 ? output[j] : input[-j];
      }
    } else if (device[i].first == "NAND") {
      output[i] = true;
      for (long long j : device[i].second) {
        output[i] &= j > 0 ? output[j] : input[-j];
      }
      output[i] = !output[i];
    } else if (device[i].first == "NOR") {
      output[i] = false;
      for (long long j : device[i].second) {
        output[i] |= j > 0 ? output[j] : input[-j];
      }
      output[i] = !output[i];
    }
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cin >> qi;
  std::string s;
  while (qi--) {
    std::cin >> mi >> ni;
    for (long long i = 1; i <= ni; i++) {
      graph[i].clear();
      device[i].second.clear();
      degree[i] = 0;
    }
    top.clear();
    // 建图
    for (long long i = 1; i <= ni; i++) {
      std::cin >> device[i].first >> ki;
      while (ki--) {
        std::cin >> s;
        long long t = stoll(s.substr(1));
        device[i].second.push_back(s[0] == 'O' ? t : -t);
        if (s[0] == 'O') {
          degree[i]++;
          graph[t].push_back(i);
        }
      }
    }
    // 读取k个输入
    std::cin >> ki;
    std::vector<std::vector<long long>> input(ki,
                                              std::vector<long long>(mi + 1));
    for (long long j = 0; j < ki; ++j) {
      for (long long i = 1; i <= mi; ++i) {
        std::cin >> input[j][i];
      }
    }
    bool result = topSort();
    if (!result) {
      std::cout << "LOOP\n";
    }
    for (long long j = 0; j < ki; ++j) {
      std::cin >> si;
      getResult(input[j]);
      long long k;
      for (long long i = 0; i < si; ++i) {
        std::cin >> k;
        if (result) {
          std::cout << output[k] << " ";
        }
      }
      if (result) {
        std::cout << "\n";
      }
    }
  }
  return 0;
}