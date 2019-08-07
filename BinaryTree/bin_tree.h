#ifndef BINARYTREE_BIN_TREE_H
#define BINARYTREE_BIN_TREE_H

#include <vector>

class BinarySearchTree {
 public:
  BinarySearchTree();
  ~BinarySearchTree();

  bool Contains(int value) const;

  void Add(int value);

  void Erase(int value);

  int Size() const;

  std::vector<int> ToSortedArray() const;

 protected:

  struct Node {

    int value;

    Node *parent;
    Node *left;
    Node *right;

    Node(int value, Node *parent) :
        value(value), parent(parent), left(nullptr), right(nullptr) {}

    ~Node() {
      delete right;
      delete left;
    }
  };

  Node *root_;
  int size_;

  Node *Find(int value) const;

  Node *GetLeftmostNode(Node *node) const;
  Node *GetRightmostNode(Node *node) const;

  void Detach(Node *target_node);

  void Attach(Node *where, Node *what);

  void AppendToSortedArray(Node *node, std::vector<int> *res) const;
};


#endif //BINARYTREE_BIN_TREE_H
