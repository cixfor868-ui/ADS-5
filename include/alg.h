// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int MaxSize>
class TStack {
 private:
  T elements[MaxSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(T value) {
    if (topIndex < MaxSize - 1) {
      elements[++topIndex] = value;
    }
  }

  void pop() {
    if (topIndex >= 0) {
      --topIndex;
    }
  }

  T get() const {
    if (topIndex >= 0) {
      return elements[topIndex];
    }
    return T();
  }

  bool isempty() const {
    return topIndex == -1;
  }

  int stack_size() const {
    return topIndex + 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
