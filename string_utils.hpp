#include <string>
#include <vector>

#pragma once
namespace string_utils {
  void rtrim(std::string& s, const std::string& delimiters = " \f") {
    s.erase(s.find_last_not_of(delimiters) + 1);
  }

  std::vector<std::string> split(const std::string& s, const std::string& delimiters = " \f") {
    std::vector<std::string> tokens;
    std::string::size_type last_pos = s.find_first_not_of(delimiters, 0);
    std::string::size_type pos = s.find_first_of(delimiters, last_pos);
    while (std::string::npos != pos || std::string::npos != last_pos) {
      tokens.push_back(s.substr(last_pos, pos - last_pos));
      last_pos = s.find_first_not_of(delimiters, pos);
      pos = s.find_first_of(delimiters, last_pos);
    }
    return tokens;
  }

  std::string join(const std::vector<std::string>& tokens, const std::string& delimiter = " ") {
    std::string s = "";
    for (auto& token : tokens) {
      s += token + delimiter;
    }
    rtrim(s, delimiter);
    return s;
  }
}