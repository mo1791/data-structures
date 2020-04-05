#include <algorithm>
#include <functional>
#include <cassert>
#include <ostream>
#include <string>
#include <exception>
#include "doubly.hpp"

	// start node

	template<typename T>
class ds::doubly<T>::node {
	friend class doubly<T>;
	friend class iterator;
	friend class reverse_iterator;
public:
	explicit node(const T value)
		: _data(value), _next(nullptr), _prev(nullptr) {}
private:
	T _data;
	node* _next;
	node* _prev;
};
	// end node
 
	// start iterators
	template<typename T>
ds::doubly<T>::iterator::iterator(ds::doubly<T>::node* ptr)
: _iterator(ptr) {}
 
	template<typename T>
typename ds::doubly<T>::iterator& ds::doubly<T>::iterator::operator++() {
	_iterator = _iterator->_next;
	return *this;
}
 
	template<typename T>
T& ds::doubly<T>::iterator::operator*() {
	return _iterator->_data;
}
 
	template<typename T>
bool ds::doubly<T>::iterator::operator!=(ds::doubly<T>::iterator const& rhs) const {
	return _iterator != rhs._iterator;
}
 
	template<typename T>
bool ds::doubly<T>::iterator::operator==(ds::doubly<T>::iterator const& rhs) const {
	return !(*this != rhs);
}
 
	template<typename T>
ds::doubly<T>::const_iterator::const_iterator(ds::doubly<T>::node* ptr)
: iterator(ptr) {}
 
 
 
	template<typename T>
ds::doubly<T>::reverse_iterator::reverse_iterator(ds::doubly<T>::node* ptr)
: _iterator(ptr) {}
 
	template<typename T>
typename ds::doubly<T>::reverse_iterator& ds::doubly<T>::reverse_iterator::operator++() {
	_iterator = _iterator->_prev;
	return *this;
}
 
	template<typename T>
T& ds::doubly<T>::reverse_iterator::operator*() {
	return _iterator->_data;
}
 
	template<typename T>
bool ds::doubly<T>::reverse_iterator::operator!=(ds::doubly<T>::reverse_iterator const& rhs) const {
	return _iterator != rhs._iterator;
}
 
	template<typename T>
bool ds::doubly<T>::reverse_iterator::operator==(ds::doubly<T>::reverse_iterator const& rhs) const {
	return !(*this != rhs);
}
 
	template<typename T>
ds::doubly<T>::const_reverse_iterator::const_reverse_iterator(ds::doubly<T>::node* ptr)
: reverse_iterator(ptr) {}
	// end iterators
 
 
	// start doubly
	template<typename T>
ds::doubly<T>::doubly()
: _head(nullptr), _tail(nullptr) {} 
 
 
	template<typename T>
ds::doubly<T>::doubly(std::initializer_list<T> list)
: ds::doubly<T>() {
	std::for_each(
		std::begin(list), 
		std::end(list),
		std::bind(&doubly::push_back, this, std::placeholders::_1)
		);
}
 
 
	template<typename T>
ds::doubly<T>::doubly(ds::doubly<T> const& outer)
: ds::doubly<T>() {
 
	std::for_each(
		std::begin(outer), std::end(outer),
		std::bind(&doubly::push_back, this, std::placeholders::_1)
		);
}
 
	template<typename T>
ds::doubly<T>::doubly(ds::doubly<T>&& outer)
: ds::doubly<T>() {
	swap(*this, outer);
}
 
	template<typename T>
ds::doubly<T>& ds::doubly<T>::operator=(ds::doubly<T> rhs) {
	swap(*this, rhs);
	return *this;
}
 
	template<typename T>
bool ds::doubly<T>::empty() const { return _head == nullptr; }
 
 
	template<typename T>
void ds::doubly<T>::push_front(const T value) try {
 
	node* _node = new node(value);
 
	if ( empty() ) {
		_head = _tail = _node;
		return;
	}
 
	_node->_next = _head;
	_head->_prev = _node;
	_head = _node;
	return;
 
} catch (std::bad_alloc const&) { 
 
	std::cout << "bfr, Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
}
 
	template<typename T>
void ds::doubly<T>::push_back(const T value) try {
 
	node* _node = new node(value);
 
	if ( empty() ) {
		_head = _tail = _node;
		return;
	}
 
	_node->_prev = _tail;
	_tail->_next = _node;
	_tail = _node;
	return;
 
} catch (std::bad_alloc const&) {
 
	std::cout << "back,Uncaught Exception 'std::bad_alloc' → ALLO FAILD\xa";
}
 
	template<typename T>
void ds::doubly<T>::push_after(const T key, const T value) {
 
	assert( !empty() );
 
	node* curr = _head;
 
	while (curr) {
		if ( curr->_data == key )
			break;
		curr = curr->_next;
	}
 
	if ( curr == nullptr )
		return;
 
	if ( curr == _tail ) {
		push_back(value); return;
	}
 
	try {
 
		node* _node = new node(value);
 
		_node->_next = curr->_next;
		_node->_prev = curr;
		curr->_next->_prev = _node;
		curr->_next = _node;
 
	} catch(std::bad_alloc const&) {
 
		std::cout << "bfr, Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
	}
}
 
 
	template<typename T>
void ds::doubly<T>::push_before(const T key, const T value) {
 
	assert( !empty() );
 
	if ( _head->_data == key ) {
		push_front(value); return;
	}
 
	try {
 
		node* _node = new node(value);
 
		node* curr = _head->_next;
 
		while(curr) {
			if (curr->_data == key)
				break;
			curr = curr->_next;
		}
 
		if ( curr == nullptr)
			return;
 
		_node->_prev = curr->_prev;
		_node->_next = curr;
		curr->_prev->_next = _node;
		curr->_prev = _node;
 
	} catch(std::bad_alloc const&) {
 
		std::cout << "bfr, Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
	}
 
}
 
 
	template<typename T>
void ds::doubly<T>::pop_front() {
 
	assert( !empty() );
 
	node* curr = _head;
	_head = _head->_next;
	if ( _head )
		_head->_prev = nullptr;
	curr = ( free(curr), nullptr);
}
 
	template<typename T>
void ds::doubly<T>::pop_back() {
 
	assert( !empty() );
 
	node* curr = _tail;
	_tail = _tail->_prev;
	_tail->_next = nullptr;
	curr = ( free(curr), nullptr );
}
 
 
	template<typename T>
void ds::doubly<T>::pop_before(const T key) {
 
	assert( !empty() );
 
	node* curr = _head;
 
	for (node* next = _head->_next; next;) {
		if (next->_data == key)
			break;
		curr = next;
		next = next->_next;
	}
 
	if ( curr == _tail )
		return;
 
	if (curr == _head) {
		pop_front(); return;
	}
 
	curr->_prev->_next = curr->_next;
	curr->_next->_prev = curr->_prev;
 
	curr = ( free(curr), nullptr );
}
 
 
	template<typename T>
void ds::doubly<T>::pop_after(const T key) {
 
	assert( !empty() );
 
	node* curr = _head;
	node* next = _head->_next;
 
	while ( next ) {
 
		if (curr->_data == key)
			break;
		curr = next;
		next = next->_next;
	}
 
	if ( curr == _tail )
		return;
 
 
	if ( next == _tail ) {
		pop_back(); return;
	}
 
	curr->_next = next->_next;
	next->_next->_prev = curr;
 
	next = ( free(next), nullptr );
}
 
 
	template<typename T>
typename ds::doubly<T>::iterator ds::doubly<T>::begin() { return iterator(_head); }
 
	template<typename T>
typename ds::doubly<T>::const_iterator ds::doubly<T>::begin() const { return const_iterator(_head); }
 
	template<typename T>		
typename ds::doubly<T>::const_iterator ds::doubly<T>::cbegin() const { return const_iterator(_head); }
 
	template<typename T>
typename ds::doubly<T>::reverse_iterator ds::doubly<T>::rbegin() { return reverse_iterator(_tail); }
 
	template<typename T>
typename ds::doubly<T>::const_reverse_iterator ds::doubly<T>::rbegin() const { return const_reverse_iterator(_tail); }
 
	template<typename T>		
typename ds::doubly<T>::const_reverse_iterator ds::doubly<T>::crbegin() const { return const_reverse_iterator(_tail); }		
 
	template<typename T>
typename ds::doubly<T>::iterator ds::doubly<T>::end() { return iterator(nullptr); }
 
	template<typename T>
typename ds::doubly<T>::const_iterator ds::doubly<T>::end() const { return const_iterator(nullptr); }
 
	template<typename T>
typename ds::doubly<T>::const_iterator ds::doubly<T>::cend() const { return const_iterator(nullptr); }
 
	template<typename T>
typename ds::doubly<T>::reverse_iterator ds::doubly<T>::rend() { return reverse_iterator(nullptr); }
 
	template<typename T>
typename ds::doubly<T>::const_reverse_iterator ds::doubly<T>::rend() const { return const_reverse_iterator(nullptr); }
 
	template<typename T>
typename ds::doubly<T>::const_reverse_iterator ds::doubly<T>::crend() const { return const_reverse_iterator(nullptr); }
 
 
	template<typename T>
ds::doubly<T>::~doubly() {
 
	while ( !empty() )
		pop_front();
}
// end doubly

template <typename T>
	using doubly = ds::doubly<T>;

template class doubly<char>;
template class doubly<short>;
template class doubly<int>;
template class doubly<unsigned char>;
template class doubly<unsigned short>;
template class doubly<unsigned int>;
template class doubly<float>;
template class doubly<double>;
template class doubly<long>;
template class doubly<long float>;
template class doubly<long double>;
template class doubly<long long>;
template class doubly<long long float>;
template class doubly<long long double>;
template class doubly<std::string>;