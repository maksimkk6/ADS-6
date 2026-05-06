// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };
  Node* head;
  Node* tail;

 public:
  TPQueue() : head(nullptr), tail(nullptr) {}
  ~TPQueue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }
  T pop() {
    T result = head->data;
    Node* temp = head;
    head = head->next;
    if (head == nullptr) {
      tail = nullptr;
    }
    delete temp;
    return result;
  }
  void push(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      return;
    }
    if (value.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }
    Node* current = head;
    while (current->next != nullptr &&
           current->next->data.prior >= value.prior) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    if (newNode->next == nullptr) {
      tail = newNode;
    }
  }
  bool empty() const {
    return head == nullptr;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
