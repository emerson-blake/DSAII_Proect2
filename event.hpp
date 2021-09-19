/*
 * event.hpp
 *
 *
 */

#define EVENT_HPP
#ifndef EVENT_HPP

class Event{
public:
	Event()
	~Event()
	void  setType(bool type);
	void  setTime(float time);
	bool  isArrival();
	float getTime();
private:
	bool  eventType;	// 0 == departure, 1 == arrival
	float eventTime;
};

#endif
