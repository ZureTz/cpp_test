#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string oriCode;
  std::getline(cin, oriCode);
  int code = (oriCode.back() == 'X') ? 10 : (oriCode.back() - '0');
  oriCode.erase(oriCode.end() - 2, oriCode.end());
  // cout << code << std::endl;

  std::stringstream ss(oriCode);

  std::string numStr;
  std::string part1, part2, part3;
  std::getline(ss, part1, '-');
  std::getline(ss, part2, '-');
  std::getline(ss, part3, '-');
  numStr = part1 + part2 + part3;
  // cout << '\"' << part1 << '\"' << std::endl;
  // cout << '\"' << part2 << '\"' << std::endl;
  // cout << '\"' << part3 << '\"' << std::endl;
  // cout << '\"' << numStr << '\"' << std::endl;

  int tempCode(0), count(1);
  for (const char ch : numStr) {
    tempCode += ((ch - '0') * count);
    count++;
  }
  tempCode %= 11;
  // cout << tempCode << ' ' << code << std::endl;

  if (code != tempCode) {
    cout << part1 << '-' << part2 << '-' << part3 << '-'
         << (tempCode == 10 ? "X" : std::to_string(tempCode)) << std::endl;
  } else {
    cout << "Right" << std::endl;
  }

  return 0;
}