#include <iostream>
#include <string>
#include <string_view>

int solve(std::string_view s) {
	int res = 0;
	for (int i = 0; i < s.length(); i++) {
		int j = (i + 1) % s.length();
		if (s[i] == s[j]) res += s[i] - '0';
	}
	return res;
}

int main() {
	std::string s;
	std::cin >> s;
	std::cout << solve(s) << "\n";
	return 0;
}