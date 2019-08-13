#ifndef BINARYTREE_FRAMEWORK_H
#define BINARYTREE_FRAMEWORK_H

#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>

template<class T>
// set
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}
template<class K, class V>
// map
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<typename First, typename Second>
// pair
std::ostream& operator<<(std::ostream& out, const std::pair<First, Second>& p) {
  out << p.first << ", " << p.second;
  return out;
}
template<typename T>
// vector
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vi) {
  for (const auto& i : vi) {
    out << i << ' ';
  }
  return out;
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
                 const std::string& hint) {
  if (t != u) {
    std::ostringstream os;
    os << "Assertion failed: " << t << " != " << u
       << " hint: " << hint;
    throw std::runtime_error(os.str());
  }
}

inline void Assert(bool b, const std::string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
 public:
  template<class TestFunc>
  void RunTest(TestFunc func, const std::string& test_name) {
    try {
      func();
      std::cerr << test_name << " OK" << std::endl;
    } catch (std::runtime_error& e) {
      ++fail_count;
      std::cerr << test_name << " fail: " << e.what() << std::endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
      exit(1);
    }
  }

 private:
  int fail_count = 0;
};

#endif //BINARYTREE_FRAMEWORK_H
