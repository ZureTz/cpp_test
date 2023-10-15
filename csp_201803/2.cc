#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>
using std::cin;
using std::cout;

struct Ball {
  int pos;
  int velocity;
  Ball(int pos, int velocity = 1) : pos(pos), velocity(velocity) {}
};

struct ballComp {
  bool operator()(std::shared_ptr<Ball> b1, std::shared_ptr<Ball> b2) const {
    return b1->pos < b2->pos;
  }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nBall, maxLength, time;
  cin >> nBall >> maxLength >> time;

  std::multiset<std::shared_ptr<Ball>, ballComp> set;
  std::unordered_map<int, std::shared_ptr<Ball>> map;
  for (int i = 0; i < nBall; i++) {
    int tempPos;
    cin >> tempPos;
    auto tempPtr = std::make_shared<Ball>(tempPos);
    map.insert({i, tempPtr});
    set.insert(tempPtr); 
  }

  auto posPlus = [=](std::shared_ptr<Ball> ballPtr) {
    // inline void BallMove() :
    //   if (pos + velocity > maxLength || pos - velocity < 0) {
    //     velocity = -velocity;
    //   }
    //   pos += velocity;
    int tempPos(ballPtr->pos + ballPtr->velocity);
    if (tempPos > maxLength || tempPos < 0) {
      ballPtr->velocity = -ballPtr->velocity;
    }
    ballPtr->pos += ballPtr->velocity;
  };

  for (int i = 0; i < time; i++) {
    for (auto it = set.begin(); it != set.end(); it++) {
      posPlus(*it);
    }
    auto it = set.begin();
    auto it_after = ++it;
    --it;
    for (; it_after != set.end(); ++it, ++it_after) {
      if (it->get()->pos == it_after->get()->pos) {
        it->get()->velocity = -it->get()->velocity;
        it_after->get()->velocity = -it_after->get()->velocity;
      }
    }
  }

  for (int i = 0; i < maxLength; i++) {
    if (map.find(i) == map.end()) {
      continue;
    }
    cout << map[i]->pos << ' ';
  }

  return 0;
}