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
	bool isEmpty();
private:
	Customer* head;
	Customer* tail;
};

#endif


