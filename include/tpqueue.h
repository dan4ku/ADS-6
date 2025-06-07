// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#pragma once
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct item {
  T data;
  item* next;
  explicit item(T data) : data(data), next(nullptr) {}
  };
  item* head;
  item* tail;
  public:
   TPQueue() : head(nullptr), tail(nullptr) {}
   ~TPQueue() {
     while (head) {
       item* temp = head;
       head = head->next;
       delete temp;
    }
  }
  T pop() {
    if (!head)
      throw std::runtime_error("empty");
    item* temp = head;
    T result = temp->data;
    head = head->next;
    if (!head)
      tail = nullptr;
    delete temp;
    return result;
  }
  void push(T value) {
    item* newItem = new item(value);
    if (!head || value.prior > head->data.prior) {
      newItem->next = head;
      head = newItem;
      if (!tail) tail = head;
      return;
    }
    item* current = head;
    while (current->next && current->next->data.prior >= value.prior) {
      current = current->next;
    }
    newItem->next = current->next;
    current->next = newItem;
    if (!newItem->next) {
      tail = newItem;
    }
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
