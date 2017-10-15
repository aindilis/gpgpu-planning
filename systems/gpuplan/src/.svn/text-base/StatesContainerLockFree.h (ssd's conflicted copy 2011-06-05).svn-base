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
#include "openListExtern.h"
#include "openListIntern.h"
#include "openListHashbased.h"
#include "StatesContainer.h"
#include "defines.h"


//typedef openListHashbased<unsigned char *> openList;
typedef openListIntern<unsigned char *> openList;


class StatesContainerLockFree : public StatesContainer  {
private:
	myModel * model;
public:
	openList * open;
	StatesContainerLockFree();
	StatesContainerLockFree(myModel * model);
	~StatesContainerLockFree();

	unsigned int get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize) ;  //get maximal bufferSize elements from open list and copy it to dst
	unsigned int getNextCosts(unsigned int layer,unsigned int current_costs);
	bool insert(unsigned int bfslayer, myState * state);
	unsigned char * getByPos(unsigned int pos,int * dst);
	bool clear();
	void printAll();
};

#endif /* STATESCONTAINERLOCKFREE_H_ */
