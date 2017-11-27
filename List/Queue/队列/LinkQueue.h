#ifndef LINKQUEUE_GUARD
#define LINKQUEUE_GUARD
#include "Queue.h"

class EmptyQueue{};

template <typename T>
class LinkQueue :public Queue<T>
{
	struct Node
	{
		T data;
		Node* next;

		Node(const T& d, Node* p = nullptr) :data(d), next(p) {}
		Node() :next(nullptr) {}
	};

	Node* front, *rear;
	int size;

public:
	void enQueue(const T& x) {
		rear->next = new Node(x);
		rear = rear->next;
		++size;
	}
	T deQueue() {
		if (isEmpty()) throw EmptyQueue();

		Node* tmp = front->next;
		front->next = tmp->next;
		--size;
		T data = tmp->data;
		delete tmp;
		if (front->next == NULL)
			rear = front;

		return data;
	}
	bool isEmpty() const { return size == 0; }
	T getHead() const {
		if (isEmpty()) throw EmptyQueue();
		return front->next->data;
	}
	T getTail() const {
		if (isEmpty()) throw EmptyQueue();
		return rear->data;
	}
	void clear() {
		Node*p = front->next;
		while (p != nullptr) {
			front->next = p->next;
			delete p;
			p = front->next;
		}
		rear = front;
	}
	int getSize() const { return size; }

	LinkQueue() :size(0) {
		front = rear = new Node();
	}
	~LinkQueue() { clear();  delete front; }
};


#endif // !LINKQUEUE_GUARD
