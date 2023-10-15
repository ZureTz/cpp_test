#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nVariable, nStatement;
  cin >> nVariable >> nStatement;

  // 设置一个vector用来存储变量的初始化状态
  std::vector<char> map(nVariable + 1, false);
  map[0] = true;

  int uninitializedCount(0);
  for (int i = 0; i < nStatement; i++) {
    int lValue, rValue;
    cin >> lValue >> rValue;
    // 如果rValue未初始化：
    if (map[rValue] == false) {
      uninitializedCount++;
    }
    // lValue被设置为已经初始化
    map[lValue] = true;
  }

  cout << uninitializedCount << std::endl;
  return 0;
}