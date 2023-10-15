#include <cstddef>
#include <iostream>
#include <limits>
#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
typedef long long ll;

#define DEBUG false

constexpr size_t charNum = 26;
constexpr ll modNum = 998244353ll;

struct stringCmp {
  bool operator()(const std::string &s1, const std::string &s2) const {
    if (s1.length() == s2.length()) {
      return s1 < s2;
    }
    return s1.length() < s2.length();
  }
};

std::set<std::string, stringCmp> dict;
std::unordered_map<char, char> map;
std::vector<std::set<std::string, stringCmp>> res(1005);

std::string encode(const std::string &str) {
  std::string res;
  for (const char ch : str) {
    res.append(1, map[ch]);
  }
  return res;
}

bool isValid(const std::string &encodedStrComb) {
  for (const std::string &word : dict) {
    if (encodedStrComb.find(word) != std::string::npos) {
      return false;
    }
    if (word.length() > encodedStrComb.length()) {
      return true;
    }
  }
  return true;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  size_t nPages, mLength;
  cin >> nPages >> mLength;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // assume that nPages == 1 (the book has only one page)
  for (size_t i = 0; i < charNum; i++) {
    std::string temp;
    for (size_t j = 0; j < nPages; j++) {
      cin >> temp;
      map[temp.front()] = char('a' + i);
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
#if DEBUG
  cout << "Encrypt map: " << std::endl;
  for (size_t i = 0; i < charNum; i++) {
    (cout).put('a' + i) << ' ' << map['a' + i] << std::endl;
  }
#endif

  while (cin.good()) {
    std::string temp;
    std::getline(cin, temp);
    dict.insert(temp);
  }
#if DEBUG
  cout << "dict: " << std::endl;
  for (const auto &word : dict) {
    cout << word << std::endl;
  }
#endif
  for (const auto &word : dict) {
    std::string temp = encode(word);
    if (!isValid(temp)) {
      continue;
    }
    res[temp.length()].insert(temp);
  }
#if DEBUG
  cout << "encrypto: " << std::endl;
  for (const auto &enc : encrypto) {
    cout << enc << std::endl;
  }
#endif

  res[0].insert("");
  for (size_t i = 1; i <= mLength; i++) {
    for (size_t j = 1; j <= i; j++) {
      for (const auto &lhs : res[j]) {
        for (const auto &rhs : res[i - j]) {
          std::string temp = lhs + rhs;
          if (!isValid(temp)) {
            continue;
          }
          res[i].insert(temp);
        }
      }
    }
    cout << res[i].size() % modNum << std::endl;
  }

  return 0;
}