/*
 * scheduler.cpp
 */

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cmath>

#include "scheduler.hpp"

Scheduler::Scheduler(int seed){
	srand(seed);
}

float Scheduler::getNextRandomInterval(int avg){
	float f = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float intervalTime = (-1) * (1.0/avg) * log(f);

	std::cout << "f: " << f << std::endl;
	std::cout << "intervalTime: " << intervalTime << std::endl;

	return intervalTime;
}
