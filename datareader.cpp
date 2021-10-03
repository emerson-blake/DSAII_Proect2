/*
 * datareader.cpp
 */

#include <iostream>
#include <string>

#include "datareader.hpp"

DataReader::DataReader(){

}

bool DataReader::openFile(const char* fileName){
	inFS.open(fileName);
	if (!inFS.is_open()) {
		std::cout << "ERROR: could not open \"" << fileName << "\"." << std::endl;
		return 0;
	}
	return 1;
}

void DataReader::closeFile(){
	if(inFS.is_open())
		inFS.close();
}

void DataReader::readParameters(int* lambda, int* mu, int* M, int* N){
	int* pointers[] = {lambda, mu, M, N};
	int maxLineLength = 8;
	char line[maxLineLength];

	for (int i=0; i<4; i++){
		inFS.getline(line, maxLineLength, '\n');
		*pointers[i] = std::stoi(line);
	}
}
