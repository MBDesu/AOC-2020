#include <string>
#include <vector>
#include <map>

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

  int unique_chars(const std::string& s) {
    std::string unique = "";
    for (auto& c : s) {
      if (unique.find(c) == std::string::npos) {
        unique += c;
      }
    }
    return unique.size();
  }

  std::map<char, int> char_frequencies(const std::string& s) {
    std::map<char, int> frequencies;
    for (auto& c : s) {
      if (frequencies.find(c) == frequencies.end()) {
        frequencies[c] = 1;
      } else {
        frequencies[c]++;
      }
    }
    return frequencies;
  }

  int count(const std::string& s, const std::string& substring) {
    int count = 0;
    std::string::size_type pos = 0;
    while ((pos = s.find(substring, pos)) != std::string::npos) {
      count++;
      pos += substring.length();
    }
    return count;
  }

}