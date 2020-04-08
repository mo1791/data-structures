#pragma once

#include <optional>


namespace ds {
	
	template<typename T>
	class stack final {
	public:
		using value_type      = T;
		using reference       = typename std::add_lvalue_reference<T>::type;
		using pointer         = typename std::add_pointer<T>::type;
		using const_reference = const reference;
		using const_pointer   = const pointer;
		using size_type       = std::size_t;
		using difference_type = std::ptrdiff_t;
	public:
		stack();

		stack(stack<T> const&);
		
		stack(stack<T>&&);
		
		stack<T>& operator=(stack<T>);
		
		bool empty() const;
		
		void push_front(const T);

		void push(const T);	

		void pop_front();

		void pop();

		std::optional<T> peep() const;

		void print() const;
				
		~stack();

		friend void swap(stack<T>& lhs, stack<T>& rhs) {
			using std::swap;
			swap(lhs._head, rhs._head);
		}

	private:
		class node;
		node* _head;
	};
}