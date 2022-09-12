#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

bool anagrams(std::string_view a, std::string_view b) {
  if (a.length() != b.length()) return false;
  int count[26] = {0};
  for (int i = 0; i < a.length(); ++i) {
    count[a[i]-'a'] += 1;
    count[b[i]-'a'] -= 1;
  }
  for (int i = 0; i < 26; i++) {
    if (count[i] != 0) return false;
  }
  return true;
}

bool check(const std::vector<std::string>& list) {
  for (int i = 0; i < list.size(); ++i) {
    for (int j = i+1; j < list.size(); ++j) {
      if (anagrams(list[i], list[j])) return false; 
    }
  }
  return true;
}

int main() {
	std::string s;
  int tot = 0;
  while (std::getline(std::cin, s)) {
    std::istringstream iss;
    iss.str(s);
    std::string w;
    std::vector<std::string> list;
    while (iss >> w) {
      list.push_back(w);
    }
    tot += check(list);
  }
  
  std::cout << tot << "\n";
}