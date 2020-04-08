#include <functional>
#include <cassert>
#include <iostream>
#include <exception>
#include <string>
#include "queue.hpp"

// start node
template<typename T>
class ds::queue<T>::node {
	friend class queue<T>;
public:
	explicit node(const T value): _data(value), _next(nullptr) {}
private:
	T _data;
	node* _next;
};


// end node

// start queue
template<typename T>
ds::queue<T>::queue()
: _head(nullptr), _tail(nullptr) {} 

template<typename T>
ds::queue<T>::queue(ds::queue<T> const& outer) try: queue<T>() { 
	
	node* _node = outer._head;

	_head = _tail =  new node(_node->_data);
	
	_node = _node->_next;

	while ( _node ) {

		push( _node->_data );

		_node = _node->_next;
	}

} catch(std::bad_alloc const&) {
	
	std::cout << "Uncaught Exception 'std::bad_alloc' → alloc faild\xa"; 
}

template<typename T>
ds::queue<T>::queue(ds::queue<T>&& outer)
	: queue<T>() {

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
void ds::queue<T>::print() const {

	for(node* it=_head; it; it=it->_next)
		std::cout << it->_data << ' ';
	std::cout << '\n';
}


template<typename T>
ds::queue<T>::~queue() {

	while ( !empty() )
		pop();
}

// end queue

template <typename T>
	using queue = ds::queue<T>;

template class queue<char>;
template class queue<short>;
template class queue<int>;
template class queue<unsigned char>;
template class queue<unsigned short>;
template class queue<unsigned int>;
template class queue<float>;
template class queue<double>;
template class queue<long>;
template class queue<long float>;
template class queue<long double>;
template class queue<long long>;
template class queue<long long float>;
template class queue<long long double>;
template class queue<std::string>;