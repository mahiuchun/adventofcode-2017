#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

std::string Lex(std::string_view s) {
	std::string res;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] != '!') {
			res += s[i];
		} else {
			i += 1;
		}
	}
	// std::cerr << s << "=>" << res << "\n";
	return res;
}

std::pair<long, int> Score(std::string_view s, int off, int score) {
	long res = 0;
	int idx = off;
	if (s.at(idx) == '{') {
		res += score;
		idx += 1;
		while (s.at(idx) != '}') {
			auto [child_score, len] = Score(s, idx, score + 1);
			res += child_score;
			idx += len;
			if (s.at(idx) == ',') {
				idx++;
			} else if (s.at(idx) != '}') {
				throw std::invalid_argument("Expected ,");
			}
		}
		idx += 1;
	} else if (s.at(idx) == '<') {
		idx += 1;
		while (s.at(idx) != '>') {
			idx += 1;
		}
		idx += 1;
	}
	return {res, idx - off};
}

int main() {
	std::string line;
	long tot = 0;
	while (std::getline(std::cin, line)) {
		line = Lex(line);
		auto [score, len] = Score(line, /*off=*/0, /*score=*/1);
		// std::cerr << line << ", score of " << score << "\n";
		tot += score;
	}
	std::cout << tot << "\n";
}
