// Copyright 2025 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

int apply_op(int left, int right, char op) {
  if (op == '+') return left + right;
  if (op == '-') return left - right;
  if (op == '*') return left * right;
  if (op == '/') return left / right;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> st;
  std::string result;
  int n = static_cast<int>(inf.size());

  for (int i = 0; i < n; ++i) {
    char c = inf[i];

    if (c == ' ') {
      continue;
    }

    if (is_digit(c)) {
      while (i < n && is_digit(inf[i])) {
        result += inf[i];
        ++i;
      }
      result += ' ';
      --i;
    } else if (c == '(') {
      st.push(c);
    } else if (c == ')') {
      while (!st.isempty() && st.get() != '(') {
        result += st.get();
        result += ' ';
        st.pop();
      }
      if (!st.isempty()) {
        st.pop();
      }
    } else {
      while (!st.isempty() && st.get() != '(' &&
             priority(st.get()) >= priority(c)) {
        result += st.get();
        result += ' ';
        st.pop();
      }
      st.push(c);
    }
  }

  while (!st.isempty()) {
    result += st.get();
    result += ' ';
    st.pop();
  }

  if (!result.empty() && result[result.size() - 1] == ' ') {
    result.pop_back();
  }

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> st;
  int n = static_cast<int>(post.size());

  for (int i = 0; i < n; ++i) {
    char c = post[i];

    if (c == ' ') {
      continue;
    }

    if (is_digit(c)) {
      int number = 0;
      while (i < n && is_digit(post[i])) {
        number = number * 10 + (post[i] - '0');
        ++i;
      }
      st.push(number);
      --i;
    } else {
      int right = st.get();
      st.pop();
      int left = st.get();
      st.pop();
      st.push(apply_op(left, right, c));
    }
  }
  
  return st.get();
}
