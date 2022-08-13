#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "../vector_utils.hpp"
#include "../string_utils.hpp"

struct node {
  std::string name;
  std::vector<node> neighbors;
};

class directed_graph {
  public:
    std::map<std::string, node> nodes;

    void add_node(std::string name, node node) {
      nodes.emplace(name, node);
    }

    void add_edge(std::string from, std::string to) {
      if (nodes.find(from) == nodes.end()) {
        nodes.emplace(from, node{from, {}});
      }
      if (nodes.find(to) == nodes.end()) {
        nodes.emplace(to, node{to, {}});
      }
      nodes.at(from).neighbors.push_back(nodes.at(to));
    }

    void remove_node(std::string name) {
      nodes.erase(name);
    }

    void remove_edge(std::string from, std::string to) {
      for (auto it = nodes[from].neighbors.begin(); it != nodes[from].neighbors.end(); ++it) {
        if ((*it).name == to) {
          nodes[from].neighbors.erase(it);
          break;
        }
      }
    }
};

std::vector<std::string> find_path(directed_graph& graph, std::string& from, std::string& to) {
  std::vector<std::string> path;
  std::vector<std::string> visited;
  std::vector<std::string> queue;
  queue.push_back(from);
  while (queue.size() > 0) {
    std::string current = queue[0];
    queue.erase(queue.begin());
    if (current == to) {
      path.push_back(current);
      return path;
    }
    if (vector_utils::contains(visited, current)) {
      continue;
    }
    visited.push_back(current);
    for (auto neighbor : graph.nodes[current].neighbors) {
      std::vector<std::string> new_path = path;
      new_path.push_back(current);
      std::vector<std::string> neighbor_path = find_path(graph, neighbor.name, to);
      if (neighbor_path.size() > 0) {
        new_path.insert(new_path.end(), neighbor_path.begin(), neighbor_path.end());
        return new_path;
      }
    }
  }
  return path;
}

int sum_num_paths_to(directed_graph& graph, std::string& bag) {
  int sum = 0;
  for (auto graph_node : graph.nodes) {
    std::string node_name = graph_node.first;
    if (node_name == bag) {
      continue;
    }
    std::vector<std::string> path = find_path(graph, node_name, bag);
    if (path.size() > 0) {
      sum++;
    }
  }
  return sum;
}

int parse_file(std::ifstream& file) {
  directed_graph graph;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    std::vector<std::string> tokens = string_utils::split(line, " ");
    long int num_containing_bags = string_utils::count(line, std::string(",")) + 1;
    if (num_containing_bags == 1 && tokens[4] == "no") {
      continue;
    }
    std::string bag = tokens[0] + " " + tokens[1];
    for (int i = 0; i < num_containing_bags; i++) {
      // int num_bags = std::stoi(tokens[4 + i * 4]);
      std::string containing_bag = tokens[5 + i * 4] + " " + tokens[6 + i * 4];
      // for (int j = 0; j < num_bags; j++) {
        graph.add_edge(bag, containing_bag);
      // }
    }
  }
  return sum_num_paths_to(graph, std::string("shiny gold"));
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
