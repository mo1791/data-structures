#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <iostream>

namespace ds {
	/* SINGLY CLASS */
	template<typename T>
	class singly final {
	private:
		class node;
		node* _head;
		node* _tail;
	public:
		/* ITERATOR CLASS */
		class _iterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			
		public:
			explicit _iterator(node*);
			_iterator& operator++();
			T& operator*();
			bool operator!=(_iterator const&) const;
			bool operator==(_iterator const&) const;
		private:
			node* __iterator;
		};

		/* CONST_ITERATOR CLASS */
		class _const_iterator final: public _iterator {
		public:
			explicit _const_iterator(node*);

			using _iterator::operator++;
			using _iterator::operator*;
			using _iterator::operator!=;
			using _iterator::operator==;
		};
	public:
		using value_type      = T;
		using reference       = typename std::add_lvalue_reference<T>::type;
		using pointer         = typename std::add_pointer<T>::type;
		using const_reference = const reference;
		using const_pointer   = const pointer;
		using size_type       = std::size_t;
		using difference_type = std::ptrdiff_t;
		using iterator        = _iterator;
		using const_iterator  = _const_iterator;
	public:
		singly();
		
		singly(std::initializer_list<T>);
		
		singly(singly<T> const&);
		
		singly(singly<T>&&);
		
		singly<T>& operator=(singly<T>);
		
		singly<T>& operator=(std::initializer_list<T>);
		
		bool empty() const;
		
		void push_front(const T);

		void push_back(const T);	
		
		void push_after(const T, const T);

		void push_before(const T, const T);

		void pop_front();

		void pop_back();

		void pop_before(const T);

		void pop_after(const T);

		iterator begin();

		const_iterator begin() const;
		
		const_iterator cbegin() const;
		
		iterator end();
		
		const_iterator end() const;
		
		const_iterator cend() const;
		
		~singly();

		friend void swap(singly<T>& lhs, singly<T>& rhs) {
			using std::swap;
			swap(lhs._head, rhs._head);
			swap(lhs._tail, rhs._tail);
		}
	};
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, ds::singly<T> const& list) {
	std::for_each(
		std::begin(list), std::end(list),
		[&stream] (const T value) { stream << value << ' '; }
		);
	return stream << '\n';
}