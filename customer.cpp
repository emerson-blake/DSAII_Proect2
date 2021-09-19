/*
 * customer.cpp
 */

Customer::Customer(){

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

void Customer::setNextCust(Customer* nextCust){
	this->nextCust = nextCust;
}

float Customer::getArrivalTime(){
	return arrivalTime;
}

float Customer::getStartOfServiceTime(){
	return startOfServiceTime;
}

float Customer::getDepartureTime(){
	return departureTime;
}

Customer* Customer::getNextCust(){
	return nextCust;
}
