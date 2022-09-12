#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::vector<int> Parse(std::string_view s) {
	std::vector<int> res;
	std::string tok;
	for (int i = 0; i < s.length(); ++i) {
		if (std::isdigit(s[i])) {
			tok += s[i];
		} else {
			if (!tok.empty()) {
				res.push_back(std::stoi(tok));
				tok.clear();
			}
		}
	}
	if (!tok.empty()) {
		res.push_back(std::stoi(tok));
	}
	return res;
}

void Reverse(std::vector<int>& list, int i, int j) {
	while (i < j) {
		std::swap(list[i%list.size()], list[j%list.size()]);
		i++;
		j--;
	}
}

int Solve(const std::vector<int>& lens, int size) {
	std::vector<int> list(size);
	for (int i = 0; i < size; ++i) {
		list[i] = i;
	}
	int pos = 0;
	int skip = 0;
	for (auto len : lens) {
		Reverse(list, pos, pos + len - 1);
		/* for (int i = 0; i < size; ++i) {
			if (i != 0) std::cerr << ", ";
			std::cerr << list[i];
		}
		std::cerr << "\n"; */
		pos += len + skip;
		pos %= size;
		skip += 1;
	}
	return list.at(0) * list.at(1);
}

int main() {
	std::string s;
	std::getline(std::cin, s);
	const auto lens = Parse(s);
	// Hack for testing the sample
	int sol;
	if (lens.size() == 4) {
		sol = Solve(lens, 5);
	} else {
		sol = Solve(lens, 256);
	}
	std::cout << sol << "\n";
}
