#pragma once

#include <iostream>
#include <optional>

namespace ds {
	template<typename T>
	class queue final {
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