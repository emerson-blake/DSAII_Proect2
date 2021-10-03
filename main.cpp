/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"main.cpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * This file "main.cpp", holds the main() function for the program.
 * Creates a Simulator class objects initialized by parameters within textfiles
 * Runs simulation on each test case and prints results to console
*/

#include "simulator.hpp"

int main(){

	const char* files[] = {"text1.txt", "text2.txt"};	// add text files here to add test cases

	for(auto file : files){					// iterates through each test case described in files array
		Simulator simulator(file);			// creates the simulation object with parameters from file
		simulator.run();				// runs simulation, shows results
	}

	return 0;
}


