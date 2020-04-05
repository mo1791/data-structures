#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>
#include <string>
#include "stack.hpp"

// start node
template<typename T>
ds::stack<T>::node::node(const T value)
: _data(value), _next(nullptr) {}

// end node

// start stack
template<typename T>
ds::stack<T>::stack()
: _head(nullptr) {} 

template<typename T>
ds::stack<T>::stack(ds::stack<T> const& outer) try: stack<T>() { 
	
	_head = new node(outer._head->_data);
	node* tracer = _head, *next = outer._head->_next;

	while (next) {
		tracer->_next = new node(next->_data);
		tracer = tracer->_next;
		next = next->_next;
	}
} catch(std::bad_alloc const&) {

	std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa"; 
}

template<typename T>
ds::stack<T>::stack(ds::stack<T>&& outer): stack<T>() {
	swap(*this, outer);
}

template<typename T>
ds::stack<T>& ds::stack<T>::operator=(ds::stack<T> rhs) {
	swap(*this, rhs);
	return *this;
}

template<typename T>
bool ds::stack<T>::empty() const {  return _head == nullptr; }


template<typename T>
void ds::stack<T>::push_front(const T value) try {
	
	node* _node = new node(value);

	if (empty()) {
		_head = _node;
		return;
	}

	_head = ( (_node->_next = _head), _node);
	
} catch(std::bad_alloc const&) {

	std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa";
}

template<typename T>
void ds::stack<T>::push(const T value) { push_front(value); }


template<typename T>
void ds::stack<T>::pop_front() {

	assert( !empty() );

	node* curr = _head;
	_head = _head->_next;
	curr =  ( free(curr), nullptr );
}

template<typename T>
void ds::stack<T>::pop() { pop_front(); }


template<typename T>
std::optional<T> ds::stack<T>::peep() const {

	if ( !empty() ) {
		return _head->_data;
	}
	return std::nullopt;
}

template<typename T>
ds::stack<T>::~stack() {

	while ( !empty() )
		pop();
}

// end stack

template class ds::stack<char>;
template class ds::stack<short>;
template class ds::stack<int>;
template class ds::stack<unsigned char>;
template class ds::stack<unsigned short>;
template class ds::stack<unsigned int>;
template class ds::stack<float>;
template class ds::stack<double>;
template class ds::stack<long>;
template class ds::stack<long float>;
template class ds::stack<long double>;
template class ds::stack<long long>;
template class ds::stack<long long float>;
template class ds::stack<long long double>;
template class ds::stack<std::string>;