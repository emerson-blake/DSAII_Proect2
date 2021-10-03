/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"heap.cpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * Definitions of class Heap's member functions
*/

#include <iostream>

#include "heap.hpp"
#include "customer.hpp"


/*
 * Heap()
 * Constructor:
 * initializes theSize to 0
 * initializes all elements of arr to nullptr
 */

Heap::Heap(){
	theSize = 0;
	for(int i=1; i<MAXSIZE+1; i++)
		arr[i] = nullptr;
}


/*
 * ~Heap()
 * Desctructor:
 * deletes any remaining customer object when heap object is destroyed
 * this function should only be called when heap is empty for this simulation
 * customer deletion is handled elsewhere after customer stats are processed
 */

Heap::~Heap(){
	for(int i=1; i<theSize+1; i++)
		delete arr[i];
}


/*
 * isEmpty()
 * if heap object is empty, theSize will equal 0.
 * if theSize = 0, !theSize will equal true
 * if theSize > 0 (not empty), !theSize will equal false
 */

bool Heap::isEmpty(){
	return !theSize;	// if theSize == 0, returns true; if theSize > 0, returns false
}


/*
 * deleteMin()
 * this function is the dequeue/serve function
 * it removes the min value object (highest priority) and returns the object
 */

Customer* Heap::deleteMin(){			// modified from PowerPoint slide.
	Customer* tmp = arr[1];
	arr[1] = arr[theSize--];
	percolateDown(1);
	return tmp;
}


/*
 * constructHeap()
 * takes an input array full of objects
 * copies them into heap object's array
 * calls buildHeap() to heapify the stored array
 */

void Heap::constructHeap(Customer** v, int vSize){	// modified from PowerPoint slide.
	for(int i=0; i<vSize; i++)
		arr[i+1] = v[i];
	buildHeap();
}


/*
 * buildHeap()
 * heapify's the stored array
 * arranges the object in the array to maintain min heap requirements
 */

void Heap::buildHeap(){				// copied from PowerPoint slide.
	for(int i=theSize/2; i>0; i--)
		percolateDown(i);
}


/*
 * percolateDown()
 * called when removing items or when building heap
 * moves lower priority item down so higher priority items can come up
 */

void Heap::percolateDown(int slot){		// modified from PowerPoint slide.
	int child;
	Customer* tmp = arr[slot];

	while(slot*2 <= theSize){
		child = slot*2;
		if(child != theSize && 	arr[child+1]->getPriorityValue() < arr[child]->getPriorityValue())
			child++;
		if(arr[child]->getPriorityValue() < tmp->getPriorityValue())
			arr[slot] = arr[child];
		else
			break;	// get out of loop-slot indexes insertion pt
		slot = child;
	}
	arr[slot] = tmp;
}


/*
 * percolateUp()
 * called when adding items to heap
 * increments theSize
 * starts new item at bottom
 * moves higher priority item up so lower priority items come down
 */

void Heap::percolateUp(Customer* customer){	// modified from PowerPoint slide.
	arr[0] = customer;
	int slot = ++theSize;
	while(customer->getPriorityValue() < arr[slot/2]->getPriorityValue()){
		arr[slot] = arr[slot/2];
		slot /= 2;
	}
	arr[slot] = customer;
}


/*
 * getTheSize()
 */

int Heap::getTheSize(){
	return theSize;
}


/*
 * getMaxSize()
 */

int Heap::getMaxSize(){
	return maxSize;
}


/*
 * getNextArrivalTime()
 * used by Simulator object when reloading arrivals into priority queue
 * finds the starting point for generating new arrival times
 */

float Heap::getLastArrivalTime(){
	float lastArrivalTime = 0;

	for(int i=1; i<theSize+1; i++)		// assumption is that there will always be at least 1 arrival when this function is called
		if(arr[i]->isArrival())
			lastArrivalTime = arr[i]->getArrivalTime();
	
	if(lastArrivalTime)
		return lastArrivalTime;

	std::cout << "ERROR: no arrivals remaining. could not getNextArrivalTime()\n";
	return -1.0;	// did not find arrival;	this should never happen in simulation
}
