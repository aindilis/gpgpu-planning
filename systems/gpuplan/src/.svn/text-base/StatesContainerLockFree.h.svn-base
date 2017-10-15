/*
 * StatesContainer.h
 *
 *  Created on: 06.01.2010
 *      Author: sulewski
 */


#ifndef STATESCONTAINERLOCKFREE_H_
#define STATESCONTAINERLOCKFREE_H_

#include "myModel.h"
#include "myState.h"
#include "openList.h"
#include "StatesContainer.h"
#include "defines.h"

typedef openList<unsigned char *> openListChar;

class StatesContainerLockFree : public StatesContainer  {
private:
	myModel * model;
public:
	openListChar * open;
	StatesContainerLockFree();
	StatesContainerLockFree(myModel * model);
	~StatesContainerLockFree();

	unsigned int get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize) ;  //get maximal bufferSize elements from open list and copy it to dst
	unsigned int getNextCosts(unsigned int layer,unsigned int current_costs);
	unsigned char * insert(unsigned int bfslayer, myState * state,bool insert);
	unsigned char * getByPos(unsigned int pos,int * dst);
	bool clear();
	void printAll();
};

#endif /* STATESCONTAINERLOCKFREE_H_ */
