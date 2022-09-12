#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

constexpr int kTimes = 50000000;

class Spinlock {
 public:
  Spinlock(int step) : step_(step), curr_(0), pos_(0), ans_(-1) {}

  void Insert() {
    curr_ += 1;
    pos_ = (pos_ + step_) % curr_ + 1;
    if (pos_ == 1) {
      ans_ = curr_;
    }
  }

  int Answer() { return ans_; }

 private:
  int step_;
  int curr_;
  int pos_;
  int ans_;
};

int main() {
  int n;
  std::cin >> n;
  Spinlock spinlock(n);
  for (int i = 0; i < kTimes; ++i) {
    spinlock.Insert();
  }
  std::cout << spinlock.Answer() << "\n";
}
