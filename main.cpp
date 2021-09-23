/*
 * main.cpp
 */

#include <iostream>

#include "simulator.hpp"
#include "director.hpp"
#include "scheduler.hpp"
#include "statistician.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "customer.hpp"

int main(){
	std::cout << "Hello World!\n";
	Queue queue;
	Customer cust1;
	Customer cust2;

	cust1.setArrivalTime(0.2);
	cust2.setArrivalTime(0.5);

	queue.enqueue(&cust1);
	queue.enqueue(&cust2);

	Customer* cust3;
	Customer* cust4;

	cust3 = queue.serve();
	cust4 = queue.serve();

	std::cout << "cust1: " << cust1.getArrivalTime() << std::endl;
	std::cout << "cust2: " << cust2.getArrivalTime() << std::endl;
	std::cout << "cust3: " << cust3->getArrivalTime() << std::endl;
	std::cout << "cust4: " << cust4->getArrivalTime() << std::endl;

	return 0;
}


