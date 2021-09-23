/*
 * queue.cpp
 * FIFO queue: Insert at tail, remove from head
 */

#include <iostream>

#include "queue.hpp"
#include "customer.hpp"

Queue::Queue(){
	head = nullptr;
	tail = nullptr;
}

Queue::~Queue(){
	// TODO: Iterate through nodes and delete pointers (shouldn't be needed for this simulation)
}

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

Customer* Queue::serve(){
	Customer* toBeServed = head;
	if(isEmpty()){
		std::cout << "Error: queue is empty. cannot serve.\n";
	}
	else if(head == tail){	// only 1 item in queue
		head = nullptr;
		tail = nullptr;
	}
	else {
		head->getNext()->setPrevious(nullptr);
		head = head->getNext();
	}
	return toBeServed;
}

bool Queue::isEmpty(){
	if(head == nullptr){
		return true;
	}
	return false;
}
