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
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestLinkedList, "TestLinkedList");

}
