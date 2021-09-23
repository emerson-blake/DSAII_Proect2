/*
 * heap.cpp
 */

#include "heap.hpp"
#include "customer.hpp"

Heap::Heap(){
	theSize = 0;
	for(int i=1; i<MAXSIZE+1; i++)
		arr[i] = nullptr;
}

Heap::~Heap(){
	for(int i=1; i<theSize+1; i++)
		delete arr[i];
}

bool Heap::isEmpty(){
	return !theSize;	// if theSize == 0, returns true; if theSize > 0, returns false
}

Customer* Heap::findMin(){ // PowerPoint slide declared this but didn't define it.

}

Customer* Heap::deleteMin(){			// modified from PowerPoint slide.
	Customer* tmp = arr[1];
	arr[1] = arr[theSize--];
	percolateDown(1);
	return tmp;
}

void Heap::makeEmpty(){	// PowerPoint slide declared this but didn't define it.

}

void Heap::constructHeap(Customer** v, int vSize){	// modified from PowerPoint slide.
	for(int i=0; i<vSize; i++)
		arr[i+1] = v[i];
	buildHeap();
}

void Heap::buildHeap(){				// copied from PowerPoint slide.
	for(int i=theSize/2; i>0; i--)
		percolateDown(i);
}

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

void Heap::percolateUp(Customer* customer){	// modified from PowerPoint slide.
	arr[0] = customer;
	int slot = ++theSize;
	while(customer->getPriorityValue() < arr[slot/2]->getPriorityValue()){
		arr[slot] = arr[slot/2];
		slot /= 2;
	}
	arr[slot] = customer;
}
