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

struct Firewall {
	std::map<int, int> layers;
	std::vector<int> fast_layers;

	void Init() {
		int size = layers.rbegin()->first + 1;
		fast_layers.resize(size, -1);
		for (int i = 0; i < size; ++i) {
			if (layers.find(i) != layers.end()) {
				fast_layers[i] = layers[i];
			}
		}
	}
};

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
	Firewall f;
	while (std::getline(std::cin, line)) {
		auto nums = Split(line, ": ");
		f.layers[std::stoi(nums[0])] = std::stoi(nums[1]);
	}
	f.Init();
	int delay = 0;
	for (;;) {
		int i;
		for (i = 0; i < f.fast_layers.size(); ++i) {
			if (f.fast_layers[i] == -1) continue;
			if ((i + delay) % (2*(f.fast_layers[i]-1)) == 0) break;
		}
		if (i == f.fast_layers.size()) break;
		delay += 1;
	}
	std::cout << delay << "\n";
}
