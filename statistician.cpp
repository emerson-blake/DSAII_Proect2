/*
 * statistician.cpp
 */

#include <cmath>
#include <iostream>

#include "statistician.hpp"
#include "customer.hpp"


void Statistician::processCustomerStats(Customer* customer){
	float currentWaitTime = customer->getStartOfServiceTime() - customer->getArrivalTime();
	float currentServiceTime = customer->getDepartureTime() - customer->getStartOfServiceTime();
	if (currentWaitTime > 0)
		customersWaitedCnt++;
	totalWaitTime += currentWaitTime;
	totalServiceTime += currentServiceTime;
}

void Statistician::startIdle(float eventTime){
	idleStartTime = eventTime;
}

void Statistician::stopIdle(float eventTime){
	totalIdleTime += eventTime - idleStartTime;
}

float Statistician::calculatePercentIdleTime(int lambda, int mu, int M){
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

float Statistician::calculateAvgCustomersInSystem(int lambda, int mu, int M){
	float L;
	float numerator;
	float denom1 = 1;	// starting this at 1 covers factorial of 0 or 1, start for loop at 2
	float denom2;
	float Po = calculatePercentIdleTime(lambda, mu, M);

	numerator = lambda * mu * std::pow( static_cast<float>(lambda)/mu , M );
	
	for(int i=2; i<M; i++)
		denom1 *= i;

	denom2 = pow( M*mu - lambda , 2);

	L = numerator / (denom1*denom2) * Po + (static_cast<float>(lambda) / mu);

	return L;
}

float Statistician::calculateAvgTimeSpentInSystem(int lambda, int mu, int M){
	return calculateAvgCustomersInSystem(lambda, mu, M) / lambda;
}

float Statistician::calculateAvgCustomersWaiting(int lambda, int mu, int M){
	return calculateAvgCustomersInSystem(lambda, mu, M) - (static_cast<float>(lambda)/mu);
}

float Statistician::calculateAvgTimeSpentWaiting(int lambda, int mu, int M){
	return calculateAvgCustomersWaiting(lambda, mu, M) / lambda;
}

float Statistician::calculateUtilizationFactor(int lambda, int mu, int M){
	return static_cast<float>(lambda) / (M*mu);
}

float Statistician::calculateWaitProbability(int N){
	return static_cast<float>(customersWaitedCnt) / N;
}

void Statistician::showSimulationResults(int lambda, int mu, int M, int N){
	std::cout << "Simulation Parameters\n";
	std::cout << "Average Arrivals per time unit (lambda): " << lambda << std::endl;
	std::cout << "Average Served per time unit (mu): " << mu << std::endl;
	std::cout << "Total service windows (M): " << M << std::endl;
	std::cout << "Total Arrivals (N): " << N << std::endl;
	std::cout << std::endl;

	std::cout << "Simulation Results\n";
	std::cout << "Percent idle time: " << calculatePercentIdleTime(lambda, mu, M) << std::endl;
	std::cout << "Average time customer spends in the system: " << calculateAvgTimeSpentInSystem(lambda, mu, M) << std::endl;
	std::cout << "Average time customer spends waiting: " << calculateAvgTimeSpentWaiting(lambda, mu, M) << std::endl;
	std::cout << "Utilization factor: " << calculateUtilizationFactor(lambda, mu, M) << std::endl;
	std::cout << "Probability of having to wait for service: " << calculateWaitProbability(N) << std::endl;
	std::cout << std::endl;
};
