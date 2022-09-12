#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

int main() {
	std::string s;
	long checksum = 0;
	while (std::getline(std::cin, s)) {
		std::istringstream iss;
		iss.str(s);
		long min = std::numeric_limits<long>::max();
		long max = std::numeric_limits<long>::min();
		long x;
		while (iss >> x) {
			min = std::min(min, x);
			max = std::max(max, x);
		}
		checksum += max - min;
	}
	std::cout << checksum << "\n";
}