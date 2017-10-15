<<<<<<< .mine
/*
 * StatesContainer.h
 *
 *  Created on: 06.01.2010
 *      Author: sulewski
 */


#ifndef STATESCONTAINER_H_
#define STATESCONTAINER_H_

#include "stdint.h" /* Replace with <stdint.h> if appropriate */
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
	  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
		                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif


#include "myModel.h"

#include "defines.h"

class StatesContainer {

private:
	unsigned char bits[8];
	unsigned long long largeprime;
	vector<char *> container;
	vector<list<unsigned char*> *> hashtable;
	vector<char> boolHashtable;
	myModel * model;
	vector<vector<unsigned long long>* > randoms;
	unsigned int max_collisions;
public:
	unsigned long long insertCounter;
	StatesContainer(myModel * model);
	virtual ~StatesContainer();

	unsigned long long getHash(unsigned char * state,unsigned long long * randomVec);

	bool insert(unsigned char * state);

	bool insertChain(unsigned char * state, unsigned long long * hash);

	bool insertBool(unsigned char * state, unsigned long long * hash);

	bool clear();


};

#endif /* STATESCONTAINER_H_ */
=======
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
	virtual unsigned char * insert(unsigned int bfslayer, myState * state,bool insert) = 0;
	virtual bool clear() = 0;
	virtual void printAll() = 0;
};

#endif /* STATESCONTAINER_H_ */
>>>>>>> .r254
