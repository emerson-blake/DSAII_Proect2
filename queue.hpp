/*
 * queue.hpp
 *
 *
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
private:
	bool isEmpty();
	Customer* head;
	Customer* tail;
};

#endif


