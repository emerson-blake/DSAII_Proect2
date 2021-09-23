/*
 * customer.cpp
 */

#include <algorithm>	// used for std::max() in Customer::getPriorityValue()

#include "customer.hpp"

Customer::Customer(){
	arrivalTime = 0;
	startOfServiceTime = -1;
	departureTime = -1;
	next = nullptr;
	previous = nullptr;
}

Customer::Customer(float arrivalTime){
	this->arrivalTime = arrivalTime;
	startOfServiceTime = -1;
	departureTime = -1;
	next = nullptr;
	previous = nullptr;
}

Customer::~Customer(){

}

void Customer::setArrivalTime(float arrivalTime){
	this->arrivalTime = arrivalTime;
}

void Customer::setStartOfServiceTime(float startOfServiceTime){
	this->startOfServiceTime = startOfServiceTime;
}

void Customer::setDepartureTime(float departureTime){
	this->departureTime = departureTime;
}

void Customer::setNext(Customer* next){
	this->next = next;
}

void Customer::setPrevious(Customer* previous){
	this->previous = previous;
}

float Customer::getPriorityValue(){
	return std::max(arrivalTime, departureTime);	// if arrival event, arrivalTime is max
}							// if departure event, departureTime is max

float Customer::getArrivalTime(){
	return arrivalTime;
}

float Customer::getStartOfServiceTime(){
	return startOfServiceTime;
}

float Customer::getDepartureTime(){
	return departureTime;
}

Customer* Customer::getNext(){
	return next;
}

Customer* Customer::getPrevious(){
	return previous;
}
