#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

bool IsPrime(long x) {
  for (long i = 2; i <= std::sqrt(x); i++) {
    if (x % i == 0) return false;
  }
  return true;
}

class Program {
 public:
  void AddLine(std::string_view line) { lines.push_back(std::string(line)); }
  void Next() {
    std::istringstream iss;
    iss.str(lines.at(pc_));
    std::string op;
    iss >> op;
    char r;
    long y;
    if (op == "set") {
      iss >> r;
      y = Read(iss);
      regs_[r - 'a'] = y;
    } else if (op == "sub") {
      iss >> r;
      y = Read(iss);
      regs_[r - 'a'] -= y;
    } else if (op == "mul") {
      iss >> r;
      y = Read(iss);
      regs_[r - 'a'] *= y;
    } else if (op == "isp") {
      iss >> r;
      y = Read(iss);
      regs_[r - 'a'] = IsPrime(y);

    } else if (op == "jnz") {
      long x = Read(iss);
      y = Read(iss);
      if (x != 0) {
        pc_ += y;
        goto end;
      }
    }
    pc_ += 1;
  end:
    if (pc_ < 0 || pc_ >= lines.size()) {
      terminated_ = true;
    }
  }
  bool Terminated() const { return terminated_; }
  void AToOne() { regs_[0] = 1; }
  long H() const { return regs_['h' - 'a']; }

 private:
  long Read(std::istringstream &iss) {
    std::string tok;
    iss >> tok;
    if (islower(tok[0])) {
      return regs_[tok[0] - 'a'];
    } else {
      return std::stol(tok);
    }
  }
  std::vector<std::string> lines;
  long regs_[26] = {0};
  int pc_ = 0;
  bool terminated_ = false;
};

int main() {
  std::string line;
  Program p;
  while (std::getline(std::cin, line)) {
    p.AddLine(line);
  }
  p.AToOne();
  while (!p.Terminated()) {
    p.Next();
  }
  std::cout << p.H() << "\n";
}
