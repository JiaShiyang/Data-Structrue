#ifndef QUEUE_GUARD
#define QUEUE_GUARD

template <typename T>
class Queue
{
	public:
		virtual void enQueue(const T&) = 0;
		virtual T deQueue() = 0;
		virtual T getHead() const = 0;
		virtual T getTail() const = 0;
		virtual bool isEmpty() const = 0;
		virtual int getSize() const = 0;
		virtual ~Queue() {}
};

#endif // !QUEUE_GUARD
