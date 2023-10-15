#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct Date {
  int year, month, day, weekDay;
  Date(int year = 1850, int month = 1, int day = 1, int weekDay = 2)
      : year(year), month(month), day(day), weekDay(weekDay) {}

  inline int isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  }

  inline int dayInMonth() const {
    if (month == 4 || month == 6 || month == 9 || month == 11) {
      return 30;
    }
    if (month != 2) {
      return 31;
    }
    return isLeapYear() ? 29 : 28;
  }

  inline bool isLastDay() const { return month == 12 && day == 31; }

  inline void addOneDay() {
    weekDay = (weekDay % 7) + 1;
    day++;

    if (day > dayInMonth()) {
      month++;
      day = 1;
    }
    if (month > 12) {
      year++;
      month = 1;
    }
  }

  Date &operator++() {
    while (!isLastDay()) {
      addOneDay();
    }
    addOneDay();
    return *this;
  }
};

int main(int argc, char const *argv[]) {
  int targetMonth, targetWeedDayCount, targetWeekDay;
  int beginYear, endYear;
  cin >> targetMonth >> targetWeedDayCount >> targetWeekDay;
  cin >> beginYear >> endYear;

  Date date;
  while (date.year < beginYear) {
    date.addOneDay();
  }

  for (; date.year <= endYear; ++date) {
    int count = 0;
    bool isFound(false);

    do {
      if (date.month == targetMonth && date.weekDay == targetWeekDay) {
        count++;
        if (count == targetWeedDayCount && !isFound) {
          cout << std::setw(4) << std::setfill('0')<< date.year << '/' << std::setw(2)<< std::setfill('0') << date.month
               << '/' << std::setw(2) << std::setfill('0')<< date.day << endl;
          isFound = true;
          break;
        }
      }
      date.addOneDay();
    } while (!date.isLastDay());

    if (!isFound) {
      cout << "none" << endl;
    }
  }

  return 0;
}