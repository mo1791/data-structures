#pragma once


#include <initializer_list>
#include <iterator>

namespace ds {
 
	template <typename> class doubly;
	template <typename> class iterator;
	template <typename> class reverse_iterator;
 
	/* NODE CLASS */
	template<typename T>
	class node {
		friend class doubly<T>;
		friend class iterator<T>;
		friend class reverse_iterator<T>;
	public:
		explicit node(const T);
	private:
		T _data;
		node<T>* _next;
		node<T>* _prev;
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
 
	/* CONST_ITERATOR */
	template<typename T>
	class const_iterator final: public iterator<T> {
	public:
		explicit const_iterator(node<T>*);
 
		using iterator<T>::operator++;
		using iterator<T>::operator*;
		using iterator<T>::operator!=;
		using iterator<T>::operator==;
	};
 
	/* REVERSE_ITERATOR */
	template<typename T>
	class reverse_iterator {
	public:
		using value_type = T;
		using reference = T&;
		using pointer = node<T>*;
		using iterator_category = std::forward_iterator_tag;
 
	public:
		explicit reverse_iterator(node<T>*);
		reverse_iterator<T>& operator++();
		value_type operator*();
		bool operator!=(reverse_iterator<T> const&) const;
		bool operator==(reverse_iterator<T> const&) const;
	private:
		pointer _iterator;
	};
 
	/* CONST_REVERSE_ITERATOR CLASS */
	template <typename T>
	class const_reverse_iterator final: public reverse_iterator<T> {
	public:
		explicit const_reverse_iterator(node<T>*);
 
		using reverse_iterator<T>::operator++;
		using reverse_iterator<T>::operator*;
		using reverse_iterator<T>::operator!=;
		using reverse_iterator<T>::operator==;
	};
 
	/* DOUBLY CLASS*/
	template<typename T>
	class doubly final {
	public:
		explicit doubly();
 
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
 
		iterator<T> begin();
 
		const_iterator<T> begin() const;
 
		const_iterator<T> cbegin() const;
 
		reverse_iterator<T> rbegin();
 
		const_reverse_iterator<T> rbegin() const;
 
		const_reverse_iterator<T> crbegin() const;
 
		iterator<T> end();
 
		const_iterator<T> end() const;
 
		const_iterator<T> cend() const;
 
		reverse_iterator<T> rend();
 
		const_reverse_iterator<T> rend() const;
 
		const_reverse_iterator<T> crend() const;
 
		~doubly();
 
		friend void swap(doubly<T>& lhs, doubly<T>& rhs) {
			using std::swap;
			swap(lhs._head, rhs._head);
			swap(lhs._tail, rhs._tail);
		}
 
	private:
		node<T>* _head;
		node<T>* _tail;
	};
}