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

#define DEBUG true

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
std::set<std::string, stringCmp> encrypto;
std::unordered_map<char, char> map;
std::vector<std::set<std::string>> dp(1005);

std::string encode(const std::string &str) {
  std::string res;
  for (const char ch : str) {
    res.append(1, map[ch]);
  }
  return res;
}

bool isValid(const std::string &encodedStrComb) {
  for (const std::string &word : dict) {
    if (word.length() > encodedStrComb.length()) {
      continue;
    }
    if (encodedStrComb.find(word) != std::string::npos) {
      return false;
    }
  }
  return true;
}

// ll decodeCount(size_t length) {
//   if (length == 1) {
//     if (dp.find(length) != dp.end()) {
//       return dp[length].size() % modNum;
//     }

//     dp[length] = {};
//     for (size_t i = 0; i < charNum; i++) {
//       // if the original string contains the character in dict:
//       if (dict.find(std::string() + char('a' + i)) != dict.end()) {
//         continue;
//       }

//       // find the decoded string in dict:
//       auto it = dict.find(std::string() + map['a' + i]);
//       // if not found
//       if (it == dict.end()) {
//         continue;
//       }
//       // if found
//       dp[length].insert(std::string() + char('a' + i));
//     }
//     return dp[length].size() % modNum;
//   }

//   // else length != 1
//   // if found used data:
//   if (dp.find(length) != dp.end()) {
//     return dp[length].size() % modNum;
//   }

//   // if not found used data,
//   // find previous data:
//   // if not found:
//   if (dp.find(length - 1) == dp.end()) {
//     decodeCount(length - 1);
//   }
//   for (size_t i = 0; i < charNum; i++) {
//     for (const auto &str : dp[length - 1]) {
//       auto prefix = char('a' + i) + str;
//       if (dict.find(prefix) != dict.end()) {
//         continue;
//       }
//       std::string temp(prefix);
//       decode(temp);
//       if (!isValid(temp)) {
//         continue;
//       }
//       dp[length].insert(prefix);
//     }
//     for (const auto &str : dp[length - 1]) {
//       auto suffix = str + char('a' + i);
//       if (dict.find(suffix) != dict.end()) {
//         continue;
//       }
//       decode(suffix);
//       if (!isValid(suffix)) {
//         continue;
//       }
//     }
//   }
//   return (dp[length - 1].size() + dp[length].size()) % modNum;
// }

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
    encrypto.insert(temp);
    dp[temp.length()].insert(temp);
  }
#if DEBUG
  cout << "encrypto: " << std::endl;
  for (const auto &enc : encrypto) {
    cout << enc << std::endl;
  }
#endif

  dp[0].insert("");
  for (size_t i = 1; i <= mLength; i++) {
    for (size_t j = 1; j <= i; j++) {
      for (const auto &lhs : dp[j]) {
        for (const auto &rhs : dp[i - j]) {
          std::string temp = lhs + rhs;
          if (!isValid(temp)) {
            continue;
          }
          dp[i].insert(temp);
        }
      }
    }
    cout << dp[i].size() % modNum << std::endl;
  }

  return 0;
}