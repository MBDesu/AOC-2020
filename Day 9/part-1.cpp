#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#if 1
  #define INPUT_FILE "input.txt"
  #define PREAMBLE_LENGTH 25
#else
  #define INPUT_FILE "sample.txt"
  #define PREAMBLE_LENGTH 5
#endif

bool is_valid(std::vector<long long int> &preamble, long long int value) {
  for (auto i = 0; i < preamble.size(); i++) {
    for (auto j = i + 1; j < preamble.size(); j++) {
      if (preamble[i] + preamble[j] == value) {
        return true;
      }
    }
  }
  return false;
}

long long int find_invalid(std::vector<long long int> &numbers) {
  for (auto i = 0; i < numbers.size(); i++) {
    std::vector<long long int> slice = std::vector<long long int>(numbers.begin() + i, numbers.begin() + i + PREAMBLE_LENGTH);
    if (!is_valid(slice, numbers[i + PREAMBLE_LENGTH])) {
      return numbers[i + PREAMBLE_LENGTH];
    }
  }
  return -1;
}

long long int parse_file(std::ifstream& file) {
  std::vector<long long int> numbers;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    numbers.push_back(std::stoll(line));
  }
  return find_invalid(numbers);
}

int main() {
  std::ifstream file(INPUT_FILE, std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
