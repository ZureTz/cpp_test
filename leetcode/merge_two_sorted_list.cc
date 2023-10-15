/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <iostream>
#include <ostream>
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    if (list1 == nullptr) {
      return list2;
    }
    if (list2 == nullptr) {
      return list1;
    }

    if (list1->val <= list2->val) {
      list1->next = mergeTwoLists(list1->next, list2);
      return list1;
    }
    list2->next = mergeTwoLists(list1, list2->next);
    return list2;
  }
};

int main(int argc, char const *argv[]) {
  ListNode *head1 = new ListNode(0);
  ListNode *ptr1 = head1;
  for (int i = 0; i < 5; i++) {
    ptr1->next = new ListNode(i + 1);
    ptr1 = ptr1->next;
  }

  ListNode *head2 = new ListNode(0);
  ListNode *ptr2 = head2;
  for (int i = 0; i < 5; i++) {
    ptr2->next = new ListNode(2 * i + 5);
    ptr2 = ptr2->next;
  }

  Solution solution;
  ListNode *result = solution.mergeTwoLists(head1, head2);
  while (result != nullptr) {
    std::cout << result->val << std::endl;
    result = result->next;
  }

  return 0;
}