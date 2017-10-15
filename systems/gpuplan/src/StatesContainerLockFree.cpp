/*
 * StatesContainer.cpp
 *
 *  Created on: 06.01.2010
 *      Author: sulewski
 */


#include "StatesContainerLockFree.h"
#include <ctime>
#include <math.h>
#include <openssl/blowfish.h>

extern "C" {
	typedef struct dbs_ll_s *dbs_ll_t;
	extern dbs_ll_t     DBSLLcreate (int len,int hashLen,int size);
	extern int          DBSLLlookup_ret (const dbs_ll_t dbs, const int *v, int *ret,bool insert);
	extern int * 				DBSLLget(const dbs_ll_t dbs, const int idx, int *dst);
	extern unsigned char * getDataPointer(const dbs_ll_t dbs, int idx);
}

typedef dbs_ll_t DBS_T;
typedef DBS_T(*dbs_create_f)(int v, int s);
static dbs_create_f create = (dbs_create_f)DBSLLcreate;

typedef int(*dbs_lookup_f)(const DBS_T dbs, const int *v);
typedef int(*dbs_lookup_ret_f)(const DBS_T dbs, const int *v, int *ret,bool insert);
static dbs_lookup_ret_f lookup_ret = (dbs_lookup_ret_f)DBSLLlookup_ret;

extern "C" {
	DBS_T dbs;
}

unsigned char * dbsdatatable;
vector<unsigned int> randoms;

StatesContainerLockFree::StatesContainerLockFree(){
}

StatesContainerLockFree::StatesContainerLockFree(myModel * newModel) {
	model = newModel;
	int hashLength = model->initial->size;
	if (model->heuristic_value) hashLength-=4; 
	int size = 0;
	if (model->initial->size-4 < 156 ) size = 27;
	if (model->initial->size-4 < 76 ) size = 28;
	if (model->initial->size-4 < 35 ) size = 29;
	if (model->initial->size-4 < 16 ) size = 30;
	if (model->initial->size-4 < 7 ) size = 31;
	assert(size);

	dbs = DBSLLcreate(model->initial->size-4,hashLength,size);
	//open = new openListChar(model->initial->size);
	
	dbsdatatable = getDataPointer(dbs,0);	

	for (int i = 0; i < model->initial->size*3; i++ )	randoms.push_back(rand());

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

}

unsigned int StatesContainerLockFree::get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize) {
	return open->get(dst,layer,cost,bufferSize);
}

unsigned int StatesContainerLockFree::getNextCosts(unsigned int layer,unsigned int current_costs){
	return open->getNextCosts(layer,current_costs);
}

unsigned char * StatesContainerLockFree::insert(unsigned int bfslayer, myState * state,bool insert){
	int idx;
	bool seen;
	
	unsigned int newLayer = state->cost();
	if(bfslayer) assert(newLayer);
	seen =  lookup_ret(dbs,(const int*) state->vector,&idx,insert);
	//*state = getDataPointer(dbs,idx);
	if(!seen) {
//		open->insert(newLayer,0,state->vector);
		return state->vector;
	}
	//if (newLayer < state->cost()) {
		//open->insert(newLayer,0,state->vector);
		//state->setCost(newLayer);
//	}

	return 0;
}

void StatesContainerLockFree::printAll(){
	int dst;
	unsigned int size = 1 << 28;
	unsigned int counter =0;
	cout << "printing all states, size " << size << endl;
	unsigned char *state ;
	for (int i = 0; i < size; i++) {
		//state = table->getByPos(i,&dst);
		if(dst) {
//			cout << "(" << (unsigned int)getHash(state,NULL) << " == " << (unsigned int)dst << ") " ;
//			for ( int i = 0; i < model->initial->size; i++ ) cout << (unsigned int) state[i] << ";";
//			cout << "<--" << i << endl;
			counter++;
		}
	}
	cout << "found " << counter << " pairs " << endl;
}

bool StatesContainerLockFree::clear(){

}

StatesContainerLockFree::~StatesContainerLockFree() {
	// TODO Auto-generated destructor stub
}

