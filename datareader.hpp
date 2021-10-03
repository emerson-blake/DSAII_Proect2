/************************************************
 * Student Name:	Blake Emerson
 * File Name:		"datareader.hpp"
 * Assignment Number:	Project 2: Customer/Service Simulator - Due 10/07/2021
 * 
 * Definition of class DataReader
 * DataReader class object handles file stream and reads parameters from textfile
 *
*/


#ifndef DATA_READER_HPP
#define DATA_READER_HPP

#include <fstream>

class DataReader{
public:
	bool openFile(const char* fileName);	// return false if file fails to open; true if successful
	void closeFile();
	void readParameters(int* lambda, int* mu, int* M, int* N);
private:
	std::ifstream inFS;
};

#endif
