/*
 * statistician.cpp
 */

#include <cmath>

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

float Statistician::calculatePercentIdleTime(int lamda, int mu, int M){
	float Po;
	float denom1 = 1;	// starting this at 1 covers the i=0 iteration
	float denom2;


	int factorial = 1;
	int i;
	for (i=1; i<M; i++) {
		factorial *= i;
		denom1 += (1.0/factorial) * std::pow((static_cast<float>(lamda)/mu), i);
	}
	denom2 = 1.0/(factorial*i) * std::pow((static_cast<float>(lamda)/mu), i) * (static_cast<float>(M*mu)/(M*mu-lamda));

	Po = 1.0 / (denom1 + denom2);
	return Po;
}

float Statistician::calculateAvgCustomersInSystem(int lamda, int mu, int M){
	float L;
	float numerator;
	float denom1 = 1;	// starting this at 1 covers factorial of 0 or 1, start for loop at 2
	float denom2;
	float Po = calculatePercentIdleTime(lamda, mu, M);

	numerator = lamda * mu * std::pow( static_cast<float>(lamda)/mu , M );
	
	for(int i=2; i<M; i++)
		denom1 *= i;

	denom2 = pow( M*mu - lamda , 2);

	L = numerator / (denom1*denom2) * Po + (static_cast<float>(lamda) / mu);

	return L;
}

float Statistician::calculateAvgTimeSpentInSystem(int lamda, int mu, int M){
	return calculateAvgCustomersInSystem(lamda, mu, M) / lamda;
}

float Statistician::calculateAvgCustomersWaiting(int lamda, int mu, int M){
	return calculateAvgCustomersInSystem(lamda, mu, M) - (static_cast<float>(lamda)/mu);
}

float Statistician::calculateAvgTimeSpentWaiting(int lamda, int mu, int M){
	return calculateAvgCustomersWaiting(lamda, mu, M) / lamda;
}

float Statistician::calculateUtilizationFactor(int lamda, int mu, int M){
	return lamda / (M*mu);
}

void Statistician::showSimulationResults(){
	//TODO:
};
