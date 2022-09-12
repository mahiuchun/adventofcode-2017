#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

int main() {
	std::string s;
  int tot = 0;
  while (std::getline(std::cin, s)) {
    std::istringstream iss;
    iss.str(s);
    std::string w;
    std::unordered_set<std::string> used;
    while (iss >> w) {
      if (used.find(w) != used.end()) {
        goto invalid;
      }
      used.insert(w);
    }
    tot += 1;
invalid:
    ;
  }
  
  std::cout << tot << "\n";
}