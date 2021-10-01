/*
 * director.cpp
 */

#include "director.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "scheduler.hpp"
#include "statistician.hpp"


Director::Director(int arrivalsPerUnit, int servedPerUnit, int totalServers, int totalEvents){
	this->arrivalsPerUnit = arrivalsPerUnit;
	this->servedPerUnit = servedPerUnit;
	this->totalServers = totalServers;
	this->totalEvents = totalEvents;

	availableServers = totalServers;
}

Director::~Director(){

}

void Director::loadArrivals(){
	float arrivalTime;

	if(eventQueue.getTheSize() > 0) {
		arrivalTime = eventQueue.getNextArrivalTime();
		arrivalTime += scheduler.getNextRandomInterval(arrivalsPerUnit);
	}
	else
		arrivalTime = 0;

	while (eventQueue.getTheSize() < eventQueue.getMaxSize()){
		Customer* customer = new Customer(arrivalTime);
		eventQueue.percolateUp(customer);
		arrivalTime += scheduler.getNextRandomInterval(arrivalsPerUnit);
	}	
}

void Director::processEvents(){
	loadArrivals();
	while (!eventQueue.isEmpty()) {
		processNextEvent();
		if (processedEvents < totalEvents && eventQueue.getTheSize() <= totalServers+1) {
			loadArrivals();
		}
	}
	statistician.showSimulationResults();
}

void Director::processNextEvent(){
	Customer* customer = eventQueue.deleteMin();
	float eventTime = customer->getPriorityValue();

	if (customer->isArrival()) {
		if (availableServers > 0)
			startServingCustomer(customer, eventTime);
		else
			waitQueue.enqueue(customer);
	}
	else {
		statistician.processCustomerStats(customer);
		if(++availableServers == totalServers)
			statistician.startIdle(eventTime);
		if (!waitQueue.isEmpty())
			startServingCustomer(waitQueue.serve(), eventTime);
	}
}

void Director::startServingCustomer(Customer* customer, float startOfServiceTime){
	if(availableServers-- == totalServers)
		statistician.stopIdle(startOfServiceTime);
	customer->setStartOfServiceTime(startOfServiceTime);
	customer->setDepartureTime(startOfServiceTime + scheduler.getNextRandomInterval(servedPerUnit));
	eventQueue.percolateUp(customer);
}
