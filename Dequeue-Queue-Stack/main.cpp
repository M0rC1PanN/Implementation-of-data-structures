#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>

template <class T, class U>
void AssertEqual (const T& t, const U& u) {
  if (t != u) {
    std::ostringstream os;
    os << "Assertion failed: " << t << "!=" << u;
    throw std::runtime_error (os.str());
  }
}

class TestRunner {
 public:
  template<class TestFunc>
  void RunTest(TestFunc func, const std::string& test_name) {
    try {
      func();
      std::cerr << test_name << " OK" << std::endl;
    } catch (std::runtime_error& e) {
      ++
          fail_count;
      std::cerr << test_name << " fail: " << e.
          what() << std::endl;
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


class Deque {
 public:
  explicit Deque(int max_size) : size_(0), head_(0), tail_(0) {

    data_.resize(max_size);

  }

  int Size() const {
    return size_;
  }
  int MaxSize() const {
    return data_.size();
  }
  bool IsEmpty() const {
    return size_ == 0;
  }
  bool IsFull() const {
    return size_ == data_.size();
  }
  bool PushBack(int insert) {
    if (!IsFull()) {
      if (IsEmpty()) {
        data_[tail_] = insert;
      } else {
        tail_ = (tail_ + 1) % MaxSize();
        data_[tail_] = insert;
      }
      ++size_;
      return true;
    } else {
      return false;
    }
  }
  int Back(int default_element = 0) const {
    if (!IsEmpty()) {
      return data_[tail_];
    } else {
      return default_element;
    }
  }
  bool PopBack() {
    if (!IsEmpty()) {
      if (size_ != 1) {
        --tail_;
        if (tail_ < 0) {
          tail_ = data_.size() - 1;
        }
      }
      --size_;
      return true;
    } else {
      return false;
    }
  }
  bool PushFront(int insert) {
    if (!IsFull()) {
      if (IsEmpty()) {
        data_[head_] = insert;
      } else {
        head_ = (head_ + MaxSize() - 1) % MaxSize();
        data_[head_] = insert;
      }
      ++size_;
      return true;
    } else {
      return false;
    }
  }
  int Front(int default_element = 0) const {
    if (!IsEmpty()) {
      return data_[head_];
    } else {
      return default_element;
    }
  }

  bool PopFront() {
    if (!IsEmpty()) {
      if (size_ != 1)
        head_ = (head_ + MaxSize() + 1) % MaxSize();
      --size_;
      return true;
    } else {
      return false;
    }
  }

 private:
  std::vector<int> data_;
  int head_;
  int tail_;
  int size_;
};

class Queue {
 public:
  explicit Queue(int max_size) : queue_(max_size) {}
  bool Push(int value = 0) {
    return queue_.PushBack(value);
  }
  int Front(int default_value = 0) const {
    return queue_.Front(default_value);
  }
  bool Pop() {
    return queue_.PopFront();
  }
  int Size() const {
    return queue_.Size();
  }
  int MaxSize() const {
    return queue_.MaxSize();
  }
  bool IsEmpty() const {
    return queue_.IsEmpty();
  }
  bool IsFull() const {
    return queue_.IsFull();
  }

 private:
  Deque queue_;
};

class Stack {
 public:
  explicit Stack(int max_size) : stack_(max_size) {}
  bool Push(int value = 0) {
    return stack_.PushFront(value);
  }
  int Top(int default_value = 0) const {
    return stack_.Front(default_value);
  }
  bool Pop() {
    return stack_.PopFront();
  }
  int Size() const {
    return stack_.Size();
  }
  int MaxSize() const {
    return stack_.MaxSize();
  }
  bool IsEmpty() const {
    return stack_.IsEmpty();
  }
  bool IsFull() const {
    return stack_.IsFull();
  }

 private:
  Deque stack_;
};

void DequeTests() {
  {
    const Deque deque(5);
    assert(deque.IsEmpty());
    assert(!deque.IsFull());
    assert(deque.Size() == 0);
    assert(deque.MaxSize() == 5);
    assert(deque.Front() == 0);
    assert(deque.Front(0) == 0);
    assert(deque.Back() == 0);
    assert(deque.Back(0) == 0);
  }
  {
    Deque deque(5);

    assert(!deque.PopBack());

    assert(deque.Size() == 0);
    assert(deque.Back() == 0);
    assert(deque.Back(42) == 42);
    assert(deque.IsEmpty());
    assert(!deque.IsFull());

    assert(deque.PushBack(13));
    assert(deque.PushBack(123));
    assert(deque.PushBack(123456));

    assert(deque.Size() == 3);
    assert(deque.Back() == 123456);
    assert(deque.Back(42) == 123456);
    assert(!deque.IsEmpty());
    assert(!deque.IsFull());

    assert(deque.PopBack());

    assert(deque.Size() == 2);
    assert(deque.Back() == 123);
    assert(deque.Back(42) == 123);
    assert(!deque.IsEmpty());
    assert(!deque.IsFull());

    assert(deque.PushBack(3));
    assert(deque.PushBack(4));
    assert(deque.PushBack(5));

    assert(deque.Size() == 5);
    assert(deque.Back() == 5);
    assert(deque.Back(42) == 5);
    assert(!deque.IsEmpty());
    assert(deque.IsFull());

    assert(!deque.PushBack(99));

    assert(deque.Size() == 5);
    assert(deque.Back() == 5);
    assert(deque.Back(42) == 5);
    assert(!deque.IsEmpty());
    assert(deque.IsFull());
  }
  {
    Deque deque(5);

    assert(!deque.PopFront());

    assert(deque.Size() == 0);
    assert(deque.Front() == 0);
    assert(deque.Front(42) == 42);
    assert(deque.IsEmpty());
    assert(!deque.IsFull());

    assert(deque.PushFront(13));
    assert(deque.PushFront(123));
    assert(deque.PushFront(123456));

    assert(deque.Size() == 3);
    assert(deque.Front() == 123456);
    assert(deque.Front(42) == 123456);
    assert(!deque.IsEmpty());
    assert(!deque.IsFull());

    assert(deque.PopFront());

    assert(deque.Size() == 2);
    assert(deque.Front() == 123);
    assert(deque.Front(42) == 123);
    assert(!deque.IsEmpty());
    assert(!deque.IsFull());

    assert(deque.PushFront(3));
    assert(deque.PushFront(4));
    assert(deque.PushFront(5));

    assert(deque.Size() == 5);
    assert(deque.Front() == 5);
    assert(deque.Front(42) == 5);
    assert(!deque.IsEmpty());
    assert(deque.IsFull());

    assert(!deque.PushFront(99));

    assert(deque.Size() == 5);
    assert(deque.Front() == 5);
    assert(deque.Front(42) == 5);
    assert(!deque.IsEmpty());
    assert(deque.IsFull());

  }
  {
    Deque deque(3);

    assert(deque.PushFront(1));

    assert(deque.Size() == 1);
    assert(deque.Back() == 1);
    assert(deque.Front() == 1);

    assert(deque.PushBack(2));

    assert(deque.Size() == 2);
    assert(deque.Back() == 2);
    assert(deque.Front() == 1);

    assert(deque.PushFront(0));

    assert(deque.Size() == 3);
    assert(deque.Back() == 2);
    assert(deque.Front() == 0);

    assert(deque.PopFront());

    assert(deque.Size() == 2);
    assert(deque.Back() == 2);
    assert(deque.Front() == 1);

    assert(deque.PushBack(3));

    assert(deque.Size() == 3);
    assert(deque.Back() == 3);
    assert(deque.Front() == 1);

    assert(deque.PopFront());

    assert(deque.Size() == 2);
    assert(deque.Back() == 3);
    assert(deque.Front() == 2);

    assert(deque.PushBack(4));

    assert(deque.Size() == 3);
    assert(deque.Back() == 4);
    assert(deque.Front() == 2);

    assert(deque.PopBack());

    assert(deque.Size() == 2);
    assert(deque.Back() == 3);
    assert(deque.Front() == 2);
  }
}

void StackTests() {
  {
    Stack stack(2);
    assert(stack.IsEmpty());
    assert(!stack.IsFull());
    assert(stack.Size() == 0);
    assert(stack.MaxSize() == 2);
    assert(stack.Top() == 0);
    assert(stack.Top(0) == 0);
  }
  {
    Stack stack(2);

    assert(stack.Size() == 0);
    assert(stack.MaxSize() == 2);
    assert(stack.IsEmpty());
    assert(!stack.IsFull());
    assert(stack.Top() == 0);
    assert(stack.Top(42) == 42);

    assert(!stack.Pop());

    assert(stack.Size() == 0);
    assert(stack.MaxSize() == 2);
    assert(stack.IsEmpty());
    assert(!stack.IsFull());
    assert(stack.Top() == 0);
    assert(stack.Top(42) == 42);

    assert(stack.Push(1));

    assert(stack.Size() == 1);
    assert(stack.MaxSize() == 2);
    assert(!stack.IsEmpty());
    assert(!stack.IsFull());
    assert(stack.Top() == 1);
    assert(stack.Top(42) == 1);

    assert(stack.Push(2));

    assert(stack.Size() == 2);
    assert(stack.MaxSize() == 2);
    assert(!stack.IsEmpty());
    assert(stack.IsFull());
    assert(stack.Top() == 2);
    assert(stack.Top(42) == 2);

    assert(!stack.Push(3));

    assert(stack.Size() == 2);
    assert(stack.MaxSize() == 2);
    assert(!stack.IsEmpty());
    assert(stack.IsFull());
    assert(stack.Top() == 2);
    assert(stack.Top(42) == 2);

    assert(stack.Pop());

    assert(stack.Size() == 1);
    assert(stack.MaxSize() == 2);
    assert(!stack.IsEmpty());
    assert(!stack.IsFull());
    assert(stack.Top() == 1);
    assert(stack.Top(42) == 1);
  }
}

int QueueTests() {
  {
    Queue queue(2);
    assert(queue.IsEmpty());
    assert(!queue.IsFull());
    assert(queue.Size() == 0);
    assert(queue.MaxSize() == 2);
    assert(queue.Front() == 0);
    assert(queue.Front(0) == 0);
  }
  {
    Queue queue(2);

    assert(queue.Size() == 0);
    assert(queue.MaxSize() == 2);
    assert(queue.IsEmpty());
    assert(!queue.IsFull());
    assert(queue.Front() == 0);
    assert(queue.Front(42) == 42);

    assert(!queue.Pop());

    assert(queue.Size() == 0);
    assert(queue.MaxSize() == 2);
    assert(queue.IsEmpty());
    assert(!queue.IsFull());
    assert(queue.Front() == 0);
    assert(queue.Front(42) == 42);

    assert(queue.Push(1));

    assert(queue.Size() == 1);
    assert(queue.MaxSize() == 2);
    assert(!queue.IsEmpty());
    assert(!queue.IsFull());
    assert(queue.Front() == 1);
    assert(queue.Front(42) == 1);

    assert(queue.Push(2));

    assert(queue.Size() == 2);
    assert(queue.MaxSize() == 2);
    assert(!queue.IsEmpty());
    assert(queue.IsFull());
    assert(queue.Front() == 1);
    assert(queue.Front(42) == 1);

    assert(!queue.Push(3));

    assert(queue.Size() == 2);
    assert(queue.MaxSize() == 2);
    assert(!queue.IsEmpty());
    assert(queue.IsFull());
    assert(queue.Front() == 1);
    assert(queue.Front(42) == 1);

    assert(queue.Pop());

    assert(queue.Size() == 1);
    assert(queue.MaxSize() == 2);
    assert(!queue.IsEmpty());
    assert(!queue.IsFull());
    assert(queue.Front() == 2);
    assert(queue.Front(42) == 2);

    assert(queue.Pop());
    assert(queue.Size() == 0);
    assert(queue.Push(5));
    assert(queue.Push(7));
    assert(queue.Front() == 5);
    assert(queue.Pop());
    assert(queue.Front() == 7);
    assert(queue.Push(9));
    assert(queue.Size() == 2);
    assert(queue.IsFull());
    assert(queue.Front() == 7);
    assert(queue.IsFull());
    assert(queue.Pop());
    assert(queue.Pop());
    assert(queue.Size() == 0);
  }
}



void TestAll() {
  TestRunner tr;
  tr.RunTest(DequeTests, "DequeTests");
  tr.RunTest(QueueTests, "QueueTests");
  tr.RunTest(StackTests, "StackTests");
}

int main() {
  TestAll();
  return 0;
}