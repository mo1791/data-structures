#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>
#include <string>
#include <exception>
#include "stack.hpp"

// start node
template <typename T>
class ds::stack<T>::node {
	friend class stack<T>;
public:
	explicit node(const T value)
		: _data(value), _next(nullptr) {};
private:
	T _data;
	node* _next;
};

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
void ds::stack<T>::print() const {
	for(node* it=_head; it; it=it->_next)
		std::cout << it->_data << ' ';
	std::cout << '\n';
}

template<typename T>
ds::stack<T>::~stack() {

	while ( !empty() )
		pop();
}

// end stack


template<typename T>
	using stack = ds::stack<T>;

template class stack<char>;
template class stack<short>;
template class stack<int>;
template class stack<unsigned char>;
template class stack<unsigned short>;
template class stack<unsigned int>;
template class stack<float>;
template class stack<double>;
template class stack<long>;
template class stack<long float>;
template class stack<long double>;
template class stack<long long>;
template class stack<long long float>;
template class stack<long long double>;
template class stack<std::string>;