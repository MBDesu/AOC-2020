#include "../string_utils.hpp"
#include <iostream>
#include <fstream>

bool password_is_valid(const std::string& password, const std::string& letter, int min, int max) {
  int count = 0;
  for (char c : password) {
    if (c == letter[0]) {
      count++;
    }
  }
  return count >= min && count <= max;
}

int parse_file(std::ifstream& file) {
  int sum = 0;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    std::vector<std::string> tokens = string_utils::split(line, " -:");
    if (password_is_valid(tokens[3], tokens[2], std::stoi(tokens[0]), std::stoi(tokens[1]))) {
      sum++;
    }
  }
  return sum;
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
