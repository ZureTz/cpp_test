#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
using std::cin;
using std::cout;
typedef unsigned int uint_32;

#define DEBUG false

uint_32 uintGetMax(uint_32 num, const uint_32 length);
struct IP {
  uint_32 ip;
  uint_32 len;
  std::pair<uint_32, uint_32> range;

  IP() : ip(0u), len(0u) {}
  IP(uint_32 ip, uint_32 len) : ip(ip), len(len) {
    range = std::make_pair(ip, uintGetMax(ip, len));
  }
  IP(const std::pair<uint_32, uint_32> &rhs) : range(rhs) {
    ip = rhs.first;
    uint_32 temp = rhs.second - rhs.first;
    uint_32 count = 0u;
    for (; temp != 0u; count++) {
      temp /= 2u;
    }
    len = 32u - count;
  }
  bool operator==(const IP &rhs) {
    return range.first == rhs.range.first && range.second == rhs.range.second;
  }
  bool operator!=(const IP &rhs) {
    return range.first != rhs.range.first || range.second != rhs.range.second;
  }
};
bool IPComp(const IP &ip1, const IP &ip2) {
  return std::tie(ip1.ip, ip1.len) < std::tie(ip2.ip, ip2.len);
}
bool isLegal(const IP &rhs) { return (rhs.ip << rhs.len) == 0; }

uint_32 uintGetMax(uint_32 num, const uint_32 length) {
  uint_32 itTimes = 32u - length;
  for (uint_32 i = 0u; i < itTimes; i++) {
    num |= (1u << i);
  }
  return num;
}
uint_32 transfer(const std::deque<std::string> &tokens) {
  if (tokens.size() != 4) {
    return 0u;
  }

  uint_32 resIp = 0u;
  for (int i = 0; i < 4; i++) {
    resIp |= (std::stoi(tokens[i]) << (32 - 8 * (i + 1)));
  }
  return resIp;
}

// input and output
std::istream &operator>>(std::istream &is, IP &rhs) {
  std::string tempStr;
  std::getline(is, tempStr);
  std::stringstream ss(tempStr);
  std::deque<std::string> tempToken(4, "0");

  // 省略长度型
  if (tempStr.find('/') == std::string::npos) {
    int count = 0;
    while (ss.good()) {
      std::getline(ss, tempStr, '.');
      tempToken[count] = tempStr;
      count++;
    }
    rhs.ip = transfer(tempToken);
    rhs.len = 8 * count;
    rhs.range = std::make_pair(rhs.ip, uintGetMax(rhs.ip, rhs.len));

#if DEBUG
    for (const auto &str : tempToken) {
      cout << str << ' ';
    }
    cout << std::setw(8) << std::setfill('0') << std::hex << rhs.ip << std::dec;
    cout << ' ' << rhs.len << std::endl;
    cout << std::hex << rhs.ip << ' ' << uintGetMax(rhs.ip, rhs.len) << std::dec
         << std::endl;
#endif
    return is;
  }

  // 标准型 / 省略后缀型
  std::string tempHead, tempLen;
  std::getline(ss, tempHead, '/');

  std::stringstream tempHeadSS(tempHead);
  int count = 0;
  while (tempHeadSS.good()) {
    std::getline(tempHeadSS, tempStr, '.');
    tempToken[count] = tempStr;
    count++;
  }
  rhs.ip = transfer(tempToken);

  std::getline(ss, tempLen);
  rhs.len = std::stoi(tempLen);
  rhs.range = std::make_pair(rhs.ip, uintGetMax(rhs.ip, rhs.len));

#if DEBUG
  for (const auto &str : tempToken) {
    cout << str << ' ';
  }
  cout << std::setw(8) << std::setfill('0') << std::hex << rhs.ip << std::dec;
  cout << ' ' << rhs.len << std::endl;
  cout << std::hex << rhs.ip << ' ' << uintGetMax(rhs.ip, rhs.len) << std::dec
       << std::endl;
#endif
  return is;
}
std::ostream &operator<<(std::ostream &os, const IP &rhs) {
  uint_32 seg1 = (0xff000000u & rhs.ip) >> 24;
  uint_32 seg2 = (0x00ff0000u & rhs.ip) >> 16;
  uint_32 seg3 = (0x0000ff00u & rhs.ip) >> 8;
  uint_32 seg4 = (0x000000ffu & rhs.ip);

  cout << seg1 << '.' << seg2 << '.' << seg3 << '.' << seg4 << '/' << rhs.len;
  return os;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  // #if DEBUG
  //   IP ip1(std::make_pair(0x0a800000u, 0x0affffffu));
  //   // cin >> ip1;
  //   // cout << std::setw(8) << std::setfill('0') << std::hex << ip1.ip << ' '
  //   //      << std::setw(8) << std::setfill('0') << uintGetMax(ip1.ip,
  //   ip1.len)
  //   //      << std::dec << std::endl;
  //   // cout << ip1;
  //   auto temp = ip1.range();
  //   cout << ip1 << ' ' << std::hex << temp.first << ' ' << temp.second
  //        << std::dec;
  // #endif

  // input
  int n;
  (cin >> n).get();
  if (n == 1) {
    IP temp;
    cin >> temp;
    cout << temp;
    return 0;
  }

  std::list<IP> IPs;
  for (int i = 0; i < n; i++) {
    IP temp;
    cin >> temp;
    IPs.push_back(temp);
  }

  // sort inputted data
  IPs.sort(IPComp);

  // merge 01
  auto it1 = IPs.begin(), it2 = IPs.begin();
  for (++it2; it2 != IPs.end() && IPs.size() > 1; ++it1, ++it2) {
    // if 2 is 1s subset
    if (it2->range.second <= it1->range.second) {
      #if DEBUG
      cout << "2 is sub of 1." << std::endl;
      #endif
      it2 = IPs.erase(it2);
      --it1;
      --it2;
      continue;
    }
  }

  // merge 02
  it1 = IPs.begin();
  it2 = IPs.begin();
  for (++it2; it2 != IPs.end(); ++it1, ++it2) {
    // if len is not the same
    if (it1->len != it2->len) {
      continue;
    }
    // if 1 and 2 dont have intersection or is not continious, the add of 1
    // and 2 is not continious, so throw them
    if (!(it2->range.first <= (it1->range.second + 1))) {
      continue;
    }

    IP temp(it1->ip, it1->len - 1u);
    // if not legal
#if DEBUG
    cout << "check if is legal" << std::endl;
#endif
    if (isLegal(temp) == false) {
      continue;
    }

    // if legal:
    // if not the same
#if DEBUG
    cout << "go" << std::endl;
#endif
    if (temp.range.first != it1->range.first ||
        temp.range.second != it2->range.second) {
      continue;
    }

    // otherwise it is the same
    *it1 = temp;
    it2 = IPs.erase(it2);
    if (it1 == IPs.begin()) {
      --it1;
      --it2;
      continue;
    }
    std::advance(it1, -2);
    std::advance(it2, -2);

    // not viable (might be illegal)
    // // if has intersection but 2 is not 1s subset or 1 and 2 are continious
    // if ((it+1)->range.first <= (it->range.second + 1)) {
    //   *it = IP(std::make_pair(it->range.first, (it+1)->range.second));
    //   IPs.erase(it + 1);
    //   it--;
    //   continue;
    // }
  }

  for (const IP &ip : IPs) {
    cout << ip << std::endl;
  }

  return 0;
}