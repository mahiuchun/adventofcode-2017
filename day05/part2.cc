#include <iostream>
#include <vector>

int main() {
  int x;
  std::vector<int> mem;
  while (std::cin >> x) {
    mem.push_back(x);
  }
  int pc = 0;
  long count = 0;
  while (0 <= pc && pc < mem.size()) {
    int old_pc = pc;
    int off;
    pc += (off = mem[pc]);
    if (off >= 3) {
      mem[old_pc] -= 1;
    } else {
      mem[old_pc] += 1;
    }
    count += 1;
  }
  
  std::cout << count << "\n";
}