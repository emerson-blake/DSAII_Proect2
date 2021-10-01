/*
 * main.cpp
 */

#include <iostream>
#include <stdio.h>
#include <time.h>

#include "simulator.hpp"
#include "director.hpp"
#include "scheduler.hpp"
#include "statistician.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "customer.hpp"

int main(){

	int lambda = 2;
	int mu = 3;
	int M = 2;
	int N = 5000;

	Director director(lambda, mu, M, N);
	director.processEvents();

	return 0;
}


