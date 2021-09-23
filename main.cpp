/*
 * main.cpp
 */

#include <iostream>
#include <stdio.h>
#include <time.h>

#include "simulator.hpp"
#include "director.hpp"
#include "scheduler.hpp"
#include "statistician.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "customer.hpp"

int main(){

	srand(time(0));

	Heap heap;
		
	Customer* customers[10];
	for(int i=0; i<10; i++){
		customers[i] = new Customer(rand());
		heap.percolateUp(customers[i]);
	}

	for(int i=0; i<10; i++){
		std::cout << heap.deleteMin()->getPriorityValue() << std::endl;
	}

	for(int i=0; i<10; i++){
		delete customers[i];
	}

	return 0;
}


