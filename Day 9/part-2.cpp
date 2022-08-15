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

long long int find_running_sum(int left, int right, std::vector<long long int> &numbers) {
  long long int sum = 0;
  for (auto i = left; i <= right; i++) {
    sum += numbers[i];
  }
  return sum;
}

long long int find_result(std::vector<long long int>& numbers, int target) {
  for (auto i = 0; i < numbers.size(); i++) {
    for (auto j = i + 1; j < numbers.size(); j++) {
      long long int sum = find_running_sum(i, j, numbers);
      if (sum == target) {
        long long int min = numbers[i];
        long long int max = numbers[i];
        for (auto k = i; k <= j; k++) {
          if (numbers[k] < min) {
            min = numbers[k];
          }
          if (numbers[k] > max) {
            max = numbers[k];
          }
        }
        return min + max;
      }
    }
  }
  return -1;
}

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
  return find_result(numbers, find_invalid(numbers));
}

int main() {
  std::ifstream file(INPUT_FILE, std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
