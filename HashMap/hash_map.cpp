#include "hash_map.h"

HashMap::Node::Node(std::string value) : value_(value), next_node_(nullptr) {}
HashMap::Node::Node(const HashMap::Node& node) : value_(node.value_),
                                                 next_node_(node.next_node_) {}
HashMap::Node::~Node() = default;

HashMap::Node* HashMap::SearchPrev(const std::string& data, bool previous)
const {
  unsigned int hashed = Hash(data, max_size_);
  if (hash_map_[hashed] != nullptr) {
    auto cur = hash_map_[hashed];
    if (cur->value_ == data) {
      return cur;
    }
    while (cur != nullptr) {
      if (!previous && cur->value_ == data) {
        return cur;
      } else if (previous && cur->next_node_->value_ == data) {
        return cur;
      }
      cur = cur->next_node_;
    }
  }
  return nullptr;
}

void HashMap::Replace(Node* node_ptr, bool clear) {
  if (node_ptr != nullptr) {
    auto prev_node = SearchPrev(node_ptr->value_, true);
    if (prev_node == node_ptr) {
      hash_map_[Hash(node_ptr->value_, max_size_)] = node_ptr->next_node_;
    } else {
      prev_node->next_node_ = node_ptr->next_node_;
    }
    --num_of_el_;
  }
  if (!clear && num_of_el_ - 1 < max_size_ / 4) {
    Reorganize(max_size_ / 2, clear);
  }
}

unsigned int HashMap::Hash(const std::string& data, unsigned int capacity)
const {
  return hash_func(data) % capacity;
}

void HashMap::InsertCpy(const std::string& data, unsigned int max_size) {
  ++num_of_el_;
  if (num_of_el_ > max_size) {
    Reorganize(max_size *= 2, false);
  }
  auto node = new Node(data);
  unsigned int hashed = Hash(data, max_size);
  if (hash_map_[hashed] != nullptr) {
    node->next_node_ = hash_map_[hashed];
  }
  hash_map_[hashed] = node;
}

void HashMap::Reorganize(unsigned int new_size, bool clear) {
  if (new_size > max_size_) {
    hash_map_.resize(new_size);
  }
  for (uint32_t j = 0; j < max_size_; ++j) {
    auto i = hash_map_[j];
    while (i != nullptr) {
      auto i_cpy = i;
      if (clear) {
        Replace(i, clear);
        delete i;
      } else if (Hash(i->value_, max_size_) != Hash(i->value_, new_size)) {
        Replace(i, clear);
        InsertCpy(i_cpy->value_, new_size);
      }
      i = i_cpy->next_node_;
    }
  }
  if (new_size < max_size_) {
    hash_map_.resize(new_size);
  }
  max_size_ = new_size;
}

HashMap::HashMap() : hash_map_(max_size_, nullptr) {}

HashMap::HashMap(const HashMap& other) : max_size_(other.max_size_),
                                         num_of_el_(0),
                                         hash_map_(max_size_, nullptr) {
  for (auto& i : other.hash_map_) {
    auto i_cpy = i;
    while (i_cpy != nullptr) {
      Insert(i_cpy->value_);
      i_cpy = i_cpy->next_node_;
    }
  }
}


HashMap::~HashMap() {
  Clear();
}

HashMap::Node* HashMap::Search(const std::string& data) const {
  SearchPrev(data, false);
}

void HashMap::Insert(const std::string& data) {
  InsertCpy(data, max_size_);
}

void HashMap::Delete(const std::string& data) {
  auto to_del = Search(data);
  Replace(to_del, false);
  delete to_del;
}

bool HashMap::IsEmpty() const {
  return !num_of_el_;
}

void HashMap::Clear() {
  Reorganize(2, true);
}

bool operator==(const HashMap& l, const HashMap& r) {
  if (l.num_of_el_ != r.num_of_el_ || l.max_size_ != r.max_size_) {
    return false;
  }
  for (int i = 0; i < l.max_size_; ++i) {
    if ((l.hash_map_[i] == nullptr && r.hash_map_[i] != nullptr) ||
        (l.hash_map_[i] != nullptr && r.hash_map_[i] == nullptr)) {
      return false;
    }
    auto el_l = l.hash_map_[i];
    if (el_l != nullptr) {
      auto el_r = r.hash_map_[i];
      std::vector<std::string> v_r;
      std::vector<std::string> v_l;
      while (el_l != nullptr) {
        v_l.push_back(el_l->value_);
        el_l = el_l->next_node_;
      }
      while (el_r != nullptr) {
        v_r.push_back(el_r->value_);
        el_r = el_r->next_node_;
      }
      std::sort(v_l.begin(), v_l.end());
      std::sort(v_r.begin(), v_r.end());
      if (v_l != v_r) {
        return false;
      }
    }
  }
  return true;
}

bool operator!=(const HashMap& l, const HashMap& r) {
  return !(l == r);
}
