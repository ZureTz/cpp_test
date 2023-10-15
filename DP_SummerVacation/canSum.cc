#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#define boolOut(x) (x ? "true" : "false")

bool canSum(int targetSum, const std::vector<int> &numbers,
            std::unordered_map<int, bool> &&memo = {}) {
  if (targetSum == 0) {
    return true;
  }
  if (targetSum < 0) {
    return false;
  }

  if (memo.find(targetSum) != memo.end()) {
    return false;
  }

  for (const int num : numbers) {
    if (canSum(targetSum - num, numbers, std::move(memo)) == true) {
      return true;
    }
  }

  memo.insert(std::make_pair(targetSum, false));
  return false;
};

int main(int argc, char const *argv[]) {
  std::cout << boolOut(canSum(300, {7, 14}));
  return 0;
}