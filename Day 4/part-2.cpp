#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "../string_utils.hpp"
#include "../vector_utils.hpp"

const std::vector<std::string> REQUIRED_FIELDS = {
  "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
};

bool is_field_required(const std::string& field) {
  return vector_utils::contains(REQUIRED_FIELDS, field);
}

bool has_all_required_fields(const std::map<std::string, std::string>& fields) {
  for (auto& required_field : REQUIRED_FIELDS) {
    if (fields.find(required_field) == fields.end()) {
      return false;
    }
  }
  return true;
}

bool is_field_valid(const std::string& field_name, const std::string& field_value) {
  if (!is_field_required(field_name)) {
    return true;
  }
  if (field_name == "byr") {
    int year = std::stoi(field_value);
    return year >= 1920 && year <= 2002;
  } else if (field_name == "iyr") {
    int year = std::stoi(field_value);
    return year >= 2010 && year <= 2020;
  } else if (field_name == "eyr") {
    int year = std::stoi(field_value);
    return year >= 2020 && year <= 2030;
  } else if (field_name == "hgt") {
    std::string unit = field_value.substr(field_value.size() - 2);
    int height = std::stoi(field_value.substr(0, field_value.size() - 2));
    if (unit == "cm") {
      return height >= 150 && height <= 193;
    } else if (unit == "in") {
      return height >= 59 && height <= 76;
    } else {
      return false;
    }
  } else if (field_name == "hcl") {
    if (field_value[0] != '#') {
      return false;
    }
    std::string color = field_value.substr(1);
    if (color.size() != 6) {
      return false;
    }
    for (auto& c : color) {
      if (!std::isxdigit(c)) {
        return false;
      }
    }
    return true;
  } else if (field_name == "ecl") {
    std::vector<std::string> valid_colors = {
      "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
    };
    return vector_utils::contains(valid_colors, field_value);
  } else if (field_name == "pid") {
    if (field_value.size() != 9) {
      return false;
    }
    for (auto& c : field_value) {
      if (!std::isdigit(c)) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

void parse_fields(const std::string& passport, std::map<std::string, std::string>& fields) {
  std::vector<std::string> tokens = string_utils::split(passport, " ");
  for (auto& token : tokens) {
    std::vector<std::string> key_value = string_utils::split(token, ":");
    std::string field_name = key_value[0];
    std::string field_value = key_value[1];
    fields.emplace(field_name, field_value);
  }
}

bool is_valid_passport(std::string& passport) {
  std::map<std::string, std::string> fields;
  parse_fields(passport, fields);
  if (!has_all_required_fields(fields)) {
    return false;
  }
  for (auto& field : fields) {
    if (!is_field_valid(field.first, field.second)) {
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
