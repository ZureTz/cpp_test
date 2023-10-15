#include <cstring>
#include <iostream>
using namespace std;

struct trip_plan {
  static int covid_delay;
  int time_enter;
  int covid_requirement;
  trip_plan *next;

public:
  trip_plan(int time, int covid_req)
      : time_enter(time), covid_requirement(covid_req), next(nullptr) {}
  bool in_sequence(int covid_test_time) {
    return covid_test_time + covid_delay <= time_enter &&
           time_enter <= covid_test_time + covid_delay + covid_requirement - 1;
  }
};

int trip_plan::covid_delay = 0;
int main(int argc, char const *argv[]) {
  int trips, searchs;
  cin >> trips >> searchs >> trip_plan::covid_delay;

  trip_plan *head;
  {
    int t_i, c_i;
    cin >> t_i >> c_i;
    head = new trip_plan(t_i, c_i);
  }
  trip_plan *ptr = head;
  for (int i = 1; i < trips; i++) {
    int t_i, c_i;
    cin >> t_i >> c_i;
    ptr->next = new trip_plan(t_i, c_i);
    ptr = ptr->next;
  }

  // for (trip_plan *ptr = head; ptr->next != nullptr; ptr = ptr->next) {
  //   cout << ptr->min << " " << ptr->max << endl;
  // }

  auto search_list = new int[searchs][2]();
  // for a specifiec search:
  // index = 0: covid test time;
  // index = 1: valid trip count(from 0).
  for (int i = 0; i < searchs; i++) {
    cin >> search_list[i][0];
  }

  // for (int i = 0; i < searchs; i++) {
  //   cout << search_list[i][0] << " " << search_list[i][1] << endl;
  // }

  for (int i = 0; i < searchs; i++) {
    for (trip_plan *ptr = head; ptr != nullptr; ptr = ptr->next) {
      search_list[i][1] += ptr->in_sequence(search_list[i][0]);
    }
  }

  for (int i = 0; i < searchs; i++) {
    cout << search_list[i][1] << endl;
  }

  return 0;
}