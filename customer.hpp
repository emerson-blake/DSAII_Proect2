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
	Customer(float arrivalTime);
	~Customer();
	void  setArrivalTime(float arrivalTime);
	void  setStartOfServiceTime(float startOfServiceTime);
	void  setDepartureTime(float departureTime);
	void  setNext(Customer* next);
	void  setPrevious(Customer* previous);
	bool  isArrival();
	float getPriorityValue();		// used in priority queue
	float getArrivalTime();
	float getStartOfServiceTime();
	float getDepartureTime();
	Customer* getNext();		// used in FIFO queue
	Customer* getPrevious();
private:
	float arrivalTime;
	float startOfServiceTime;
	float departureTime;
	Customer* next;			// used in FIFO queue
	Customer* previous;		// used in FIFO queue
};

#endif
