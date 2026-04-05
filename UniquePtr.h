#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
template <typename T> class UniquePtr {
public:
  explicit UniquePtr(T *ptr);
  UniquePtr(UniquePtr &rhs) = delete;
  ~UniquePtr();
  UniquePtr &operator=(UniquePtr &&rhs) noexcept;
  UniquePtr &operator=(UniquePtr &rhs) = delete;
  explicit UniquePtr(UniquePtr &&ptr);
  UniquePtr() = default;
  T *get() const;
  T *release();
  void reset(T *ptr);
  void swap(UniquePtr &other) noexcept;
  T &operator*() const;
  bool operator==(const UniquePtr &rhs) const;
  T *operator->() const;
  explicit operator bool() const;

private:
  T *pointer_ = nullptr;
};

template <typename T> class UniquePtr<T[]> {
public:
  explicit UniquePtr(T *ptr);
  explicit UniquePtr(UniquePtr &&rhs);
  explicit UniquePtr(const UniquePtr &rhs) = delete;
  UniquePtr() = default;
  ~UniquePtr();
  T &operator=(const UniquePtr &rhs) = delete;
  T &operator=(UniquePtr &&rhs);
  bool operator==(const UniquePtr &rhs) const;
  T *operator->() const;
  T &operator[](int ind) const;
  T *get() const;
  void swap(UniquePtr &rhs);
  T *release();

private:
  T *pointer_ = nullptr;
};

template <typename T> UniquePtr<T>::UniquePtr(T *ptr) { pointer_ = ptr; }

template <typename T> UniquePtr<T>::UniquePtr(UniquePtr &&ptr) {
  pointer_ = ptr.pointer_;
  pointer_ = nullptr;
}

template <typename T> UniquePtr<T>::~UniquePtr() { delete pointer_; }

template <typename T>
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr &&rhs) noexcept {
  if (rhs.pointer_ != pointer_) {
    delete pointer_;
    pointer_ = rhs.pointer_;
    rhs.pointer_ = nullptr;
  }
  return *this;
}

template <typename T> T *UniquePtr<T>::get() const { return pointer_; }

template <typename T> T *UniquePtr<T>::release() {
  T *ptr = pointer_;
  pointer_ = nullptr;
  return ptr;
}

template <typename T> void UniquePtr<T>::reset(T *ptr) {
  if (ptr != pointer_) {
    delete pointer_;
    pointer_ = ptr;
  }
}

template <typename T> void UniquePtr<T>::swap(UniquePtr &other) noexcept {
  std::swap(other.pointer_, pointer_);
}

template <typename T> T &UniquePtr<T>::operator*() const { return *pointer_; }

template <typename T> T *UniquePtr<T>::operator->() const { return pointer_; }

template <typename T> UniquePtr<T>::operator bool() const {
  return pointer_ != nullptr;
}

template <typename T>
bool UniquePtr<T>::operator==(const UniquePtr &rhs) const {
  return rhs.pointer_ == pointer_;
}

template <typename T> UniquePtr<T[]>::UniquePtr(T *ptr) : pointer_(ptr) {}

template <typename T> UniquePtr<T[]>::UniquePtr(UniquePtr &&ptr) {
  pointer_ = ptr.pointer_;
  ptr.pointer_ = nullptr;
}

template <typename T> UniquePtr<T[]>::~UniquePtr() { delete[] pointer_; }

template <typename T> T &UniquePtr<T[]>::operator=(UniquePtr &&rhs) {
  if (rhs.pointer_ != pointer_) {
    delete[] pointer_;
    pointer_ = rhs.pointer_;
    rhs.pointer_ = nullptr;
  }
  return *this;
}

template <typename T>
bool UniquePtr<T[]>::operator==(const UniquePtr &rhs) const {
  return rhs.pointer_ == pointer_;
}

template <typename T> T *UniquePtr<T[]>::operator->() const { return pointer_; }

template <typename T> T &UniquePtr<T[]>::operator[](int ind) const {
  return pointer_[ind];
}

template <typename T> T *UniquePtr<T[]>::release() { return pointer_; }

template <typename T> void UniquePtr<T[]>::swap(UniquePtr &rhs) {
  std::swap(pointer_, rhs.pointer_);
}

template <typename T> T *UniquePtr<T[]>::get() const { return pointer_; }
