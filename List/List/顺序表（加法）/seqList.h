#ifndef SEQLIST_GUARD
#define SEQLIST_GUARD
#include "list.h"
#include <iostream>
using namespace std;

class OutOfBound{};
class IllegalSize{};

template <typename T>
class seqList:public list<T>
{
	T* data = NULL;
	unsigned maxSize;
	unsigned currentSize = 0;
	void doubleSpace();
	public:
		seqList(int size = 1);
		seqList(const seqList<T>&);
		seqList<T> operator+(const seqList<T>&);
		void clear() { currentSize = 0; }
		int length() const { return currentSize; }
		void insert(int i, const T&);		// 0 <= i <= currentSize
		void remove(int i);					// 0 <= i < currentSize
		int search(const T& x) const;		// return currentSize if x is not found
		T visit(int i) const;				// 0 <= i < currentSize
		void traverse() const;
		~seqList() { if(!data) delete [] data; }
};


template <typename T>
seqList<T>::seqList(const seqList<T>& other):
	maxSize(other.maxSize),currentSize(other.currentSize)
{
	data = new T(maxSize);

	for (int i = 0;i < currentSize;++i)
		data[i] = other.data[i];
}

template <typename T>
seqList<T> seqList<T>:: operator+(const seqList<T>& other)
{
	seqList<T> result(currentSize + other.currentSize);
	int i = 0;

	for (;i < currentSize;++i)
		result.insert(i, data[i]);
	for (;i < result.maxSize;++i)
		result.insert(i, other.data[i - currentSize]);

	return result;
}

template <typename T>
seqList<T>::seqList(int size)
{
	if (size <= 0) throw IllegalSize();
	maxSize = size;
	data = new T[maxSize];
}

template <typename T>
void seqList<T>::doubleSpace()
{
	T* tmp = data;
	maxSize *= 2;
	data = new T[maxSize];
	for (int i = 0;i < currentSize;++i)
		data[i] = tmp[i];
	delete[] tmp;
}

template <typename T>
void seqList<T>::insert(int i, const T& x)
{
	if (i<0 || i>currentSize) throw OutOfBound();
	if (currentSize == maxSize) doubleSpace();
	for (int j = currentSize;j > i;--j)
		data[j] = data[j - 1];
	data[i] = x;
	++currentSize;
}

template <typename T>
void seqList<T>::remove(int i)
{
	if (i < 0 || i >= currentSize) throw OutOfBound();
	for (int j = i;j < currentSize;++j)
		data[j] = data[j + 1];
	--currentSize;
}

template <typename T>
int seqList<T>::search(const T& x) const
{
	int i = 0;
	for (;i < currentSize;++i)
		if (data[i] == x) break;
	return i;
}

template <typename T>
T seqList<T>::visit(int i) const
{
	if (i < 0 || i >= currentSize) throw OutOfBound();
	return data[i];
}

template <typename T>
void seqList<T>::traverse() const
{
	for (int i = 0;i < currentSize;++i)
		cout << data[i] << '\t';
}

#endif // !SEQLIST_GUARD
