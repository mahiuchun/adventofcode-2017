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

std::pair<long, int> Backtrack(
    int u, const std::vector<std::string>& comps,
    const std::unordered_map<int, std::vector<std::string>>& valid,
    std::unordered_set<std::string>& used, long sofar, int len) {
  long best = sofar;
  int best_len = len;
  for (const auto& cand : valid.at(u)) {
    if (used.find(cand) == used.end()) {
      used.insert(cand);
      const auto parts = Split(cand, "/");
      int v = std::stoi(parts.at(0));
      int w = std::stoi(parts.at(1));
      if (v != u) std::swap(v, w);
      sofar += v + w;
      const auto [new_strength, new_len] =
          Backtrack(w, comps, valid, used, sofar, len + 1);
      if (new_len > best_len) {
        best = new_strength;
        best_len = new_len;
      } else if (new_len == best_len) {
        best = std::max(best, new_strength);
      }
      sofar -= v + w;
      used.erase(cand);
    }
  }
  return {best, best_len};
}

int main() {
  std::string line;
  std::vector<std::string> comps;
  std::unordered_map<int, std::vector<std::string>> valid;
  while (std::getline(std::cin, line)) {
    const auto parts = Split(line, "/");
    int u = std::stoi(parts.at(0));
    int v = std::stoi(parts.at(1));
    if (u != v) {
      valid[u].push_back(line);
      valid[v].push_back(line);
    } else {
      valid[u].push_back(line);
    }
    comps.push_back(line);
  }
  std::unordered_set<std::string> used;
  std::cout << Backtrack(0, comps, valid, used, 0, 0).first << "\n";
}
