#pragma once

using namespace std;

template <typename T>
class Queue {
public:
	int front;
	int rear;
	int count;
	int max_size;
	T* queue_node;

public:
	Queue(int size);
	virtual ~Queue();
	virtual bool IsFull() const;
	virtual bool IsEmpty() const;
	virtual void Enqueue(const T node);
	virtual T Dequque();

};
template <typename T>
inline Queue<T>::Queue(int size) {
	front = 0;	//first node
	rear = -1;	//last node
	count = 0;	//current node
	max_size = size;
	queue_node = new T[max_size];
}
template <typename T>
inline Queue<T>::~Queue()
{
	delete[] queue_node;
}
template <typename T>
inline bool Queue<T>::IsFull() const
{
	if (count == max_size) {
		return true;
	}
	else return false;
}
template <typename T>
inline bool Queue<T>::IsEmpty() const
{
	if (count == 0) {
		return true;
	}
	else return false;
}
template <typename T>
inline void Queue<T>::Enqueue(const T node)
{
	if (IsFull()) {
		return;
	}
	else {
		rear++; //move last queue point
		queue_node[count++] = node;
	}
}
template <typename T>
inline T Queue<T>::Dequque()
{
	if (IsEmpty()) {
		return NULL;
	}
	else {
		T return_node = queue_node[front];
		queue_node[front++] = NULL; //remove queue
		count--; //reduce queue size
		return return_node;
	}
}