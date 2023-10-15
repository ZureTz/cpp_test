#include <iostream>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nowStat /* 表示当前状态 */;
  int prevAddedScore(1) /*用来表示上一次跳跃的得分*/, sum(0) /* 最终得分 */;
  // 对于每次的跳跃：
  while (cin >> nowStat) {
    // nowstat == 0: 结束游戏
    if (nowStat == 0) {
      break;
    }
    // nowstat == 1: 不在中间；得1分
    if (nowStat == 1) {
      sum++;
      prevAddedScore = 1;
      continue;
    }

    // nowstat == 2:
    // 若上一次的得分为1分或这是本局游戏的第一次跳跃则此次得分为2分
    // 否则此次得分比上一次得分多2分
    prevAddedScore += (prevAddedScore == 1) ? 1 : 2;
    sum += prevAddedScore;
  }

  cout << sum;
  return 0;
}