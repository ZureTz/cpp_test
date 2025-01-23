// 瑞士轮赛制因最早使用于1895年在瑞士举办的国际象棋比赛而得名。它可以看作是淘汰赛与循环赛的折中，既保证了比赛的稳定性，又能使赛程不至于过长。

// 题目描述：
// N名编号为1∼2N的选手共进行R轮比赛。每轮比赛开始前，以及所有比赛结束后，都会按照总分从高到低对选手进行一次排名。选手的总分为第一轮开始前的初始分数加上已参加过的所有比赛的得分和。总分相同的，约定编号较小的选手排名靠前。

// 每轮比赛的对阵安排与该轮比赛开始前的排名有关：第1名和第2名、第3名和第4名、……、第2K-1名和第2K名、……
// 、第2N-1名和第2N名，各进行一场比赛。每场比赛胜者得1分，负者得0分。也就是说除了首轮以外，其它轮比赛的安排均不能事先确定，而是要取决于选手在之前比赛中的表现。

// 现给定每个选手的初始分数及其实力值，试计算在R轮比赛过后，排名第Q的选手编号是多少。我们假设选手的实力值两两不同，且每场比赛中实力值较高的总能获胜。

// 输入格式：
// 第一行是三个正整数N, R,
// Q，每两个数之间用一个空格隔开，表示有2×N名选手、R轮比赛，以及我们关心的名次Q。
// 第二行是2×N个非负整数s1, s2, …,
// s2N，每两个数之间用一个空格隔开，其中si表示编号为i的选手的初始分数。
// 第三行是2×N个正整数w1, w2, …,
// w2N，每两个数之间用一个空格隔开，其中wi表示编号为i的选手的实力值。

// 输出格式：
// 一个整数，即R轮比赛结束后，排名第Q的选手的编号。

// 输入输出样例

// 输入 #1
// 2 4 2
// 7 6 6 7
// 10 5 20 15

// 输出 #1
// 1

#include <algorithm>
#include <iostream>
#include <vector>

struct Player {
  int index;
  int score;
  int skillLevel;
};

// 总分相同的，约定编号较小的选手排名靠前
bool playerSort(const Player &a, const Player &b) {
  if (a.score == b.score) {
    return a.index < b.index;
  }

  return a.score > b.score;
}

int main(int argc, char const *argv[]) {
  int numOfPlayersDiv2, numOfRounds, rankQ;
  std::cin >> numOfPlayersDiv2 >> numOfRounds >> rankQ;

  std::vector<Player> players(numOfPlayersDiv2 * 2);

  // Set index for each player
  for (int i = 0; i < numOfPlayersDiv2 * 2; i++) {
    players[i].index = i + 1;
  }

  // Read initial score and skill level for each player
  for (Player &player : players) {
    std::cin >> player.score;
  }

  for (Player &player : players) {
    std::cin >> player.skillLevel;
  }

  // Perform first sorting before the first round
  std::sort(players.begin(), players.end(), playerSort);

  // Perform rounds
  for (int i = 0; i < numOfRounds; i++) {
    // For each pair of players
    for (int k = 0; k < numOfPlayersDiv2; k++) {
      int player1Index = k * 2;
      int player2Index = k * 2 + 1;

      if (players[player1Index].skillLevel > players[player2Index].skillLevel) {
        players[player1Index].score++;
        continue;
      }
      players[player2Index].score++;
    }
    // After each round, sort the players
    // Note that use stable_sort to be faster in this case
    std::stable_sort(players.begin(), players.end(), playerSort);
  }

  // Finally, output the rankQ player's index
  std::cout << players[rankQ - 1].index << std::endl;

  return 0;
}