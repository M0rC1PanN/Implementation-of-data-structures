#include "bin_tree.h"

BinarySearchTree::BinarySearchTree() : root_(nullptr), size_(0) {}

BinarySearchTree::~BinarySearchTree() {
  delete root_;
}

void BinarySearchTree::Detach(Node *target_node) {
  if (target_node == nullptr) { return; }
  if (target_node->left == nullptr) {
    Attach(target_node, target_node->right);
  } else if (target_node->right == nullptr) {
    Attach(target_node, target_node->left);
  } else {
    Node *left_most_node = GetLeftmostNode(target_node->right);
    if (left_most_node->parent != target_node) {
      Attach(left_most_node, left_most_node->right);
      left_most_node->right = target_node->right;
      left_most_node->right->parent = left_most_node;
    }
    Attach(target_node, left_most_node);
    left_most_node->left = target_node->left;
    left_most_node->left->parent = left_most_node;
  }
  target_node->left = nullptr;
  target_node->right = nullptr;
}


void BinarySearchTree::Attach(Node *where, Node *what) {
  if (where == root_) {
    root_ = what;
  } else if (where->parent->right == where) {
    where->parent->right = what;
  } else {
    where->parent->left = what;
  }
  if (what != nullptr) {
    what->parent = where->parent;
  }
}

BinarySearchTree::Node *BinarySearchTree::Find(int value) const {
  Node *cur = root_;
  while (cur != nullptr && cur->value != value) {
    if (cur->value > value) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return cur;
}

BinarySearchTree::Node *BinarySearchTree::GetLeftmostNode(Node *node) const {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}


BinarySearchTree::Node *BinarySearchTree::GetRightmostNode(Node *node) const {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}


void BinarySearchTree::AppendToSortedArray(
    Node *node,
    std::vector<int> *res) const {

  if (node == nullptr) {
    return;
  }
  AppendToSortedArray(node->left, res);
  res->push_back(node->value);
  AppendToSortedArray(node->right, res);
}

bool BinarySearchTree::Contains(int value) const {
  return (Find(value) != nullptr);
}

void BinarySearchTree::Add(int value) {
  size_++;
  if (root_ == nullptr) {
    root_ = new Node(value, nullptr);
    return;
  }
  Node *comparable = root_;
  while (true) {
    if (value >= comparable->value) {
      if (comparable->right != nullptr) {
        comparable = comparable->right;
      } else {
        comparable->right = new Node(value, comparable);
        return;
      }
    } else if (value < comparable->value) {
      if (comparable->left != nullptr) {
        comparable = comparable->left;
      } else {
        comparable->left = new Node(value, comparable);
        return;
      }
    }
  }
}

void BinarySearchTree::Erase(int value) {
  if (Find(value) == nullptr) { return; }
  size_--;
  if (size_ == 0) {
    delete root_;
    root_ = nullptr;
    return;
  }
  Node *f = Find(value);
  Detach(f);
  delete f;
}

int BinarySearchTree::Size() const {
  return size_;
}

std::vector<int> BinarySearchTree::ToSortedArray() const {
  std::vector<int> sorted_array;
  AppendToSortedArray(root_, &sorted_array);
  return (sorted_array);
}
