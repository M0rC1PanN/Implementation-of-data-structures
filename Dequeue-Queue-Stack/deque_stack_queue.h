#ifndef DEQUEUE_QUEUE_STACK_DEQUE_STACK_QUEUE_H
#define DEQUEUE_QUEUE_STACK_DEQUE_STACK_QUEUE_H
#include <vector>
#include <iostream>

template <typename T>
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
  std::vector<T> data_;
  int head_;
  int tail_;
  int size_;
};

template <typename T>
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
  Deque<T> queue_;
};

template <typename T>
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
  Deque<T> stack_;
};

#endif //DEQUEUE_QUEUE_STACK_DEQUE_STACK_QUEUE_H
