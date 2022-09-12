#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr int kTimes = 2017;

class Spinlock {
 public:
  Spinlock(int step) : step_(step), curr_(0), pos_(0), list_({0}) {}

  void Insert() {
    if (list_.size() <= 10) {
      DebugPrint();
    }
    curr_ += 1;
    pos_ = (pos_ + step_) % list_.size() + 1;
    auto it = list_.begin();
    for (int i = 0; i < pos_; i++) {
      it++;
    }
    list_.insert(it, curr_);
  }

  std::vector<int> Values() {
    std::vector<int> res;
    res.insert(res.begin(), list_.begin(), list_.end());
    return res;
  }

 private:
  void DebugPrint() {
    const auto xs = Values();
    for (int i = 0; i < xs.size(); i++) {
      if (i != 0) std::cerr << " ";
      if (i == pos_) std::cerr << "(";
      std::cerr << xs[i];
      if (i == pos_) std::cerr << ")";
    }
    std::cerr << "\n";
  }
  int step_;
  int curr_;
  int pos_;
  std::list<int> list_;
};

int main() {
  int n;
  std::cin >> n;
  Spinlock spinlock(n);
  for (int i = 0; i < kTimes; ++i) {
    spinlock.Insert();
  }
  const auto xs = spinlock.Values();
  for (int i = 0; i < xs.size(); i++) {
    if (xs[i] == 2017) {
      std::cout << xs[(i + 1) % xs.size()] << "\n";
    }
  }
}
