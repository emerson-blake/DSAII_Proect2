/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"simulator.cpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * Definitions of class Simulator's member functions:
 *
 */


#include "simulator.hpp"


/*
 * Simulator()
 * Constructor:
 * takes string, opens file of that name, reads/stores parameters from file
 * stores parameters into data members. Initializes other data members.
 */

Simulator::Simulator(const char* fileName){
	int lambda, mu, M, N;

	reader.openFile(fileName);
	reader.readParameters(&lambda, &mu, &M, &N);
	reader.closeFile();

	arrivalsPerUnit = lambda;
	servedPerUnit   = mu;
	totalServers    = M;
	totalCustomers  = N;

	availableServers = totalServers;
	arrivalsLoaded = 0;
}


/*
 * loadArrivals()
 *
 * if loadArrivals() not called for first time: 
 * | finds last scheduled arrival and adds random interval to it, saves in arrivalTime
 * else (loadArrivals() called for first time)
 * | sets arrivalTime to 0
 * end if
 *
 * while the event queue isn't full AND customers haven't all been loaded yet, loop:
 * | create new customer with calculated arrivalTime, add customer's arrival to event queue.
 * | add random interval to arrivalTime for next customer to use
 * end loop
 */

void Simulator::loadArrivals(){
	float arrivalTime;

	if(eventQueue.getTheSize() > 0) {
		arrivalTime = eventQueue.getLastArrivalTime();
		arrivalTime += calculator.calculateRandomInterval(arrivalsPerUnit);
	}
	else
		arrivalTime = 0;

	while (eventQueue.getTheSize() < eventQueue.getMaxSize() && arrivalsLoaded++ < totalCustomers){
		Customer* customer = new Customer(arrivalTime);
		eventQueue.percolateUp(customer);
		arrivalTime += calculator.calculateRandomInterval(arrivalsPerUnit);
	}	
}


/*
 * processEvents()
 * processes events until the event queue is empty
 * reloads event queue when it gets low and hasn't loaded all customers yet
 */

void Simulator::processEvents(){
	while (!eventQueue.isEmpty()) {	// loops until event queue is empty
		processNextEvent();
		if (eventQueue.getTheSize() <= totalServers+1 && arrivalsLoaded < totalCustomers) { // only loads when low AND more customers need loading
			loadArrivals();
		}
	}
}


/*
 * processNextEvent()
 *
 * processes a single event
 * removes priority event/customer from event queue, determines if it is arrival or departure event, handles differently
 *
 * if arrival
 * | if server available
 * | | start serving customer, checks to stop counting idle time
 * | else (no servers available)
 * | | make customer wait in queue
 * | end if
 * else (departure)
 * | process customer stats, delete customer
 * | checks if last event, checks if customers waiting, checks to start counting idle time
 * end if
 */

void Simulator::processNextEvent(){
	Customer* customer = eventQueue.deleteMin();
	float eventTime = customer->getPriorityValue();

	if (customer->isArrival()) {

		if (availableServers > 0) {
			if (availableServers-- == totalServers)
				calculator.stopIdle(eventTime);
			startServingCustomer(customer, eventTime);
		}
		else
			waitQueue.enqueue(customer);
	}
	else {
		calculator.processCustomerStats(customer);
		delete customer;

		if(eventQueue.isEmpty())
			calculator.setSimulationTime(eventTime);
		else if (!waitQueue.isEmpty())
			startServingCustomer(waitQueue.serve(), eventTime);
		else if(++availableServers == totalServers)
			calculator.startIdle(eventTime);
	}
}


/*
 * startServingCustomer()
 * used in processNextEvent()
 * handles when a customer is moved to a service window, adds departure event to event queue
 */

void Simulator::startServingCustomer(Customer* customer, float startOfServiceTime){
	customer->setStartOfServiceTime(startOfServiceTime);
	customer->setDepartureTime(startOfServiceTime + calculator.calculateRandomInterval(servedPerUnit));
	eventQueue.percolateUp(customer);
}


/*
 * run()
 * initializes event queue
 * processes all events, tracks stats
 * analyzes data, compares results, prints results
 */

void Simulator::run(){
	loadArrivals();
	processEvents();
	calculator.showSimulationResults(arrivalsPerUnit, servedPerUnit, totalServers, totalCustomers);
}
