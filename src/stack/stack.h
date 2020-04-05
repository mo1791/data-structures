#pragma once

#include <optional>


namespace ds {
	
	template<typename T>
	class stack final {
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