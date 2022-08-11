#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int get_result(std::vector<int>& nums, int target) {
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      for (int k = j + 1; k < nums.size(); k++) {
        if (nums[i] + nums[j] + nums[k] == target) {
          return nums[i] * nums[j] * nums[k];
        }
      }
    }
  }
  return -1;
}

int parse_file(std::ifstream& file) {
  std::vector<int> nums;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    nums.push_back(std::stoi(line));
  }
  return get_result(nums, 2020);
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file);
  file.close();
  return 0;
}
