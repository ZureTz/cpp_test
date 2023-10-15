#include <iostream>
using std::cin;
using std::cout;

struct BinaryTree {
  int data;
  BinaryTree *left;
  BinaryTree *right;
  explicit BinaryTree(int data, BinaryTree *left = nullptr,
                      BinaryTree *right = nullptr)
      : data(data), left(left), right(right) {}
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  

  return 0;
}