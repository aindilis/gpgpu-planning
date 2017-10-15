
#include "openListHashbased.h"
extern myModel * model;
extern unsigned char * dbsdatatable;


template <class T> openListHashbased<T>::openListHashbased(unsigned int elementLength_){
	elementLength= elementLength_;
	elements=0;
	serialize_mutexes = PTHREAD_MUTEX_INITIALIZER;
}

template <class T> bool openListHashbased<T>::insert(unsigned int layer, unsigned int cost, T element, unsigned int elementCount) {
	if (openLists.find(layer) == openLists.end()) {
		pthread_mutex_lock(&serialize_mutexes);
		if (serialize_open_map.find(layer) == serialize_open_map.end()) {
			//if (openLists.find(layer) == openLists.end()) {
			serialize_open_map[layer] = new pthread_mutex_t();
			*serialize_open_map[layer] = PTHREAD_MUTEX_INITIALIZER;
			pthread_mutex_lock(serialize_open_map[layer]);
			openLists[layer] = new map<unsigned int, unsigned int>();
			(*openLists[layer])[cost] = 0;
			pthread_mutex_unlock(serialize_open_map[layer]);
		}
		pthread_mutex_unlock(&serialize_mutexes);
		}

	assert(!cost);
	pthread_mutex_lock(serialize_open_map[layer]);
	(*openLists[layer])[cost]++;
	pthread_mutex_unlock(serialize_open_map[layer]);
	return true;
}

template <class T> unsigned int openListHashbased<T>::get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize){
	assert(dst);
	assert(openLists[layer]);
	assert((*openLists[layer])[cost]);
	int c = 0;
	myState state(model);
	cout << " reading from  open["<< layer << ","<< cost << "] size of ["<< layer << ","<< cost << "] " << (*openLists[layer])[cost] << " , elments " << elements << endl;
	unsigned int dbsc =0;
	while (dbsc < (unsigned int) 1 << 29 && c < bufferSize && c < (*openLists[layer])[cost] ) {
		state = &dbsdatatable[dbsc*elementLength];;
		if (state.cost() == layer) {
			memcpy(&dst[c*elementLength],state.vector,elementLength);
			c++;
		}
		dbsc++;
	}
	(*openLists[layer])[cost] -= c;
	cout << "read " << c << " elements now in layer " << layer << endl;
	return c;
}

template <class T> unsigned int openListHashbased<T>::getNextCosts(unsigned int layer,unsigned int current_costs){
//	cout << "getting next costs, starting with [" << layer << "][" << current_costs << "] size  " << (*openLists[layer])[current_costs]->size()<< endl;
	assert(openLists[layer]);
	typename map<unsigned int,map<unsigned int, unsigned int>* >::iterator it1; // 2 dimensional array of lists (depth, costs)
	it1 = openLists.find(layer);
	typename map<unsigned int, unsigned int>::iterator it2 ;
	it2 = (*it1).second->find(current_costs);
//	if ((*it1).second.second->size() != 0) it2++;
	do{	
		if (it2 != (*it1).second->end() && (*it2).second) return (*it1).first;
		// else it2 is at the end of the list so go on to the next depth
		it1++;
		if (it1 != openLists.end()) {
			it2 = (*it1).second->begin();
		}
	}while (it1 != openLists.end()) ;

	return -1;
}

template <class T> bool openListHashbased<T>::clear(){
	elements=0;
	return true;
}

