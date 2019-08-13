#ifndef BIDIRECTIONALLIST_LIST_H
#define BIDIRECTIONALLIST_LIST_H

#include <vector>
#include <functional>
#include <algorithm>

template<typename T>
class BiDirectionalList {
 protected:
  struct Node;

 public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
   public:
    T& operator*() const;
    T* operator->() const;

    Iterator& operator++();
    Iterator operator++(int);

    Iterator& operator--();
    const Iterator operator--(int);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

   private:
    friend class BiDirectionalList;

    const BiDirectionalList* const list_;
    Node* node_;

    Iterator(const BiDirectionalList* const list, Node* node)
        : list_(list), node_(node) {}
  };

  class ConstIterator :
      public std::iterator<std::bidirectional_iterator_tag, T> {
   public:
    const T& operator*() const;
    const T* operator->() const;

    ConstIterator& operator++();
    const ConstIterator operator++(int);

    ConstIterator& operator--();
    const ConstIterator operator--(int);

    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;

   private:
    friend class BiDirectionalList;

    const BiDirectionalList* const list_;
    const Node* node_;

    ConstIterator(const BiDirectionalList* const list, Node* node)
        : list_(list), node_(node) {}
  };

  BiDirectionalList() : first_(nullptr), last_(nullptr) {}

  ~BiDirectionalList() { Clear(); }

  bool IsEmpty() const;

  void Clear();

  Iterator begin();
  Iterator end();

  ConstIterator begin() const;
  ConstIterator end() const;

  std::vector<T> AsArray() const;

  void InsertBefore(Iterator position, const T& value);
  void InsertBefore(Iterator position, T&& value);

  void InsertAfter(Iterator position, const T& value);
  void InsertAfter(Iterator position, T&& value);

  void PushBack(const T& value);
  void PushBack(T&& value);

  void PushFront(const T& value);
  void PushFront(T&& value);

  void Erase(Iterator position);

  void PopFront();
  void PopBack();

  Iterator Find(const T& value);
  ConstIterator Find(const T& value) const;

  Iterator Find(std::function<bool(const T&)> predicate);
  ConstIterator Find(std::function<bool(const T&)> predicate) const;

 protected:
  struct Node {
    Node(const T& value);
    Node(T&& value);

    ~Node();

    T value_;
    Node* next_node_;
    Node* previous_node_;
  };

  Node* first_;
  Node* last_;

  void InsertBefore(Node* existing_node, Node* new_node);
  void InsertAfter(Node* existing_node, Node* new_node);
  void Erase(Node* node);
};


// Definitions of BiDirectionalList Iterator methods

template<typename T>
T& BiDirectionalList<T>::Iterator::operator*() const {
  return node_->value_;
}

template<typename T>
T* BiDirectionalList<T>::Iterator::operator->() const {
  return &(node_->value_);
}

template<typename T>
typename BiDirectionalList<T>::Iterator&
BiDirectionalList<T>::Iterator::operator++() {
  if (node_ == nullptr) {
    throw std::runtime_error("Out of range: increment nullptr");
  }
  node_ = node_->next_node_;
  return *this;
}

template<typename T>
typename BiDirectionalList<T>::Iterator
BiDirectionalList<T>::Iterator::operator++(int) {
  if (node_ == nullptr) {
    throw std::runtime_error("Out of range: increment nullptr");
  }
  auto result = *this;
  node_ = node_->next_node_;
  return result;
}

template<typename T>
typename BiDirectionalList<T>::Iterator&
BiDirectionalList<T>::Iterator::operator--() {
  if (node_ == list_->first_) {
    throw std::runtime_error("Out of range: decrement begin");
  }
  if (node_ == nullptr) {
    node_ = list_->last_;
  } else {
    node_ = node_->previous_node_;
  }
  return *this;
}

template<typename T>
const typename BiDirectionalList<T>::Iterator
BiDirectionalList<T>::Iterator::operator--(int) {
  if (node_ == list_->first_) {
    throw std::runtime_error("Out of range: decrement begin");
  }
  auto result = *this;
  if (node_ == nullptr) {
    node_ = list_->last_;
  } else {
    node_ = node_->previous_node_;
  }
  return result;
}

template<typename T>
bool BiDirectionalList<T>::Iterator::operator==
    (const BiDirectionalList::Iterator& other) const {
  return (list_ == other.list_ && node_ == other.node_);
}

template<typename T>
bool BiDirectionalList<T>::Iterator::operator!=
    (const BiDirectionalList::Iterator& other) const {
  return !(*this == other);
}


// Definitions of BiDirectionalList ConstIterator methods

template<typename T>
const T& BiDirectionalList<T>::ConstIterator::operator*() const {
  return node_->value_;
}

template<typename T>
const T* BiDirectionalList<T>::ConstIterator::operator->() const {
  return &(node_->value_);
}
template<typename T>
typename BiDirectionalList<T>::ConstIterator&
BiDirectionalList<T>::ConstIterator::operator++() {
  if (node_ == nullptr) {
    throw std::runtime_error("Out of range: increment nullptr");
  }
  node_ = node_->next_node_;
  return *this;
}

template<typename T>
const typename BiDirectionalList<T>::ConstIterator
BiDirectionalList<T>::ConstIterator::operator++(int) {
  if (node_ == nullptr) {
    throw std::runtime_error("Out of range: increment nullptr");
  }
  auto result = *this;
  node_ = node_->next_node_;
  return result;
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator&
BiDirectionalList<T>::ConstIterator::operator--() {
  if (node_ == list_->first_) {
    throw std::runtime_error("Out of range: decrement begin");
  }
  if (node_ == nullptr) {
    node_ = list_->last_;
  } else {
    node_ = node_->previous_node_;
  }
  return *this;
}

template<typename T>
const typename BiDirectionalList<T>::ConstIterator
BiDirectionalList<T>::ConstIterator::operator--(int) {
  if (node_ == list_->first_) {
    throw std::runtime_error("Out of range: decrement begin");
  }
  auto result = *this;
  if (node_ == nullptr) {
    node_ = list_->last_;
  } else {
    node_ = node_->previous_node_;
  }
  return result;
}

template<typename T>
bool BiDirectionalList<T>::ConstIterator::operator==
    (const BiDirectionalList<T>::ConstIterator& other) const {
  return (list_ == other.list_ && node_ == other.node_);
}

template<typename T>
bool BiDirectionalList<T>::ConstIterator::operator!=
    (const BiDirectionalList<T>::ConstIterator& other) const {
  return !(*this == other);
}

// Constructors & destructor of Node

template<typename T>
BiDirectionalList<T>::Node::Node(const T& value) : value_(value),
                                                   next_node_(nullptr),
                                                   previous_node_(nullptr) {}

template<typename T>
BiDirectionalList<T>::Node::Node(T&& value) : value_(std::move(value)),
                                              next_node_(nullptr),
                                              previous_node_(nullptr) {}

template<typename T>
BiDirectionalList<T>::Node::~Node() = default;


// Definitions of BiDirectionalList protected methods

template<typename T>
void BiDirectionalList<T>::InsertBefore(Node* existing_node, Node* new_node) {
  if (new_node == nullptr) {
    throw std::invalid_argument("Invalid new node");
  }
  if (IsEmpty()) {
    first_ = new_node;
    last_ = new_node;
    return;
  }
  if (existing_node == nullptr) {
    throw std::runtime_error("Invalid operation: insert before nullptr");
  }
  if (existing_node->previous_node_ == nullptr) {
    existing_node->previous_node_ = new_node;
    new_node->next_node_ = existing_node;
    new_node->previous_node_ = nullptr;
    first_ = new_node;
  } else {
    new_node->previous_node_ = existing_node->previous_node_;
    new_node->next_node_ = existing_node;
    existing_node->previous_node_->next_node_ = new_node;
    existing_node->previous_node_ = new_node;
  }
}

template<typename T>
void BiDirectionalList<T>::InsertAfter(Node* existing_node, Node* new_node) {
  if (new_node == nullptr) {
    throw std::invalid_argument("Invalid new node");
  }
  if (IsEmpty()) {
    first_ = new_node;
    last_ = new_node;
    return;
  }
  if (existing_node == nullptr) {
    throw std::runtime_error("Invalid operation: insert after nullptr");
  }
  if (existing_node->next_node_ == nullptr) {
    existing_node->next_node_ = new_node;
    new_node->previous_node_ = existing_node;
    new_node->next_node_ = nullptr;
    last_ = new_node;
  } else {
    new_node->previous_node_ = existing_node;
    new_node->next_node_ = existing_node->next_node_;
    existing_node->next_node_->previous_node_ = new_node;
    existing_node->next_node_ = new_node;
  }
}

template<typename T>
void BiDirectionalList<T>::Erase(Node* node) {
  if (node == nullptr) {
    throw std::invalid_argument("Erasing nullptr");
  }
  if (first_ == last_) {
    Clear();
    return;
  }
  if (node->next_node_ == nullptr) {
    node->previous_node_->next_node_ = nullptr;
    last_ = node->previous_node_;
    delete node;
  } else if (node->previous_node_ == nullptr) {
    node->next_node_->previous_node_ = nullptr;
    first_ = node->next_node_;
    delete node;
  } else {
    node->previous_node_->next_node_ = node->next_node_;
    node->next_node_->previous_node_ = node->previous_node_;
    delete node;
  }
}

// Definitions of BiDirectionalList public methods

template<typename T>
bool BiDirectionalList<T>::IsEmpty() const {
  return first_ == nullptr;
}

template<typename T>
void BiDirectionalList<T>::Clear() {
  if (IsEmpty()) { return; }
  for (auto i = first_; i != nullptr; i = i->next_node_) {
    delete i;
  }
  first_ = nullptr;
  last_ = nullptr;
}
template<typename T>
typename BiDirectionalList<T>::Iterator BiDirectionalList<T>::begin() {
  return Iterator(this, first_);
}
template<typename T>
typename BiDirectionalList<T>::Iterator BiDirectionalList<T>::end() {
  if (IsEmpty()) {
    return begin();
  }
  return Iterator(this, last_->next_node_);
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator
BiDirectionalList<T>::begin() const {
  return {this, first_};
}
template<typename T>
typename BiDirectionalList<T>::ConstIterator
BiDirectionalList<T>::end() const {
  if (IsEmpty()) {
    return begin();
  }
  return {this, last_->next_node_};
}

template<typename T>
std::vector<T> BiDirectionalList<T>::AsArray() const {
  std::vector<T> list_as_vector;
  std::copy(begin(), end(), back_inserter(list_as_vector));
  return list_as_vector;
}

template<typename T>
void BiDirectionalList<T>::InsertBefore(Iterator position, const T& value) {
  if (position == this->end()) {
    InsertAfter(last_, new Node(std::move(value)));
    return;
  }
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator");
  }
  InsertBefore(position.node_, new Node(value));
}

template<typename T>
void BiDirectionalList<T>::InsertBefore(Iterator position, T&& value) {
  if (position == this->end()) {
    InsertAfter(last_, new Node(std::move(value)));
    return;
  }
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator");
  }
  InsertBefore(position.node_, new Node(std::move(value)));
}

template<typename T>
void BiDirectionalList<T>::InsertAfter(Iterator position, const T& value) { // ?
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator");
  }
  InsertAfter(position.node_, new Node(value));
}
template<typename T>
void BiDirectionalList<T>::InsertAfter(Iterator position, T&& value) { // ?
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator");
  }
  InsertAfter(position.node_, new Node(std::move(value)));
}

template<typename T>
void BiDirectionalList<T>::PushBack(const T& value) {
  InsertAfter(last_, new Node(value));
}

template<typename T>
void BiDirectionalList<T>::PushBack(T&& value) { // ?
  InsertAfter(last_, new Node(std::move(value)));
}

template<typename T>
void BiDirectionalList<T>::PushFront(const T& value) {
  InsertBefore(first_, new Node(value));
}

template<typename T>
void BiDirectionalList<T>::PushFront(T&& value) {
  InsertBefore(first_, new Node(value));
  value = T();
}

template<typename T>
void BiDirectionalList<T>::Erase(Iterator position) {
  Erase(position.node_);
}

template<typename T>
void BiDirectionalList<T>::PopFront() {
  Erase(first_);
}

template<typename T>
void BiDirectionalList<T>::PopBack() {
  Erase(last_);
}

template<typename T>
typename BiDirectionalList<T>::Iterator
BiDirectionalList<T>::Find(const T& value) {
  return find(begin(), end(), value);
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator
BiDirectionalList<T>::Find(const T& value) const {
  return find(begin(), end(), value);
}

template<typename T>
typename BiDirectionalList<T>::Iterator
BiDirectionalList<T>::Find(std::function<bool(const T&)> predicate) {
  return std::find_if(begin(), end(), predicate);
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator
BiDirectionalList<T>::Find(std::function<bool(const T&)> predicate) const {
  return std::find_if(begin(), end(), predicate);
}

#endif //BIDIRECTIONALLIST_LIST_H
