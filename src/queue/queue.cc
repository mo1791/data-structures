#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>
#include <string>
#include "queue.hpp"

// start node
template<typename T>
ds::queue<T>::node::node(const T value)
: _data(value), _next(nullptr) {}

// end node

// start queue
template<typename T>
ds::queue<T>::queue()
: _head(nullptr), _tail(nullptr) {} 

template<typename T>
ds::queue<T>::queue(ds::queue<T> const& outer) try: queue<T>() { 
	
	_head = _tail =  new node(outer._head->_data);
	
	for(
		node* next = outer._head->_next; 
		next; next=next->_next)
	{
		push(next->_data);
	}

} catch(std::bad_alloc const&) {
	
	std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa"; 
}

template<typename T>
ds::queue<T>::queue(ds::queue<T>&& outer): queue<T>() {
	swap(*this, outer);
}

template<typename T>
ds::queue<T>& ds::queue<T>::operator=(ds::queue<T> rhs) {
	swap(*this, rhs);
	return *this;
}

template<typename T>
bool ds::queue<T>::empty() const { return _head == nullptr; }


template<typename T>
void ds::queue<T>::push_back(const T value) try {
	
	node* _node = new node(value);

	if ( empty() ) {
		_head = _tail = _node; return;
	}

	_tail->_next = _node;
	_tail = _node;
	
} catch(std::bad_alloc const&) {
	
	std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa";
}

template<typename T>
void ds::queue<T>::push(const T value) { push_back(value); }


template<typename T>
void ds::queue<T>::pop_front() {

	assert( !empty() );

	node* curr = _head;
	_head = _head->_next;
	curr =  ( free(curr), nullptr );
}

template<typename T>
void ds::queue<T>::pop() { pop_front(); }


template<typename T>
std::optional<T> ds::queue<T>::peek() const { 
	if ( !empty() ) {
		return _head->_data; 
	}
	 return std::nullopt;
}


template<typename T>
ds::queue<T>::~queue() {

	while ( !empty() )
		pop();
}

// end queue

template class ds::queue<char>;
template class ds::queue<short>;
template class ds::queue<int>;
template class ds::queue<unsigned char>;
template class ds::queue<unsigned short>;
template class ds::queue<unsigned int>;
template class ds::queue<float>;
template class ds::queue<double>;
template class ds::queue<long>;
template class ds::queue<long float>;
template class ds::queue<long double>;
template class ds::queue<long long>;
template class ds::queue<long long float>;
template class ds::queue<long long double>;
template class ds::queue<std::string>;