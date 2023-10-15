#include <cstddef>
#include <iostream>
#include <vector>
struct Subject {
  Subject *requirement;
  int timeCost;
  Subject() : requirement(nullptr), timeCost(1) {}
};

int main(int argc, char const *argv[]) {
  int deadline_days, num_subjects;
  std::cin >> deadline_days >> num_subjects;

  // create array and read in stdin
  std::vector<Subject> subjects(num_subjects);
  for (Subject &subject : subjects) {
    int index;
    std::cin >> index;
    subject.requirement = index ? &subjects.at(index - 1) : nullptr;
  }
  for (Subject &subject : subjects) {
    std::cin >> subject.timeCost;
  }

  // find minimum days foreach subject
  for (const Subject &subject : subjects) {
    int beginDay = 1;
    const Subject *ptr = &subject;
    while (ptr->requirement != nullptr) {
      ptr = ptr->requirement;
      beginDay += ptr->timeCost;
    }
    std::cout << beginDay << ' ';
  }

  // find maximum days foreach subject
  std::vector<int> maxDays(num_subjects);
  bool isAllSatisfied = true;
  for (int i = 0; i < num_subjects; i++) {
    const Subject *ptr = &subjects.at(i);
    int lastDay = deadline_days + 1 - ptr->timeCost;
    int lastDay_beforeCost = lastDay;
    while (ptr->requirement != nullptr) {
      ptr = ptr->requirement;
      lastDay_beforeCost -= ptr->timeCost;
    }

    if (lastDay_beforeCost < 1) {
      isAllSatisfied = false;
      break;
    }
    maxDays.at(i) = lastDay;
  }
  if (isAllSatisfied) {
    std::cout << std::endl;
    for (const int num : maxDays) {
      std::cout << num << ' ';
    }
  }
  return 0;
}