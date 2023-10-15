#include <iostream>
#include <unordered_map>
#include <utility>

int main(int argc, char const *argv[]) {
  std::unordered_map<char, int> mymap{
      {'a', 2},
      {'b', 3},
  };
  std::cout << mymap.find('b')->second << std::endl;

  mymap.insert(std::make_pair('b', 5));
  std::cout << mymap.find('b')->second << std::endl;

  mymap.find('b')->second = 5;
  std::cout << mymap.find('b')->second << std::endl;

  return 0;
}