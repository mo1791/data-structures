#pragma once

#include <iostream>
#include <optional>

namespace ds {
	template<typename T>
	class queue final {
	private:
		class node {
			friend class queue<T>;
		public:
			explicit node(const T);
		private:
			T _data;
			node* _next;
		};
	public:
		explicit queue();

		queue(queue<T> const&);
		
		queue(queue<T>&&);
		
		queue<T>& operator=(queue<T>);
		
		bool empty() const;
		
		void push_back(const T);

		void push(const T);	

		void pop_front();

		std::optional<T> peek() const;

		void pop();
		
		void print() const {
			for(node* it=_head; it; it=it->_next)
				std::cout << it->_data << ' ';
			std::cout << '\n';
		}
		
		~queue();

		friend void swap(queue<T>& lhs, queue<T>& rhs) {
			using std::swap;
			swap(lhs._head, rhs._head);
			swap(lhs._tail, rhs._tail);
		}

	private:
		node* _head, *_tail;
	};
}