#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using VI = std::vector<int>;
using string = std::string;

string VI_to_s(const VI &vi) {
	std::ostringstream oss;
	for (int i = 0; i < vi.size(); ++i) {
		if (i != 0) oss << ' ';
		oss << vi[i];
	}
	return oss.str();
}

VI S_to_VI(const string& s) {
	std::istringstream iss;
	iss.str(s);
	VI res;
	int x;
	while (iss >> x) {
		res.push_back(x);
	}
	return res;
}

void redistributes(VI& vi) {
	int maxi = 0;
	for (int i = 1; i < vi.size(); ++i) {
		if (vi[i] > vi[maxi]) maxi = i;
	}
	int max = vi[maxi];
	vi[maxi] = 0;
	for (int i = maxi + 1; i <= maxi + max; ++i) {
		int j = i % vi.size();
		vi[j] += 1;
	}
}

int main() {
	string s;
	std::getline(std::cin, s);
	s = VI_to_s(S_to_VI(s));
	auto vi = S_to_VI(s);
	std::unordered_set<string> seen{s};
	int count = 0;
	for (;;) {
		redistributes(vi);
		s = VI_to_s(vi);
		// std::cerr << "s=" << s << "\n";
		count += 1;
		if (seen.find(s) != seen.end()) break;
		seen.insert(s);
	}
	std::cout << count << "\n";
}