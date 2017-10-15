/*
 * openList.h
 *
 * Created on: 18.08.2010
 * 	Author: damian
 */

#ifndef OPENLISTHASHBASED_H_
#define OPENLISTHASHBASED_H_


//#include "GPUCheck.h"
#include <map>
#include "myModel.h"
#include "string"
#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <list>


template <class T>
class openListHashbased {
	private:
		unsigned int elementLength; //length of inserted elements in bytes
		map<unsigned int,map<unsigned int, unsigned int>* > openLists; // 2 dimensional array of lists (depth, costs)

    pthread_mutex_t serialize_mutexes;
		map<unsigned int,pthread_mutex_t * > serialize_open_map;

	public:

		unsigned int elements; //move to private later
		openListHashbased(unsigned int elementLength_);

		bool insert(unsigned int layer, unsigned int cost, T state, unsigned int elementCount = 1); //insert a state into the open list
		unsigned int get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize);  //get maximal bufferSize elements from open list and copy it to dst

		unsigned int getNextCosts(unsigned int layer,unsigned int current_costs);
		bool clear(); // remove all elements
		bool close();

};

#include "openListHashbased.cc"

#endif //OPENLISTINTERN_H_
