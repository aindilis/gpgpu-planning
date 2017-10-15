/*
 * StatesContainer.h
 *
 *  Created on: 06.01.2010
 *      Author: sulewski
 */

#ifndef STATESCONTAINER_H_
#define STATESCONTAINER_H_

#include "defines.h"

#ifdef BOOLHASH
#include "bloomHash.h"
typedef bloomHash<unsigned char *> hashing;
#endif

class myState;

class StatesContainer {
private:
public:
	virtual unsigned int get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize) = 0 ;  //get maximal bufferSize elements from open list and copy it to dst
	virtual	unsigned int getNextCosts(unsigned int layer,unsigned int current_costs) = 0;
	virtual bool insert(unsigned int bfslayer, myState * state) = 0;
	virtual bool clear() = 0;
	virtual void printAll() = 0;
};

#endif /* STATESCONTAINER_H_ */
