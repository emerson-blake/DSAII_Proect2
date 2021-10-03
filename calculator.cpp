/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"calculator.cpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * Definitions of class Calculator's member functions
 */

#include <cmath>
#include <iostream>

#include "calculator.hpp"
#include "customer.hpp"

/*
 * Calculator()
 * Constructor:
 * sets seed from int parameter (default time(0))
 * initializes all data members to 0;
 */

Calculator::Calculator(int seed){
	srand(seed);

	idleStartTime	    = 0;
	customersWaitedCnt  = 0;
	totalIdleTime       = 0;
	totalWaitTime       = 0;
	totalServiceTime    = 0;
	totalSimulationTime = 0;
}


/*
 * calculateRandomInterval()
 * takes int parameter
 * returns random float interval, averages over time to reciprical of input
 */

float Calculator::calculateRandomInterval(int avg){
	float f = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);	// random float between 0 and 1
	float intervalTime = (-1) * (1.0/avg) * std::log(f);

	return intervalTime;
}


/*
 * processCustomerStats()
 * takes departing customer just before deletion
 * gets customer's waitTime and serviceTime, adds to accumulative total wait/service times
 * tracks how many customers waited
 */

void Calculator::processCustomerStats(Customer* customer){
	
	float currentWaitTime    = customer->getStartOfServiceTime() - customer->getArrivalTime();
	float currentServiceTime = customer->getDepartureTime() - customer->getStartOfServiceTime();
	
	if (currentWaitTime > 0)
		customersWaitedCnt++;

	totalWaitTime    += currentWaitTime;
	totalServiceTime += currentServiceTime;
}


/*
 * startIdle()
 * starts tracking idle time, triggered by all service windows becoming open
 */

void Calculator::startIdle(float eventTime){
	idleStartTime = eventTime;
}


/*
 * stopIdle()
 * stops tracking idle time, triggered by a service window becoming closed when all service windows were open
 */

void Calculator::stopIdle(float eventTime){
	totalIdleTime += eventTime - idleStartTime;
}


/*
 * setSimulationTime()
 * triggered once near the end of the simulation.
 * eventTime = the departure time of the last customer = end of simulation time
 * simulation start time = 0, so stop time - start time = stop time.
 * therefore, totalSimulationTime = stop time = eventTime.
 */

void Calculator::setSimulationTime(float eventTime){
	totalSimulationTime = eventTime;
}


/*
 * analytical_PercentIdleTime()
 * equation given in project description sheet
 * calculates analytically without simulation data
 */

float Calculator::analytical_PercentIdleTime(int lambda, int mu, int M){
	float Po;
	float denominator = 1;	// starting this at 1 covers the i=0 iteration

	int factorial = 1;
	int i;
	for (i=1; i<M; i++) {	// skips i=0 iteration, runs through i=M-1 iteration
		factorial *= i;	// always equals i!
		denominator += std::pow((static_cast<float>(lambda)/mu), i) / factorial; // (lambda/mu)^i / i!
	}
	// i=M iteration below
	denominator += std::pow((static_cast<float>(lambda)/mu), i) * (static_cast<float>(M*mu)/(M*mu-lambda)) / (factorial*i);	// (lambda/mu)^i * M*mu/(M*mu - lambda) / i!

	Po = 1.0 / denominator;
	return Po;
}


/*
 * analytical_AvgCustomerInSystem()
 * equation given in project description sheet
 * calculates analytically without simulation data
 */

float Calculator::analytical_AvgCustomersInSystem(int lambda, int mu, int M){
	float L;
	float numerator;
	float denom1 = 1;	// starting this at 1 covers factorial of 0 and 1, start for loop at 2
	float denom2;
	float Po = analytical_PercentIdleTime(lambda, mu, M);

	numerator = lambda * mu * std::pow( static_cast<float>(lambda)/mu , M ); // lambda*mu*(lambda/mu)^M
	
	for(int i=2; i<M; i++)	// denom1 = (M-1)! after loop
		denom1 *= i;

	denom2 = pow( M*mu - lambda , 2); // (M*mu - lambda)^2

	L = numerator / (denom1*denom2) * Po + (static_cast<float>(lambda) / mu); // Po*lambda*mu*(lambda/mu)^M / [(M-1)!*(M*mu-lambda)^2] + lambda/mu

	return L;
}


/*
 * analytical_AvgTimeSpentInSystem()
 * equation given in project description sheet
 * calculates analytically without simulation data
 */

float Calculator::analytical_AvgTimeSpentInSystem(int lambda, int mu, int M){
	return analytical_AvgCustomersInSystem(lambda, mu, M) / lambda; // L/lambda
}


/*
 * analytical_AvgCustomersWaiting()
 * equation given in project description sheet
 * calculates analytically without simulation data
 */

float Calculator::analytical_AvgCustomersWaiting(int lambda, int mu, int M){
	return analytical_AvgCustomersInSystem(lambda, mu, M) - (static_cast<float>(lambda)/mu);	// L - lambda/mu
}


/*
 * analytical_AvgTimeSpentWaiting()
 * equation given in project description sheet
 * calculates analytically without simulation data
 */

float Calculator::analytical_AvgTimeSpentWaiting(int lambda, int mu, int M){
	return analytical_AvgCustomersWaiting(lambda, mu, M) / lambda;			// (L - lambda/mu) / lambda
}


/*
 * analytical_UtilizationFactor()
 * equation given in project description sheet
 * calculates analytically without simulation data
 */

float Calculator::analytical_UtilizationFactor(int lambda, int mu, int M){
	return static_cast<float>(lambda) / (M*mu);					// lambda / (M*mu)
}


/*
 * simulated_PercentIdleTime()
 * calculates percent idle time demonstrated by simulation
 */

float Calculator::simulated_PercentIdleTime(){
	return totalIdleTime / totalSimulationTime;
}


/*
 * simulated_AvgTimeSpentInSystem()
 * calculates average time customers spent in system (from arrival to departure) demonstrated by simulation
 */

float Calculator::simulated_AvgTimeSpentInSystem(int N){
	return (totalWaitTime + totalServiceTime) / N;
}


/*
 * simulated_AvgTimeSpentWaiting()
 * calculates average time customers spent waiting for service (from arrival to startOfServiceTime) demonstrated by simulation
 */

float Calculator::simulated_AvgTimeSpentWaiting(int N){
	std::cout << "totalWaitTime: " << totalWaitTime << std::endl;
	return totalWaitTime / N;
}


/*
 * simulated_UtilizationFactor()
 * calculates how well service windows were utilized demonstrated by simulation
 */

float Calculator::simulated_UtilizationFactor(int M){
	return totalServiceTime / (M * totalSimulationTime);
}


/*
 * simulated_ProbabilityOfWaiting()
 * calculates chance any given customer will have to wait for service domonstrated by simulation
 */

float Calculator::simulated_ProbabilityOfWaiting(int N){
	return static_cast<float>(customersWaitedCnt) / N;
}


/*
 * showSimulationResults()
 * prints to console simulation parameters
 * calls all calculations
 * displays results to compare analytical and simulated methods
 */

void Calculator::showSimulationResults(int lambda, int mu, int M, int N){
	float analyticalResult, simulatedResult, percentError;

	std::cout.fill(' ');

	std::cout << std::endl;
	std::cout.width(30); std::cout << std::right << "Simulation Parameters  " << std::endl;

	std::cout.width(30); std::cout << std::right << "Avg arrivals / time unit:  ";
	std::cout.width(12); std::cout << std::left  << lambda << std::endl;
	
	std::cout.width(30); std::cout << std::right << "Avg served / time unit:  ";
	std::cout.width(12); std::cout << std::left  << mu << std::endl;

	std::cout.width(30); std::cout << std::right << "Service windows:  ";
	std::cout.width(12); std::cout << std::left  << M << std::endl;

	std::cout.width(30); std::cout << std::right << "Total customers:  ";
	std::cout.width(12); std::cout << std::left  << N << std::endl;

	std::cout << std::endl;
	std::cout.width(30); std::cout << std::right << "Simulation Results  ";
	std::cout.width(12); std::cout << std::left  << "Analytical"; 
	std::cout.width(12); std::cout << std::left  << "Simulated";
	std::cout.width(12); std::cout << std::left  << "Percent Error";
	std::cout << std::endl;

	
	analyticalResult = analytical_PercentIdleTime(lambda, mu, M);
	simulatedResult  = simulated_PercentIdleTime();
	percentError     = std::abs(analyticalResult - simulatedResult) / analyticalResult * 100;
	std::cout.width(30); std::cout << std::right << "Percent idle time:  "; 
       	std::cout.width(12); std::cout << std::left  << analyticalResult;
	std::cout.width(12); std::cout << std::left  << simulatedResult;
	std::cout.width(12); std::cout << std::left  << percentError;
	std::cout << std::endl;

	analyticalResult = analytical_AvgCustomersInSystem(lambda, mu, M);
	std::cout.width(30); std::cout << std::right << "Avg customers in system:  ";
	std::cout.width(12); std::cout << std::left  << analyticalResult;
	std::cout.width(12); std::cout << std::left  << "---";
	std::cout.width(12); std::cout << std::left  << "---";
	std::cout << std::endl;

	analyticalResult = analytical_AvgTimeSpentInSystem(lambda, mu, M);
	simulatedResult  = simulated_AvgTimeSpentInSystem(N);
	percentError     = std::abs(analyticalResult - simulatedResult) / analyticalResult * 100;
	std::cout.width(30); std::cout << std::right << "Avg time spent in system:  ";  
	std::cout.width(12); std::cout << std::left  << analyticalResult;
	std::cout.width(12); std::cout << std::left  << simulatedResult;
	std::cout.width(12); std::cout << std::left  << percentError;
	std::cout << std::endl;

	analyticalResult = analytical_AvgCustomersWaiting(lambda, mu, M);
	std::cout.width(30); std::cout << std::right << "Avg customers waiting:  ";  
	std::cout.width(12); std::cout << std::left  << analyticalResult;
	std::cout.width(12); std::cout << std::left  << "---";
	std::cout.width(12); std::cout << std::left  << "---";
	std::cout << std::endl;

	analyticalResult = analytical_AvgTimeSpentWaiting(lambda, mu, M);
	simulatedResult  = simulated_AvgTimeSpentWaiting(N);
	percentError     = std::abs(analyticalResult - simulatedResult) / analyticalResult * 100;
	std::cout.width(30); std::cout << std::right << "Avg time spent waiting:  ";  
	std::cout.width(12); std::cout << std::left  << analyticalResult;
	std::cout.width(12); std::cout << std::left  << simulatedResult;
	std::cout.width(12); std::cout << std::left  << percentError;
	std::cout << std::endl;

	analyticalResult = analytical_UtilizationFactor(lambda, mu, M);
	simulatedResult  = simulated_UtilizationFactor(M);
	percentError     = std::abs(analyticalResult - simulatedResult) / analyticalResult * 100;
	std::cout.width(30); std::cout << std::right << "Utilization factor:  ";  
	std::cout.width(12); std::cout << std::left  << analyticalResult;
	std::cout.width(12); std::cout << std::left  << simulatedResult;
	std::cout.width(12); std::cout << std::left  << percentError;
	std::cout << std::endl;

	simulatedResult  = simulated_ProbabilityOfWaiting(N);
	std::cout.width(30); std::cout << std::right << "Probablity of waiting:  ";  
	std::cout.width(12); std::cout << std::left  << "---";
	std::cout.width(12); std::cout << std::left  << simulatedResult;
	std::cout.width(12); std::cout << std::left  << "---";
	std::cout << std::endl;
	std::cout << std::endl;
}
