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
  Program(int id) { regs_['p' - 'a'] = id; }
  void AddLine(std::string_view line) { lines.push_back(std::string(line)); }
  bool Ready() {
    if (terminated_) return false;
    std::istringstream iss;
    iss.str(lines.at(pc_));
    std::string op;
    iss >> op;
    if (op == "rcv") {
      return !queue_.empty();
    } else {
      return true;
    }
  }
  void Next() {
    std::istringstream iss;
    iss.str(lines.at(pc_));
    std::string op;
    iss >> op;
    char r;
    long y;
    if (op == "snd") {
      other_->Enqueue(Read(iss));
      count_ += 1;
    } else if (op == "set") {
      iss >> r;
      y = Read(iss);
      regs_[r - 'a'] = y;
    } else if (op == "add") {
      iss >> r;
      y = Read(iss);
      regs_[r - 'a'] += y;
    } else if (op == "mul") {
      iss >> r;
      y = Read(iss);
      regs_[r - 'a'] *= y;
    } else if (op == "mod") {
      iss >> r;
      y = Read(iss);
      regs_[r - 'a'] %= y;
    } else if (op == "rcv") {
      iss >> r;
      regs_[r - 'a'] = queue_.front();
      queue_.pop_front();
    } else if (op == "jgz") {
      long x = Read(iss);
      y = Read(iss);
      if (x > 0) {
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
  int SendCount() { return count_; }
  void Enqueue(long val) { queue_.push_back(val); }
  void SetOther(Program *other) { other_ = other; }

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
  std::deque<long> queue_;
  int pc_ = 0;
  int count_ = 0;
  bool terminated_ = false;
  Program *other_ = nullptr;
};

int main() {
  std::string line;
  Program p0(0);
  Program p1(1);
  p0.SetOther(&p1);
  p1.SetOther(&p0);
  while (std::getline(std::cin, line)) {
    p0.AddLine(line);
    p1.AddLine(line);
  }
  while (p0.Ready() || p1.Ready()) {
    while (p0.Ready()) p0.Next();
    while (p1.Ready()) p1.Next();
  }
  std::cout << p1.SendCount() << "\n";
}
