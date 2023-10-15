#include <iostream>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  int numOfPoints;
  cin >> numOfPoints;

  // 当点数为1或为2时，不存在折点，可以直接输出0
  if (numOfPoints == 1 || numOfPoints == 2) {
    cout << 0;
    return 0;
  }

  int countOfTurning(0), prev, now, next;
  // 先输入 prev 和 now，然后在循环内读入 next
  cin >> prev >> now;
  // 使用 for 循环， 使得循环最后的出口处更加可读性更强
  for (int i = 2; i < numOfPoints; i++, prev = now, now = next) {
    cin >> next;
    if ((prev > now && next > now) || (prev < now && next < now)) {
      countOfTurning++;
    }
  }

  cout << countOfTurning;
  return 0;
}