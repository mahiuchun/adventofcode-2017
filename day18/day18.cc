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

long regs[26];

long Read(std::istringstream& iss) {
  std::string tok;
  iss >> tok;
  if (islower(tok[0])) {
    return regs[tok[0] - 'a'];
  } else {
    return std::stol(tok);
  }
}

int main() {
  std::string line;
  long last = 0;
  std::vector<std::string> program;
  while (std::getline(std::cin, line)) {
    program.push_back(line);
  }
  int pc = 0;
  while (0 <= pc && pc < program.size()) {
    std::istringstream iss;
    iss.str(program.at(pc));
    std::string op;
    iss >> op;
    char r;
    long y;
    if (op == "snd") {
      last = Read(iss);
    } else if (op == "set") {
      iss >> r;
      y = Read(iss);
      regs[r - 'a'] = y;
    } else if (op == "add") {
      iss >> r;
      y = Read(iss);
      regs[r - 'a'] += y;
    } else if (op == "mul") {
      iss >> r;
      y = Read(iss);
      regs[r - 'a'] *= y;
    } else if (op == "mod") {
      iss >> r;
      y = Read(iss);
      regs[r - 'a'] %= y;
    } else if (op == "rcv") {
      iss >> r;
      long x = regs[r - 'a'];
      if (x != 0) {
        regs[r - 'a'] = last;
        break;
      }
    } else if (op == "jgz") {
      long x = Read(iss);
      y = Read(iss);
      if (x > 0) {
        pc += y;
        continue;
      }
    }
    pc += 1;
  }
  std::cout << last << "\n";
}
