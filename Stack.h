#pragma once

using namespace std;

template <typename T>
class Stack {
public:
	int top;
	int maxsize;
	T* stack_node;

public:
	Stack(int size);
	virtual ~Stack();
	virtual bool IsFull() const;
	virtual bool IsEmpty() const;
	virtual T Pop();
	virtual void Push(T node);
};

template <typename T>
inline Stack<T>::Stack(int size) {
	top = -1;
	maxsize = size;
	stack_node = new T[maxsize];
}

template <typename T>
inline Stack<T>::~Stack()
{
	delete[] stack_node;
}

template <typename T>
inline bool Stack<T>::IsFull() const
{
	if (top == maxsize-1) return true; //array[299] -> total size=300
	else return false;
}

template <typename T>
inline bool Stack<T>::IsEmpty() const
{
	if (top == -1) return true; //->total size=0
	else return false;
}

template <typename T>
inline T Stack<T>::Pop()
{
	if (IsEmpty()) {
		return NULL;
	}
	else {
		//move stack (remove)
		return stack_node[top--];
	}
}

template <typename T>
inline void Stack<T>::Push(T node)
{
	if (IsFull()) {
		return;
	}
	else {
		//insert stack
		stack_node[++top] = node;
	}

}
