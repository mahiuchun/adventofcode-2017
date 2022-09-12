#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr int kClean = 0;
constexpr int kWeakened = 1;
constexpr int kInfected = 2;
constexpr int kFlagged = 3;

struct Carrier {
  int i = 0;
  int j = 0;
  int di = -1;
  int dj = 0;
  void TurnL() {
    std::swap(di, dj);
    di *= -1;
  }
  void TurnR() {
    std::swap(di, dj);
    dj *= -1;
  }
  void Fwd() {
    i += di;
    j += dj;
  }
  void Reverse() {
    di *= -1;
    dj *= -1;
  }
};

int main() {
  std::vector<std::string> map;
  std::string line;
  while (std::getline(std::cin, line)) {
    map.push_back(line);
  }
  // std::cerr << map.size() << "x" << map[0].size() << "\n";
  int ci = map.size() / 2;
  int cj = map[0].size() / 2;
  std::map<std::pair<int, int>, int> infected;
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 0; j < map[0].size(); ++j) {
      if (map[i][j] == '#') {
        infected[{i - ci, j - cj}] = kInfected;
      }
    }
  }
  Carrier virus;
  long count = 0;
  for (int t = 1; t <= 10000000; ++t) {
    auto it = infected.find({virus.i, virus.j});
    if (it == infected.end()) {
      virus.TurnL();
      infected[{virus.i, virus.j}] = kWeakened;
    } else if (it->second == kWeakened) {
      count += 1;
      infected[{virus.i, virus.j}] = kInfected;
    } else if (it->second == kInfected) {
      virus.TurnR();
      infected[{virus.i, virus.j}] = kFlagged;
    } else {
      virus.Reverse();
      infected.erase(it);
    }
    virus.Fwd();
  }
  std::cout << count << "\n";
}
