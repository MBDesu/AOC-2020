#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "../string_utils.hpp"
#include "../vector_utils.hpp"

const std::vector<std::string> REQUIRED_FIELDS = {
  "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
};

void parse_fields(const std::string& passport, std::vector<std::string>& fields) {
  std::vector<std::string> tokens = string_utils::split(passport, " ");
  for (auto& token : tokens) {
    std::vector<std::string> key_value = string_utils::split(token, ":");
    fields.push_back(key_value[0]);
  }
}

bool is_valid_passport(std::string& passport) {
  std::vector<std::string> fields;
  parse_fields(passport, fields);
  for (auto& required_field : REQUIRED_FIELDS) {
    if (!vector_utils::contains(fields, required_field)) {
      return false;
    }
  }
  return true;
}

void parse_passport(std::ifstream& file, std::string& passport) {
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    if (line.empty()) {
      break;
    }
    passport += line + " ";
  }
}

int parse_file(std::ifstream& file) {
  int valid_passports = 0;
  std::vector<std::string> fields = {};
  while (!file.eof()) {
    std::string passport = "";
    parse_passport(file, passport);
    valid_passports += is_valid_passport(passport);
  }
  return valid_passports;
}

int main() {
  std::ifstream file("input.txt", std::ios::in); 
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
