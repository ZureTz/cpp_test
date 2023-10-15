#include <iostream>
using std::endl;
using std::cout;
typedef long long ll;

ll gridTraveler(int rows, int cols) {
  if (rows == 0 || cols == 0) {
    return 0L;
  }
  if (rows == 1 && cols == 1) {
    return 1L;
  }
  return gridTraveler(rows - 1, cols) + gridTraveler(rows, cols - 1);
}

int main(int argc, char const *argv[]) {
  cout << gridTraveler(1, 1) << endl;
  cout << gridTraveler(2, 3) << endl;
  cout << gridTraveler(3, 2) << endl;
  cout << gridTraveler(3, 3) << endl;
  cout << gridTraveler(5, 4) << endl;
  cout << gridTraveler(4, 5) << endl;
  cout << gridTraveler(18, 18) << endl;
  return 0;
}