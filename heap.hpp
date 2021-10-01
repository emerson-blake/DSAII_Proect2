/*
 * heap.hpp
 *
 *
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
//	Customer* findMin();			// empty definition
	Customer* deleteMin();			// this IS the serve/dequeue function
//	void makeEmpty();			// empty definition
	void constructHeap(Customer** v, int vSize);
	void buildHeap();
	void percolateDown(int slot);
	void percolateUp(Customer* customer);	// this IS the insert/enqueue function
	int  getTheSize();
	int  getMaxSize();
	float getNextArrivalTime();
private:
	int maxSize = MAXSIZE;
	int theSize = 0;
	Customer* arr[MAXSIZE+1];
};

#endif
