#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>

int main() {
	std::string line;
	std::unordered_set<std::string> set;
	std::unordered_set<std::string> sub;
	const auto line_re = std::regex(R"(^([a-z]+) \(([0-9]+)\)(.*)$)");
    std::smatch parts;
	while (std::getline(std::cin, line)) {
		std::regex_match(line, parts, line_re);
		if (parts.size() != 4) {
			return -1; // INVALID
		}
		std::string lhs = parts[1].str();
		set.insert(lhs);
		std::string rhs = parts[3].str();
		if (rhs.empty()) continue;
		std::istringstream iss;
		iss.str(rhs);
		std::string w;
		while (iss >> w) {
			if (w == "->") continue;
			if (w.back() == ',') w.pop_back();
			sub.insert(w);
		}
	}
	for (const auto& elem : set) {
		if (sub.find(elem) == sub.end()) {
			std::cout << elem << "\n";
		}
	}
}
