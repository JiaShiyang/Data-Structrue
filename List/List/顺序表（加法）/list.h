#ifndef LIST_GUARD
#define LIST_GUARD

template <typename T>
class list
{
public:
	virtual void clear() = 0;
	virtual int length() const = 0;
	virtual void insert(int i, const T&) = 0;
	virtual void remove(int i) = 0;
	virtual int search(const T&) const = 0;
	virtual T visit(int i) const = 0;
	virtual void traverse() const = 0;
	virtual ~list() {}
};

#endif // !LIST_GUARD