#include <iostream>
#include <string>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::string inStr;
  std::getline(cin, inStr, '\n');
  int sum = 0;
  for (const char ch : inStr) {
    sum += ch - '0';
  }
  cout << sum; 
  return 0;
}