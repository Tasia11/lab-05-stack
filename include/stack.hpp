// Copyright 2020 Osipova Anastasiya anastasiyaosipova2001@gmail.com
#ifndef TEMPLATE_STACK_HPP
#define TEMPLATE_STACK_HPP
#include "header.hpp"
template <typename T>
class stack : public NonCopStack<T> {
 public:
  template <typename... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  const T& head() const;
  T pop();
};
template <typename T>
template <typename... Args>
void stack<T>::push_emplace(Args&&... value) {
  if ((std::is_copy_constructible<T>::value) ||
      (std::is_copy_assignable<T>::value)) {
    throw std::exception();
  }
  auto* elem = new Elem<T>{{std::forward<Args>(value)...}, NonCopStack<T>::Head};
  NonCopStack<T>::Head = elem;
}
template <typename T>
void stack<T>::push(T&& value) {
  if ((std::is_copy_constructible<T>::value) ||
      (std::is_copy_constructible<T>::value)) {
    throw std::exception();
  }
  auto* elem = new Elem<T>{std::forward<T>(value), NonCopStack<T>::Head};
  NonCopStack<T>::Head = elem;
}
template <typename T>
T stack<T>::pop() {
  if (NonCopStack<T>::Head == nullptr) {
    throw std::exception();
  }
  auto * temp = NonCopStack<T>::Head;
  T val = std::move(NonCopStack<T>::Head->val);
  NonCopStack<T>::Head = NonCopStack<T>::Head->prev;
  delete temp;
  return val;
}
template <typename T>
const T& stack<T>::head() const {
  if (NonCopStack<T>::Head == nullptr) {
    throw std::exception();
  }
  return NonCopStack<T>::Head->val;
}
#endif  // TEMPLATE_STACK_HPP
