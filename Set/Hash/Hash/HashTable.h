#ifndef HASH_TABLE_GUARD
#define HASH_TABLE_GUARG

template <typename T>
class HashTable
{
public:
	virtual bool find(const T &x) const = 0;
	virtual bool insert(const T &x) = 0;
	virtual bool remove(const T &x) = 0;
protected:
	int(*key)(const T &x);
	static int defaultKey(const int &x) { return x; }
};

#endif // !HASH_TABLE_GUARD
