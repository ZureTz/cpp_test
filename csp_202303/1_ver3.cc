#include <iostream>
using namespace std;

// inline int ge(int num) { return num < 0 ? 0 : num; }
// inline int le(int num, int bound) { return num > bound ? bound : num; }
inline int makeInArea(int num, int bound) {
  if (num < 0) {
    return 0;
  }
  if (num > bound) {
    return bound;
  }
  return num;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n, a, b;
  cin >> n >> a >> b;

  int sumArea = 0, tempX1, tempY1, tempX2, tempY2;
  for (int i = 0; i < n; ++i) {
    cin >> tempX1 >> tempY1 >> tempX2 >> tempY2;
    tempX1 = makeInArea(tempX1, a);
    tempX2 = makeInArea(tempX2, a);
    tempY1 = makeInArea(tempY1, b);
    tempY2 = makeInArea(tempY2, b);
    sumArea += (tempX2 - tempX1) * (tempY2 - tempY1);
  }
  cout << sumArea;

  return 0;
}