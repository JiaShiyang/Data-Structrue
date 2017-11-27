#ifndef BINARY_SEARCH_TREE_GUARD
#define BINARY_SEARCH_TREE_GUARD
#include <iostream>
#include "linkStack.h"
using namespace std;


template <typename T>
class BinarySearchTree
{
	// to test
	friend ostream& operator<<(ostream& os, const BinarySearchTree<T>& obj)
	{
		if (obj.root == nullptr) return os;

		LinkStack<BinaryNode*> st;
		st.push(obj.root);
		BinaryNode *elem;

		while (!st.isEmpty()) {
			elem = st.pop();
			os << elem->data << '\t';
			if (elem->right != nullptr) st.push(elem->right);
			if (elem->left != nullptr) st.push(elem->left);
		}

		return os;
	}
public:
	BinarySearchTree() :root(nullptr) {}
	~BinarySearchTree() { clear(root); }

	// 12.2
	void delete_less_than(const T &x) { delete_less_than(root, x); }
	void delete_more_than(const T &x) { delete_more_than(root, x); }
	void delete_range(const T &x1, const T &x2) {
		delete_moer_than(x1);
		delete_less_than(x2);
	}

	// 12.3
	bool find(const T& x) const;
	bool insert(const T& x);
	bool remove(const T& x);

	// 12.9
	bool find_max(int i, T& data) const;

private:
	struct BinaryNode
	{
		T data;
		BinaryNode *left, *right;

		BinaryNode(const T& x, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
			:data(x), left(l), right(r) {}
	};

	BinaryNode *root;

	void clear(BinaryNode* t);

	// 12.2
	void delete_less_than(BinaryNode* &t, const T &x);
	void delete_more_than(BinaryNode* &t, const T &x);
};


// implement

template <typename T>
void BinarySearchTree<T>::clear(BinaryNode* t)
{
	if (t == nullptr) return;
	clear(t->left);
	clear(t->right);
	delete t;
}

/****************************** 12.2 ********************************/

template <typename T>
void BinarySearchTree<T>::delete_less_than(BinaryNode* &t, const T &x)
{
	if (t == nullptr) return;
	if (t->data == x) {
		clear(t->left);
		t->left = nullptr;
	}
	else 
		if (t->data > x) delete_less_than(t->left, x);
		else {
			clear(t->left);
			BinaryNode *tmp = t;
			delete_less_than(t = t->right, x);
			delete tmp;
		}
}

template <typename T>
void BinarySearchTree<T>::delete_more_than(BinaryNode* &t, const T& x)
{
	if (t == nullptr) return;
	if (t->data == x) {
		clear(t->right);
		t->right = nullptr;
	}
	if (t->data < x) delete_more_than(t->right, x);
	else {
		clear(t->right);
		BinaryNode *tmp = t;
		delete_more_than(t = t->left, x);
		delete tmp;
	}
}

/**************************** 12.2 end ******************************/



/****************************** 12.3 ********************************/

template <typename T>
bool BinarySearchTree<T>::find(const T& x) const
{
	BinaryNode* tmp = root;

	while (tmp != nullptr) {
		if (tmp->data == x) return true;
		if (x > tmp->data) tmp = tmp->right;
		else tmp = tmp->left;
	}
	return false;
}

template <typename T>
bool BinarySearchTree<T>::insert(const T& x)
{
	if (root == nullptr) {
		root = new BinaryNode(x);
		return true;
	}
	BinaryNode *tmp = root, *child = root;

	while (child != nullptr) {
		tmp = child;
		if (tmp->data == x) return false;
		if (x < tmp->data) child = tmp->left;
		else child = tmp->right;
	}
	if (x < tmp->data) tmp->left = new BinaryNode(x);
	else tmp->right = new BinaryNode(x);

	return true;
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& x)
{
	if (root == nullptr) return false;
	
	BinaryNode *par = root, *child = root;
	BinaryNode *tmp = nullptr;

	while (child != nullptr) {
		if (child->data == x) {
			// if Node child have 2 children, change par and child
			if (child->left && child->right) {
				tmp = child;
				par = child;
				child = par->left;
				while (child->right != nullptr) {
					par = child;
					child = child->right;
				}
				tmp->data = child->data;
			}
			tmp = ((child->left == nullptr) ? child->right : child->left);
			if (par->left == child) par->left = tmp;
			else par->right = tmp;
			delete child;
			return true;
		}
		par = child;
		if (x < child->data) child = child->left;
		else child = child->right;
	}
	// loop ends means x is not found!
	return false;
}

/****************************** 12.3 end ****************************/



/****************************** 12.9 ********************************/

template <typename T>
bool BinarySearchTree<T>::find_max(int i, T& data) const
{
	if (root == nullptr || i <= 0) return false;

	LinkStack<BinaryNode*> st;
	BinaryNode *elem, *tmp;
	for (elem = root;elem != nullptr;elem = elem->right)
		st.push(elem);

	for (int j = 1;j <= i;++j) {
		if (st.isEmpty()) return false;
		elem = st.pop();
		tmp = elem->left;
		while (tmp != nullptr) {
			st.push(tmp);
			tmp = tmp->right;
		}
	}
	data = elem->data;
	return true;
}

/****************************** 12.9 end ****************************/

#endif // !BINARY_SEARCH_TREE_GUARD
