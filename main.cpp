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

	int lamda = 2;
	int mu = 3;
	int M = 2;

	Statistician statistician;

	std::cout << "Test 1\n";

	std::cout << statistician.calculatePercentIdleTime(lamda, mu, M)      << std::endl;		// Analytical & Simulated
	std::cout << statistician.calculateAvgCustomersInSystem(lamda, mu, M) << std::endl;	// Analytical
	std::cout << statistician.calculateAvgTimeSpentInSystem(lamda, mu, M) << std::endl;
	std::cout << statistician.calculateAvgCustomersWaiting(lamda, mu, M)  << std::endl;	// Analytical
	std::cout << statistician.calculateAvgTimeSpentWaiting(lamda, mu, M)  << std::endl;	// Analytical & Simulated
	std::cout << statistician.calculateUtilizationFactor(lamda, mu, M)    << std::endl;		// Analytical & Simulated

	lamda = 5;
	mu = 6;
	M = 4;

	std::cout << "\nTest 2\n";

	std::cout << statistician.calculatePercentIdleTime(lamda, mu, M)      << std::endl;		// Analytical & Simulated
	std::cout << statistician.calculateAvgCustomersInSystem(lamda, mu, M) << std::endl;	// Analytical
	std::cout << statistician.calculateAvgTimeSpentInSystem(lamda, mu, M) << std::endl;
	std::cout << statistician.calculateAvgCustomersWaiting(lamda, mu, M)  << std::endl;	// Analytical
	std::cout << statistician.calculateAvgTimeSpentWaiting(lamda, mu, M)  << std::endl;	// Analytical & Simulated
	std::cout << statistician.calculateUtilizationFactor(lamda, mu, M)    << std::endl;		// Analytical & Simulated

	return 0;
}


