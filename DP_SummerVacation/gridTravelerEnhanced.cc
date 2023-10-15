#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
typedef long long ll;
using std::cout;
using std::endl;

class orderedPair {
  int first;
  int second;

public:
  orderedPair(int first = 0, int second = 0) : first(first), second(second) {}
  inline bool operator==(const orderedPair &rhs) const noexcept {
    return first == rhs.first && second == rhs.second;
  }
  inline int getFirst() const noexcept { return first; }
  inline int getSecond() const noexcept { return second; }
};

// 这就是 C++
template <> struct std::hash<orderedPair> {
  std::size_t operator()(const orderedPair &op) const {
    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:
    return std::hash<int>()(op.getFirst()) ^
           (std::hash<int>()(op.getSecond()) << 1);
  }
};

ll gridTravelerEnhanced(int rows, int cols,
                        std::unordered_map<orderedPair, ll> &&memo = {}) {
  // Recursive

  // auto it = memo.find(orderedPair(rows, cols));
  // if (it != memo.end()) {
  //   return it->second;
  // }
  // if (rows == 0 || cols == 0) {
  //   return 0L;
  // }
  // if (rows == 1 && cols == 1) {
  //   return 1L;
  // }

  // ll result_tmp = gridTravelerEnhanced(rows - 1, cols, std::move(memo)) +
  //                 gridTravelerEnhanced(rows, cols - 1, std::move(memo));
  // memo.insert(std::make_pair(orderedPair(rows, cols), result_tmp));
  // memo.insert(std::make_pair(orderedPair(cols, rows), result_tmp));
  // return result_tmp;

  // Iteration

  // specialization
  if (rows == 0 || cols == 0) {
    return 0L;
  }
  if (rows == 1 || cols == 1) {
    return 1L;
  }

  // basic requirements
  memo.reserve(rows * cols);
  for (int i = 0; i <= rows; i++) {
    memo.insert(std::make_pair(orderedPair(i, 0), 0L));
  }
  for (int i = 0; i <= cols; i++) {
    memo.insert(std::make_pair(orderedPair(0, i), 0L));
  }
  memo.insert(std::make_pair(orderedPair(1, 1), 1L));

  for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= cols; j++) {
      if (memo.find(orderedPair(i, j)) != memo.end()) {
        continue;
      }
      memo.insert(
          std::make_pair(orderedPair(i, j), memo[orderedPair(i - 1, j)] +
                                                memo[orderedPair(i, j - 1)]));
      memo.insert(
          std::make_pair(orderedPair(j, i), memo[orderedPair(i - 1, j)] +
                                                memo[orderedPair(i, j - 1)]));
    }
  }
  return memo[orderedPair(rows, cols)];
}

int main(int argc, char const *argv[]) {
  cout << gridTravelerEnhanced(1, 1) << endl;
  cout << gridTravelerEnhanced(2, 3) << endl;
  cout << gridTravelerEnhanced(3, 2) << endl;
  cout << gridTravelerEnhanced(3, 3) << endl;
  cout << gridTravelerEnhanced(5, 4) << endl;
  cout << gridTravelerEnhanced(4, 5) << endl;
  cout << gridTravelerEnhanced(18, 18) << endl;
  cout << gridTravelerEnhanced(20, 20) << endl;
  return 0;
}