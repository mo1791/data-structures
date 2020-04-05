#include <algorithm>
#include <functional>
#include <cassert>
#include <ostream>
#include <string>
#include <exception>
#include "singly.hpp"

// start node
template<typename T>
ds::node<T>::node(const T value)
: _data(value), _next(nullptr) {}

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

// end iterators


// start singly
template<typename T>
ds::singly<T>::singly()
: _head(nullptr), _tail(nullptr) {} 


template<typename T>
ds::singly<T>::singly(std::initializer_list<T> list)
: ds::singly<T>() {
	std::for_each(
		std::begin(list), 
		std::end(list),
		std::bind(&singly::push_back, this, std::placeholders::_1)
		);
}


template<typename T>
ds::singly<T>::singly(ds::singly<T> const& outer)
: ds::singly<T>() {

	std::for_each(
		std::begin(outer), std::end(outer),
		std::bind(&singly::push_back, this, std::placeholders::_1)
		);
}

template<typename T>
ds::singly<T>::singly(ds::singly<T>&& outer)
: ds::singly<T>() {
	swap(*this, outer);
}

template<typename T>
ds::singly<T>& ds::singly<T>::operator=(ds::singly<T> rhs) {
	swap(*this, rhs);
	return *this;
}

template<typename T>
bool ds::singly<T>::empty() const { return _head == nullptr; }


template<typename T>
void ds::singly<T>::push_front(const T value) try {
	
	node<T>* _node = new node<T>(value);

	if ( empty() ) {
		_head = _tail = _node;
		return;
	}

	_head = ( (_node->_next = _head), _node);
	
} catch(std::bad_alloc const&) {

	std::cout << "Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
}

template<typename T>
void ds::singly<T>::push_back(const T value) try {
	
	node<T>* _node = new node<T>(value);

	if ( empty() ) {
		_head = _tail = _node;
		return;
	}

	_tail->_next = _node;
	_tail = _node;

} catch(std::bad_alloc const&) {

	std::cout << "Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa" ;
}

template<typename T>
void ds::singly<T>::push_after(const T key, const T value) {

	assert( !empty() );

	node<T>* trace = _head;

	while(trace->next) {
		if (trace->data == key)
			break;
		trace = trace->_next;
	}

	if (trace->_data != key)
		return; // node not founded

	try {
		node<T>* _node = new node<T>(value);

		_node->_next = trace->_next;
		trace->_next = _node;

		if (trace == _tail)
			_tail = _node;

	} catch(std::bad_alloc const&) {

		std::cout << "Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
	}
}


template<typename T>
void ds::singly<T>::push_before(const T key, const T value) {

	assert( !empty() );

	node<T>* curr = _head;

	for(node<T>* next=_head->_next; next;) {

		if (next->_data == key)
			break;
		curr = next;
		next = next->_next;
	}

	if (curr == _head) {

		push_front(value); return;
	}


	try {

		node<T>* _node = new node<T>(value);

		curr->_next = (( _node->_next = curr->_next ), _node);

	} catch(std::bad_alloc const&) {

		std::cout << "Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
	}
}


template<typename T>
void ds::singly<T>::pop_front() {

	assert( !empty() );

	node<T>* curr = _head;
	_head = _head->_next;
	curr =  ( free(curr), nullptr );
}

template<typename T>
void ds::singly<T>::pop_back() {

	assert( !empty() );

	node<T>* curr = _head;

	while (curr->_next != _tail)
		curr = curr->_next;

	curr->_next = nullptr;
	
	std::swap(_tail, curr);
	
	curr = ( free(curr), nullptr );
}


template<typename T>
void ds::singly<T>::pop_before(const T key) {

	assert( !empty() );

	node<T>* prev = nullptr;
	node<T>* curr = _head;

	for( node<T>* next = _head->_next; next;) {

		if (next->_data == key)
			break;
		next = (( prev = curr ),( curr = next ), next->_next );
	}

	if (curr == _tail)
		return;

	prev->_next = curr->_next;
	curr = ( free(curr), nullptr );
}


template<typename T>
void ds::singly<T>::pop_after(const T key) {

	assert( !empty() );

	node<T>* curr = _head;
	node<T>* next = _head->_next;

	while ( next ) {

		if (curr->_data == key)
			break;

		next = ((curr = next), next->_next );
	}

	if ( curr == _tail )
		return;

	curr->_next = next->_next;
	next = ( free(next), nullptr );
}


template<typename T>
ds::iterator<T> ds::singly<T>::begin() { return iterator<T>(_head); }

template<typename T>
ds::const_iterator<T> ds::singly<T>::begin() const { return const_iterator<T>(_head); }

template<typename T>		
ds::const_iterator<T> ds::singly<T>::cbegin() const { return const_iterator<T>(_head); }		

template<typename T>
ds::iterator<T> ds::singly<T>::end() { return iterator<T>(nullptr); }

template<typename T>
ds::const_iterator<T> ds::singly<T>::end() const { return const_iterator<T>(nullptr); }

template<typename T>
ds::const_iterator<T> ds::singly<T>::cend() const { return const_iterator<T>(nullptr); }


template<typename T>
ds::singly<T>::~singly() {

	while ( !empty() )
		pop_front();
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, ds::singly<T> const& list) {
	std::for_each(
		std::begin(list), std::end(list),
		[&stream] (const T value) { stream << value << ' '; }
		);
	return stream << '\n';
}

// end singly

template class ds::singly<char>;
template class ds::singly<short>;
template class ds::singly<int>;
template class ds::singly<unsigned char>;
template class ds::singly<unsigned short>;
template class ds::singly<unsigned int>;
template class ds::singly<float>;
template class ds::singly<double>;
template class ds::singly<long>;
template class ds::singly<long float>;
template class ds::singly<long double>;
template class ds::singly<long long>;
template class ds::singly<long long float>;
template class ds::singly<long long double>;
template class ds::singly<std::string>;