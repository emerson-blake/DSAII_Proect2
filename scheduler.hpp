/*
 * scheduler.hpp
 *
 *
 */

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <time.h>

class Scheduler{
public:
	Scheduler(int seed = time(0));
	float getNextRandomInterval(int avg);
private:
};

#endif
