#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "../string_utils.hpp"

// TODO: finish this
struct edge;

struct node {
  std::string name;
  std::vector<edge> neighbors;
};

struct edge {
  node* neighbor;
  int weight;
};

class weighted_digraph {
  public:
    std::map<std::string, node> nodes;

    void add_node(std::string name, node node) {
      nodes.emplace(name, node);
    }

    void add_edge(std::string from, std::string to, int weight) {
      if (nodes.find(from) == nodes.end()) {
        nodes.emplace(from, node{from, {}});
      }
      if (nodes.find(to) == nodes.end()) {
        nodes.emplace(to, node{to, {}});
      }
      nodes.at(from).neighbors.push_back(edge{&nodes.at(to), weight});
    }
};

void visit_neighbors(weighted_digraph& graph, std::string& from, std::vector<std::string>& visited) {
  visited.push_back(from);
  for (auto& neighboring_node : graph.nodes.at(from).neighbors) {
    if (std::find(visited.begin(), visited.end(), neighboring_node.neighbor->name) == visited.end()) {
      visit_neighbors(graph, neighboring_node.neighbor->name, visited);
    }
  }
}

unsigned long long int sum_num_bags(weighted_digraph& graph, std::string from, std::vector<std::string>& visited) {
  unsigned long long int sum = 0;
  visit_neighbors(graph, from, visited);
  for (auto& neighbor : graph.nodes.at(from).neighbors) {
    sum += neighbor.weight + neighbor.weight * sum_num_bags(graph, neighbor.neighbor->name, visited);
  }
  return sum;
}

int parse_file(std::ifstream& file) {
  weighted_digraph graph;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    std::vector<std::string> tokens = string_utils::split(line, " ");
    int num_containing_bags = string_utils::count(line, std::string(",")) + 1;
    if (num_containing_bags == 1 && tokens[4] == "no") {
      continue;
    }
    std::string bag = tokens[0] + " " + tokens[1];
    for (int i = 0; i < num_containing_bags; i++) {
      int num_bags = std::stoi(tokens[4 + i * 4]);
      std::string containing_bag = tokens[5 + i * 4] + " " + tokens[6 + i * 4];
      std::cout << bag << " contains " << num_bags << " " << containing_bag << " bags" << std::endl;
      for (int j = 0; j < num_bags; j++) {
        graph.add_edge(bag, containing_bag, num_bags);
      }
    }
  }
  std::vector<std::string> visited;
  return sum_num_bags(graph, "shiny gold", visited);
}

int main() {
  std::ifstream file("sample.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
