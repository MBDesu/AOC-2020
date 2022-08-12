#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const int ROWS = 128;
const int COLS = 8;

int calculate_partition(std::string& partition) {
  int low = 0;
  int high = partition.size() == 7 ? ROWS : COLS;
  for (auto i = 0; i < partition.size(); i++) {
    if (partition[i] == 'F' || partition[i] == 'L') {
      high -= (high - low) / 2;
    } else {
      low += (high - low) / 2;
    }
  }
  return low;
}

int calculate_seat_id(std::string& seat) {
  int row = calculate_partition(seat.substr(0, 7));
  int col = calculate_partition(seat.substr(7, 3));
  return row * 8 + col;
}

int parse_file(std::ifstream& file) {
  int max = 0;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    max = std::max(max, calculate_seat_id(line));
  }
  return max;
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
