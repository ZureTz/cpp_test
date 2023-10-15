#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  int numOfStudents, numOfChanges;
  cin >> numOfStudents >> numOfChanges;
  std::list<int> students(numOfStudents);

  // using map to avoid searching.
  // if not using map, average searching time complexity == O(n) every time.
  // if using map, average time complexity == O(1) every time.
  // the time complexity of the whole program is enhanced from O(m * n) to O(n).

  // in this line of code, the "vector" functions identically as a map.
  // (instead of "std::unordered_map<int, std::list<int>::iterator> map")
  std::vector<std::list<int>::iterator> map(numOfStudents);
  {
    int count = 1;
    // for (auto &num : students) {
    //   num = count;
    //   count++;
    // }
    for (auto it = students.begin(); it != students.end(); it++) {
      *it = count;
      map[count] = it;
      count++;
    }
  }

  for (int i = 0; i < numOfChanges; i++) {
    int target, displacement;
    cin >> target >> displacement;
    auto temp = map[target];

    /*
    if (q < 0) { // 向前移动 
      auto temp = it; // 创建临时迭代器指向当前要移动的学生
      advance(temp, q); // algorithm库的函数，向前移动迭代器，即确定新位置
      arr.splice(temp, arr, it); // 移动学生到新位置
    } else {  // 向后移动
      auto temp = it; // 创建临时迭代器指向当前要移动的学生
      advance(temp, q + 1); // 向后移动"q + 1"位，因为需要插入到指定学生的后面
      arr.splice(temp, arr, it); // 移动学生到新位置
    }
    */ // equals to:
    std::advance(temp, displacement < 0 ? displacement : displacement + 1);
    students.splice(temp, students, map[target]);
    map[target] = --temp;
    // these line of code uses "?, :" expression, avoiding if&else expression, duplication
    // and indentation to make it more easy to read comparing to above.

    }

    for (const auto num : students) {
      cout << num << ' ';
    }
    cout.put('\n');

    return 0;
  }