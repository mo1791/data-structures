#pragma once


#include <initializer_list>
#include <iterator>
#include <ostream>

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
		class iterator {
		public:
			using value_type = T;
			using reference = T&;
			using pointer = node*;
			using iterator_category = std::forward_iterator_tag;
		
		public:
			explicit iterator(node*);
			iterator& operator++();
			reference operator*();
			bool operator!=(iterator const&) const;
			bool operator==(iterator const&) const;
		private:
			pointer _iterator;
		};
		
		/* CONST_ITERATOR */
		class const_iterator final: public iterator {
		public:
			explicit const_iterator(node*);
		
			using iterator::operator++;
			using iterator::operator*;
			using iterator::operator!=;
			using iterator::operator==;
		};
		
		/* REVERSE_ITERATOR */
		class reverse_iterator {
		public:
			using value_type = T;
			using reference = T&;
			using pointer = node*;
			using iterator_category = std::forward_iterator_tag;
		
		public:
			explicit reverse_iterator(node*);
			reverse_iterator& operator++();
			reference operator*();
			bool operator!=(reverse_iterator const&) const;
			bool operator==(reverse_iterator const&) const;
		private:
			pointer _iterator;
		};
		
		/* CONST_REVERSE_ITERATOR CLASS */
		class const_reverse_iterator final: public reverse_iterator {
		public:
			explicit const_reverse_iterator(node*);
		
			using reverse_iterator::operator++;
			using reverse_iterator::operator*;
			using reverse_iterator::operator!=;
			using reverse_iterator::operator==;
		};

	public:
		doubly();
 
		doubly(std::initializer_list<T>);
 
		doubly(doubly<T> const&);
 
		doubly(doubly<T>&&);
 
		doubly<T>& operator=(doubly<T>);
 
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