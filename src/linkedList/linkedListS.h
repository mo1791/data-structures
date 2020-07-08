#pragma once

#include <cassert>
#include <iostream>
#include <optional>
#include <type_traits>

template <typename>
class linkedList;
template <typename>
class BaseIterator;
template <typename>
class BaseReverseIterator;
template <typename>
class Iterator;
template <typename>
class ReverseIterator;

/* START CONSTRAINTS */
template <typename T>
concept IsClass = std::is_class<T>::value;

template <typename T, typename U>
concept NonSelf = !std::is_same<typename std::decay<T>::type, U>::value && !std::is_base_of<U, typename std::decay<T>::type>::value;
/* END CONSTRAINTS */

/* START NODE */
template <typename T>
class node {
    friend class linkedList<T>;
    friend class BaseIterator<node<T>>;
    friend class BaseIterator<const node<T>>;
    friend class BaseReverseIterator<node<T>>;
    friend class BaseReverseIterator<const node<T>>;
    friend class Iterator<node<T>>;
    friend class Iterator<const node<T>>;
    friend class ReverseIterator<node<T>>;
    friend class ReverseIterator<const node<T>>;

public:
    using value_type      = T;
    using reference       = typename std::add_lvalue_reference<T>::type;
    using const_reference = typename std::add_const<T>::type&;
    using pointer         = typename std::add_pointer<T>::type;
    using const_pointer   = typename std::add_const<T>::type*;
    
protected:
    void push_front(node* _node) noexcept
    {
        _node->next_ = next_;
        _node->prev_ = this;
        next_->prev_ = _node;
        next_ = _node;
    }

    void push_back(node* _node) noexcept
    {
        _node->prev_ = prev_;
        _node->next_ = this;
        prev_->next_ = _node;
        prev_ = _node;
    }

    void unlink()
    {
        node *next = next_, *prev = prev_;
        next->prev_ = prev;
        prev->next_ = next;
        next_ = prev_ = this;
    }

public:
    node() noexcept
        : data_(0)
        , prev_(this)
        , next_(this) {}
    
    node(const T& _data) noexcept
        : data_(_data) 
        , prev_(this)
        , next_(this)
    {
    }

    node(T&& _data) noexcept
        : data_(std::move(_data)) 
        , prev_(this)
        , next_(this)
    {
    }
    
    friend void swap(node& lhs, node& rhs) {
        using std::swap;
        swap(lhs.data_, rhs.data_);
        swap(lhs.prev_, rhs.prev_);
        swap(lhs.next_, rhs.next_);
    }
    
    
    T& operator*() { return data_; }
    
    T const& operator*() const { return data_; }

    virtual ~node() { unlink(); }

protected:
    T data_;
    node* prev_;
    node* next_;
};

//

/* END NODE */

// //
template <typename T>
class BaseIterator {

public:
    BaseIterator(T* _node)
        : node_(_node)
    {
    }

    decltype(auto) operator*() { return **node_; }

    decltype(auto) operator*() const { return **node_; }
    
    decltype(auto) operator->() { return &**node_; }

    decltype(auto) operator->() const { return &**node_; }

    bool operator==(BaseIterator rhs) const { return rhs.node_ == node_; }

    bool operator!=(BaseIterator rhs) const { return rhs.node_ != node_; }

    // operator BaseIterator() const { return node_; }

protected:
    T* node_;
};

//
template <typename T>
class Iterator : public BaseIterator<T> {
protected:
    using BaseIterator<T>::node_;

public:
    using BaseIterator<T>::BaseIterator;

    Iterator& operator++()
    {
        node_ = node_->next_;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator tmp(node_);
        ++(*this);
        return tmp;
    }
};

//
template <typename T>
class ReverseIterator : public BaseIterator<T> {
protected:
    using BaseIterator<T>::node_;

public:
    using BaseIterator<T>::BaseIterator;

    ReverseIterator& operator++()
    {
        node_ = node_->prev_;
        return *this;
    }

    ReverseIterator operator++(int)
    {
        ReverseIterator tmp(node_);
        ++(*this);
        return tmp;
    }
};
//

// //

//
template <typename T>
class linkedList final {
public:
    using value_type              = T;
    using reference               = typename std::add_lvalue_reference<T>::type;
    using pointer                 = typename std::add_pointer<T>::type;
    using const_reference         = typename std::add_const<T>::type&;
    using const_pointer           = typename std::add_const<T>::type*;
    using size_type               = std::size_t;
    using difference_type         = std::ptrdiff_t;
    using iterator                = Iterator<node<T>>;
    using const_iterator          = Iterator<const node<T>>;
    using reverse_iterator        = ReverseIterator<node<T>>;
    using const_reverse_iterator  = ReverseIterator<const node<T>>;

public:
    linkedList() = default;

    linkedList(std::initializer_list<T>);

    linkedList(linkedList const&);

    linkedList(linkedList&&);

    linkedList& operator=(linkedList);

    template <typename U>
    void push_front(U&&);

    template <typename U>
    void push_back(U&&);

    void pop_front();

    void pop_back();

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_type size() const;

    std::optional<value_type> front() const;

    std::optional<value_type> back() const;

    const_iterator data() const;

    iterator begin();

    iterator begin() const;

    const_iterator cbegin() const;

    iterator end();

    iterator end() const;

    const_iterator cend() const;

    reverse_iterator rbegin();

    reverse_iterator rbegin() const;

    const_reverse_iterator crbegin() const;

    reverse_iterator rend();

    reverse_iterator rend() const;

    const_reverse_iterator crend() const;

    friend void swap(linkedList<T>& lhs, linkedList<T>& rhs)
    {
        using std::swap;
        swap(lhs.list_, rhs.list_);
        swap(lhs.size_, rhs.size_);
    }

    void print_forward() const
    {
        auto it = cbegin();

        while (it != cend()) {
            std::cout << *it << ' ';
            ++it;
        }
        std::cout << '\n';
    }

    void print_backward() const
    {
        auto it = crbegin();

        while (it != crend()) {
            std::cout << *it << ' ';
            ++it;
        }
        std::cout << '\n';
    }

    ~linkedList();

private:
    node<T> list_;
    size_type size_ { 0 };
};

// // start linkedList

template <typename T>
linkedList<T>::linkedList(std::initializer_list<T> lst)
{
    for (auto value : lst)
        push_back(std::move(value));
}

template <typename T>
linkedList<T>::linkedList(linkedList const& outer)
{
    for (auto value : outer)
        push_back(std::move(value));
}

template <typename T>
linkedList<T>::linkedList(linkedList&& outer)
{
    swap(*this, outer);
}

template <typename T>
linkedList<T>& linkedList<T>::operator=(linkedList list)
{
    swap(*this, list);
    return *this;
}

//
template <typename T>
template <typename U>
void linkedList<T>::push_front(U&& data)
{
    list_.push_front(new node<T>(std::forward<U>(data)));
    size_ = size_ + 1;
}

template <typename T>
template <typename U>
void linkedList<T>::push_back(U&& data)
{
    list_.push_back(new node<T>(std::forward<U>(data)));
    size_ = size_ + 1;
}

template <typename T>
void linkedList<T>::pop_front()
{
    assert(list_.next_ != &list_);

    node<T>* curr = list_.next_;
    curr->next_->prev_ = &list_;
    list_.next_ = curr->next_;

    curr = (free(curr), nullptr);

    size_ = size_ - 1;
}

template <typename T>
void linkedList<T>::pop_back()
{
    assert(list_.next_ != &list_);

    node<T>* curr = list_.prev_;
    curr->prev_->next_ = &list_;
    list_.prev_ = curr->prev_;

    curr = (free(curr), nullptr);

    size_ = size_ - 1;
}

template <typename T>
[[nodiscard]] bool linkedList<T>::empty() const
{
    return &list_ == list_.next_;
}

template <typename T>
[[nodiscard]] typename linkedList<T>::size_type linkedList<T>::size() const
{
    return size_;
}

template <typename T>
std::optional<T> linkedList<T>::front() const
{
    return !empty() ? *begin() : std::nullopt;
}

template <typename T>
std::optional<T> linkedList<T>::back() const
{
    return !empty() ? *rbegin() : std::nullopt;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::data() const
{
    return cbegin();
}

template <typename T>
typename linkedList<T>::iterator linkedList<T>::begin()
{
    return list_.next_;
}

template <typename T>
typename linkedList<T>::iterator linkedList<T>::begin() const
{
    return list_.next_;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::cbegin() const
{
    return list_.next_;
}

template <typename T>
typename linkedList<T>::iterator linkedList<T>::end()
{
    return &list_;
}

template <typename T>
typename linkedList<T>::iterator linkedList<T>::end() const
{
    return &list_;
}

template <typename T>
typename linkedList<T>::const_iterator linkedList<T>::cend() const
{
    return &list_;
}

template <typename T>
typename linkedList<T>::reverse_iterator linkedList<T>::rbegin()
{
    return list_.prev_;
}

template <typename T>
typename linkedList<T>::reverse_iterator linkedList<T>::rbegin() const
{
    return list_.prev_;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::crbegin() const
{
    return list_.prev_;
}

template <typename T>
typename linkedList<T>::reverse_iterator linkedList<T>::rend()
{
    return &list_;
}

template <typename T>
typename linkedList<T>::reverse_iterator linkedList<T>::rend() const
{
    return &list_;
}

template <typename T>
typename linkedList<T>::const_reverse_iterator linkedList<T>::crend() const
{
    return &list_;
}

template <typename T>
linkedList<T>::~linkedList()
{
    while (list_.next_ != &list_)
        pop_front();
}
//
// // end linkedList
