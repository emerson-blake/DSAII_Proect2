/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"heap.hpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 *
 * Definition of class Heap
 * Used as priority queue of Customer objects
 * Manages data in array
 * Performs organization to maintain heap requirements
 */

#ifndef HEAP_HPP
#define HEAP_HPP

#include "customer.hpp"

#define MAXSIZE 200

class Heap{
public:
	Heap();
	~Heap();
	bool isEmpty();
	Customer* deleteMin();			// this IS the serve/dequeue function
	void constructHeap(Customer** v, int vSize);
	void buildHeap();
	void percolateDown(int slot);
	void percolateUp(Customer* customer);	// this IS the insert/enqueue function
	int  getTheSize();
	int  getMaxSize();
	float getLastArrivalTime();
private:
	int maxSize = MAXSIZE;
	int theSize = 0;
	Customer* arr[MAXSIZE+1];
};

#endif
