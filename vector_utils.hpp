#include <vector>

#pragma once
namespace vector_utils {
  template <typename T>
  bool contains(std::vector<T> v, T t) {
    return std::find(v.begin(), v.end(), t) != v.end();
  }

  template <typename T>
  int index_of(std::vector<T> v, T t) {
    for (auto i = 0; i < v.size(); i++) {
      if (v[i] == t) {
        return i;
      }
    }
    return -1;
  }

  template <typename T>
  void print(std::vector<T> v) {
    std::cout << "[";
    int len = v.size();
    for (auto i = 0; i < v.size(); i++) {
      std::cout << v[i];
      if (i != len - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "]" << std::endl;
  }

}

