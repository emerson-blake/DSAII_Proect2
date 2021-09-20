/*
 * event.cpp
 */

#include "event.hpp"

Event::Event(){

}

Event::~Event(){

}

void Event::setType(bool type){
	eventType = type;
}

void Event::setTime(float time){
	eventTime = time;
}

bool Event::isArrival(){
	return eventType;
}

float Event::getTime(){
	return eventTime;
}

