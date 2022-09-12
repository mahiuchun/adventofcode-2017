#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
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

int main() {
	std::string line;
	std::map<int, int> layers;
	while (std::getline(std::cin, line)) {
		auto nums = Split(line, ": ");
		layers[std::stoi(nums[0])] = std::stoi(nums[1]);
	}
	std::map<int, int> states;
	std::map<int, int> signs;

	for (auto it = layers.begin(); it != layers.end(); ++it) {
		states[it->first] = 0;
		signs[it->first] = 1;
	}
	int severity = 0;
	for (int pos = 0; pos <= layers.rbegin()->first; ++pos) {
		auto it = layers.find(pos);
		if (it != layers.end() && states.at(pos) == 0) {
			severity += pos * layers[pos];
			// std::cerr << "states.at(" << pos << ")=" << states.at(pos) << "\n";
		}
		for (auto it = states.begin(); it != states.end(); ++it) {
			it->second += signs[it->first];
			if (it->second == 0 || it->second == layers[it->first]-1) {
				signs[it->first] *= -1;
			}
		}
	}
	std::cout << severity << "\n";
}
