/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"customer.hpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 *
 * Definition of Customer class
 * Customer class object keeps track of arrival, startOfService, and departure times for 1 customer
 * Customer class object is a node in a priority queue used by a Heap class object (requiring priority value)
 * Customer class object is also used in FIFO queue used by a Queue class object (requiring next and previous pointers)
 */ 

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

class Customer{
public:
	Customer(float arrivalTime = 0.0);
	void  setArrivalTime(float arrivalTime);
	void  setStartOfServiceTime(float startOfServiceTime);
	void  setDepartureTime(float departureTime);
	void  setNext(Customer* next);
	void  setPrevious(Customer* previous);
	bool  isArrival();
	float getPriorityValue();		// used in priority queue
	float getArrivalTime();
	float getStartOfServiceTime();
	float getDepartureTime();
	Customer* getNext();		// used in FIFO queue
	Customer* getPrevious();
private:
	float arrivalTime;
	float startOfServiceTime;
	float departureTime;
	Customer* next;			// used in FIFO queue
	Customer* previous;		// used in FIFO queue
};

#endif
