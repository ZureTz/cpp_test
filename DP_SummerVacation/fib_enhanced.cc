#include <iostream>
#include <unordered_map>
#include <utility>
typedef long long ll;

class Fibo {
public:
  static ll fibo(int n, std::unordered_map<int, ll> &&memo = {}) {
    auto it = memo.find(n);
    if (it != memo.end()) {
      return it->second;
    }
    if (n <= 2) {
      return 1L;
    }
    memo.insert(std::make_pair(n, fibo(n - 1, std::move(memo)) +
                                      fibo(n - 2, std::move(memo))));
    return memo[n];
  }
};

int main(int argc, char const *argv[]) {
  for (int i = 1; i < 52; i++) {
    std::cout << i << ": " << Fibo::fibo(i) << std::endl;
  }
  return 0;
}