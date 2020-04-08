#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>

namespace ds {

	/* DOUBLY CLASS*/
	template<typename T>
	class doubly final {

	private:
		/* NODE CLASS */
		class node;
		node* _head;
		node* _tail;

	public:
		/* ITERATOR CLASS */
		class _iterator {
		public:
			using iterator_category = std::bidirectional_iterator_tag;
		
		public:
			explicit _iterator(node*);
			_iterator& operator++();
			T& operator*();
			bool operator!=(_iterator const&) const;
			bool operator==(_iterator const&) const;
		private:
			node* __iterator;
		};
		
		/* CONST_ITERATOR */
		class _const_iterator final: public _iterator {
		public:
			explicit _const_iterator(node*);
		
			using _iterator::operator++;
			using _iterator::operator*;
			using _iterator::operator!=;
			using _iterator::operator==;
		};
		
		/* REVERSE_ITERATOR */
		class _reverse_iterator {
		public:
			using iterator_category = std::bidirectional_iterator_tag;
		
		public:
			explicit _reverse_iterator(node*);
			_reverse_iterator& operator++();
			T& operator*();
			bool operator!=(_reverse_iterator const&) const;
			bool operator==(_reverse_iterator const&) const;
		private:
			node* __iterator;
		};
		
		/* CONST_REVERSE_ITERATOR CLASS */
		class _const_reverse_iterator final: public _reverse_iterator {
		public:
			explicit _const_reverse_iterator(node*);
		
			using _reverse_iterator::operator++;
			using _reverse_iterator::operator*;
			using _reverse_iterator::operator!=;
			using _reverse_iterator::operator==;
		};
	public:
		using value_type              = T;
		using reference               = typename std::add_lvalue_reference<T>::type;
		using pointer                 = typename std::add_pointer<T>::type;
		using const_reference         = const reference;
		using const_pointer           = const pointer;
		using size_type               = std::size_t;
		using difference_type         = std::ptrdiff_t;
		using iterator                = _iterator;
		using const_iterator          = _const_iterator;
		using reverse_iterator        = _reverse_iterator;
		using const_reverse_iterator  = _const_reverse_iterator;
	public:
		doubly();
 
		doubly(std::initializer_list<T>);
 
		doubly(doubly<T> const&);
 
		doubly(doubly<T>&&);
 
		doubly<T>& operator=(doubly<T>);

		doubly<T>& operator=(std::initializer_list<T>);
 
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
 
		reverse_iterator rbegin();
 
		const_reverse_iterator rbegin() const;
 
		const_reverse_iterator crbegin() const;
 
		iterator end();
 
		const_iterator end() const;
 
		const_iterator cend() const;
 
		reverse_iterator rend();
 
		const_reverse_iterator rend() const;
 
		const_reverse_iterator crend() const;
 
		~doubly();
 
		friend void swap(doubly<T>& lhs, doubly<T>& rhs) {
			using std::swap;
			swap(lhs._head, rhs._head);
			swap(lhs._tail, rhs._tail);
		}
	};
}

	template<typename T>
std::ostream& operator<<(std::ostream& stream, ds::doubly<T> const& list) {
	std::for_each(
		std::begin(list), std::end(list),
		[&stream] (const T value) { stream << value << ' '; }
		);
	return stream << '\n';
}