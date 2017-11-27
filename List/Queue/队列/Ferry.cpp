#include "Ferry.h"
using namespace std;

Ferry::Ferry() {
	cout << "Input total time(minute): ";
	cin >> totalTime;

	cout << "Input cars' minimum and maximal interval: ";
	cin >> carArriveLow >> carArriveHigh;

	cout << "Input trucks' minimum and maximal interval: ";
	cin >> truckArriveLow >> truckArriveHigh;

	srand(time(NULL));
}

void Ferry::avgWaitTime() {
	makeQueue();

	int carNUm = car.getSize();
	int truckNUm = truck.getSize();
	int time = 10, onboard = 0;

	for (time; time <= totalTime;time+=10) {
		onboard = 0;
		while (!car.isEmpty() && onboard < 8 && car.getHead() <= time) {
			carWaitTime += time - car.deQueue();
			++onboard;
		}
		while (!truck.isEmpty() && onboard<10 && truck.getHead()<=time)
		{
			truckWaitTime += time - truck.deQueue();
			++onboard;
		}
		while (!car.isEmpty() && onboard < 10 && car.getHead() <= time) {
			carWaitTime += time - car.deQueue();
			++onboard;
		}
	}

	carWaitTime /= carNUm;
	truckWaitTime /= truckNUm;

	display();
}

void Ferry::makeQueue() {
	int time = 0;

	while (time <= totalTime) {
		time += rand() % (carArriveHigh - carArriveLow + 1) + carArriveLow;
		car.enQueue(time);
	}
	time = 0;
	while (time<=totalTime)
	{
		time += rand() % (truckArriveHigh - truckArriveLow + 1) + truckArriveLow;
		truck.enQueue(time);
	}
}

void Ferry::display() const {
	cout << "Cars' average wait time: " << carWaitTime << "minutes\n";
	cout << "Trucks' average wait time: " << truckWaitTime << "minutes\n";
}