/*
 * openList.h
 *
 * Created on: 18.08.2010
 * 	Author: damian
 */

#include "GPUCheck.h"
#include "myModel.h"
#include "string"
#include <iostream>
#include <fstream>
#include <sstream>

class openList{
	private:
		string  getOpenFileName(unsigned int num);
		unsigned int elements;
		ofstream * outputFile;
		unsigned int id;
	public:
		openList(unsigned int id);

		bool insert(myState *state);

		vector<unsigned long long> opencount; //counter for elements in open lists

		bool clear(); // remove all elements
		bool close();

};
