#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using std::cin;
using std::cout;

struct Student {
  int number;
  int score;
  Student(int number, int score) : number(number), score(score) {}
};

struct StudentCmp {
  inline bool operator()(const Student &s1, const Student &s2) const {
    if (s1.score == s2.score) {
      return s1.number < s2.number;
    }
    return s1.score > s2.score;
  }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nStudents, mGenshins, kScoreMax;
  cin >> nStudents >> mGenshins >> kScoreMax;
  std::vector<std::set<Student, StudentCmp>> set(mGenshins);
  for (int i = 1; i <= nStudents; ++i) {
    int genshinIndex;
    Student student(i, 0);
    cin >> genshinIndex >> student.score;
    set[genshinIndex - 1].insert(student);
  }

  for (const auto &genshin : set) {
    if (genshin.empty()) {
      cout << "-1\n";
      continue;
    }
    for (const auto &student : genshin) {
      cout << student.number << ' ';
    }
    cout << '\n';
  }

  return 0;
}