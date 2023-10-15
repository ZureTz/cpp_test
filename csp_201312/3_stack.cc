#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;
  std::vector<int> arr(n);
  for (int &num : arr) {
    cin >> num;
  }
  arr.push_back(0);

  // n == 0 or n == 1
  if (n == 0) {
    cout << 0;
    return 0;
  }
  if (n == 1) {
    cout << arr.front();
    return 0;
  }

  // calculation
  int maxArea = 0;
  std::stack<int> monoStack;
  for (int i = 0; i < n + 1; i++) {
    while (!monoStack.empty() && arr[monoStack.top()] > arr[i]) {
      int tempHeight = arr[monoStack.top()];
      monoStack.pop();
      while (!monoStack.empty()&&arr[monoStack.top()]==tempHeight) {
        monoStack.pop();
      }
      
      int width = (monoStack.empty() ? i : (i - monoStack.top() - 1));
      maxArea = std::max(maxArea, tempHeight * width);
    }

    // monoStack.empty() || arr[monoStack.top()] <= arr[i]
    monoStack.push(i);
  }

  cout << maxArea;
  return 0;
}