#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../string_utils.hpp"
#include "../map_utils.hpp"

int find_common_answers(std::map<char, int>& frequencies, int group_size) {
  int common_answers = 0;
  std::map<char, int>::iterator it;
  for (it = frequencies.begin(); it != frequencies.end(); it++) {
    if (it->second == group_size) {
      common_answers++;
    }
  }
  return common_answers;
}

void get_next_group(std::ifstream& file, std::vector<std::string>& group) {
  std::string line;
  while (std::getline(file, line)) {
    if (line == "") {
      break;
    }
    group.push_back(line);
  }
}

int parse_file(std::ifstream& file) {
  int sum = 0;
  while (!file.eof()) {
    std::vector<std::string> group;
    std::map<char, int> frequencies;
    get_next_group(file, group);
    for (auto& s : group) {
      std::map<char, int> group_char_frequencies = string_utils::char_frequencies(s);
      frequencies = map_utils::merge(frequencies, group_char_frequencies);
    }
    sum += find_common_answers(frequencies, group.size());
  }
  return sum;
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
