/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"simulator.hpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * Definition of class Simulator
 * Simulator class objects are initialized with 4 parameters from a textfile
 * arrivalsPerUnit, servedPerUnit, totalServers, totalCustomers (lambda, mu, M, N)
 *
 * uses 4 different class objects to run simulation:
 * DataReader class object handles file stream and reads parameters from textfile
 * Calculator class object performs analytical and simulated calculations and prints result
 * Heap class object acts as priority queue to handle arrival and departure events
 * Queue class object acts as FIFO queue to handle customers waiting for service
 */


#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "datareader.hpp"
#include "calculator.hpp"
#include "queue.hpp"
#include "heap.hpp"

class Simulator{
public:
	Simulator(const char* fileName);
	void run();

private:
	DataReader reader;
	Queue waitQueue;
	Heap eventQueue;
	Calculator calculator;

	int arrivalsPerUnit;		// lambda
	int servedPerUnit;		// mu
	int totalServers;		// M
	int totalCustomers;		// N
	int availableServers;		// how many service windows are not currently serving customers
	int arrivalsLoaded;		// accumulates loaded arrivals so loadArrivals() doesn't load more than totalCustomers

	// private member functions
	float getNextArrivalTime();	
	void loadArrivals();
	void processEvents();
	void processNextEvent();
	void startServingCustomer(Customer* customer, float eventTime);};

#endif
