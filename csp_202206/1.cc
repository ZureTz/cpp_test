#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

double avg(const vector<int> &src) {
  double avg = 0;
  for (const int num : src) {
    avg += double(num);
  }
  return avg / double(src.size());
}

double DX(const vector<int> &src, double avg) {
  double dX = 0;
  for (const int num : src) {
    dX += pow(double(num) - avg, 2);
  }
  return dX / double(src.size());
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  cout.tie(0);

  int n;
  cin >> n;
  vector<int> arr(n);
  for (int &num : arr) {
    cin >> num;
  }

  double avgNum = avg(arr);
  double dxNum = DX(arr, avgNum);

  dxNum = sqrt(dxNum);
  for (const int num : arr) {
    cout << setprecision(15) << (num - avgNum) / dxNum << endl;
  }

  return 0;
}