#include "test.h"

void TestEmpty() {
  BinarySearchTree tr;
  AssertEqual(tr.Size(), 0, "1.1");
  AssertEqual(tr.Contains(0), 0, "1.2");
  std::vector<int> arr;
  AssertEqual(tr.ToSortedArray(), arr, "1.3");
}

void TestTree() {
  std::vector<int> caps = {0, 1, 2, 5, 75, 1006};
  std::mt19937_64 random_generator(2112);
  for (const auto& c : caps) {
    BinarySearchTree tr;
    std::vector<int> tree_as_vec(c);
    for (int j = 0; j < c; ++j) {
      int el = random_generator() % 20;
      tr.Add(el);
      tree_as_vec[j] = el;
    }
//    std::vector<int> tree_as_vec_uns(tree_as_vec);
    for (const auto& i : tree_as_vec) {
      Assert(tr.Contains(i), "1.4");
    }
    std::sort(begin(tree_as_vec), end(tree_as_vec));
    std::vector<int> tree_to_vec(tr.ToSortedArray());
    AssertEqual(tr.Size(), c, "2.0 with capacity " + std::to_string(c));
    for (int i = 0; i < c; ++i) {
      AssertEqual(tree_as_vec[i], tree_to_vec[i], "2." + std::to_string(i) +
          " with capacity " + std::to_string(c));
    }
    int cap = c;
    for (int i = 0; cap > 1; i = random_generator() % cap) {
      tr.Erase(tree_as_vec[i]);
      std::vector<int> tree_to_vec2(tr.ToSortedArray());
      tree_as_vec.erase(std::find(begin(tree_as_vec), end(tree_as_vec), tree_as_vec[i]));
      --cap;
      for (int j = 0; j < cap; ++j) {
        AssertEqual(tree_as_vec[j], tree_to_vec2[j], "3." + std::to_string(j) + " with capacity " + std::to_string(c));
      }
    }
    Assert(!tr.Contains(-1), "4.1 with capacity " + std::to_string(c));
    Assert(!tr.Contains(21), "4.2 with capacity " + std::to_string(c));
  }
}

void TestAll() {
  TestEmpty();
  TestTree();
}
