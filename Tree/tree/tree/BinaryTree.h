#ifndef BINARY_TREE_GUARD
#define BINARTY_TREE_GUARD
#include <iostream>
#include "LinkStack.h"
#include "LinkQueue.h"
using namespace std;

template <typename T>
class BinaryTree
{
protected:
	struct Node
	{
		T data;
		Node *right, *left;

		Node(T d, Node* l = nullptr, Node*r = nullptr) :
			data(d), left(l), right(r) {}
	};

	Node *root;
	void clear(Node*);

public:
	BinaryTree() :root(nullptr) {}
	BinaryTree(const T& data) { root = new Node(data); }
	BinaryTree(const Node *p) :root(p) {}
	~BinaryTree() { clear(root); }

	bool isEmpty() const { return root == nullptr; }
	void makeTree(const T& x, BinaryTree &t1, BinaryTree &t2);
	void creatTree(T flag);
	void preOrder() const;
	void midOrder() const;
	void postOrder() const;
	void levelOrder() const;		// 5.3
	bool is_complete() const;		// 5.4 
};

template <typename T>
void BinaryTree<T>::clear(Node *root) {
	if (root == nullptr) return;

	LinkStack<Node*> st;
	Node *current;

	st.push(root);
	while (!st.isEmpty()) {
		current = st.pop();
		if (current->left != nullptr) st.push(current->left);
		if (current->right != nullptr) st.push(current->right);
		delete current;
	}
}

template <typename T>
void BinaryTree<T>::makeTree(const T& x, BinaryTree &t1, BinaryTree &t2) {
	clear(root);
	root = new Node(x, t1.root, t2.root);
	t1.root = nullptr;
	t2.root = nullptr;
}

template <typename T>
void BinaryTree<T>::creatTree(T flag) {
	clear(root);
	T ldata, rdata;
	Node *current;
	LinkQueue<Node*> que;

	cout << "start creating BinaryTree:\n";
	do {
		cout << "input root data:";
		cin >> ldata;
	} while (ldata == flag);
	que.enQueue(root = new Node(ldata));
	
	while (!que.isEmpty()) {
		current = que.deQueue();
		cout << "input " << current->data << " 's children:";
		cin >> ldata >> rdata;
		if (ldata != flag)
			que.enQueue(current->left = new Node(ldata));
		if (rdata != flag)
			que.enQueue(current->right = new Node(rdata));
	}
	cout << "finish creating BinaryTree!\n";
}


template <typename T>
void BinaryTree<T>::preOrder() const {
	LinkStack<Node*> st;
	Node *current;

	cout << "pre_order:\n";
	if (root == nullptr) return;
	st.push(root);
	while (!st.isEmpty()) {
		current = st.pop();
		cout << current->data << '\t';
		if (current->right != nullptr) st.push(current->right);
		if (current->left != nullptr) st.push(current->left);
	}
	cout << endl;
}

template <typename T>
void BinaryTree<T>::midOrder() const {
	struct StNode
	{
		Node *node;
		int times_pop;

		StNode(Node *p = nullptr, int t = 0) :node(p), times_pop(t) {}
	};
	LinkStack<StNode> st;
	StNode current;

	cout << "mid_order:\n";
	if (root == nullptr) return;
	st.push(StNode(root));
	while (!st.isEmpty()) {
		current = st.pop();
		++current.times_pop;
		if (current.times_pop == 1) {
			st.push(current);
			if (current.node->left != nullptr)
				st.push(StNode(current.node->left));
		}
		else {
			cout << current.node->data << '\t';
			if (current.node->right != nullptr)
				st.push(StNode(current.node->right));
		}
	}
	cout << endl;
}

template <typename T>
void BinaryTree<T>::postOrder() const {
	struct StNode
	{
		Node *node;
		int times_pop;

		StNode(Node *p = nullptr, int t = 0) :node(p), times_pop(t) {}
	};
	LinkStack<StNode> st;
	StNode current;

	cout << "post_order:\n";
	if (root == nullptr) return;
	st.push(StNode(root));

	while (!st.isEmpty()) {
		current = st.pop();
		++current.times_pop;
		switch (current.times_pop)
		{
		case 1:
			st.push(current);
			if (current.node->left != nullptr)
				st.push(StNode(current.node->left));
			break;
		case 2:
			st.push(current);
			if (current.node->right != nullptr)
				st.push(StNode(current.node->right));
			break;
		case 3:
			cout << current.node->data << '\t';
		}
	}
	cout << endl;
}

template <typename T>
void BinaryTree<T>::levelOrder() const {
	Node *current;
	LinkQueue<Node*> que;

	if (root == nullptr) return;
	cout << "level order: \n";
	que.enQueue(root);
	while (!que.isEmpty()) {
		current = que.deQueue();
		cout << current->data << '\t';
		if (current->left != nullptr) que.enQueue(current->left);
		if (current->right != nullptr) que.enQueue(current->right);
	}
	cout << endl;
}

template <typename T>
bool BinaryTree<T>::is_complete() const {
	if (root == nullptr) return true;

	LinkQueue<Node*> que;
	Node *current = root;

	que.enQueue(root);
	// level-order traverse untill meet the first node that doesn't have two children
	while (current->left != nullptr && current->right != nullptr) {
		que.deQueue();
		que.enQueue(current->left);
		que.enQueue(current->right);
		current = que.getHead();
	}
	// the last no-leaf node can only have left child
	if (current->left != nullptr) {
		que.deQueue();
		que.enQueue(current->left);
	}
	// then all of the node left in queue must be leaves
	while (!que.isEmpty()) {
		current = que.deQueue();
		if (current->left != nullptr || current->right != nullptr)
			return false;
	}

	return true;
}

#endif // !BINARY_TREE_GUARD