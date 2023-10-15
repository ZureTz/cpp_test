#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

class Bracket {
public:
  static inline bool isLeftBracket(const char ch) {
    return ch == '(' || ch == '[' || ch == '{';
  };
  static inline bool isRightBracket(const char ch) {
    return ch == ')' || ch == ']' || ch == '}';
  };

  static inline bool isPaired(const char left, const char right) {
    return (left == '(' && right == ')') || (left == '[' && right == ']') ||
           (left == '{' && right == '}');
  };
};

bool isAllMatched(const std::string &str) {
  std::stack<char> leftBrackets;
  for (const char ch : str) {
    if (Bracket::isLeftBracket(ch)) {
      leftBrackets.push(std::move(ch));
      continue;
    }

    if (leftBrackets.empty()) {
      return false;
    }

    if (!Bracket::isPaired(leftBrackets.top(), ch)) {
      return false;
    }

    leftBrackets.pop();
  }
  return leftBrackets.empty();
}

int main(int argc, char const *argv[]) {
  std::cout << (isAllMatched(std::string(argv[1])) ? "true" : "false");
  return 0;
}