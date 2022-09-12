#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

char SafeAt(const std::vector<std::string>& diagram, int i, int j) {
  if (i < 0 || i >= diagram.size() || j < 0 || j >= diagram[0].size()) {
    return ' ';
  } else {
    return diagram[i][j];
  }
}

int main() {
  std::string sol;
  std::vector<std::string> diagram;
  std::string line;
  while (std::getline(std::cin, line)) {
    diagram.push_back(line);
  }
  int i, j, di, dj;
  for (j = 0; j < diagram[0].size(); ++j) {
    if (diagram[0][j] == '|') {
      i = 0;
      di = 1;
      dj = 0;
      break;
    }
  }
  if (j == diagram[0].size()) {
    throw std::invalid_argument("Cannot find starting point!");
  }
  while (i >= 0 && i < diagram.size() && j >= 0 && j < diagram[0].size()) {
    // std::cerr << "i=" << i << " j=" << j << "\n";
    if (diagram[i][j] == '+') {
      if (di != 0) {
        di = 0;
        for (dj = -1; dj <= 1; dj += 2) {
          if (SafeAt(diagram, i + di, j + dj) != ' ') {
            break;
          }
        }
      } else if (dj != 0) {
        dj = 0;
        for (di = -1; di <= 1; di += 2) {
          if (SafeAt(diagram, i + di, j + dj) != ' ') {
            break;
          }
        }
      }
    } else {
      if (isalpha(diagram[i][j])) {
        sol += diagram[i][j];
      }
    }
    i += di;
    j += dj;
  }
  std::cout << sol << "\n";
}
