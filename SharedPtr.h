#pragma once

template <typename T> class SharedPtr {
public:
  explicit SharedPtr(T *ptr);
  SharedPtr(const SharedPtr &rhs);
  explicit SharedPtr(SharedPtr &&rhs);
  ~SharedPtr();
  SharedPtr &operator=(const SharedPtr &rhs);
  SharedPtr &operator=(SharedPtr &&rhs);
  void DeleteMemory();
  T &operator*() const;
  T *operator->() const;
  int use_count() const;
  T *get() const;

private:
  T *pointer_;
  int *number_of_instances_;
};

template <typename T> SharedPtr<T>::SharedPtr(T *ptr) {
  pointer_ = ptr;
  number_of_instances_ = new int(1);
}

template <typename T> SharedPtr<T>::SharedPtr(const SharedPtr &rhs) {
  pointer_ = rhs.pointer_;
  number_of_instances_ = rhs.number_of_instances_;
  (*number_of_instances_)++;
}

template <typename T> SharedPtr<T>::SharedPtr(SharedPtr &&rhs) {
  if (&rhs != this) {
    pointer_ = rhs.pointer_;
    number_of_instances_ = rhs.number_of_instances_;
    rhs.pointer_ = nullptr;
    rhs.number_of_instances_ = nullptr;
  }
}

template <typename T> SharedPtr<T>::~SharedPtr() { DeleteMemory(); }

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr &rhs) {
  if (this != &rhs) {
    DeleteMemory();
    pointer_ = rhs.pointer_;
    number_of_instances_ = rhs.number_of_instances_;
    (*number_of_instances_)++;
  }
  return *this;
}

template <typename T> SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr &&rhs) {
  if (this != &rhs) {
    DeleteMemory();
    pointer_ = rhs.pointer_;
    number_of_instances_ = rhs.number_of_instances_;
    rhs.pointer_ = nullptr;
    rhs.number_of_instances_ = nullptr;
  }
  return *this;
}

template <typename T> void SharedPtr<T>::DeleteMemory() {
  if (number_of_instances_ == nullptr) {
    delete pointer_;
  } else {
    (*number_of_instances_)--;
    if (*number_of_instances_ == 0) {
      delete pointer_;
      delete number_of_instances_;
    }
  }
}

template <typename T> int SharedPtr<T>::use_count() const {
  if (number_of_instances_ == nullptr) {
    return 0;
  }
  return *number_of_instances_;
}

template <typename T> T *SharedPtr<T>::operator->() const { return pointer_; }

template <typename T> T &SharedPtr<T>::operator*() const { return *pointer_; }

template <typename T> T *SharedPtr<T>::get() const { return pointer_; }
