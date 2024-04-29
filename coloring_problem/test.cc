// https://twitter.com/MLKE139115/status/1784607081150169566

// 今日排列组合2/1：
// 一个正方体，用五种颜色染它的八个顶点，要求同一棱两端顶点颜色不同，求方法数 :D

#include <iostream>
#include <vector>

// colors
enum colorType {
  null,
  a,
  b,
  c,
  d,
  e,
};

const std::vector<colorType> types = {
    colorType::a, colorType::b, colorType::c, colorType::d, colorType::e,
};

struct boxNode {
  colorType color;

  boxNode() { color = colorType::null; }
};

auto box = std::vector<std::vector<std::vector<boxNode>>>(
    2, std::vector<std::vector<boxNode>>(2, std::vector<boxNode>(2)));

bool isNodeSatisfied(const int x, const int y, const int z) {
  const auto node = box[x][y][z];
  if (node.color == colorType::null) {
    std::cerr << "Color null\n";
    return false;
  }
  return (node.color != box[!x][y][z].color) &&
         (node.color != box[x][!y][z].color) &&
         (node.color != box[x][y][!z].color);
  // std::cout << "Color not null\n";
};

bool isBoxSatisfied() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        if (isNodeSatisfied(i, j, k) == false) {
          return false;
        }
      }
    }
  }
  // std::cout << "Box satisfied\n";
  return true;
}

void assign(long long &count, const int index) {
  if (index > 0b111) {
    count += (isBoxSatisfied() ? 1 : 0);
    // std::cout << count << '\r';
    return;
  }

  const int x = (index & 0b100) >> 2, y = (index & 0b010) >> 1,
            z = index & 0b001;
  // std::cout << index<<' '<< x<<y<<z<<std::endl;

  for (const auto color : types) {
    box[x][y][z].color = color;
    assign(count, index + 1);
  }
}

int main(int argc, char const *argv[]) {
  long long count = 0;
  assign(count, 0);
  std::cout << count << std::endl;

  return 0;
}