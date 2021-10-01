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

	float calculatePercentIdleTime(int lamda, int mu, int M);	// Analytical & Simulated
	float calculateAvgCustomersInSystem(int lamda, int mu, int M);	// Analytical
	float calculateAvgTimeSpentInSystem(int lamda, int mu, int M);	// Analytical & Simulated
	float calculateAvgCustomersWaiting(int lamda, int mu, int M);	// Analytical
	float calculateAvgTimeSpentWaiting(int lamda, int mu, int M);	// Analytical & Simulated
	float calculateUtilizationFactor(int lamda, int mu, int M);	// Analytical & Simulated

	void showSimulationResults();
private:
	int customersWaitedCnt;
	float totalWaitTime;
	float totalServiceTime;
	float totalIdleTime;
	float idleStartTime;
};

#endif
