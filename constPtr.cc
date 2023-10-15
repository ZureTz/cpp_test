#include <iostream>
using std::cin;
using std::cout;

struct Node {
  int data;
  Node *next;
  Node(int data, Node *next = nullptr) : data(data), next(next) {}
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  Node *const head = new Node(0);
  {
    auto p = head;
    for (int i = 0; i < 25; i++) {
      p->next = new Node(i);
      p = p->next;
    }
  }

  for (auto ptr = head->next; ptr != nullptr; ptr = ptr->next) {
    cout << ptr->data << ' ';
  }

  return 0;
}