// Copyright 2020 Osipova Anastasiya anastasiyaosipova2001@gmail.com

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <algorithm>
#include <type_traits>
#include <utility>

template <typename T>

struct Elem {
  T val;
  Elem<T>* prev;
};
template <typename T>
class NonCopStack {
 public:
  NonCopStack() = default;
  NonCopStack(const NonCopStack&) = delete;
  NonCopStack(NonCopStack&&) = default;
  ~NonCopStack();

  auto operator=(const NonCopStack<T>&) -> NonCopStack<T>& = delete;
  auto operator=(NonCopStack<T>&&) noexcept -> NonCopStack<T>& = default;

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  size_t Size() const;

 protected:
  Elem<T>* Head = nullptr;
};

template <typename T>
void NonCopStack<T>::push(T&& value) {
  Elem<T>* temp = Head;
  Head = new Elem<T>{std::forward<T>(value), temp};
}

template <typename T>
void NonCopStack<T>::push(const T& value) {
  Elem<T>* temp = Head;
  Head = new Elem<T>{value, temp};
}

template <typename T>
void NonCopStack<T>::pop() {
  if (Head == nullptr) {
    throw std::exception();
  }
  Elem<T>* temp = Head;
  Head = Head->prev;
  delete temp;
}

template <typename T>
const T& NonCopStack<T>::head() const {
  if (Head == nullptr) {
    throw std::exception();
  }
  return Head->val;
}

template <typename T>
size_t NonCopStack<T>::Size() const {
  size_t _size = 0;
  Elem<T>* temp = Head;
  while (temp != nullptr) {
    ++_size;
    temp = temp->prev;
  }
  return _size;
}

template <typename T>
NonCopStack<T>::~NonCopStack() {
  while (Head != nullptr) {
    pop();
  }
}
#endif // INCLUDE_HEADER_HPP_
