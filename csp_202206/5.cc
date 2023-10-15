#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

constexpr PI = cos

void move1(vector<pair<double, double>> &points, int l, int r, double a,
           double b) {
  auto begin = points.begin() + l, end = points.begin() + r;
  for (auto it = begin; it != end; ++it) {
    it->first += a;
    it->second += b;
  }
}

void rotate2(vector<pair<double, double>> &points, int l, int r, double a,
             double b, double theta) {
  double cosT = cos(theta), sinT = sin(theta);
  auto begin = points.begin() + l, end = points.begin() + r;
  for (auto it = begin; it != end; ++it) {
    pair<double, double> temp = {it->first - a, it->second - b};
    it->first = a + temp.first * cosT - temp.second * sinT;
    it->second = b + temp.first * sinT + temp.second * cosT;
  }
}

void resize3(vector<pair<double, double>> &points, int l, int r, double a,
             double b, double lambda) {
  auto begin = points.begin() + l, end = points.begin() + r;
  for (auto it = begin; it != end; ++it) {
    pair<double, double> temp = {it->first - a, it->second - b};
    it->first = a + lambda * temp.first;
    it->second = b + lambda * temp.second;
  }
}

void mirror4(vector<pair<double, double>> &points, int l, int r, double theta,
             double y0) {
  double k = tan(theta);
  auto begin = points.begin() + l, end = points.begin() + r;
  for (auto it = begin; it != end; ++it) {
    pair<double, double> temp(*it);
    double t1 = (k * temp.first - temp.second + y0) / (pow(k, 2) + 1);
    it->first = temp.first - 2.0 * k * (t1);
    it->second = temp.second + 2.0 * t1;
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n, q;
  cin >> n >> q;
  vector<pair<double, double>> points;
  for (auto &pair : points) {
    cin >> pair.first >> pair.second;
  }

  while (q-- > 0) {
    int code;
    cin >> code;
    switch (code) {
    case 1:
      int l, r, a, b;
      cin >> l >> r >> a >> b;
      move1(points, --l, --r, a, b);
      break;
    case 2:

      break;
    }
  }

  return 0;
}