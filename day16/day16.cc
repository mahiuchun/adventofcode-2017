#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Programs {
public:
	Programs(int size) : size_(size), pos_to_name_(size), name_to_pos_(size) {
		for (int i = 0; i < size_; ++i) {
			pos_to_name_[i] = i;
			name_to_pos_[i] = i;
		}
	}
	void Spin(int x) {
		x %= size_;
		Reverse(0, size_ - x - 1);
		Reverse(size_ - x, size_ - 1);
		Reverse(0, size_ - 1);
	}
	void Exchange(int a, int b) {
		// std::cerr << "Exchange " << a << " " << b << "\n";
		std::swap(pos_to_name_[a], pos_to_name_[b]);
		name_to_pos_[pos_to_name_[a]] = a;
		name_to_pos_[pos_to_name_[b]] = b;
	}
	void Partner(int a, int b) {
		Exchange(name_to_pos_[a], name_to_pos_[b]);
	}
	void Print() {
		for (int i = 0; i < size_; ++i) {
			std::cout << char('a' + pos_to_name_[i]);
		}
		std::cout << "\n";
	}
private:
	void Reverse(int i, int j) {
		while (i < j) {
			Exchange(i, j);
			i += 1;
			j -= 1;
		}
	}
	int size_;
	std::vector<int> pos_to_name_;
	std::vector<int> name_to_pos_;
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
	std::string s;
	std::cin >> s;
	std::unique_ptr<Programs> p;
	if (s == "s1,x3/4,pe/b") {
		p = std::make_unique<Programs>(5);
	} else {
		p = std::make_unique<Programs>(16);
	}
	const auto moves = Split(s, ",");
	for (const auto& move : moves) {
		switch (move[0]) {
			case 's': {
				p->Spin(std::stoi(move.substr(1)));
				break;
			}
			case 'x': {
				const auto positions = Split(move.substr(1), "/");
				p->Exchange(std::stoi(positions[0]), std::stoi(positions[1]));
				break;
			}
			case 'p': {
				p->Partner(move[1]-'a', move[3]-'a');
				break;
			}
			default: {
				throw std::invalid_argument("Invalid move: '" + move + "'!");
			}
		}
	}
	p->Print();
}
