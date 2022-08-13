#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "../vector_utils.hpp"

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
  // TODO: parse file
  graph.add_edge("light red", "bright white");
  graph.add_edge("light red", "muted yellow");
  graph.add_edge("dark orange", "bright white");
  graph.add_edge("dark orange", "muted yellow");
  graph.add_edge("bright white", "shiny gold");
  graph.add_edge("muted yellow", "shiny gold");
  graph.add_edge("muted yellow", "faded blue");
  graph.add_edge("shiny gold", "dark olive");
  graph.add_edge("shiny gold", "vibrant plum");
  graph.add_edge("dark olive", "faded blue");
  graph.add_edge("dark olive", "dotted black");
  graph.add_edge("vibrant plum", "faded blue");
  graph.add_edge("vibrant plum", "dotted black");
  return sum_num_paths_to(graph, std::string("shiny gold"));
}

int main() {
  std::ifstream file("sample.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
