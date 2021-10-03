/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"datareader.cpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * Definitions of class DataReader's member functions
 * 
*/


#include <iostream>
#include <string>

#include "datareader.hpp"


/*
 * openFile()
 * takes string input, opens file of that name
 * prints error if can't open
 */

bool DataReader::openFile(const char* fileName){
	inFS.open(fileName);
	if (!inFS.is_open()) {
		std::cout << "ERROR: could not open \"" << fileName << "\"." << std::endl;
		return 0;
	}
	return 1;
}


/*
 * closeFile()
 * if filestream has open file, closes it
 */

void DataReader::closeFile(){
	if(inFS.is_open())
		inFS.close();
}


/*
 * readParameters()
 * reads each line from file, stores data into parameter addresses
 */

void DataReader::readParameters(int* lambda, int* mu, int* M, int* N){
	int* pointers[] = {lambda, mu, M, N};
	int maxLineLength = 8;
	char line[maxLineLength];

	for (int i=0; i<4; i++){
		inFS.getline(line, maxLineLength, '\n');
		*pointers[i] = std::stoi(line);
	}
}
