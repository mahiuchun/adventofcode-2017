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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct Action {
  int write_value;
  int move;
  int next_state;
};

struct StateDef {
  Action action0;
  Action action1;
};

StateDef example[] = {
    {{1, 1, 1}, {0, -1, 1}},
    {{1, -1, 0}, {1, 1, 0}},
};

StateDef input[] = {
    {{1, 1, 1}, {0, -1, 2}}, {{1, -1, 0}, {1, 1, 3}},  {{0, -1, 1}, {0, -1, 4}},
    {{1, 1, 0}, {0, 1, 1}},  {{1, -1, 5}, {1, -1, 2}}, {{1, 1, 3}, {1, 1, 0}},
};

long Turing(const StateDef defs[], int ndefs, int steps) {
  std::unordered_map<int, int> tape;
  int state = 0;
  int pos = 0;
  while (steps--) {
    int val = tape[pos];
    if (val == 0) {
      tape[pos] = defs[state].action0.write_value;
      pos += defs[state].action0.move;
      state = defs[state].action0.next_state;
    } else {
      tape[pos] = defs[state].action1.write_value;
      pos += defs[state].action1.move;
      state = defs[state].action1.next_state;
    }
  }
  long res = 0;
  for (const auto& [idx, val] : tape) {
    res += val;
  }
  return res;
}

int main() {
  std::cerr << "Example: " << Turing(example, 2, 6) << "\n";
  std::cerr << "Input: " << Turing(input, 2, 12667664) << "\n";
}
