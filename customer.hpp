/*
 * customer.hpp
 *
 *
 */

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

class Customer{
public:
	Customer();
	~Customer();
	void  setArrivalTime(float arrivalTime);
	void  setStartOfServiceTime(float startOfServiceTime);
	void  setDepartureTime(float departureTime);
	void  setNextCust(Customer* nextCust);
	float getArrivalTime();
	float getStartOfServiceTime();
	float getDepartureTime();
	Customer* getNextCust();
private:
	float arrivalTime;
	float startOfServiceTime;
	float departureTime;
	Customer* nextCust;
};

#endif
