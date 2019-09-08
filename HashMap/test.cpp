#include "test.h"

bool PresenceOfData(const HashMap& hm, const std::string& data) {
  return hm.Search(data) != nullptr;
}

void TestAll() {
  setlocale(LC_ALL, "Rus");
  std::ifstream fin;
  fin.open("test_input.txt");
  HashMap hm;
  std::string data;
  std::string command;
  Assert(hm.IsEmpty(), "1.1");
  Assert(!PresenceOfData(hm, ""), "1.2");
  Assert(!PresenceOfData(hm, "qwer"), "1.3");
  hm.Insert("math");
  HashMap hm7 = hm;
  Assert(!hm.IsEmpty(), "1.4");
  Assert(PresenceOfData(hm, "math"), "1.5");
  hm.Delete("math");
  Assert(hm != hm7, "1.6");
  Assert(!PresenceOfData(hm, "qwer"), "1.7");
  Assert(!hm7.IsEmpty(), "a");
  Assert(hm.IsEmpty(), "1.8");
  uint32_t counter = 0;
  bool expected;
  while (fin >> command) {
    if (command == "INSERT") {
      fin >> data;
      hm.Insert(data);
      Assert(PresenceOfData(hm, data), "2." + std::to_string(counter));
    } else if (command == "DELETE") {
      fin >> data;
      hm.Delete(data);
      Assert(!PresenceOfData(hm, data), "3." + std::to_string(counter));
    } else if (command == "SEARCH") {
      fin >> data;
      fin >> expected;
      if (expected) {
        AssertEqualNO(hm.Search(data)->value_, data, "4." +
            std::to_string(counter));
      } else {
        AssertEqualNO(hm.Search(data), nullptr, "4." +
            std::to_string(counter));
      }
    } else if (command == "ISEMPTY") {
      hm.IsEmpty();
    } else if (command == "CLEAR") {
      hm.Clear();
      Assert(hm.IsEmpty(), "5." + std::to_string(counter));
    }
    ++counter;
  }
  HashMap hm2 = hm;
  AssertEqualNO(hm, hm2, "6.1");
  HashMap hm3(hm);
  AssertEqualNO(hm, hm3, "6.2");
  hm3.Insert("point");
  AssertNEqualNO(hm, hm3, "6.2");
  HashMap hm4(std::move(hm));
  AssertEqualNO(hm2, hm4, "6.3");
}

