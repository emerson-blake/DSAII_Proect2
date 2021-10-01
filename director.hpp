/*
 * director.hpp
 *
 *
 */

#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include "scheduler.hpp"
#include "statistician.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "customer.hpp"

class Director{
public:
	Director(int arrivalsPerUnit, int serverdPerUnit, int totalServers, int totalEvents);
	~Director();

	void loadArrivals();
	float getNextArrivalTime();
	void processEvents();
	void processNextEvent();
	void startServingCustomer(Customer* customer, float eventTime);
private:
	Queue waitQueue;
	Heap eventQueue;
	Scheduler scheduler;
	Statistician statistician;
	int totalServers;		// M
	int availableServers;
	int arrivalsPerUnit;		// lambda
	int servedPerUnit;		// mu
	int totalEvents;		// n
	int processedEvents;
};

#endif
