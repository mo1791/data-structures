#include <algorithm>
#include <functional>
#include <cassert>
#include <ostream>
#include <string>
#include "doubly.hpp"

	// start node
	template<typename T>
ds::node<T>::node(const T value)
: _data(value), _next(nullptr), _prev(nullptr) {}
 
	// end node
 
	// start iterators
	template<typename T>
ds::iterator<T>::iterator(ds::node<T>* ptr)
: _iterator(ptr) {}
 
	template<typename T>
ds::iterator<T>& ds::iterator<T>::operator++() {
	_iterator = _iterator->_next;
	return *this;
}
 
	template<typename T>
T ds::iterator<T>::operator*() {
	return _iterator->_data;
}
 
	template<typename T>
bool ds::iterator<T>::operator!=(ds::iterator<T> const& rhs) const {
	return _iterator != rhs._iterator;
}
 
	template<typename T>
bool ds::iterator<T>::operator==(ds::iterator<T> const& rhs) const {
	return !(*this != rhs);
}
 
	template<typename T>
ds::const_iterator<T>::const_iterator(ds::node<T>* ptr)
: ds::iterator<T>(ptr) {}
 
 
 
	template<typename T>
ds::reverse_iterator<T>::reverse_iterator(ds::node<T>* ptr)
: _iterator(ptr) {}
 
	template<typename T>
ds::reverse_iterator<T>& ds::reverse_iterator<T>::operator++() {
	_iterator = _iterator->_prev;
	return *this;
}
 
	template<typename T>
T ds::reverse_iterator<T>::operator*() {
	return _iterator->_data;
}
 
	template<typename T>
bool ds::reverse_iterator<T>::operator!=(ds::reverse_iterator<T> const& rhs) const {
	return _iterator != rhs._iterator;
}
 
	template<typename T>
bool ds::reverse_iterator<T>::operator==(ds::reverse_iterator<T> const& rhs) const {
	return !(*this != rhs);
}
 
	template<typename T>
ds::const_reverse_iterator<T>::const_reverse_iterator(ds::node<T>* ptr)
: ds::reverse_iterator<T>(ptr) {}
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
 
	node<T>* _node = new node<T>(value);
 
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
 
	node<T>* _node = new node<T>(value);
 
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
 
	node<T>* curr = _head;
 
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
 
		node<T>* _node = new node<T>(value);
 
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
 
		node<T>* _node = new node<T>(value);
 
		node<T> *curr = _head->_next;
 
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
 
	node<T>* curr = _head;
	_head = _head->_next;
	if ( _head )
		_head->_prev = nullptr;
	curr = ( free(curr), nullptr);
}
 
	template<typename T>
void ds::doubly<T>::pop_back() {
 
	assert( !empty() );
 
	node<T>* curr = _tail;
	_tail = _tail->_prev;
	_tail->_next = nullptr;
	curr = ( free(curr), nullptr );
}
 
 
	template<typename T>
void ds::doubly<T>::pop_before(const T key) {
 
	assert( !empty() );
 
	node<T>* curr = _head;
 
	for (node<T>* next = _head->_next; next;) {
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
 
	node<T>* curr = _head;
	node<T>* next = _head->_next;
 
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
ds::iterator<T> ds::doubly<T>::begin() { return iterator<T>(_head); }
 
	template<typename T>
ds::const_iterator<T> ds::doubly<T>::begin() const { return const_iterator<T>(_head); }
 
	template<typename T>		
ds::const_iterator<T> ds::doubly<T>::cbegin() const { return const_iterator<T>(_head); }
 
	template<typename T>
ds::reverse_iterator<T> ds::doubly<T>::rbegin() { return reverse_iterator<T>(_tail); }
 
	template<typename T>
ds::const_reverse_iterator<T> ds::doubly<T>::rbegin() const { return const_reverse_iterator<T>(_tail); }
 
	template<typename T>		
ds::const_reverse_iterator<T> ds::doubly<T>::crbegin() const { return const_reverse_iterator<T>(_tail); }		
 
	template<typename T>
ds::iterator<T> ds::doubly<T>::end() { return iterator<T>(nullptr); }
 
	template<typename T>
ds::const_iterator<T> ds::doubly<T>::end() const { return const_iterator<T>(nullptr); }
 
	template<typename T>
ds::const_iterator<T> ds::doubly<T>::cend() const { return const_iterator<T>(nullptr); }
 
	template<typename T>
ds::reverse_iterator<T> ds::doubly<T>::rend() { return reverse_iterator<T>(nullptr); }
 
	template<typename T>
ds::const_reverse_iterator<T> ds::doubly<T>::rend() const { return const_reverse_iterator<T>(nullptr); }
 
	template<typename T>
ds::const_reverse_iterator<T> ds::doubly<T>::crend() const { return const_reverse_iterator<T>(nullptr); }
 
 
	template<typename T>
ds::doubly<T>::~doubly() {
 
	while ( !empty() )
		pop_front();
}


	template<typename T>
std::ostream& operator<<(std::ostream& stream, ds::doubly<T> const& list) {
	std::for_each(
		std::begin(list), std::end(list),
		[&stream] (const T value) { stream << value << ' '; }
		);
	return stream << '\n';
}

// end doubly

template class ds::doubly<char>;
template class ds::doubly<short>;
template class ds::doubly<int>;
template class ds::doubly<unsigned char>;
template class ds::doubly<unsigned short>;
template class ds::doubly<unsigned int>;
template class ds::doubly<float>;
template class ds::doubly<double>;
template class ds::doubly<long>;
template class ds::doubly<long float>;
template class ds::doubly<long double>;
template class ds::doubly<long long>;
template class ds::doubly<long long float>;
template class ds::doubly<long long double>;
template class ds::doubly<std::string>;
