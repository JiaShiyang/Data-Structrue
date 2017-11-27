#ifndef ARRAY_TREE_GUARD
#define ARRAY_TREE_GUARD
#include <iostream>
using namespace std;

class IllegalSize{};

template <typename T>
class ArrayTree
{
	T *tree;
	T flag;
	int max_size;
	int current_size;

	void doubleSpace();
	void preOrder(int i) const;
	void midOrder(int i) const;
	void postOrder(int i) const;

public:
	ArrayTree(const T& flag, int size = 10);
	ArrayTree(const T& flag, const T tree[], int size);
	~ArrayTree() { if (tree) delete [] tree; }

	bool isEmpty() const { return current_size == 0; }
	void creatTree();
	void preOrder() const {
		cout << "pre order:\n";
		preOrder(1);
		cout << endl;
	}
	void midOrder() const {
		cout << "mid order:\n";
		midOrder(1);
		cout << endl;
	}
	void postOrder() const {
		cout << "post order:\n";
		postOrder(1);
		cout << endl;
	}
	void levelOrder() const;
};

template <typename T>
ArrayTree<T>::ArrayTree(const T& f, int size = 10) 
	: flag(f), current_size(0)
{
	if (size <= 0) throw IllegalSize();
	max_size = size;
	tree = new T[max_size + 1];
}

template <typename T>
ArrayTree<T>::ArrayTree(const T& f,const T data[], int size) {
	if (size <= 0) throw IllegalSize();
	flag = f;
	current_size = size;
	max_size = size + 10;
	tree = new T[max_size + 1];
	for (int i = 0;i < size;++i)
		tree[i + 1] = data[i];
}

template <typename T>
void ArrayTree<T>::doubleSpace() {
	T *tmp = tree;

	max_size *= 2;
	tree = new T[max_size + 1];
	for (int i = 1;i <= current_size;++i)
		tree[i] = tmp[i];
	delete tmp;
}

template <typename T>
void ArrayTree<T>::creatTree() {
	T ldata, rdata;
	current_size = 0;	// clear the tree

	cout << "start creating tree:\n";
	do {
		cout << "input the root:";
		cin >> ldata;
	} while (ldata == flag);
	tree[++current_size] = ldata;

	for (int i = 1;i <= current_size;++i) {
		if (tree[i] == flag) continue;

		cout << "input " << tree[i] << " 's children:";
		cin >> ldata >> rdata;
		// skip the leaves
		if (ldata == flag && rdata == flag) continue;
		// fill the blank with flag
		while (current_size < 2 * i + 1) {
			if (current_size == max_size) doubleSpace();
			tree[++current_size] = flag;
		}
		tree[2 * i] = ldata;
		tree[2 * i + 1] = rdata;
	}
}

template <typename T>
void ArrayTree<T>::preOrder(int i) const {
	if (i > current_size || tree[i] == flag) return;
	cout << tree[i] << '\t';
	preOrder(2 * i);
	preOrder(2 * i + 1);
}

template <typename T>
void ArrayTree<T>::midOrder(int i) const {
	if (i > current_size || tree[i] == flag) return;
	midOrder(2 * i);
	cout << tree[i] << '\t';
	midOrder(2 * i + 1);
}

template <typename T>
void ArrayTree<T>::postOrder(int i) const {
	if (i > current_size || tree[i] == flag) return;
	postOrder(2 * i);
	postOrder(2 * i + 1);
	cout << tree[i] << '\t';
}

template <typename T>
void ArrayTree<T>::levelOrder() const  {
	cout << "level order:\n";
	for (int i = 1;i <= current_size;++i) {
		if (tree[i] == flag) continue;
		cout << tree[i] << '\t';
	}
}

#endif // !ARRAY_TREE_GUARD