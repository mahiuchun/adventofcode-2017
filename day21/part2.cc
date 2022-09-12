#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
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

using Pattern = std::vector<std::string>;
using Rule = std::pair<Pattern, Pattern>;

class Image {
 public:
  Image(int size) : size_(size), img_(size * size) {
    for (int i = 0; i < img_.size(); ++i) {
      img_[i] = '.';
    }
  }
  char& At(int i, int j) { return img_[size_ * i + j]; }
  char At(int i, int j) const { return img_[size_ * i + j]; }
  int Size() const { return size_; }
  int Count() const {
    int res = 0;
    for (int i = 0; i < img_.size(); ++i) {
      if (img_[i] == '#') res += 1;
    }
    return res;
  }
  bool Match(int ii, int jj, const Pattern& p) const {
    return Match0(ii, jj, p) || Match1(ii, jj, p) || Match2(ii, jj, p) ||
           Match3(ii, jj, p) || Match4(ii, jj, p) || Match5(ii, jj, p) ||
           Match6(ii, jj, p) || Match7(ii, jj, p);
  }
  void Fill(int ii, int jj, const Pattern& p) {
    for (int i = ii; i < ii + p.size(); ++i) {
      for (int j = jj; j < jj + p[0].size(); ++j) {
        At(i, j) = p[i - ii][j - jj];
      }
    }
  }
  void DebugPrint() const {
    for (int i = 0; i < img_.size(); ++i) {
      if (i != 0 && i % size_ == 0) std::cerr << "\n";
      std::cerr << img_[i];
    }
    std::cerr << "\n";
  }

 private:
  bool Match0(int ii, int jj, const Pattern& p) const {
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < p[0].size(); ++j) {
        if (At(ii + i, jj + j) != p[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  bool Match1(int ii, int jj, const Pattern& p) const {
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < p[0].size(); ++j) {
        if (At(ii + i, jj + j) != p[p.size() - j - 1][i]) {
          return false;
        }
      }
    }
    return true;
  }
  bool Match2(int ii, int jj, const Pattern& p) const {
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < p[0].size(); ++j) {
        if (At(ii + i, jj + j) != p[p.size() - i - 1][p.size() - j - 1]) {
          return false;
        }
      }
    }
    return true;
  }
  bool Match3(int ii, int jj, const Pattern& p) const {
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < p[0].size(); ++j) {
        if (At(ii + i, jj + j) != p[j][p.size() - i - 1]) {
          return false;
        }
      }
    }
    return true;
  }
  bool Match4(int ii, int jj, const Pattern& p) const {
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < p[0].size(); ++j) {
        if (At(ii + i, jj + j) != p[p.size() - i - 1][j]) {
          return false;
        }
      }
    }
    return true;
  }
  bool Match5(int ii, int jj, const Pattern& p) const {
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < p[0].size(); ++j) {
        if (At(ii + i, jj + j) != p[i][p.size() - j - 1]) {
          return false;
        }
      }
    }
    return true;
  }
  bool Match6(int ii, int jj, const Pattern& p) const {
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < p[0].size(); ++j) {
        if (At(ii + i, jj + j) != p[j][i]) {
          return false;
        }
      }
    }
    return true;
  }
  bool Match7(int ii, int jj, const Pattern& p) const {
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < p[0].size(); ++j) {
        if (At(ii + i, jj + j) != p[p.size() - j - 1][p.size() - i - 1]) {
          return false;
        }
      }
    }
    return true;
  }
  int size_;
  std::vector<char> img_;
};

std::vector<std::string> Split(std::string_view s, std::string_view sep) {
  std::vector<std::string> res;
  std::string tok;
  for (int i = 0; i < s.length(); ++i) {
    if (sep.find(s[i]) == std::string_view::npos) {
      tok += s[i];
    } else {
      if (!tok.empty()) {
        res.push_back(tok);
        tok.clear();
      }
    }
  }
  if (!tok.empty()) {
    res.push_back(tok);
  }
  return res;
}

Pattern Parse(std::string_view s) { return Split(s, "/"); }

int main() {
  std::string line;
  std::vector<Rule> two_rules;
  std::vector<Rule> three_rules;
  while (std::getline(std::cin, line)) {
    const auto parts = Split(line, " =>");
    Pattern lhs = Parse(parts.at(0));
    Pattern rhs = Parse(parts.at(1));
    if (lhs[0].size() % 2 == 0) {
      two_rules.push_back({lhs, rhs});
    } else {
      three_rules.push_back({lhs, rhs});
    }
  }
  Image curr(3);
  curr.At(0, 1) = '#';
  curr.At(1, 2) = '#';
  curr.At(2, 0) = '#';
  curr.At(2, 1) = '#';
  curr.At(2, 2) = '#';
  for (int i = 0; i < 18; ++i) {
    int new_size;
    if (curr.Size() % 2 == 0) {
      new_size = curr.Size() / 2 * 3;
    } else if (curr.Size() % 3 == 0) {
      new_size = curr.Size() / 3 * 4;
    } else {
      throw std::invalid_argument("Size is invalid!");
    }
    Image next(new_size);
    if (curr.Size() % 2 == 0) {
      for (int i = 0; i < curr.Size(); i += 2) {
        for (int j = 0; j < curr.Size(); j += 2) {
          bool matched = false;
          for (const auto& rule : two_rules) {
            if (curr.Match(i, j, rule.first)) {
              next.Fill(i / 2 * 3, j / 2 * 3, rule.second);
              matched = true;
              break;
            }
          }
          if (!matched)
            throw std::invalid_argument("No match found at (" +
                                        std::to_string(i) + "," +
                                        std::to_string(j) + ")!");
        }
      }
    } else {
      for (int i = 0; i < curr.Size(); i += 3) {
        for (int j = 0; j < curr.Size(); j += 3) {
          bool matched = false;
          for (const auto& rule : three_rules) {
            if (curr.Match(i, j, rule.first)) {
              next.Fill(i / 3 * 4, j / 3 * 4, rule.second);
              matched = true;
              break;
            }
          }
          if (!matched) {
            throw std::invalid_argument("No match found at (" +
                                        std::to_string(i) + "," +
                                        std::to_string(j) + ")!");
          }
        }
      }
    }
    std::swap(curr, next);
    // std::cerr << "Iteration " << i + 1 << "\n";
    // curr.DebugPrint();
  }
  std::cout << curr.Count() << "\n";
}
