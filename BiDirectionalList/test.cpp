#include "test.h"
#include "framework.h"

void TestLinkedList() {
  BiDirectionalList<int> list;
  BiDirectionalList<int> list2;
  Assert(list.IsEmpty(), "1.1");
  std::vector<int> a = {};
  AssertEqual(list.AsArray(), a, "1.2");
  AssertEqualNO(list.Find(1), list.end(), "1.3");
  list.PushBack(1);
  Assert(!list.IsEmpty(), "2.1");
  AssertEqualNO(list.Find(1), list.begin(), "2.2");
  list.PushFront(0);
  AssertEqual(*list.begin(), 0, "3.1");
  AssertEqual(*(++list.begin()), 1, "3.2");
  list.InsertAfter(list.begin(), 7);
  AssertEqual(*(++list.begin()), 7, "4.1");
  list.InsertBefore(list.end(), 11);
  AssertEqual(*(--list.end()), 11, "5.1");
  list.InsertBefore(list.begin(), -1);
  AssertEqual(*list.begin(), -1, "5.2");
  try {
    list.InsertBefore(list2.begin(), 0);
  } catch (std::runtime_error& ex) {
    AssertEqual<std::string, std::string>
        (ex.what(), "Incorrect iterator", "6.1");
  }
  try {
    list.InsertAfter(list.end(), 0);
  } catch (std::runtime_error& ex) {
    AssertEqual<std::string, std::string>
        (ex.what(), "Invalid operation: insert after nullptr", "6.2");
  }
  AssertEqualNO(list.Find([](int a) {
    return a > 7;
  }), --list.end(), "6.3");

  a = {-1, 0, 7, 1, 11};
  AssertEqual(list.AsArray(), a, "7.1");
  list.Erase(list.begin());
  a = {0, 7, 1, 11};
  AssertEqual(list.AsArray(), a, "7.2");
  try {
    list.Erase(list.end());
  } catch (std::invalid_argument& ex) {
    AssertEqual<std::string, std::string>
        (ex.what(), "Erasing nullptr", "7.3");
  }
  list.Erase(++list.begin());
  a = {0, 1, 11};
  AssertEqual(list.AsArray(), a, "7.4");
  list.Erase(--list.end());
  a = {0, 1};
  AssertEqual(list.AsArray(), a, "7.5");
  list.PopBack();
  a.pop_back();
  AssertEqual(list.AsArray(), a, "7.6");
  list.PopFront();
  Assert(list.IsEmpty(), "7.7");
  try {
    list.PopBack();
  } catch (std::invalid_argument& ex) {
    AssertEqual<std::string, std::string>
        (ex.what(), "Erasing nullptr", "7.8");
  }
  try {
    list.PopFront();
  } catch (std::invalid_argument& ex) {
    AssertEqual<std::string, std::string>
        (ex.what(), "Erasing nullptr", "7.9");
  }
  list.Clear();
  Assert(list.IsEmpty(), "7.10");
  int n = 0;
  list.PushBack(n);
  list.PushFront(n);
  a = {0, 0};
  AssertEqual(list.AsArray(), a, "8.1");
}

void TestConstLinkedList() {
  BiDirectionalList<int> list;
  int a = 0;
  list.PushBack(a++);
  list.PushFront(a++);
  list.InsertBefore(list.begin(), a);
  list.InsertAfter(list.begin(), ++a);
  const BiDirectionalList<int> const_list = list;
  AssertEqual(*const_list.begin(), 2, "1.1");
  AssertEqual(*(++const_list.begin()), 3, "1.2");
  AssertEqual(*(--const_list.end()), 0, "1.3");
  AssertEqualNO(const_list.Find(a), ++const_list.begin(), "1.4");
  AssertEqualNO(const_list.Find([](int i) {
    return i > 10;
  }), const_list.end(), "1.5");
  BiDirectionalList<std::map<int, int>> int_to_int_list;
  int_to_int_list.PushBack({{10, 20}, {20, 30}, {5, 10}});
  std::map<int, int> m {{1, 2}, {2, 3}, {5, 10}};
  int_to_int_list.PushBack(m);
  AssertEqual(int_to_int_list.begin()->at(10), 20, "2.1");
  AssertNEqualNO(++int_to_int_list.begin()->begin(), m.begin(), "2.2");
  AssertEqual((*(++int_to_int_list.begin())->begin()).first, 1, "2.3");
  AssertEqual((*(++int_to_int_list.begin())->begin()).second, 2, "2.4");
  Assert(int_to_int_list.begin()->begin() != m.begin(), "2.5");
  const BiDirectionalList<std::map<int, int>> int_to_int_const_list =
      int_to_int_list;
  Assert(int_to_int_const_list.begin()->begin() != m.begin(), "3.1");
  AssertEqual(int_to_int_const_list.begin()->at(10), 20, "3.2");
  AssertNEqualNO(++int_to_int_const_list.begin()->begin(), m.begin(), "3.3");
  AssertEqual((*(++int_to_int_const_list.begin())->begin()).first, 1, "3.4");
  AssertEqual((*(++int_to_int_const_list.begin())->begin()).second, 2, "3.5");
  Assert
  (int_to_int_const_list.begin()->begin() == int_to_int_const_list.begin()->begin(),
      "3.6");
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestLinkedList, "TestLinkedList");
  tr.RunTest(TestConstLinkedList, "TestConstLinkedList");
}
