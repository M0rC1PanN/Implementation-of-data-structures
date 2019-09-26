#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <typeinfo>
#include <algorithm>

using namespace std;

template<typename T>
class VectorInternalsAccessor;

template<class T>
class Vector {
 public:
  Vector() : size_(0), allocated_size_(1), data_(new T[1]) {}
  Vector(const Vector& vector) : size_(vector.size_),
                                 allocated_size_(vector.allocated_size_),
                                 data_(new T[vector.allocated_size_]) {
    for (size_t i = 0; i < vector.size_; i++) {
      data_[i] = vector.data_[i];
    }
  }

  Vector& operator=(Vector const& vector) {
    if (allocated_size_ != vector.allocated_size_) {
      delete[] data_;
      data_ = new T[vector.allocated_size_];
      allocated_size_ = vector.allocated_size_;
    }
    size_ = vector.size_;
    for (size_t i = 0; i < max(vector.size_, size_); i++) {
      data_[i] = vector.data_[i];
    }
    return *this;
  }

  Vector(Vector&& vector) noexcept : size_(vector.size_),
                                     allocated_size_(vector.allocated_size_),
                                     data_(vector.data_) {
    vector.size_ = 0;
    vector.allocated_size_ = 1;
    vector.data_ = nullptr;
    vector.data_ = new T[1];
  }
  Vector& operator=(Vector&& vector) noexcept {
    delete[] data_;
    data_ = vector.data_;
    allocated_size_ = vector.allocated_size_;
    size_ = vector.size_;
    vector.size_ = 0;
    vector.allocated_size_ = 1;
    vector.data_ = nullptr;
    vector.data_ = new T[1];
    return *this;
  }

  ~Vector() {
    delete[] data_;
  }

  size_t Size() const {
    return size_;
  }

  bool IsEmpty() const {
    return size_ == 0;
  }

  void PushBack(const T& value) {
    if (size_ + 1 > allocated_size_) {
      Relocate(2 * allocated_size_);
    }
    data_[size_] = value;
    ++size_;
  }

  void PopBack() {
    assert(size_ != 0);
    if (size_ - 1 < allocated_size_ / 4) {
      Relocate(allocated_size_ / 2);
    }
    --size_;
  }

  T& operator[](size_t i) {
    assert(i < size_);
    return data_[i];
  }

  const T& operator[](size_t i) const {
    assert(i < size_);
    return data_[i];
  }

  void PushFront(const T& value) {
    if (size_ + 1 > allocated_size_) {
      Relocate(2 * allocated_size_);
    }
    for (size_t i = size_; i > 0; i--) {
      data_[i] = data_[i - 1];
    }
    ++size_;
    data_[0] = value;
  }

  void PopFront() {
    assert(size_ != 0);
    if (size_ - 1 < allocated_size_ / 4) {
      Relocate(allocated_size_ / 2);
    }
    for (size_t i = 0; i < size_ - 1; i++) {
      data_[i] = data_[i + 1];
    }

    --size_;
  }

  template<class... Args>
  void EmplaceBack(Args&& ...args) {
    if (size_ + 1 > allocated_size_) {
      Relocate(2 * allocated_size_);
    }
    data_[size_] = T(forward<Args>(args)...);
    ++size_;
  }

  template<class... Args>
  void EmplaceFront(Args&& ...args) {
    if (size_ + 1 > allocated_size_) {
      Relocate(2 * allocated_size_);
    }
    for (size_t i = size_; i > 0; i--) {
      data_[i] = data_[i - 1];
    }
    ++size_;
    data_[0] = T(forward<Args>(args)...);
  }

  int Find(const T& value) const {
    for (size_t i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return -1;
  }

 protected:
  friend class VectorInternalsAccessor<T>;

  size_t size_;
  size_t allocated_size_;
  T* data_;
  void Relocate(size_t new_size) {
    T* copy = data_;
    data_ = new T[new_size];
    for (size_t i = 0; i < size_; i++) {
      data_[i] = copy[i];
    }
    delete[] copy;
    allocated_size_ = new_size;
  }
};


template<typename T>
class VectorInternalsAccessor {
 public:
  VectorInternalsAccessor() = delete;
  static size_t Size(const Vector<T>& vector) {
    return vector.size_;
  }
  static T* AllocData(const Vector<T>& vector) {
    return vector.data_;
  }
  static size_t AllocSize(const Vector<T>& vector) {
    return vector.allocated_size_;
  }
};

#endif //VECTOR_VECTOR_H
