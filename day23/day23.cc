#include <algorithm>
#include <cctype>
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
      count_ += 1;
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
  int Count() const { return count_; }

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
  int count_ = 0;
  bool terminated_ = false;
};

int main() {
  std::string line;
  Program p;
  while (std::getline(std::cin, line)) {
    p.AddLine(line);
  }
  while (!p.Terminated()) {
    p.Next();
  }
  std::cout << p.Count() << "\n";
}
