#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int parse_file(std::ifstream& file) {
  return 0;
}

int main() {
  std::ifstream file("sample.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
