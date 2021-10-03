/*
 * datareader.hpp
 *
 */

#ifndef DATA_READER_HPP
#define DATA_READER_HPP

#include <fstream>

class DataReader{
public:
	DataReader();
	bool openFile(const char* fileName);	// return false if file fails to open; true if successful
	void closeFile();
	void readParameters(int* lambda, int* mu, int* M, int* N);
private:
	std::ifstream inFS;
};

#endif
