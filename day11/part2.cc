#include <algorithm>
#include <cctype>
#include <iostream>
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

int Dist(int x, int y) {
	if (x * y >= 0) {
		return std::abs(x) + std::abs(y);
	} else {
		return std::max(std::abs(x), std::abs(y));
	}
}

int main() {
	std::string s;
	while (std::getline(std::cin, s)) {
		int x = 0;
		int y = 0;
		auto moves = Split(s, ",");
		int furthest = 0;
		for (const auto& move : moves) {
			if (move == "n") {
				y += 1;
			} else if (move == "s") {
				y -= 1;
			} else if (move == "nw") {
				x -= 1;
				y += 1;
			} else if (move == "sw") {
				x -= 1;
			} else if (move == "se") {
				x += 1;
				y -= 1;
			} else if (move == "ne") {
				x += 1;
			} else {
				throw std::invalid_argument("'" + move + "' is not a valid move!");
			}
			furthest = std::max(furthest, Dist(x, y));
		}
		std::cout << furthest << "\n";
	}
}
