#include <cmath>
#include <iostream>

constexpr int puzzle = 361527;

int solve(int x) {
	if (x == 1) return 0;
	int root = std::ceil(std::sqrt(x));
	if ((root & 1) == 0) {
		root += 1;
	}
	int lo = (root-2)*(root-2)+1;
	int hi = root*root;
	int quarter = (hi-lo+1) / 4;
	while (x >= lo + quarter) {
		x -= quarter;
	}
	int mid = lo + root/2 - 1;
	return root/2 + std::abs(x-mid);
}

int main() {
	std::cerr << "solve(1)=" << solve(1) << "\n";
	std::cerr << "solve(12)=" << solve(12) << "\n";
	std::cerr << "solve(23)=" << solve(23) << "\n";
	std::cerr << "solve(1024)=" << solve(1024) << "\n";
	std::cout << solve(puzzle) << "\n";
}