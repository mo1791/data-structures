#pragma once

#include <algorithm>
#include <cassert>
#include <exception>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

template <typename T>
class stack final {

    class node {
    public:
        explicit node(const T& value, node* next = nullptr)
            : data_(value)
            , next_(next) {};

        explicit node(T&& value, node* next = nullptr)
            : data_(std::move(value))
            , next_(next) {};

    private:
        T data_;
        node* next_;
    };

public:
    using value_type = T;
    using reference = typename std::add_lvalue_reference<T>::type;
    using pointer = typename std::add_pointer<T>::type;
    using const_reference = const reference;
    using const_pointer = const pointer;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

public:
    stack();

    stack(stack<T> const&);

    stack(stack<T>&&);

    stack<T>& operator=(stack<T>);

    bool empty() const;

    template <typename U>
    void push_front(U&&);

    template <typename U>
    void push(U&&);

    void pop_front();

    void pop();

    std::optional<T> peep() const;

    void print() const;

    ~stack();

    friend void swap(stack<T>& lhs, stack<T>& rhs)
    {
        using std::swap;
        swap(lhs.head_, rhs.head_);
    }

private:
    node* head_;
};

// start stack
template <typename T>
stack<T>::stack()
    : head_(nullptr)
{
}

template <typename T>
stack<T>::stack(stack<T> const& outer)
try : stack() {

    node *curr = outer.head_, *tracer = nullptr;

    head_ = new node(curr->data_);

    curr = curr->next_;

    tracer = head_;

    while (curr) {

        tracer->next_ = new node(curr->data_);
        tracer = tracer->next_;
        curr = curr->next_;
    }
} catch (std::bad_alloc const&) {

    std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa";
}

template <typename T>
stack<T>::stack(stack<T>&& outer)
    : stack()
{
    swap(*this, outer);
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T> rhs)
{
    swap(*this, rhs);
    return *this;
}

template <typename T>
bool stack<T>::empty() const { return head_ == nullptr; }

template <typename T>
template <typename U>
void stack<T>::push_front(U&& value)
try {

    node* _node = new node(std::forward<U>(value), head_);

    if (empty()) {

        head_ = _node;
        return;
    }

    head_ = _node;

} catch (std::bad_alloc const&) {

    std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa";
}

template <typename T>
template <typename U>
void stack<T>::push(U&& value)
{
    push_front(std::forward<U>(value));
}

template <typename T>
void stack<T>::pop_front()
{

    assert(!empty());

    node* curr = head_;
    head_ = head_->next_;
    curr = (free(curr), nullptr);
}

template <typename T>
void stack<T>::pop() { pop_front(); }

template <typename T>
std::optional<T> stack<T>::peep() const
{

    if (!empty()) {
        return head_->data_;
    }
    return std::nullopt;
}

template <typename T>
void stack<T>::print() const
{

    for (node* it = head_; it; it = it->next_)
        std::cout << it->data_ << ' ';

    std::cout << '\n';
}

template <typename T>
stack<T>::~stack()
{

    while (!empty())
        pop();
}