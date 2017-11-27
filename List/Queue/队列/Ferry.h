#ifndef FERRY_GUARD
#define FERRY_GUARD
#include "LinkQueue.h"
#include <iostream>
#include <ctime>

class Ferry
{
	LinkQueue<unsigned> car, truck;
	unsigned carArriveLow, carArriveHigh;
	unsigned truckArriveLow, truckArriveHigh;
	unsigned totalTime;
	double carWaitTime, truckWaitTime;

	void makeQueue();
	void display() const;

public:
	Ferry();
	void avgWaitTime();
};

#endif // !FERRY_GUARD
