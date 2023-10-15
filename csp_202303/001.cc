#include <iostream>
#include <memory>
using namespace std;
/*

4 10 10
0 0 5 5
5 -2 15 3
8 8 15 15
-2 10 3 15

*/
inline int abs(int x) { return x < 0 ? -x : x; }

int intersection_length(const int a, const int b, const int arg1,
                        const int arg2) {
  // a < b; arg1 < arg2
  if (arg2 <= a or arg1 >= b) {
    return 0;
  }
  if (arg1 <= a and arg2 >= b) {
    return b - a;
  }
  if (arg1 <= b and arg2 >= b) {
    return b - arg1;
  }
  if (arg1 <= a and arg2 >= a) {
    return arg2 - a;
  }
  return arg2 - arg1;
}

int main(int argc, char const *argv[]) {
  int n, a, b;
  cin >> n >> a >> b;

  int sum_area(0);
  for (int i = 0; i < n; i++) {
    int x1(0), y1(0), x2(0), y2(0);
    cin >> x1 >> y1 >> x2 >> y2;
    sum_area +=
        intersection_length(0, a, x1, x2) * intersection_length(0, b, y1, y2);
  }

  cout << sum_area;

  return 0;
}