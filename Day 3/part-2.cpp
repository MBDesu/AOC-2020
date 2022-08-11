#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const char TREE = '#';

int num_trees(const std::vector<std::string>& map, int right, int down) {
  int num_trees = 0;
  int x = 0;
  int y = 0;
  while (y < map.size()) {
    if (map[y][x] == TREE) {
      num_trees++;
    }
    x = (x + right) % map[0].size();
    y += down;
  }
  return num_trees;
}

int parse_file(std::ifstream& file) {
  std::vector<std::string> map;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    map.push_back(line);
  }
  return num_trees(map, 1, 1) * num_trees(map, 3, 1) * num_trees(map, 5, 1) * num_trees(map, 7, 1) * num_trees(map, 1, 2);
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
