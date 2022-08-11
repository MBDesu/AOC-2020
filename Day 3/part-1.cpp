#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const char TREE = '#';

int parse_file(std::ifstream& file) {
  std::vector<std::string> map;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    map.push_back(line);
  }
  int x = 0;
  int sum = 0;
  for (auto y = 1; y < map.size(); y++) {
    x = (x + 3) % map[y].size();
    sum += map[y][x] == TREE;
  }
  return sum;
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
