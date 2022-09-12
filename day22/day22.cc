#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

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
  std::set<std::pair<int, int>> infected;
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 0; j < map[0].size(); ++j) {
      if (map[i][j] == '#') {
        infected.insert({i - ci, j - cj});
      }
    }
  }
  Carrier virus;
  long count = 0;
  for (int t = 1; t <= 10000; ++t) {
    if (infected.find({virus.i, virus.j}) == infected.end()) {
      // clean
      virus.TurnL();
      infected.insert({virus.i, virus.j});
      count += 1;
    } else {
      // infected
      virus.TurnR();
      infected.erase({virus.i, virus.j});
    }
    virus.Fwd();
  }
  std::cout << count << "\n";
}
