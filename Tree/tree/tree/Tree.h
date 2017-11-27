#ifndef TREE_GUARD
#define TREE_GUARD
#include "LinkQueue.h"
#include <iostream>
using namespace std;

template <typename T>
class Tree {
protected:
	struct Node
	{
		T data;
		Node *bro, *son;

		Node(T d, Node* l = nullptr, Node*r = nullptr) :
			data(d), son(l), bro(r) {}
	};

	Node *root;

private:
	void clear(Node*);
	void preOrder(Node*) const;
	void postOrder(Node*) const;

public:
	Tree() :root(nullptr) {}
	Tree(const T& data) { root = new Node(data); }
	Tree(const Node *p) :root(p) {}
	~Tree() { clear(root); }

	bool isEmpty() const { return root == nullptr; }
	void creatTree(T flag);
	void preOrder() const { 
		cout << "pre order:\n";
		preOrder(root); 
		cout << endl;
	}
	void postOrder() const {
		cout << "post order:\n";
		postOrder(root); 
		cout << endl;
	}
	void levelOrder() const;
};

template <typename T>
void Tree<T>::clear(Node *root) {
	if (root == nullptr) return;
	Node *p = root->son, *q;

	// delete root'a all sons
	while (p != nullptr) {
		q = p;
		p = q->bro;
		delete q;
	}
	// then delete root
	delete root;
}

template <typename T>
void Tree<T>::creatTree(T flag) {
	clear(root);
	LinkQueue<Node*> que;
	Node *current;
	T data;

	// creat tree, flag means tranverse ends
	cout << "start crearting tree:\n";
	do {
		cout << "input the root:";
		cin >> data;
	} while (data == flag);
	que.enQueue(root = new Node(data));

	while (!que.isEmpty()) {
		current = que.deQueue();
		cout << "input " << current->data << " 's all children:";
		cin >> data;
		if (data == flag) continue;
		que.enQueue(current->son = new Node(data));
		current = current->son;
		while (cin >> data && data != flag) {
			que.enQueue(current->bro = new Node(data));
			current = current->bro;
		}
	}
}

template <typename T>
void Tree<T>::preOrder(Node *root) const {
	if (root == nullptr) return;
	cout << root->data << '\t';
	root = root->son;
	while (root != nullptr) {
		preOrder(root);
		root = root->bro;
	}
}

template <typename T>
void Tree<T>::postOrder(Node *root) const {
	if (root == nullptr) return;

	Node *p = root->son;
	while (p != nullptr) {
		postOrder(p);
		p = p->bro;
	}
	cout << root->data << '\t';
}

template <typename T>
void Tree<T>::levelOrder() const {
	if (root == nullptr) return;

	LinkQueue<Node*> que;
	Node *current;

	cout << "level order:\n";
	que.enQueue(root);
	while (!que.isEmpty()) {
		current = que.deQueue();
		// tranverse current's brothers
		while (current) {
			cout << current->data << '\t';
			// enqueue if current has sons
			if (current->son != nullptr)
				que.enQueue(current->son);
			current = current->bro;
		}
	}
	cout << endl;
}

#endif // !TREE_GUARD
