#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> regs;

bool eval(std::string src, std::string cmp, int i) {
	if (cmp == ">") {
		return regs[src] > i;
	} else if (cmp == "<") {
		return regs[src] < i;
	} else if (cmp == ">=") {
		return regs[src] >= i;
	} else if (cmp == "==") {
		return regs[src] == i;
	} else if (cmp == "<=") {
		return regs[src] <= i;
	} else if (cmp == "!=") {
		return regs[src] != i;
	} else {
		throw std::invalid_argument(cmp + " is not a valid cmp!");
	}
}

int main() {
	std::string line;
	while (std::getline(std::cin, line)) {
		std::istringstream iss;
		iss.str(line);
		std::string dst, op, src, cmp;
		int i1, i2;
		iss >> dst;
		iss >> op;
		iss >> i1;
		iss >> cmp;  // DISCARD
		iss >> src;
		iss >> cmp;
		iss >> i2;
		if (eval(src, cmp, i2)) {
			if (op == "inc") {
				regs[dst] += i1;
			} else {
				regs[dst] -= i1;
			}
		}
	}
	int max = -987654321;
	for (const auto& [key, val] : regs) {
		max = std::max(max, val);
	}
	std::cout << max << "\n";
}
