#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::vector<int> Parse(std::string_view s) {
	std::vector<int> res;
	for (int i = 0; i < s.length(); ++i) {
		res.push_back(s[i]);
	}
	res.insert(res.end(), {17, 31, 73, 47, 23});
	return res;
}

void Reverse(std::vector<int>& list, int i, int j) {
	while (i < j) {
		std::swap(list[i%list.size()], list[j%list.size()]);
		i++;
		j--;
	}
}

std::vector<int> Hash(const std::vector<int>& lens) {
	std::vector<int> list(256);
	for (int i = 0; i < 256; ++i) {
		list[i] = i;
	}
	int pos = 0;
	int skip = 0;
	for (int k = 0; k < 64; ++k) {
		for (auto len : lens) {
			Reverse(list, pos, pos + len - 1);
			pos += len + skip;
			pos %= 256;
			skip += 1;
		}
	}
	std::vector<int> res(16);
	for (int i = 0; i < 16; ++i) {
		res[i] = 0;
		for (int j = 0; j < 16; ++j) {
			res[i] ^= list[16*i+j];
		}
	}
	return res;
}

void Print(const std::vector<int>& h) {
	for (int x : h) {
		std::printf("%02x", x);
	}
	std::printf("\n");
}

int main() {
	std::string s;
	while (std::getline(std::cin, s)) {
		const auto lens = Parse(s);
		auto h = Hash(lens);
		Print(h);
	}
}
