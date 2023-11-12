#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// avg：平均值
double avg(const vector<int> &src) {
  double avg = 0.0;
  for (const int num : src) {
    avg += double(num);
  }
  return avg / double(src.size());
}

// DX：方差
double DX(const vector<int> &src, double avg) {
  double dX = 0.0;
  for (const int num : src) {
    dX += pow(double(num) - avg, 2);
  }
  return dX / double(src.size());
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  cout.tie(0);

  // 输入n
  int n;
  cin >> n;

  // 依次读入数据
  vector<int> arr(n);
  for (int &num : arr) {
    cin >> num;
  }

  // 计算平均值
  double avgNum = avg(arr);
  // 计算方差
  double dxNum = DX(arr, avgNum);

  // 使得方差变为标准差
  dxNum = sqrt(dxNum);
  // 输出归一化处理后的数据
  for (const int num : arr) {
    cout << setprecision(15) << (num - avgNum) / dxNum << endl;
  }

  return 0;
}