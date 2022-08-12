#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../string_utils.hpp"

void get_next_group(std::ifstream& file, std::string& group) {
  group = "";
  std::string line;
  while (std::getline(file, line)) {
    if (line == "") {
      break;
    }
    group += line;
  }
}

int parse_file(std::ifstream& file) {
  int sum = 0;
  while (!file.eof()) {
    std::string group;
    get_next_group(file, group);
    sum += string_utils::unique_chars(group);
  }
  return sum;
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
