#include <iostream>
#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
using std::cin;
using std::cout;

struct UserData {
  int day;
  int index;
  int area;
  UserData(int day = 0, int index = 0, int area = 0)
      : day(day), index(index), area(area) {}
};

struct dataComp {
  bool operator()(const UserData &d1, const UserData &d2) const {
    return std::tie(d1.index, d1.day, d1.area) <
           std::tie(d2.index, d2.day, d2.area);
  }
};

inline bool isQualified(const int time, const std::pair<int, int> &timeSeq) {
  return timeSeq.first <= time && time <= timeSeq.second;
}

std::unordered_map<int, std::pair<int, int>> mapRiskArea;
std::set<UserData, dataComp> last7DaysData;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  mapRiskArea.reserve(1010);

  int nDays;
  cin >> nDays;

  for (int day = 0; day < nDays; day++) {
    int nRiskArea, nMessages;
    cin >> nRiskArea >> nMessages;

    for (int j = 0; j < nRiskArea; j++) {
      int areaIndex;
      cin >> areaIndex;

      auto it = mapRiskArea.find(areaIndex);
      // if not found:
      // pair represents [begin, end], if "begin <= day <= end" it is in risky
      // area.
      if (it == mapRiskArea.end()) {
        mapRiskArea.insert({areaIndex, {day, day + 6}});
        continue;
      }
      // if found:
      // if the day is in the sequence, or the day is continious to the end day
      // of the sequence before
      if (day <= (it->second.second + 1)) {
        it->second.second = day + 6;
        continue;
      }
      // otherwise it becomes another sequence
      it->second.first = day;
      it->second.second = day + 6;
    }

    // for (auto it = riskyUsers.begin(); it != riskyUsers.end(); it++) {
    //   if (it->day < day - 6) {
    //     continue;
    //   }

    //   auto mapIt = mapRiskArea.find(it->area);
    //   // if not found
    //   if (mapIt == mapRiskArea.end()) {
    //     continue;
    //   }
    //   // if found
    //   // if this day not qualified
    //   if (!(isQualified(it->day, mapIt->second) &&
    //         isQualified(day, mapIt->second))) {
    //     continue;
    //   }
    //   // if until this day, still qualified
    //   tempData.insert(*it);
    // }
    // riskyUsers.swap(tempData);

    // check the data before.
    // throw unqualified
    std::set<UserData, dataComp> allUserDataTemp;
    for (auto it = last7DaysData.begin(); it != last7DaysData.end(); it++) {
      if (it->day < day - 6) {
        continue;
      }
      allUserDataTemp.insert(*it);
    }

    for (int j = 0; j < nMessages; j++) {
      int userDay, userIndex, userArea;
      cin >> userDay >> userIndex >> userArea;
      allUserDataTemp.insert(UserData(userDay, userIndex, userArea));

      // auto it = mapRiskArea.find(userArea);
      // // if not found:
      // if (it == mapRiskArea.end()) {
      //   continue;
      // }

      // // if found
      // // if not qualified
      // if (!(isQualified(userDay, it->second) && isQualified(day,
      // it->second))) {
      //   continue;
      // }
      // // otherwise it is qualified
      // riskyUsers.insert(UserData(userDay, userIndex, userArea));
    }
    last7DaysData.swap(allUserDataTemp);

    std::set<UserData, dataComp> tempRiskData;
    for (const auto &data : last7DaysData) {
      if (data.day < day - 6) {
        continue;
      }

      auto mapIt = mapRiskArea.find(data.area);
      // if not found
      if (mapIt == mapRiskArea.end()) {
        continue;
      }
      // if found but not qualified
      if (!(isQualified(data.day, mapIt->second) &&
            isQualified(day, mapIt->second))) {
        continue;
      }
      // if found and qualified
      tempRiskData.insert(data);
    }

    cout << day << ' ';
    // scaning again, output the data
    int prevIndexTemp = -1;
    for (const UserData &userData : tempRiskData) {
      if (userData.index == prevIndexTemp) {
        continue;
      }
      prevIndexTemp = userData.index;
      cout << userData.index << ' ';
    }
    cout << std::endl;
  }

  return 0;
}