#pragma once

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

		/* CONST_ITERATOR CLASS */
		class const_iterator final: public iterator {
		public:
			explicit const_iterator(node*);

			using iterator::operator++;
			using iterator::operator*;
			using iterator::operator!=;
			using iterator::operator==;
		};
	public:
		singly();
		
		singly(std::initializer_list<T>);
		
		singly(singly<T> const&);
		
		singly(singly<T>&&);
		
		singly<T>& operator=(singly<T>);
		
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