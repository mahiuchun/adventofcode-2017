#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Generator {
public:
	Generator(int init, int factor): val_(init), factor_(factor) {}

	int Next() {
		val_ = (val_ * factor_) % 2147483647;
		return static_cast<int>(val_);
	}
private:
	long val_;
	int factor_;
};

constexpr int kMask = 0xFFFF;
constexpr int kPairs = 40000000;

int main() {
	std::string s;
	for (int i = 0; i < 5; ++i) {
		std::cin >> s;
	}
	Generator ga(std::stoi(s), 16807);
	for (int i = 0; i < 5; ++i) {
		std::cin >> s;
	}
	Generator gb(std::stoi(s), 48271);
	int count = 0;
	std::cerr << "--Gen. A--  --Gen. B--\n";
	for (int i = 0; i < kPairs; ++i) {
		int va = ga.Next();
		int vb = gb.Next();
		if (i < 5) {
			std::fprintf(stderr, "%10d  %10d\n", va, vb);
		}
		if ((va & kMask) == (vb & kMask)) {
			count += 1;
		}
	}
	std::cout << count << "\n";
}
