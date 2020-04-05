#pragma once

#include <initializer_list>
#include <iterator>

namespace ds {

	template <typename> class singly;
	template <typename> class iterator;


	/* NODE CLASS */
	template <typename T>
	class node {
		friend class singly<T>;
		friend class iterator<T>;
	public:
		explicit node(const T);
	private:
		T _data;
		node<T>* _next;
	};

	/* ITERATOR CLASS */
	template <typename T>
	class iterator {
	public:
		using value_type = T;
		using reference = T&;
		using pointer = node<T>*;
		using iterator_category = std::forward_iterator_tag;
		
	public:
		explicit iterator(node<T>*);
		iterator<T>& operator++();
		value_type operator*();
		bool operator!=(iterator<T> const&) const;
		bool operator==(iterator<T> const&) const;
	private:
		pointer _iterator;
	};

	/* CONST_ITERATOR CLASS */
	template<typename T>
	class const_iterator final: public iterator<T> {
	public:
		explicit const_iterator(node<T>*);

		using iterator<T>::operator++;
		using iterator<T>::operator*;
		using iterator<T>::operator!=;
		using iterator<T>::operator==;
	};


	/* SINGLY CLASS */
	template<typename T>
	class singly final {
	public:
		explicit singly();
		
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

		iterator<T> begin();

		const_iterator<T> begin() const;
		
		const_iterator<T> cbegin() const;
		
		iterator<T> end();
		
		const_iterator<T> end() const;
		
		const_iterator<T> cend() const;
		
		~singly();

		friend void swap(singly<T>& lhs, singly<T>& rhs) {
			using std::swap;
			swap(lhs._head, rhs._head);
			swap(lhs._tail, rhs._tail);
		}

	private:
		node<T>* _head;
		node<T>* _tail;
	};
}