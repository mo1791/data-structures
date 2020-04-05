#pragma once

#include <optional>


namespace ds {
	template<typename T>
	class stack final {
	private:
		class node {
			friend class stack<T>;
		public:
			explicit node(const T);
		private:
			T m_data;
			node* m_next;
		};
	public:
		explicit stack();

		stack(stack<T> const&);
		
		stack(stack<T>&&);
		
		stack<T>& operator=(stack<T>);
		
		bool empty() const;
		
		void push_front(const T);

		void push(const T);	

		void pop_front();

		void pop();

		std::optional<T> peep() const;
		
		~stack();

		friend void swap(stack<T>& lhs, stack<T>& rhs) {
			using std::swap;
			swap(lhs.m_head, rhs.m_head);
		}

	private:
		node* m_head;
	};
}