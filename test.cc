#include <cstdlib>
#include <iostream>
#include <sys/_types/_size_t.h>
#include <unordered_map>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  system("git add --all");
  system("git commit -m \"\\\'test.cc\\\' modified\"");
  system("git push -u origin master");
  return 0;
}