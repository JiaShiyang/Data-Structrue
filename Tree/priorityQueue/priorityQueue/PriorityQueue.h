#ifndef PRIORITY_QUEUE_GUARD
#define PRIORITY_QUEUE_GUARD

class EmptyQueue{};
class IllegalInput{};
template <typename T>
class PriorityQueue
{
public:
	PriorityQueue(int size = 10);
	PriorityQueue(const T* queue, int size);
	~PriorityQueue() { if (queue) delete[]queue; }
	bool isEmpty() const { return current_size == 0; }
	T getHead() const { 
		if (isEmpty()) throw EmptyQueue();
		return queue[1]; 
	}
	void enQueue(const T& data);
	T deQueue();

	int findMin(const T& x) const;					// 7.(1)
	void decreaseKey(int index, const T& value);	// 7.(2)

private:
	T *queue;
	int max_size;
	int current_size;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int i);
	void percolateUp(int i);
};

template <typename T>
PriorityQueue<T>::PriorityQueue(int size)
{
	if (size <= 0) throw IllegalInput();
	current_size = 0;
	max_size = size;
	queue = new T[size + 1];
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const T* q, int size)
{
	if (size <= 0) throw IllegalInput();
	max_size = size + 10;
	current_size = size;
	queue = new T[max_size + 1];
	for (int i = 0;i < size;++i)
		queue[i + 1] = q[i];
	buildHeap();
}

template <typename T>
void PriorityQueue<T>::doubleSpace()
{
	T *tmp = queue;
	max_size *= 2;
	queue = new T[max_size + 1];
	for (int i = 1;i <= current_size;++i)
		queue[i] = tmp[i];
}

template <typename T>
void PriorityQueue<T>::buildHeap()
{
	for (int i = current_size / 2;i > 0;--i)
		percolateDown(i);
}

template <typename T>
void PriorityQueue<T>::percolateDown(int i)
{
	T tmp = queue[i];
	int child, hole = i;

	while (hole * 2 <= current_size) {
		child = hole * 2;
		if (child + 1 <= current_size && queue[child + 1] < queue[child])
			++child;
		if (queue[child] < queue[hole]) {
			queue[hole] = queue[child];
			hole = child;
		}
		else break;
	}
	queue[hole] = tmp;
}

template <typename T>
void PriorityQueue<T>::percolateUp(int i)
{
	T tmp = queue[i];

	while (i > 1 && tmp < queue[i / 2]) {
		queue[i] = queue[i / 2];
		i /= 2;
	}
	queue[i] = tmp;
}

template <typename T>
void PriorityQueue<T>::enQueue(const T& x)
{
	if (current_size == max_size) doubleSpace();
	queue[++current_size] = x;

	percolateUp(current_size);
}

template <typename T>
T PriorityQueue<T>::deQueue()
{
	if (isEmpty()) throw EmptyQueue();
	T min = queue[1];
	queue[1] = queue[current_size--];
	percolateDown(1);
	return min;
}

template <typename T>
int PriorityQueue<T>::findMin(const T& x) const
// if all of elements in queue are less than x, return 0
{
	int index = 0;
	
	for (int i = 1;i <= current_size;++i)
		if (x <= queue[i] && (index == 0 || queue[i] < queue[index]))
			index = i;
	return index;
}

template <typename T>
void PriorityQueue<T>::decreaseKey(int i, const T& value)
// change queue[i] then sort the queue using percolateUp and percolateDown
{
	// examine input parameters
	if (i < 1) throw IllegalInput();
	if (value == 0) return;

	queue[i] -= value;
	if (value > 0) percolateUp(i);
	if (value < 0) percolateDown(i);
}

#endif // !PRIORITY_QUEUE_GUARD

