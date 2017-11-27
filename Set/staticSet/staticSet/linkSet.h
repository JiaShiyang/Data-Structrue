#ifndef LINKSET_GUARD
#define LINKSET_GUARD
#include <iostream>
using namespace std;

template <typename T>
class linkSet
{
	friend ostream& operator<<(ostream &os, const linkSet<T> &obj) {
		for (auto p = obj.head->next;p != nullptr;p = p->next)
			os << p->data << '\t';
		return os;
	}
public:
	linkSet(const T *data,int size);
	linkSet(const linkSet &other);
	linkSet& operator=(const linkSet &other);
	~linkSet() { clear(); delete head; }
	bool find(const T &x);

private:
	struct Node
	{
		T data;
		Node *next;
		Node(T d, Node* p = nullptr) :data(d), next(p) {}
		Node() :next(nullptr) {}
	};
	Node *head;

	void clear();
	void exchange(Node* p);		// exchange p->next with head->next
};

template <typename T>
linkSet<T>::linkSet(const T *data, int size)
{
	head = new Node();
	for (int i = 0;i < size;++i)
		head->next = new Node(data[i], head->next);
}

template <typename T>
linkSet<T>::linkSet(const linkSet &other)
{
	head = new Node();
	Node *tmp = head;

	for (Node *p = other.head->next;p != nullptr;p = p->next) {
		tmp->next = new Node(p->data);
		p = p->next;
	}
}

template <typename T>
linkSet<T>& linkSet<T>::operator=(const linkSet &other)
{
	if (this == &other) return *this;

	clear();
	Node *tmp = head;
	for (Node *p = other.head->next;p != nullptr;p = p->next) {
		tmp->next = new Node(p->data);
		p = p->next;
	}

	return *this;
}

template <typename T>
bool linkSet<T>::find(const T &x)
{
	Node *p = head;

	for (;p->next != nullptr;p = p->next)
		if (p->next->data == x) break;
	if (p->next == nullptr) return false;
	exchange(p);
	return true;
}

template <typename T>
void linkSet<T>::exchange(Node *p)
{
	if (p == head) return;

	Node *tmp = p->next;
	p->next = tmp->next;
	tmp->next = head->next;
	head->next = tmp;
}

template <typename T>
void linkSet<T>::clear()
{
	Node *p = head->next;

	while (p != nullptr) {
		head->next = p->next;
		delete p;
		p = head->next;
	}
}

#endif // !LINKSET_GUARD
