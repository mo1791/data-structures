#pragma once

#include <algorithm>
#include <optional>
#include <functional>
#include <cassert>
#include <iostream>
#include <exception>
#include <string>

template <typename T>
class queue final {
	
	class node {
		public:
			explicit node(const T& value)
				noexcept : data_(value), next_(nullptr) {}

			explicit node(T&& value)
				noexcept : data_(std::move(value)), next_(nullptr) {}

		private:
			T data_;
			node* next_;
	};
	
public:
	using value_type      = T;
	using reference       = typename std::add_lvalue_reference<T>::type;
	using pointer         = typename std::add_pointer<T>::type;
	using const_reference = const reference;
	using const_pointer   = const pointer;
	using size_type       = std::size_t;
	using difference_type = std::ptrdiff_t;


public:
	queue();

	queue(queue<T> const&);
	
	queue(queue<T>&&);
	
	queue<T>& operator=(queue<T>);
	
	bool empty() const;
	
	template <typename U>
	void push_back(U&&);

	template <typename U>
	void push(U&&);	

	void pop_front();

	std::optional<T> peek() const;

	void pop();
	
	void print() const;
	
	~queue();

	friend void swap(queue<T>& lhs, queue<T>& rhs) {
		using std::swap;
		swap(lhs.head_, rhs.head_);
		swap(lhs.tail_, rhs.tail_);
	}

private:
	node* head_, *tail_;
};




// start queue
template <typename T>
queue<T>::queue()
: head_(nullptr), tail_(nullptr) {} 

template <typename T>
queue<T>::queue(queue<T> const& outer) try: queue() { 
	
	node* _node = outer.head_;

	head_ = tail_ =  new node(_node->data_);
	
	_node = _node->next_;

	while ( _node ) {

		push( _node->data_ );

		_node = _node->next_;
	}

} catch(std::bad_alloc const&) {
	
	std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa"; 
}

template <typename T>
queue<T>::queue(queue<T>&& outer)
	: queue() {

	swap(*this, outer);
}

template <typename T>
queue<T>& queue<T>::operator=(queue<T> rhs) {
	
	swap(*this, rhs);
	return *this;
}

template <typename T>
bool queue<T>::empty() const { return head_ == nullptr; }


template <typename T>
template <typename U>
void queue<T>::push_back(T&& value) try {
	
	node* _node = new node(std::forward<U>(value));

	if ( empty() ) {
		head_ = tail_ = _node; return;
	}

	tail_->next_ = _node;
	tail_ = _node;
	
} catch(std::bad_alloc const&) {
	
	std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa";
}

template <typename T>
template <typename U>
void queue<T>::push(U&&value) { push_back( std::forward<U>(value) ); }


template <typename T>
void queue<T>::pop_front() {

	assert( !empty() );

	node* curr = head_;
	head_ = head_->next_;
	curr =  ( free(curr), nullptr );
}

template <typename T>
void queue<T>::pop() { pop_front(); }


template <typename T>
std::optional<T> queue<T>::peek() const { 

	if ( !empty() ) {
		return head_->data_; 
	}
	 return std::nullopt;
}


template <typename T>
void queue<T>::print() const {

	for(node* it=head_; it; it=it->next_)
		std::cout << it->data_ << ' ';
	std::cout << '\n';
}


template <typename T>
queue<T>::~queue() {

	while ( !empty() )
		pop();
}