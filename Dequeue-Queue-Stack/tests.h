#ifndef DEQUEUE_QUEUE_STACK_TESTS_H
#define DEQUEUE_QUEUE_STACK_TESTS_H

#include <string>
#include "deque_stack_queue.h"
#include <cassert>

class TestRunner {
 public:
  template<class TestFunc>
  void RunTest(TestFunc func, const std::string& test_name);

  ~TestRunner();
 private:
  int fail_count = 0;
};

void TestAll();

#endif //DEQUEUE_QUEUE_STACK_TESTS_H
