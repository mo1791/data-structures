#pragma once

#include <cassert>
#include <iostream>
#include <optional>
#include <type_traits>

template <typename> class linkedList;
template <typename> class BaseIterator;
template <typename> class BaseReverseIterator;
template <typename> class ForwardIterator;
template <typename> class BackwardIterator;

/* START CONSTRAINTS */
template <typename T> concept IsClass = std::is_class<T>::value;

template <typename T, typename U>
concept NonSelf = !std::is_same<typename std::decay<T>::type, U>::value &&
                  !std::is_base_of<U, typename std::decay<T>::type>::value;
/* END CONSTRAINTS */

/* START NODE */
class Node {
  template <typename> friend class linkedList;
  template <typename> friend class BaseIterator;
  template <typename> friend class BaseReverseIterator;
  template <typename> friend class ForwardIterator;
  template <typename> friend class BackwardIterator;

protected:
  void push_front(Node *_node) noexcept {
    _node->next_ = next_;
    _node->prev_ = this;
    next_->prev_ = _node;
    next_ = _node;
  }

  void push_back(Node *_node) noexcept {
    _node->prev_ = prev_;
    _node->next_ = this;
    prev_->next_ = _node;
    prev_ = _node;
  }

  void unlink() {
    Node *next = next_, *prev = prev_;
    next->prev_ = prev;
    prev->next_ = next;
    next_ = prev_ = this;
  }

public:
  Node() noexcept : prev_(this), next_(this) {}

  virtual ~Node() { unlink(); }

protected:
  Node *prev_;
  Node *next_;
};


// 
template <typename T> class node : public Node {
  friend class linkedList<T>;
  friend class BaseIterator<T>;
  friend class BaseReverseIterator<T>;
  friend class ForwardIterator<T>;
  friend class BackwardIterator<T>;

private:
  node(const T &_data) noexcept : data_(_data) {}

  node(T &&_data) noexcept : data_(std::move(_data)) {}

  T &data() { return data_; }

  T const &data() const { return data_; }

private:
  T data_;
};

// 

/* END NODE */

// //
template <typename T> class BaseIterator {
protected:
  node<T> *_node() const { return static_cast<node<T> *>(node_); }

public:
  BaseIterator(Node *_node) : node_(_node) {}

  T &operator*() { return _node()->data_; }

  T const &operator*() const { return _node()->data_; }

  bool operator==(BaseIterator rhs) const { return rhs.node_ == node_; }

  bool operator!=(BaseIterator rhs) const { return rhs.node_ != node_; }

  // operator BaseIterator() const { return node_; }

protected:
  Node *node_;
};

//
template <typename T> class ForwardIterator : public BaseIterator<T> {
protected:
  using BaseIterator<T>::node_;

public:
  using BaseIterator<T>::BaseIterator;

  ForwardIterator &operator++() {
    node_ = node_->next_;
    return *this;
  }

  ForwardIterator operator++(int) {
    ForwardIterator tmp(node_);
    ++(*this);
    return tmp;
  }
};

//
template <typename T> class Iterator : public ForwardIterator<T> {
public:
  using ForwardIterator<T>::ForwardIterator;
};

template <IsClass T> class Iterator<T> : public ForwardIterator<T> {
protected:
  using ForwardIterator<T>::_node;

public:
  using ForwardIterator<T>::ForwardIterator;

  T *operator->() { return &_node()->data(); }

  T const *operator->() const { return &_node()->data(); }
};
//

//
template <typename T> class BackwardIterator : public BaseIterator<T> {
protected:
  using BaseIterator<T>::node_;

public:
  using BaseIterator<T>::BaseIterator;

  BackwardIterator &operator++() {
    node_ = node_->prev_;
    return *this;
  }

  BackwardIterator operator++(int) {
    BackwardIterator tmp(node_);
    ++(*this);
    return tmp;
  }
};

template <typename T> class ReverseIterator : public BackwardIterator<T> {
public:
  using BackwardIterator<T>::BackwardIterator;
};

template <IsClass T> class ReverseIterator<T> : public BackwardIterator<T> {
protected:
  using BackwardIterator<T>::_node;

public:
  using BackwardIterator<T>::BackwardIterator;

  T *operator->() { return &_node()->data(); }

  T const *operator->() const { return &_node()->data(); }
};
//

// //

//
template <typename T> class linkedList final {
public:
  using value_type = T;
  using reference = typename std::add_lvalue_reference<T>::type;
  using pointer = typename std::add_pointer<T>::type;
  using const_reference = const reference;
  using const_pointer = const pointer;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using iterator = Iterator<T>;
  using const_iterator = Iterator<const T>;
  using reverse_iterator = ReverseIterator<T>;
  using const_reverse_iterator = ReverseIterator<const T>;

public:
  linkedList() = default;

  linkedList(std::initializer_list<T>);

  linkedList(linkedList const &);

  linkedList(linkedList &&);

  linkedList &operator=(linkedList);

  template <typename U> void push_front(U &&);

  template <typename U> void push_back(U &&);

  void pop_front();

  void pop_back();

  bool empty() const;

  size_type size() const;

  std::optional<value_type> front() const;

  std::optional<value_type> back() const;

  const_iterator data() const;

  iterator begin();

  const_iterator begin() const;

  const_iterator cbegin() const;

  iterator end();

  const_iterator end() const;

  const_iterator cend() const;

  reverse_iterator rbegin();

  const_reverse_iterator rbegin() const;

  const_reverse_iterator crbegin() const;

  reverse_iterator rend();

  const_reverse_iterator rend() const;

  const_reverse_iterator crend() const;

  friend void swap(linkedList<T> &lhs, linkedList<T> &rhs) {
    using std::swap;
    swap(lhs.list_, rhs.list_);
    swap(lhs.size_, rhs.size_);
  }

  void print_forward() {
    iterator it = begin();

    while (it != end()) {
      std::cout << *it << ' ';
      ++it;
    }
    std::cout << '\n';
  }

  void print_backward() {
    reverse_iterator it = rbegin();

    while (it != rend()) {
      std::cout << *it << ' ';
      ++it;
    }
    std::cout << '\n';
  }

  ~linkedList();

private:
  Node list_;
  size_type size_{0};
};

// // start linkedList

template <typename T> linkedList<T>::linkedList(std::initializer_list<T> list) {
  for (auto value : list)
    push_back(value);
}

template <typename T> linkedList<T>::linkedList(linkedList const &outer) {
  for (auto value : outer)
    push_back(value);
}

template <typename T> linkedList<T>::linkedList(linkedList &&outer) {
  swap(*this, outer);
}

template <typename T> linkedList<T> &linkedList<T>::operator=(linkedList list) {
  swap(*this, list);
  return *this;
}

//
template <typename T>
template <typename U>
void linkedList<T>::push_front(U &&data) {
  list_.push_front(new node<T>(std::forward<U>(data)));
  size_ = size_ + 1;
}

template <typename T>
template <typename U>
void linkedList<T>::push_back(U &&data) {
  list_.push_back(new node<T>(std::forward<U>(data)));
  size_ = size_ + 1;
}

template <typename T> void linkedList<T>::pop_front() {
  assert(list_.next_ != &list_);

  Node *curr = list_.next_;
  curr->next_->prev_ = &list_;
  list_.next_ = curr->next_;

  curr = (free(curr), nullptr);

  size_ = size_ - 1;
}

template <typename T> void linkedList<T>::pop_back() {
  assert(list_.next_ != &list_);

  Node *curr = list_.prev_;
  curr->prev_->next_ = &list_;
  list_.prev_ = curr->prev_;

  curr = (free(curr), nullptr);

  size_ = size_ - 1;
}

template <typename T> bool linkedList<T>::empty() const {
  return &list_ == list_.next_;
}

template <typename T>
typename linkedList<T>::size_type linkedList<T>::size() const {
  return size_;
}

template <typename T> std::optional<T> linkedList<T>::front() const {
  return !empty() ? *begin() : std::nullopt;
}

template <typename T> std::optional<T> linkedList<T>::back() const {
  return !empty() ? *rbegin() : std::nullopt;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::data() const {
  return begin();
}

template <typename T> typename linkedList<T>::iterator linkedList<T>::begin() {
  return list_.next_;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::begin() const {
  return list_.next_;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::cbegin() const {
  return list_.next_;
}

template <typename T> typename linkedList<T>::iterator linkedList<T>::end() {
  return &list_;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::end() const {
  return &list_;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::cend() const {
  return &list_;
}

template <typename T>
typename linkedList<T>::reverse_iterator linkedList<T>::rbegin() {
  return list_.prev_;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::rbegin() const {
  return list_.prev_;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::crbegin() const {
  return list_.prev_;
}

template <typename T>
typename linkedList<T>::reverse_iterator linkedList<T>::rend() {
  return &list_;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::rend() const {
  return &list_;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::crend() const {
  return &list_;
}

template <typename T> linkedList<T>::~linkedList() {
  while (list_.next_ != &list_)
    pop_front();
}
//
// // end linkedList
