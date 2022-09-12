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

using Graph = std::map<int, std::set<int>>;

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

void Dfs(const Graph& g, int u, std::set<int>& seen) {
	if (seen.find(u) != seen.end()) return;
	seen.insert(u);
	for (int v : g.at(u)) {
		Dfs(g, v, seen);
	}
}

int main() {
	Graph g;
	std::string line;
	while (std::getline(std::cin, line)) {
		std::istringstream iss;
		iss.str(line);
		int u;
		iss >> u;
		std::string w;
		iss >> w;  // DISCARD
		std::string rest;
		while (iss >> w) {
			rest += w;
		}
		for (const auto &w : Split(rest, ",")) {
			int v = std::stoi(w);
			g[u].insert(v);
			g[v].insert(u);
		}
	}
	std::set<int> seen;
	int counter = 0;
	for (auto it = g.begin(); it != g.end(); it++) {
		int u = it->first;
		if (seen.find(u) == seen.end()) {
			Dfs(g, u, seen);
			counter += 1;
		}
	}
	std::cout << counter << "\n";
}
