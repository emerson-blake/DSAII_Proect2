/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"queue.cpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * Definitions of class Queue's data members
*/


#include <iostream>

#include "queue.hpp"
#include "customer.hpp"


/*
 * Queue()
 * Constructor:
 * initiazes head and tail to nullptr
 */

Queue::Queue(){
	head = nullptr;
	tail = nullptr;
}


/*
 * ~Queue()
 * Desctructor:
 * iterates through list and deletes objects
 * this should never be called with items in list for this simulation
 */

Queue::~Queue(){
	Customer* ptr = head;
	if(head != nullptr){										// if at least 1 item in list
		if(head->getNext() != nullptr){								// if at least 2 items in list
			for(ptr = head->getNext(); ptr->getNext() != nullptr; ptr = ptr->getNext())	// runs n-2 times
				delete ptr->getPrevious();						// deletes all but last 2 items
			delete ptr->getPrevious();							// deletes 2nd to last item
		} 											// only 1 item left
		delete ptr;										// deletes last item
	}												// 0 items left
}


/*
 * enqueue()
 * adds object to list
 * objects are added to tail, will be removed from head
 */

void Queue::enqueue(Customer* customer){
	if(isEmpty()){
		head = customer;
		tail = customer;
	}
	else {
		customer->setPrevious(tail);
		tail->setNext(customer);
		tail = customer;
	}
}


/*
 * serve()
 * removes object from head, returns object
 */

Customer* Queue::serve(){
	Customer* toBeServed = head;
	if(isEmpty()){
		std::cout << "Error: queue is empty. cannot serve.\n";
	}
	else if(head == tail){			// only 1 item in queue
		head = nullptr;
		tail = nullptr;
	}
	else {					// more than 1 item in queue
		head->getNext()->setPrevious(nullptr);
		head = head->getNext();
	}
	return toBeServed;
}


/*
 * isEmpty()
 * if queue is empty, the head will equal nullptr
 * returns true if queue is empty, false if at least 1 object in it
 */

bool Queue::isEmpty(){
	if(head == nullptr){
		return true;
	}
	return false;
}
