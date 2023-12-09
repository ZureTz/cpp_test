#include <iostream>
#include <list>
#include <utility>
using std::cin;
using std::cout;

// 判断是否满足出局的条件
inline bool isSatisfied(int num, const int k) {
  return num % k == 0 || num % 10 == k;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // 输入n个小朋友和数字k
  int n, k;
  cin >> n >> k;

  // 使用一个列表来储存小朋友的序号
  std::list<int> myList(n);
  {
    std::list<int>::iterator it = myList.begin();
    for (int i = 1; i <= n && it != myList.end(); i++, it++) {
      *it = i;
    }
  }

  auto it = myList.begin();
  auto increment = [&]() {
    ++it;
    if (it == myList.end()) {
      it = myList.begin();
    }
  };

  // 持续用iterator遍历list，使用count来报数
  for (int count = 1; n > 1; increment()) {
    // 遇到已经出局的则继续
    if (*it == 0) {
      continue;
    }

    // 判断是否出局，如果出局则删除
    if (isSatisfied(count, k)) {
      *it = 0;
      n--;
    }
    ++count;
  }

  // 最后输出唯一一个没有出局的小朋友
  for (const int num : myList) {
    if (num != 0) {
      cout << num;
      break;
    }
  }
  return 0;
}