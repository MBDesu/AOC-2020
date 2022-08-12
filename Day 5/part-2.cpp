#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../vector_utils.hpp"

const int ROWS = 128;
const int COLS = 8;

int find_my_seat(std::vector<int>& seat_ids) {
  for (auto i = 0; i < seat_ids.size() - 1; i++) {
    for (auto j = i + 1; j < seat_ids.size(); j++) {
      bool is_candidate = abs(seat_ids[i] - seat_ids[j]) == 2;
      int id = std::max(seat_ids[i], seat_ids[j]) - 1;
      if (is_candidate && !vector_utils::contains(seat_ids, id)) return id;
    }
  }
  return -1;
}

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
  std::vector<int> seat_ids;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    seat_ids.push_back(calculate_seat_id(line));
  }
  return find_my_seat(seat_ids);
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
