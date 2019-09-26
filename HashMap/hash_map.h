#ifndef HASHMAP_HASHMAP_H
#define HASHMAP_HASHMAP_H

#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <fstream>
#include <map>
#include <algorithm>

class HashMap {
 private:
  struct Node {
    std::string value_;
    Node* next_node_ = nullptr;
    explicit Node(std::string value);
    Node(const Node& node);
    ~Node();
  };
  unsigned int max_size_ = 2;
  unsigned int num_of_el_ = 0;
  std::vector<Node*> hash_map_;
  std::hash<std::string> hash_func;

  Node* SearchPrev(const std::string& data, bool previous) const;

  unsigned int Hash(const std::string& data, unsigned int capacity) const;

  void InsertCpy(const std::string& data, unsigned int max_size);

  void Reorganize(unsigned int new_size, bool clear);

  void Replace(Node*, bool);

 public:

  HashMap();
  HashMap(const HashMap&);
  ~HashMap();

  Node* Search(const std::string& data) const;

  void Insert(const std::string& data);

  void Delete(const std::string& data);

  bool IsEmpty() const;

  void Clear();

  friend bool operator==(const HashMap&, const HashMap&);
  friend bool operator!=(const HashMap&, const HashMap&);
};

#endif //HASHMAP_HASHMAP_H
