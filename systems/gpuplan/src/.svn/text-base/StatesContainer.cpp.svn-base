/*
 * StatesContainer.cpp
 *
 *  Created on: 06.01.2010
 *      Author: sulewski
 */


#include "StatesContainer.h"
#include <ctime>
#include <math.h>

extern "C" {
	typedef struct dbs_ll_s *dbs_ll_t;
	extern dbs_ll_t     DBSLLcreate (int len);
	extern int          DBSLLlookup_ret (const dbs_ll_t dbs, const int *v, int *ret);
	extern int * 				DBSLLget(const dbs_ll_t dbs, const int idx, int *dst);
}


typedef void *DBS_T;
typedef DBS_T(*dbs_create_f)(int v, int s);
static dbs_create_f create = (dbs_create_f)DBSLLcreate;

typedef int(*dbs_lookup_f)(const DBS_T dbs, const int *v);
typedef int(*dbs_lookup_ret_f)(const DBS_T dbs, const int *v, int *ret);
static dbs_lookup_ret_f lookup_ret = (dbs_lookup_ret_f)DBSLLlookup_ret;

DBS_T dbs;


StatesContainer::StatesContainer(myModel * newModel) {
	model = newModel;
	srand(time(0));
	for (int b = 0; b < NUMOFBITS; b++ ) {
		vector<unsigned long long> * rands = new vector<unsigned long long>();
		for (int i = 0; i < model->initial->size; i++ )	rands->push_back(rand());
		randoms.push_back(rands);
	}
	bits[0] = 128;
	bits[1] = bits[0]>>1;
	bits[2] = bits[1]>>1;
	bits[3] = bits[2]>>1;
	bits[4] = bits[3]>>1;
	bits[5] = bits[4]>>1;
	bits[6] = bits[5]>>1;
	bits[7] = bits[6]>>1;

	unsigned long long largeprime = 3203431780337; //prime
	insertCounter = 0;

#ifdef PRIMETEST
	//find next prime

	unsigned long long test = HASHTABLESIZE+1;
	unsigned long long divisor;
	do {
		test--;
		divisor = 2;
		for (; divisor < sqrt(test) && test % divisor  ; divisor++ );
		if (divisor > 10000) printf("%llu not prime dividabe by %llu \n",test,divisor);
	}while (test && divisor < sqrt(test));

	printf("started test with %llu nex prime is %llu", HASHTABLESIZE,test);
	exit(0);
#endif


#ifdef BOOLHASH
	printf("reserving %llu GB for bithash table \n",HASHTABLESIZE/8/1024/1024/1024);
	boolHashtable.reserve(HASHTABLESIZE/8);
	memset(&boolHashtable[0],0,HASHTABLESIZE/8);

#else 
#ifdef LLHASHING
	dbs = DBSLLcreate(model->initial->size);
#else
	hashtable.reserve(HASHTABLESIZE);
	memset(&hashtable[0],0,HASHTABLESIZE);
#endif
#endif
	max_collisions =0;
}


unsigned long long StatesContainer::getHash(unsigned char * state, unsigned long long * randomVec) {
	if(NUMOFBITS==0) return true;

//#define jenkins
#ifdef jenkins

	unsigned long long hash;

	hash = largeprime;
	for (int i = 0; i < model->initial->size; i++ ) hash ^= randomVec[i]*(state[i]+1);
	hash = hash % (HASHTABLESIZE);
	
#else //hsieh
	unsigned int len = model->initial->size;
	unsigned char * data = state;

	uint32_t hash = len, tmp;
	int rem;

	rem = len & 3;
	len >>= 2;


	/* Main loop */
	for (;len > 0; len--) {
		hash  += get16bits (data);
		tmp    = (get16bits (data+2) << 11) ^ hash;
		hash   = (hash << 16) ^ tmp;
		data  += 4;
		hash  += hash >> 11;
	}

	/* Handle end cases */
	switch (rem) {
		case 3: hash += get16bits (data);
						hash ^= hash << 16;
						hash ^= data[2] << 18;
						hash += hash >> 11;
						break;
		case 2: hash += get16bits (data);
						hash ^= hash << 11;
						hash += hash >> 17;
						break;
		case 1: hash += *data;
						hash ^= hash << 10;
						hash += hash >> 1;
	}

	/* Force "avalanching" of final 127 bits */
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 4;
	hash += hash >> 17;
	hash ^= hash << 25;
	hash += hash >> 6;

#endif

	return hash;

}

bool StatesContainer::insert(unsigned char * state){
#ifdef DEBUGING
	cout << "inserting ";
	for (int i = 0;  i < model->initial->size ; i++ ) cout << (int) state[i]  << ";";
	cout << endl;
#endif

	if(NUMOFBITS==0) return true;

	unsigned long long hashes[NUMOFBITS];
	for (int b = 0; b < NUMOFBITS; b++) {
		hashes[b] = getHash(state,&(*randoms[b])[0]);
	}


#ifdef BOOLHASH
	return insertBool(state,hashes);
#else
#ifdef LLHASHING
	int idx;
	int seen;
	seen =  lookup_ret(dbs,(const int*) state,&idx);
	//cout << "idx " << idx << " inserted " << !seen << endl;
	return !seen;
#else
	return insertChain(state,hashes);
#endif
#endif
}

bool StatesContainer::insertBool(unsigned char * state, unsigned long long * longhashes){
	unsigned char b = 0;
	unsigned int * hashes = (unsigned int *) longhashes;
	while (b < NUMOFBITS && 	(boolHashtable[hashes[b]>>3] & bits[hashes[b]&7] )) b++;
	if (b == NUMOFBITS) return false;

	insertCounter++;
	for (b = 0; b < NUMOFBITS; b++) boolHashtable[hashes[b]>>3] |= bits[hashes[b]&7];
	return true;

}

bool StatesContainer::insertChain(unsigned char * state, unsigned long long * hashes){
	unsigned long long hash = hashes[0];

	if (!hashtable[hash]) {
		hashtable[hash] = new list<unsigned char *>;
	}
	else {
		list<unsigned char *>::iterator it;
#ifndef _FAST
		unsigned int ccount =0;
#endif
		for (it = hashtable[hash]->begin(); it != hashtable[hash]->end(); it++) {
			if (!memcmp((*it),state,model->initial->size)) return false;
#ifndef _FAST
			ccount++;
#endif
		}
#ifndef _FAST
		if (max_collisions < ccount) {
			max_collisions = ccount;
			printf("max_collisions %u",max_collisions);
		}
#endif
	}
	unsigned char * element = (unsigned char * ) malloc(model->initial->size); //generate space for child
	memcpy(element,state,model->initial->size); //store child in new space
	hashtable[hash]->push_back(element);
	insertCounter++;
	return true;

}

unsigned char * StatesContainer::getByPos(unsigned int pos, int * dst)  {
	return (unsigned char *) DBSLLget((dbs_ll_s*)dbs,pos,dst);
}

void StatesContainer::printAll(){
	int dst;
	unsigned int size = 1 << 28;
	unsigned int counter =0;
	cout << "printing all states, size " << size << endl;
	unsigned char *state ;
	for (int i = 0; i < size; i++) {
		state = getByPos(i,&dst);
		if(dst) {
//			cout << "(" << (unsigned int)getHash(state,NULL) << " == " << (unsigned int)dst << ") " ;
//			for ( int i = 0; i < model->initial->size; i++ ) cout << (unsigned int) state[i] << ";";
//			cout << "<--" << i << endl;
			counter++;
		}
	}
	cout << "found " << counter << " pairs " << endl;
}

bool StatesContainer::clear(){
#ifdef BOOLHASH
	memset(&boolHashtable[0],0,HASHTABLESIZE/8);
#else
	memset(&hashtable[0],0,HASHTABLESIZE);
#endif

}

StatesContainer::~StatesContainer() {

	// TODO Auto-generated destructor stub
}

