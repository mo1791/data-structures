#include <functional>
#include <cassert>
#include <string>
#include <exception>
#include "singly.hpp"


// start node
	template <typename T>
class ds::singly<T>::node {
	friend class singly<T>;
	friend class _iterator;
public:
	explicit node(const T value, node* next = nullptr)
		: _data(value), _next(next) {}
private:
	T _data;
	node* _next;
};

// end node

// start iterators
	template<typename T>
ds::singly<T>::_iterator::_iterator(ds::singly<T>::node* ptr)
: __iterator(ptr) {}

	template<typename T>
typename ds::singly<T>::_iterator& 
	ds::singly<T>::_iterator::operator++() {
		__iterator = __iterator->_next;
		return *this;
	}

	template<typename T>
T& ds::singly<T>::_iterator::operator*() {
	return __iterator->_data;
}

	template<typename T>
bool ds::singly<T>::_iterator::operator!=(
					ds::singly<T>::_iterator const& rhs) const {
	return __iterator != rhs.__iterator;
}

	template<typename T>
bool ds::singly<T>::_iterator::operator==(
					ds::singly<T>::_iterator const& rhs) const {
	return !(*this != rhs);
}

	template<typename T>
ds::singly<T>::_const_iterator::_const_iterator(
											ds::singly<T>::node* ptr)
: _iterator(ptr) {}

// end iterators


// start singly
	template<typename T>
ds::singly<T>::singly()
: _size(0), _head(nullptr), _tail(nullptr) {} 


	template<typename T>
ds::singly<T>::singly(std::initializer_list<T> list)
: singly<T>() {
	std::for_each(
		std::begin(list), 
		std::end(list),
		std::bind(&singly::push_back, this, std::placeholders::_1)
	);
}


	template<typename T>
ds::singly<T>::singly(ds::singly<T> const& outer)
: singly<T>() {
	std::for_each(
		std::begin(outer), std::end(outer),
		std::bind(&singly::push_front, this, std::placeholders::_1)
	);
}

	template<typename T>
ds::singly<T>::singly(ds::singly<T>&& outer)
: singly<T>() {
	swap(*this, outer);
}

	template<typename T>
ds::singly<T>& ds::singly<T>::operator=(ds::singly<T> rhs) {
	swap(*this, rhs);
	return *this;
}

	template<typename T>
ds::singly<T>& ds::singly<T>::operator=(std::initializer_list<T> rhs) {
	this->~singly();
	std::for_each(
		std::begin(rhs), std::end(rhs),
		std::bind(&singly::push_front, this, std::placeholders::_1)
	);
	return *this;
}

	template<typename T>
bool ds::singly<T>::empty() const { return _head == nullptr; }

	template<typename T>
typename ds::singly<T>::size_type 
	ds::singly<T>::size() const { return _size; }

	template<typename T>
std::optional<const T&> 
	ds::singly<T>::front() const { return !empty() ? _head->_data : std::nullopt; }

	template<typename T>
std::optional<const T&> 
	ds::singly<T>::back() const {  return !empty() ? _tail->_data : std::nullopt; }

	template<typename T>
typename ds::singly<T>::const_iterator
	ds::singly<T>::data() const { return begin(); }


	template<typename T>
void ds::singly<T>::push_front(const T value) try {
	
	node* _node = new node(value, _head);

	if ( empty() ) {
		_head = _tail = _node; 
		_size = _size + 1;
		return;
	}

	_head = _node;
	_size = _size + 1;

	
} catch(std::bad_alloc const&) {

	std::cout << "Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
}

	template<typename T>
void ds::singly<T>::push_back(const T value) try {
	
	node* _node = new node(value);

	if ( empty() ) {
		_head = _tail = _node; 
		_size = _size + 1;
		return;
	}

	_tail->_next = _node;
	_tail = _node;
	_size = _size + 1;

} catch(std::bad_alloc const&) {

	std::cout << "Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa" ;
}

	template<typename T>
void ds::singly<T>::push_after(const T key, const T value) {

	assert( !empty() );

	node* trace = _head;

	while(trace->next) {
		if (trace->data == key)
			break;
		trace = trace->_next;
	}

	if (trace->_data != key)
		return; // node not founded

	try {

		node* _node = new node(value, trace->_next);

		trace->_next = _node;

		if (trace == _tail)
			_tail = _node;

		_size = _size + 1;

	} catch(std::bad_alloc const&) {

		std::cout << "Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
	}
}


	template<typename T>
void ds::singly<T>::push_before(const T key, const T value) {

	assert( !empty() );

	node* curr = _head;

	for(node* next=_head->_next; next;) {

		if (next->_data == key)
			break;
		curr = next;
		next = next->_next;
	}

	if (curr == _head) {

		push_front(value); return;
	}


	try {

		node* _node = new node(value, curr->_next);

		curr->_next =  _node;

		_size = _size + 1;

	} catch(std::bad_alloc const&) {

		std::cout << "Uncaught Exception 'std::bad_alloc' → ALLOC FAILD\xa";
	}
}


	template<typename T>
void ds::singly<T>::pop_front() {

	assert( !empty() );

	node* curr = _head;
	
	_head = _head->_next;

	curr =  ( free(curr), nullptr );
	
	_size = _size - 1;
}

	template<typename T>
void ds::singly<T>::pop_back() {

	assert( !empty() );

	node* curr = _head;

	while (curr->_next != _tail)
		curr = curr->_next;

	curr->_next = nullptr;
	
	std::swap(_tail, curr);
	
	curr = ( free(curr), nullptr );

	_size = _size - 1;
}


	template<typename T>
void ds::singly<T>::pop_before(const T key) {

	assert( !empty() );

	node* prev = nullptr;
	node* curr = _head;

	for( node* next = _head->_next; next;) {

		if (next->_data == key)
			break;
		next = (( prev = curr ),( curr = next ), next->_next );
	}

	if (curr == _tail)
		return;

	prev->_next = curr->_next;

	curr = ( free(curr), nullptr );

	_size = _size - 1;
}


	template<typename T>
void ds::singly<T>::pop_after(const T key) {

	assert( !empty() );

	node* curr = _head;
	node* next = _head->_next;

	while ( next ) {

		if (curr->_data == key)
			break;

		next = ((curr = next), next->_next );
	}

	if ( curr == _tail )
		return;

	curr->_next = next->_next;
	next = ( free(next), nullptr );
	_size = _size - 1;
}


	template<typename T>
typename ds::singly<T>::iterator 
	ds::singly<T>::begin() { return iterator(_head); }

	template<typename T>
typename ds::singly<T>::const_iterator 
	ds::singly<T>::begin() const { return const_iterator(_head);  }

	template<typename T>		
typename ds::singly<T>::const_iterator
	ds::singly<T>::cbegin() const { return const_iterator(_head); }		

	template<typename T>
typename ds::singly<T>::iterator
	ds::singly<T>::end() { return iterator(nullptr); }

	template<typename T>
typename ds::singly<T>::const_iterator
	ds::singly<T>::end() const { return const_iterator(nullptr); }

	template<typename T>
typename ds::singly<T>::const_iterator 
	ds::singly<T>::cend() const { return const_iterator(nullptr); }

	template<typename T>
ds::singly<T>::~singly() {

	while ( !empty() )
		pop_front();
}


// end singly

template<typename T>
	using singly = ds::singly<T>;

template class singly<char>;
template class singly<short>;
template class singly<int>;
template class singly<unsigned char>;
template class singly<unsigned short>;
template class singly<unsigned int>;
template class singly<float>;
template class singly<double>;
template class singly<long>;
template class singly<long float>;
template class singly<long double>;
template class singly<long long>;
template class singly<long long float>;
template class singly<long long double>;
template class singly<std::string>;

