#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
	std::string s;
	long checksum = 0;
	while (std::getline(std::cin, s)) {
		std::istringstream iss;
		iss.str(s);
		std::vector<long> row;
		long x;
		while (iss >> x) {
			row.push_back(x);
		}
		for (int i = 0; i < row.size(); ++i) {
			for (int j = i+1; j < row.size(); ++j) {
				if (row[i] % row[j] == 0) {
					checksum += row[i] / row[j];
					goto found;					
				} else if (row[j] % row[i] == 0) {
					checksum += row[j] / row[i];
					goto found;
				}
			}
		}
found:	
		;
	}
	std::cout << checksum << "\n";
}