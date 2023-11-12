#include <iostream>
#include <vector>

struct point {
  int x, y;
  char type;
  point(int x = 0, int y = 0, char type = '\0') : x(x), y(y), type(type) {}
};

struct line {
  int arg1, arg2, arg3;
  line(int arg1 = 0, int arg2 = 0, int arg3 = 0)
      : arg1(arg1), arg2(arg2), arg3(arg3) {}
};

// 检测所有的点是否在直线的同一边
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

  // 输入所有点
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

  // 输入直线
  for (int i = 0; i < test; i++) {
    int temp_arg1, temp_arg2, temp_arg3;
    std::cin >> temp_arg1 >> temp_arg2 >> temp_arg3;
    test_lines.emplace_back(temp_arg1, temp_arg2, temp_arg3);
  }
  // 按照每条线，对于两个点集A和B，判断是否满足要求
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