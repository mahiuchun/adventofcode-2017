#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <set>
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

std::vector<int> Hash(std::string_view s) {
	const auto lens = Parse(s);
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

bool Used(const std::vector<std::vector<int>>& grid, int i, int j) {
	return grid[i][j/8] & (1<<(7-j%8));
}

void DfsImpl(const std::vector<std::vector<int>>& grid, int i, int j, std::set<std::pair<int,int>>& seen) {
	if (i < 0 || i >= grid.size()) return;
	if (j < 0 || j >= grid.size()) return ;
	if (!Used(grid, i, j)) return;
	if (seen.find({i, j}) != seen.end()) {
		return;
	}
	seen.insert({i, j});
	DfsImpl(grid, i-1, j, seen);
	DfsImpl(grid, i+1, j, seen);
	DfsImpl(grid, i, j-1, seen);
	DfsImpl(grid, i, j+1, seen);
}

int Dfs(const std::vector<std::vector<int>>& grid) {
	int res = 0;
	std::set<std::pair<int,int>> seen;
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			if (Used(grid, i, j) && seen.find({i, j}) == seen.end()) {
				DfsImpl(grid, i, j, seen);
				res += 1;
			}
		}
	}
	return res;
}

int main() {
	std::string s;
	while (std::getline(std::cin, s)) {
		std::vector<std::vector<int>> grid;
		for (int i = 0; i < 128; ++i) {
			grid.push_back(Hash(s + "-" + std::to_string(i)));
		}
		std::cout << Dfs(grid) << "\n";
	}
}
