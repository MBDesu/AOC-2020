#include <map>

#pragma once
namespace map_utils {
  // this is undoubtedly very stupid, but I
  // couldn't figure out how to merge maps
  // using the STL because I am also very stupid
  template <typename K, typename V>
  std::map<K, V> merge(std::map<K, V> m, std::map<K, V> n) {
    std::map<K, V> merged_map;
    std::map<K, V>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
      merged_map.emplace(it->first, it->second);
    }
    for (it = n.begin(); it != n.end(); it++) {
      K key = it->first;
      V value = it->second;
      if (merged_map.find(key) != merged_map.end()) {
        merged_map[key] += value;
      } else {
        merged_map.emplace(key, value);
      }
    }
    return merged_map;
  }
}
