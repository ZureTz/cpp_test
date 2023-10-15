#include <iostream>
#include <list>
#include <utility>
using std::cin;
using std::cout;

inline bool isSatisfied(int num, const int k) {
  return num % k == 0 || num % 10 == k;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n, k;
  cin >> n >> k;
  std::list<int> myList(n);
  {
    std::list<int>::iterator it = myList.begin();
    for (int i = 1; i <= n && it != myList.end(); i++, it++) {
      *it = i;
    }
  }

  auto it = myList.begin();
  int count = 1;
  for (; n > 1; ++it) {
    if (it == myList.end()) {
      it = myList.begin();
    }

    if (*it == 0) {
      continue;
    }

    if (isSatisfied(count, k)) {
      *it = 0;
      n--;
    }
    count++;
  }

  for (const int num : myList) {
    if (num != 0) {
      cout<<num;break;
    }
  }
  return 0;
}