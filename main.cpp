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

	Scheduler scheduler;
	float avg = 5;
	float total = 0;
	int trials = 5000;

	for (int i=0; i<trials; i++)
		total += scheduler.getNextRandomInterval(avg);
	
	avg = total / trials;

	std::cout << avg << std::endl;

	return 0;
}


