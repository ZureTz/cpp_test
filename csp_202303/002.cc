#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  int num_of_field, resource, min_time;
  cin >> num_of_field >> resource >> min_time;

  auto fields = new int[num_of_field][2];

  int max_time = 0;
  for (int i = 0; i < num_of_field; i++) {
    for (int j = 0; j < 2; j++) {
      cin >> fields[i][j];
    }
    max_time = fields[i][0] > max_time ? fields[i][0] : max_time;
  }

  do {
    if (max_time == min_time) {
      cout << max_time;
      break;
    }

    int pred_resouce(0);
    for (int i = 0; i < num_of_field; i++) {
      if (fields[i][0] == max_time) {
        pred_resouce += fields[i][1];
      }
    }

    if (pred_resouce > resource) {
      cout << max_time;
      break;
    } else if (pred_resouce == resource) {
      cout << max_time - 1;
      break;
    }

    resource -= pred_resouce;
    for (int i = 0; i < num_of_field; i++) {
      if (fields[i][0] == max_time) {
        fields[i][0]--;
      }
    }
  } while (max_time--);

  delete[] fields;
  return 0;
}