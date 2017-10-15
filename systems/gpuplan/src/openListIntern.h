/*
 * openList.h
 *
 * Created on: 18.08.2010
 * 	Author: damian
 */

#ifndef OPENLIST_H_
#define OPENLIST_H_

#define READBUFFERSIZE 1048576000

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
class openListIntern {
	private:
		unsigned int elementLength; //length of inserted elements in bytes
		map<unsigned int,map<unsigned int, unsigned int> * > openElements; // 2 dimensional array containing number of elements in each list
		map<unsigned int,map<unsigned int, vector<T> *>* > openLists; // 2 dimensional array of lists (depth, costs) // for internal usage
		map<unsigned int,map<unsigned int, fstream * > * > openFiles; //open lists for external usage
		map<unsigned int,map<unsigned int, fstream * > * > openFilesRead; //open lists for external usage
		map<unsigned int,map<unsigned int, filebuf * > * > openBuffers;

    pthread_mutex_t serialize_mutexes;
		map<unsigned int,pthread_mutex_t * > serialize_open_map;

	public:

		unsigned int elements; //move to private later
		openListIntern(unsigned int elementLength_);

		bool insert(unsigned int layer, unsigned int cost, T state, unsigned int elementCount = 1); //insert a state into the open list
		unsigned int get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize);  //get maximal bufferSize elements from open list and copy it to dst

		unsigned int getNextCosts(unsigned int layer,unsigned int current_costs);
		bool clear(); // remove all elements
		bool close();

};

#include "openListIntern.cc"

#endif //OPENLIST_H_
