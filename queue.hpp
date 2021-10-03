/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"queue.hpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * Definition of class Queue
 * acts as FIFO queue of Customer class objects
 * doubly-linked list
*/


#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "customer.hpp"

class Queue{	// FIFO
public:
	Queue();
	~Queue();
	void enqueue(Customer* customer);
	Customer* serve();
	bool isEmpty();
private:
	Customer* head;
	Customer* tail;
};

#endif


