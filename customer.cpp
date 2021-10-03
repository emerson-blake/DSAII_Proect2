/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"customer.cpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 *
 * Definitions of class Customer's member functions
 *
 */

#include <algorithm>	// used for std::max() in Customer::getPriorityValue()

#include "customer.hpp"

/*
 * Customer()
 * Constructor: default parameter = 0.0
 * arrivalTime set to input parameter
 * initializes other float data members to 0.0, 
 * initializes pointer data members to nullptr
 */

Customer::Customer(float arrivalTime){
	this->arrivalTime = arrivalTime;
	startOfServiceTime = 0.0;
	departureTime = 0.0;
	next = nullptr;
	previous = nullptr;
}


/*
 * setArrivalTime()
 * used by Simulator class object
 */

void Customer::setArrivalTime(float arrivalTime){
	this->arrivalTime = arrivalTime;
}


/*
 * setStartOfServiceTime()
 * used by Simulator class object
 */

void Customer::setStartOfServiceTime(float startOfServiceTime){
	this->startOfServiceTime = startOfServiceTime;
}


/*
 * setDepartureTime()
 * used by Simulator class object
 */

void Customer::setDepartureTime(float departureTime){
	this->departureTime = departureTime;
}


/*
 * setNext()
 * used by Queue class object
 */

void Customer::setNext(Customer* next){
	this->next = next;
}


/*
 * setPrevious()
 * used by Queue class object
 */

void Customer::setPrevious(Customer* previous){
	this->previous = previous;
}


/*
 * isArrival()
 * used by Simulator class object
 * 
 * Customers can be viewed as arrival events or departure events
 * if departure time has not been set, it is an arrival event
 * its default value of 0.0 when viewed as a bool is false
 * !departureTime returns true when departureTime has not been set
 */

bool Customer::isArrival(){
	return !departureTime;
}


/*
 * getPriorityValue()
 * used by Heap class object
 *
 * Customers are sometimes nodes in a priority queue (Heap) object
 * They are sorted by a priority value
 * The value is arrivalTime if customer is an arrival
 * the value is departureTime if customer is not an arrival
 */

float Customer::getPriorityValue(){
	return std::max(arrivalTime, departureTime);	// if arrival event, arrivalTime is max
}							// if departure event, departureTime is max


/*
 * getArrivalTime()
 */

float Customer::getArrivalTime(){
	return arrivalTime;
}


/*
 * getStartOfServiceTime()
 */

float Customer::getStartOfServiceTime(){
	return startOfServiceTime;
}


/*
 * getDepartureTime()
 */

float Customer::getDepartureTime(){
	return departureTime;
}


/*
 * getNext()
 */

Customer* Customer::getNext(){
	return next;
}


/*
 * getPrevious()
 */

Customer* Customer::getPrevious(){
	return previous;
}
