#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

int Majority(std::vector<int> vec) {
	std::sort(vec.begin(), vec.end());
	return vec[vec.size()/2];
}

struct Node {
	std::string name;
	int weight = -1;
	std::vector<std::string> children;
	int sum = -1;
	bool is_root = true;
};

struct Graph {
	void AddNode(std::string name, int weight) {
		Node n;
		n.name = name;
		n.weight = weight;
		nodes[name] = n;
	}

	void AddEdge(const std::string& a, std::string b) {
		nodes[a].children.push_back(std::move(b));
	}

	void ComputeRoot() {
		for (const auto& entry : nodes) {
			for (const auto& name : entry.second.children) {
				nodes[name].is_root = false;
			}
		}
	}

	int ComputeAndCheckSums(const std::string& name) {
		auto& node = nodes.at(name);
		node.sum = node.weight;
		if (!node.children.empty()) {
			std::vector<int> sums;
			sums.reserve(node.children.size());
			for (const auto& child_name : node.children) {
				int bad = ComputeAndCheckSums(child_name);
				if (bad >= 0) {
					return bad;
				}
				node.sum += nodes.at(child_name).sum;
				sums.push_back(nodes.at(child_name).sum);
			}
			int expected = Majority(sums);
			for (const auto& child_name : node.children) {
				if (nodes.at(child_name).sum != expected) {
					return nodes.at(child_name).weight - nodes.at(child_name).sum + expected;
				}
			}
		}
		return -1;
	}

	std::unordered_map<std::string,Node> nodes;
} G;

int main() {
	std::string line;
	const auto line_re = std::regex(R"(^([a-z]+) \(([0-9]+)\)(.*)$)");
    std::smatch parts;
	while (std::getline(std::cin, line)) {
		std::regex_match(line, parts, line_re);
		if (parts.size() != 4) {
			return -1; // INVALID
		}
		std::string lhs = parts[1].str();
		int weight = std::stoi(parts[2].str());
		G.AddNode(lhs, weight);
		std::string rhs = parts[3].str();
		if (rhs.empty()) continue;
		std::istringstream iss;
		iss.str(rhs);
		std::string w;
		while (iss >> w) {
			if (w == "->") continue;
			if (w.back() == ',') w.pop_back();
			G.AddEdge(lhs, w);
		}
	}
	G.ComputeRoot();
	for (const auto& entry : G.nodes) {
		if (entry.second.is_root) {
			std::cout << "'" << entry.second.name << "' -> " << G.ComputeAndCheckSums(entry.second.name) << "\n";
		}
	}
}
