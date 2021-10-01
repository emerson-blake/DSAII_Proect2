/*
 * statistician.hpp
 */

#ifndef STATISTICIAN_HPP
#define STATISTICIAN_HPP

#include "customer.hpp"

class Statistician{
public:
	void processCustomerStats(Customer* customer);
	void startIdle(float eventTime);
	void stopIdle(float eventTime);

	float calculatePercentIdleTime(int lambda, int mu, int M);	// Analytical & Simulated
	float calculateAvgCustomersInSystem(int lambda, int mu, int M);	// Analytical
	float calculateAvgTimeSpentInSystem(int lambda, int mu, int M);	// Analytical & Simulated
	float calculateAvgCustomersWaiting(int lambda, int mu, int M);	// Analytical
	float calculateAvgTimeSpentWaiting(int lambda, int mu, int M);	// Analytical & Simulated
	float calculateUtilizationFactor(int lambda, int mu, int M);	// Analytical & Simulated
	float calculateWaitProbability(int N);				// Simulated

	void showSimulationResults(int lambda, int mu, int M, int N);
private:
	int customersWaitedCnt;
	float totalWaitTime;
	float totalServiceTime;
	float totalIdleTime;
	float idleStartTime;
};

#endif
