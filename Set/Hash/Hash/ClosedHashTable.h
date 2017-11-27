#ifndef CLOSED_HASH_TABLE_GUARD
#define CLOSED_HASH_TABLE_GUARD
#include "HashTable.h"

template <typename T>
class ClosedHashTable : public HashTable<T>
{
private:
	struct Node
	{
		T data;
		int state;		// 0:empty  1:active  2:deleted

		Node() :state(0) {}
	};

	Node * array;
	int size;
	int active, deleted;
	int max_deleted;

	int get_prime(int size) const;	// get the smallest prime not less than size
	void expand();		// expend size to the smallest prime not less than double size

public:
	ClosedHashTable(int s, int max, int(*f)(const T &x) = defaultKey);
	ClosedHashTable() = delete;
	~ClosedHashTable() { delete[] array; }
	int get_size() const { return size; }
	int get_active() const { return active; }
	int get_deleted() const { return deleted; }
	bool find(const T &x) const;
	bool insert(const T &x);
	bool remove(const T &x);
	void reHash();
};

template <typename T>
ClosedHashTable<T>::ClosedHashTable(int s, int max, int(*f)(const T &x))
	:max_deleted(max), active(0), deleted(0)
{
	size = get_prime(s);
	array = new Node[size];
	key = f;
}

template <typename T>
int ClosedHashTable<T>::get_prime(int size) const
{
	int i, j;
	if (size == 2 || size == 3) return size;
	if (size % 2 == 0) ++size;

	for (i = size;;i += 2) {
		for (j = 3; j*j <= i;j += 2)
			if (i % j == 0) break;
		if (j*j > i) return i;
	}
}

template <typename T>
void ClosedHashTable<T>::expand()
{
	int old_size = size;
	size = get_prime(size * 2);		// using prime as size
	Node *tmp = array;
	array = new Node[size];
	active = deleted = 0;

	for (int i = 0;i < old_size;++i) 
		if (tmp[i].state == 1) insert(tmp[i].data);

	delete[]tmp;
}

template <typename T>
void ClosedHashTable<T>::reHash()
{
	Node *tmp = array;
	array = new Node[size];
	active = deleted = 0;

	for (int i = 0;i < size;++i)
		if (tmp[i].state == 1) insert(tmp[i].data);

	delete[]tmp;
}

template <typename T>
bool ClosedHashTable<T>::find(const T &x) const
{
	int pop = key(x) % size;

	for (int i = 1;i <= size / 2;++i) {
		if (array[pop].state == 1 && array[pop].data == x)
			return true;
		pop += 2 * i - 1;
		if (pop >= size) pop -= size;
	}
	
	return false;
}

template <typename T>
bool ClosedHashTable<T>::insert(const T &x)
{
	int pop = key(x) % size;

	for (int i = 1;i <= size / 2;++i) {
		if (array[pop].state == 1 && array[pop].data == x)
			return false;
		if (array[pop].state == 0) break;
		pop += 2 * i - 1;
		if (pop >= size) pop -= size;
	}

	if (++active > size / 2) expand();

	pop = key(x) % size;
	for (int i = 1;i <= size / 2;++i) {
		if (array[pop].state != 1) break;
		pop += 2 * i - 1;
		if (pop >= size) pop -= size;
	}
	if (array[pop].state == 2) --deleted;
	array[pop].state = 1;
	array[pop].data = x;
	
	return true;
}

template <typename T>
bool ClosedHashTable<T>::remove(const T &x)
{
	int pop = key(x) % size;

	for (int i = 1;i <= size / 2;++i) {
		if (array[pop].state == 1 && array[pop].data == x) {
			array[pop].state = 2;
			if (++deleted == max_deleted) reHash();
			return true;
		}
		pop += 2 * i - 1;
		if (pop >= size) pop -= size;
	}

	return false;
}

#endif // !CLOSED_HASH_TABLE_GUARD
