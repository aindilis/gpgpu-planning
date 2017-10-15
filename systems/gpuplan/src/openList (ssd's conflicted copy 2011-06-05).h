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

#ifndef OPENLIST_H_
#define OPENLIST_H_

template <class T>
class openList{
	private:
		unsigned int elementLength; //length of inserted elements in bytes
		map<unsigned int,map<unsigned int, fstream *>* > openLists; // 2 dimensional array of lists (depth, costs)
		map<unsigned int,map<unsigned int, unsigned long long > > added; //number of elements added to list
		map<unsigned int,map<unsigned int, unsigned long long > > removed; //number of elements removed from list
		string  getOpenFileNamePrivate(unsigned int id1, unsigned int id2);



		ofstream * outputFile;
		unsigned int id;
	public:
		unsigned int elements; //move to private later
		openList(unsigned int elementLength_);
		string  getOpenFileName(unsigned int id1, unsigned int id2); //to be removed

		bool insert(unsigned int layer, unsigned int cost, T state, unsigned int elementCount = 1); //insert a state into the open list
		unsigned int get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize);  //get maximal bufferSize elements from open list and copy it to dst

		unsigned int getNextCosts(unsigned int layer,unsigned int current_costs);
		bool clear(); // remove all elements
		bool close();

};

#include "openList.cc"

#endif //OPENLIST_H_
