#ifndef SEQSET_GUARD
#define SEQSET_GUARD
#include <iostream>
using namespace std;

template <typename T>
class seqSet
{
	friend ostream& operator<<(ostream &os, const seqSet<T> obj) {
		for (int i = 0;i < obj.size;++i)
			os << obj.data[i] << '\t';
		return os;
	}
public:
	seqSet(const T* data, int size);
	seqSet(const seqSet &other);
	seqSet() = default;
	~seqSet() { if (data) delete [] data; }
	seqSet& operator=(const seqSet &other);
	seqSet operator*(const seqSet &other);
	seqSet operator+(const seqSet &other);
	seqSet operator-(const seqSet &other);

private:
	T *data;
	int size;
};

template <typename T>
seqSet<T>::seqSet(const T* d, int s) :size(s)
{
	data = new T[size];
	for (int i = 0;i < size;++i)
		data[i] = d[i];
}

template <typename T>
seqSet<T>::seqSet(const seqSet &other) :size(other.size)
{
	data = new T[size];
	for (int i = 0;i < size;++i)
		data[i] = other.data[i];
}

template <typename T>
seqSet<T>& seqSet<T>::operator=(const seqSet &other)
{
	if (this == &other) return *this;

	size = other.size;
	delete [] data;
	data = new T[size];
	for (int i = 0;i < size;++i)
		data[i] = other.data[i];

	return *this;
}

template <typename T>
seqSet<T> seqSet<T>::operator*(const seqSet &other)
{
	int new_size = 0;
	T *new_data = new T[size + other.size];

	for (int i = 0;i < size;++i)
		for (int j = 0;j < other.size;++j)
			if (data[i] == other.data[j])
				new_data[new_size++] = data[i];

	return seqSet(new_data, new_size);
}

template <typename T>
seqSet<T> seqSet<T>::operator+(const seqSet &other)
{
	int new_size = 0, i = 0;
	T *new_data = new T[size + other.size];

	for (int j = 0;j < size;++j)
		new_data[new_size++] = data[j];
	for (int j = 0;j < other.size;++j) {
		for (i = 0;i < size;++i)
			if (data[i] == other.data[j]) break;
		if (i == size)
			new_data[new_size++] = other.data[j];
	}

	return seqSet(new_data, new_size);

}

template <typename T>
seqSet<T> seqSet<T>::operator-(const seqSet &other)
{
	int new_size = 0, i = 0;
	T *new_data = new T[size];

	for (int j = 0;j < size;++j) {
		for (i = 0;i < other.size;++i)
			if (data[j] == other.data[i]) break;
		if (i == other.size)
			new_data[new_size++] = data[j];
	}

	return seqSet(new_data, new_size);
}

#endif // !SEQSET_GUARD
