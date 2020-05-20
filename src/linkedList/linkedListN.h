#pragma once

#include <algorithm>
#include <cassert>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>

/* FORWARD DECLARING */
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

/* START NODE CLASS */
template <typename T> class Node {

friend class linkedList<T>;
friend class BaseIterator<T>;
friend class BaseReverseIterator<T>;
friend class ForwardIterator<T>;
friend class BackwardIterator<T>;

public:
  explicit Node(const T &value, Node *next = nullptr,
    Node *prev = nullptr) noexcept
  : data_(value), next_(next), prev_(prev) {}

  explicit Node(T &&value, Node *next = nullptr, Node *prev = nullptr) noexcept
  : data_(std::move(value)), next_(next), prev_(prev) {}

private:
  T data_;
  Node *next_;
  Node *prev_;
};

/* END NODE CLASS */

/* START ITERATOR CLASSES */

/* START BASEITERATOR CLASS*/

template <typename T> class BaseIterator {
public:
  BaseIterator(Node<T> *_node) : node_(_node) {}

  T &operator*() { return node_->data_; }

  T const &operator*() const { return node_->data_; }

  bool operator==(BaseIterator rhs) const { return rhs.node_ == node_; }

  bool operator!=(BaseIterator rhs) const { return rhs.node_ != node_; }

  // operator BaseIterator() const { return node_; }

protected:
  Node<T> *node_;
};

/* END BASEITERATOR CLASS */

/* START FORWARDITERATOR CLASS */
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

template <typename T> class Iterator : public ForwardIterator<T> {

public:
  using ForwardIterator<T>::ForwardIterator;

  // operator const Iterator() const { return node_; }
};

template <IsClass T> class Iterator<T> : public ForwardIterator<T> {

protected:
  using ForwardIterator<T>::node_;

public:
  using ForwardIterator<T>::ForwardIterator;

  T *operator->() { return &node_->data_; }

  T const *operator->() const { return &node_->data_; }

  // operator Iterator() const { return node_; }
};

/* END FORWARDITERATOR CLASS */

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
  using BackwardIterator<T>::node_;

public:
  using BackwardIterator<T>::BackwardIterator;

  T *operator->() { return &node_->data_; }

  T const *operator->() const { return &node_->data_; }
};

/* END ITERATOR CLASSES */

/* START LINKEDLIST CLASS*/

template <typename T> class linkedList final {

using node = Node<T>;

private:
  /* NODE CLASS */
  std::size_t size_;
  node *head_;
  node *tail_;

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
  linkedList();

  linkedList(std::initializer_list<T>);

  linkedList(linkedList<T> const &);

  linkedList(linkedList<T> &&);

  linkedList<T> &operator=(linkedList<T>);

  template <typename U> void push_front(U &&);

  template <typename U> void push_back(U &&);

  template <typename U> void push_after(const U &, U &&);

  template <typename U> void push_before(const U &, U &&);

  void pop_front();

  void pop_back();

  void pop_before(const T &);

  void pop_after(const T &);

  bool empty() const;

  size_type size() const;

  std::optional<T> front() const;

  std::optional<T> back() const;

  const_iterator data() const;

  iterator begin();

  const_iterator begin() const;

  const_iterator cbegin() const;

  reverse_iterator rbegin();

  const_reverse_iterator rbegin() const;

  const_reverse_iterator crbegin() const;

  iterator end();

  const_iterator end() const;

  const_iterator cend() const;

  reverse_iterator rend();

  const_reverse_iterator rend() const;

  const_reverse_iterator crend() const;

  void print_forward() const {

    auto it = begin();

    while (it != end()) {

      std::cout << *it << ' ';
      ++it;
  }

  std::cout << '\n';
}

void print_backward() const {

    auto it = rbegin();

    while (it != rend()) {

      std::cout << *it << ' ';
      ++it;
  }
  std::cout << '\n';
}

~linkedList();

friend void swap(linkedList<T> &lhs, linkedList<T> &rhs) {

    using std::swap;
    swap(lhs.size_, rhs.size_);
    swap(lhs.head_, rhs.head_);
    swap(lhs.tail_, rhs.tail_);
}
};

/* END LINKEDLIST CLASS */

template <typename T>
std::ostream &operator<<(std::ostream &out, linkedList<T> const &ls) {
  for (auto value : ls)
    out << value << ' ';
return out << '\n';
}

template <typename T>
linkedList<T>::linkedList() : size_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
linkedList<T>::linkedList(std::initializer_list<T> list) : linkedList() {

  for (auto value : list)
    push_back(std::move(value));
}

template <typename T>
linkedList<T>::linkedList(linkedList<T> const &outer) : linkedList() {

  for (auto value : outer)
    push_back(std::move(value));
}

template <typename T>
linkedList<T>::linkedList(linkedList<T> &&outer) : linkedList() {
  swap(*this, outer);
}

template <typename T>
linkedList<T> &linkedList<T>::operator=(linkedList<T> rhs) {
  swap(*this, rhs);
  return *this;
}

template <typename T> bool linkedList<T>::empty() const {
return head_ == nullptr;
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

template <typename T>
template <typename U>
void linkedList<T>::push_front(U &&value) try {

  node *_node = new node(std::forward<U>(value), head_);

  if (empty()) {

    head_ = tail_ = _node;

    size_ = size_ + 1;
    return;
}

head_->prev_ = _node;
head_ = _node;

size_ = size_ + 1;

} catch (std::bad_alloc const &) {

  std::cout << "bfr, Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
}

template <typename T>
template <typename U>
void linkedList<T>::push_back(U &&value) try {

  node *_node = new node(std::forward<U>(value), nullptr, tail_);

  if (empty()) {

    head_ = tail_ = _node;

    size_ = size_ + 1;
    return;
}

tail_->next_ = _node;
tail_ = _node;

size_ = size_ + 1;

} catch (std::bad_alloc const &) {

  std::cout << "back,Uncaught Exception 'std::bad_alloc' → ALLO FAILD\xa";
}

template <typename T>
template <typename U>
void linkedList<T>::push_after(const U &key, U &&value) {

  assert(!empty());

  node *curr = head_;

  while (curr) {
    if (curr->data_ == key)
      break;
  curr = curr->next_;
}

if (curr == nullptr)
    return;

if (curr == tail_) {
    push_back(std::forward<U>(value));
    return;
}

try {

    node *_node = new node(std::forward<U>(value), curr->next_, curr);

    curr->next_->prev_ = _node;
    curr->next_ = _node;

    size_ = size_ + 1;

} catch (std::bad_alloc const &) {

    std::cout << "bfr, Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
}
}

template <typename T>
template <typename U>
void linkedList<T>::push_before(const U &key, U &&value) {

  assert(!empty());

  if (head_->data_ == key) {
    push_front(std::forward<U>(value));
    return;
}

try {

    node *curr = head_->next_;

    while (curr) {
      if (curr->data_ == key)
        break;
    curr = curr->next_;
}

if (curr == nullptr)
  return;

node *_node = new node(std::forward<U>(value), curr, curr->prev_);

curr->prev_->next_ = _node;
curr->prev_ = _node;

size_ = size_ + 1;

} catch (std::bad_alloc const &) {

    std::cout << "bfr, Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
}
}

template <typename T> void linkedList<T>::pop_front() {

assert(!empty());

node *curr = head_;
head_ = head_->next_;

if (head_)
    head_->prev_ = nullptr;

curr = (free(curr), nullptr);

size_ = size_ - 1;
}

template <typename T> void linkedList<T>::pop_back() {

assert(!empty());

node *curr = tail_;
tail_ = tail_->prev_;
tail_->next_ = nullptr;

curr = (free(curr), nullptr);

size_ = size_ - 1;
}

template <typename T> void linkedList<T>::pop_before(const T &key) {

assert(!empty());

node *curr = head_;

for (node *next = head_->next_; next;) {
    if (next->data_ == key)
      break;
  curr = next;
  next = next->next_;
}

if (curr == tail_)
    return;

if (curr == head_) {
    pop_front();
    return;
}

curr->prev_->next_ = curr->next_;
curr->next_->prev_ = curr->prev_;

curr = (free(curr), nullptr);

size_ = size_ - 1;
}

template <typename T> void linkedList<T>::pop_after(const T &key) {

assert(!empty());

node *curr = head_;
node *next = head_->next_;

while (next) {

    if (curr->data_ == key)
      break;
  curr = next;
  next = next->next_;
}

if (curr == tail_)
    return;

if (next == tail_) {
    pop_back();
    return;
}

curr->next_ = next->next_;
next->next_->prev_ = curr;

next = (free(next), nullptr);

size_ = size_ - 1;
}

template <typename T> typename linkedList<T>::iterator linkedList<T>::begin() {
return head_;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::begin() const {
  return head_;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::cbegin() const {
  return head_;
}

template <typename T>
typename linkedList<T>::reverse_iterator linkedList<T>::rbegin() {
  return tail_;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::rbegin() const {
  return tail_;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::crbegin() const {
  return tail_;
}

template <typename T> typename linkedList<T>::iterator linkedList<T>::end() {
return nullptr;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::end() const {
  return nullptr;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::cend() const {
  return nullptr;
}

template <typename T>
typename linkedList<T>::reverse_iterator linkedList<T>::rend() {
  return nullptr;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::rend() const {
  return nullptr;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::crend() const {
  return nullptr;
}

template <typename T> linkedList<T>::~linkedList() {

while (!empty())
    pop_front();
}