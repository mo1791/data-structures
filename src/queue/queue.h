#pragma once

#include <algorithm>
#include <optional>

namespace ds {
	template<typename T>
	class queue final {
	public:
		using value_type      = T;
		using reference       = typename std::add_lvalue_reference<T>::type;
		using pointer         = typename std::add_pointer<T>::type;
		using const_reference = const reference;
		using const_pointer   = const pointer;
		using size_type       = std::size_t;
		using difference_type = std::ptrdiff_t;


	public:
		queue();

		queue(queue<T> const&);
		
		queue(queue<T>&&);
		
		queue<T>& operator=(queue<T>);
		
		bool empty() const;
		
		void push_back(const T);

		void push(const T);	

		void pop_front();

		std::optional<T> peek() const;

		void pop();
		
		void print() const;
		
		~queue();

		friend void swap(queue<T>& lhs, queue<T>& rhs) {
			using std::swap;
			swap(lhs._head, rhs._head);
			swap(lhs._tail, rhs._tail);
		}

	private:
		class node;
		node* _head, *_tail;
	};
}