/*
 * statistician.cpp
 */

#include <cmath>
#include <iostream>

#include "calculator.hpp"
#include "customer.hpp"

Calculator::Calculator(int seed){
	srand(seed);

	idleStartTime	    = 0;
	customersWaitedCnt  = 0;
	totalIdleTime       = 0;
	totalWaitTime       = 0;
	totalServiceTime    = 0;
	totalSimulationTime = 0;
}

float Calculator::calculateRandomInterval(int avg){
	float f = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float intervalTime = (-1) * (1.0/avg) * log(f);

	return intervalTime;
}

void Calculator::processCustomerStats(Customer* customer){
	
	float currentWaitTime    = customer->getStartOfServiceTime() - customer->getArrivalTime();
	float currentServiceTime = customer->getDepartureTime() - customer->getStartOfServiceTime();
	
	if (currentWaitTime > 0)
		customersWaitedCnt++;

	totalWaitTime    += currentWaitTime;
	totalServiceTime += currentServiceTime;
}

void Calculator::startIdle(float eventTime){
	idleStartTime = eventTime;
}

void Calculator::stopIdle(float eventTime){
	totalIdleTime += eventTime - idleStartTime;
}

void Calculator::setSimulationTime(float eventTime){
	totalSimulationTime = eventTime;
}

float Calculator::analytical_PercentIdleTime(int lambda, int mu, int M){
	float Po;
	float denom1 = 1;	// starting this at 1 covers the i=0 iteration
	float denom2;


	int factorial = 1;
	int i;
	for (i=1; i<M; i++) {
		factorial *= i;
		denom1 += (1.0/factorial) * std::pow((static_cast<float>(lambda)/mu), i);
	}
	denom2 = 1.0/(factorial*i) * std::pow((static_cast<float>(lambda)/mu), i) * (static_cast<float>(M*mu)/(M*mu-lambda));

	Po = 1.0 / (denom1 + denom2);
	return Po;
}

float Calculator::analytical_AvgCustomersInSystem(int lambda, int mu, int M){
	float L;
	float numerator;
	float denom1 = 1;	// starting this at 1 covers factorial of 0 or 1, start for loop at 2
	float denom2;
	float Po = analytical_PercentIdleTime(lambda, mu, M);

	numerator = lambda * mu * std::pow( static_cast<float>(lambda)/mu , M );
	
	for(int i=2; i<M; i++)
		denom1 *= i;

	denom2 = pow( M*mu - lambda , 2);

	L = numerator / (denom1*denom2) * Po + (static_cast<float>(lambda) / mu);

	return L;
}

float Calculator::analytical_AvgTimeSpentInSystem(int lambda, int mu, int M){
	return analytical_AvgCustomersInSystem(lambda, mu, M) / lambda;
}

float Calculator::analytical_AvgCustomersWaiting(int lambda, int mu, int M){
	return analytical_AvgCustomersInSystem(lambda, mu, M) - (static_cast<float>(lambda)/mu);
}

float Calculator::analytical_AvgTimeSpentWaiting(int lambda, int mu, int M){
	return analytical_AvgCustomersWaiting(lambda, mu, M) / lambda;
}

float Calculator::analytical_UtilizationFactor(int lambda, int mu, int M){
	return static_cast<float>(lambda) / (M*mu);
}

float Calculator::simulated_PercentIdleTime(){
	return totalIdleTime / totalSimulationTime;
}

float Calculator::simulated_AvgTimeSpentInSystem(int N){
	return (totalWaitTime + totalServiceTime) / N;
}

float Calculator::simulated_AvgTimeSpentWaiting(int N){
	return totalWaitTime / N;
}

float Calculator::simulated_UtilizationFactor(int M){
	return totalServiceTime / (M * totalSimulationTime);
}


float Calculator::simulated_ProbabilityOfWaiting(int N){
	return static_cast<float>(customersWaitedCnt) / N;
}

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
