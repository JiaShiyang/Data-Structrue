#ifndef SINGLE_LINK_LIST_GUARD
#define SINGLE_LINK_LIST_GUARD
#include <iostream>
#include "list.h"
using namespace std;

class OutOfBound{};

template <typename T>
class singleLinkList :public list<T>
{
	struct Node
	{
		T data;
		Node* next;
		Node(T d, Node* p = NULL) :data(d), next(p) {}
		Node() :next(NULL) {}
		~Node() {}
	};
	int currentLength = 0;
	Node* head;
	Node* move(int i) const;

public:
	singleLinkList() { head = new Node;  }
	void clear();
	int length() const { return currentLength; }
	T visit(int i) const;		// 0 <= i < currentLength
	void traverse() const;
	int search(const T& x) const;		// return currentSize if x is not found
	void insert(int i, const T&);		// 0 <= i <= currentLength
	void remove(int i);					// 0 <= i < currentLength
	void reverse();
	~singleLinkList() { clear(); delete head; }
};

template <typename T>
typename singleLinkList<T>::Node* singleLinkList<T>::move(int i) const
{
	if (i < 0) return head;

	Node* p = head->next;
	while (i > 0) {
		p = p->next;
		--i;
	}
	return p;
}

template <typename T>
void singleLinkList<T>::clear()
{
	Node* p = head->next, *q;
	while (p != NULL) {
		q = p;
		p = q->next;
		delete q;
	}
	currentLength = 0;
}

template <typename T>
T singleLinkList<T>::visit(int i) const
{
	if (i < 0 || i >= currentLength) throw OutOfBound();
	return move(i)->data;
}

template <typename T>
void singleLinkList<T>::traverse() const
{
	Node* p = head->next;
	while (p != NULL) {
		cout << p->data << '\t';
		p = p->next;
	}
}

template <typename T>
int singleLinkList<T>::search(const T& x) const
{
	Node* p = head->next;
	int i = 0;
	while (p != NULL && p->data != x) {
		p = p->next;
		++i;
	}
	return i;
}

template <typename T>
void singleLinkList<T>::insert(int i, const T& x)
{
	if (i<0 || i>currentLength) throw OutOfBound();
	Node* p = move(i - 1);
	p->next = new Node(x, p->next);

	++currentLength;
}

template <typename T>
void singleLinkList<T>::remove(int i)
{
	if (i < 0 || i >= currentLength) throw OutOfBound();
	Node* p = move(i - 1);
	Node* tmp = p->next;
	p->next = tmp->next;
	delete tmp;

	--currentLength;
}

template <typename T>
void singleLinkList<T>::reverse()
// reverse pointers at the same space
{
	if (currentLength <= 1) return;		// ensure there are at least 2 nodes

	Node* p = head->next, *q = p->next, *r = q->next;
	p->next = NULL;
	while (true) {
		q->next = p;		// make the next pointer point to a former node
		if (r == NULL) break;
		p = q; q = r;
		r = r->next;
	}
	head->next = q;		// switch the hear->next point to the new first node
}

// another way to achieve reverse()
/*
template <typename T>
void singleLinkList<T>::reverse()
// traverse the list and create a new reversed one
{
	if(currentLength == 1) return;

	Node* p = head->next, *q, *tmp = NULL;
	while (p != NULL) {
		tmp = new Node(p->data, tmp);
		q = p;
		p = q->next;
		delete q;
	}
	head->next = tmp;
}
*/

#endif // !SINGLE_LINK_LIST_GUARD