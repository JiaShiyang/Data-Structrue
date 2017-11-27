#ifndef PACKAGE_GUARD
#define PACKAGE_GUARD
#include <iostream>
#include "PriorityQueue.h"
using namespace std;

class Package
{
public:
	Package();
	~Package() { if (weights) delete weights; }
	int boxs() const;

private:
	double *weights;
	int size;
};

Package::Package()
// initialize the weights array
{
	do {
		cout << "input the number of goods: ";
		cin >> size;
	} while (size <= 0);
	
	weights = new double[size];
	for(int i = 0;i<size;++i)
		do {
			cout << "input weight of No." << i + 1 << " good:";
			cin >> weights[i];
		} while (weights[i] > 1 | weights[i] <= 0);
}

int Package::boxs() const
// calculate the number of boxs required
{
	PriorityQueue<double> boxs(size);
	int i, index;
	int No_box = 0;		// the number of boxs
	for (i = 1;i <= size;++i) boxs.enQueue(1);

	for (i = 0;i < size;++i) {
		index = boxs.findMin(weights[i]);
		boxs.decreaseKey(index, weights[i]);
	}

	while (!boxs.isEmpty()) {
		if (boxs.deQueue() < 1) ++No_box;
		else break;
	}
	return No_box;
}

#endif // !PACKAGE_GUARD