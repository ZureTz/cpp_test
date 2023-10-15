#include <iostream>
#include <vector>

struct point {
  int x;
  int y;
  char type;
  point() : x(0), y(0), type('\0') {}
  point(int src_x, int src_y, char src_type)
      : x(src_x), y(src_y), type(src_type) {}
};

struct line {
  int arg1;
  int arg2;
  int arg3;
  line() : arg1(), arg2(), arg3() {}
  line(int targ1, int targ2, int targ3)
      : arg1(targ1), arg2(targ2), arg3(targ3) {}
};

bool eligible_at_one_side(const line &line, const std::vector<point> &points) {
  for (auto it = points.begin() + 1; it != points.end(); ++it) {
    bool prev_stat =
        line.arg1 + line.arg2 * ((it - 1)->x) + line.arg3 * ((it - 1)->y) > 0
            ? true
            : false;
    bool now_stat = line.arg1 + line.arg2 * (it->x) + line.arg3 * (it->y) > 0
                        ? true
                        : false;

    if (prev_stat != now_stat) {
      return false;
    }
  }
  return true;
}

int main(int argc, char const *argv[]) {
  int train = 0, test = 0;
  std::cin >> train >> test;
  std::vector<point> train_points_A;
  std::vector<point> train_points_B;
  std::vector<line> test_lines;

  for (int i = 0; i < train; i++) {
    int temp_x, temp_y;
    char temp_type;
    std::cin >> temp_x >> temp_y >> temp_type;
    if (temp_type == 'A') {
      train_points_A.emplace_back(temp_x, temp_y, temp_type);
    } else if (temp_type == 'B') {
      train_points_B.emplace_back(temp_x, temp_y, temp_type);
    }
  }

  for (int i = 0; i < test; i++) {
    int temp_arg1, temp_arg2, temp_arg3;
    std::cin >> temp_arg1 >> temp_arg2 >> temp_arg3;
    test_lines.emplace_back(temp_arg1, temp_arg2, temp_arg3);
  }

  for (const auto &item : test_lines) {
    bool A_stat = eligible_at_one_side(item, train_points_A);
    bool B_stat = eligible_at_one_side(item, train_points_B);
    if (!(A_stat && B_stat)) {
      std::cout << "No" << std::endl;
      continue;
    }

    int A_side = item.arg1 + item.arg2 * train_points_A.at(0).x +
                             item.arg3 * train_points_A.at(0).y >
                         0
                     ? 1
                     : -1;
    int B_side = item.arg1 + item.arg2 * train_points_B.at(0).x +
                             item.arg3 * train_points_B.at(0).y >
                         0
                     ? 1
                     : -1;
    if (A_side * B_side == 1) {
      std::cout << "No" << std::endl;
      continue;
    }
    std::cout << "Yes" << std::endl;
  }

  return 0;
}