#include <iostream>
using std::cin;
using std::cout;

inline int intersectionLength(int begin1, int end1, int begin2, int end2) {
  if (end1 <= begin2 || end2 <= begin1) {
    return 0;
  }

  if (begin1 <= begin2 && end1 <= end2) {
    return end1 - begin2;
  }

  if (begin2 <= begin1 && end2 <= end1) {
    return end2 - begin1;
  }

  if (begin1 < begin2 && end1 > end2) {
    return end2 - begin2;
  }

  return end1 - begin1;
}

struct Rectangle {
  int left, bottom, right, top;
  Rectangle(int left, int bottom, int right, int top)
      : left(left), bottom(bottom), right(right), top(top) {}
  inline int intersectionArea(const Rectangle &rhs) const {
    return intersectionLength(left, right, rhs.left, rhs.right) *
           intersectionLength(bottom, top, rhs.bottom, rhs.top);
  }
};

int main(int argc, char const *argv[]) {
  int numOfRects, a, b;
  cin >> numOfRects >> a >> b;
  Rectangle rect(0, 0, a, b);

  int sumArea = 0;
  for (int i = 0; i < numOfRects; i++) {
    int left, bottom, right, top;
    cin >> left >> bottom >> right >> top;
    sumArea += rect.intersectionArea(Rectangle(left, bottom, right, top));
  }
  
  cout << sumArea;
  return 0;
}
