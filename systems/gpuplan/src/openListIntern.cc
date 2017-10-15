
#include "openListIntern.h"
extern myModel * model;
extern unsigned int best_cost;

template <class T> openListIntern<T>::openListIntern(unsigned int elementLength_){
	elementLength= elementLength_;
	elements=0;
	serialize_mutexes = PTHREAD_MUTEX_INITIALIZER;
}

template <class T> bool openListIntern<T>::insert(unsigned int layer, unsigned int cost, T element, unsigned int elementCount) {
	if (openLists.find(layer) == openLists.end()) {
		pthread_mutex_lock(&serialize_mutexes);
		if (serialize_open_map.find(layer) == serialize_open_map.end()) {
			//if (openLists.find(layer) == openLists.end()) {
			serialize_open_map[layer] = new pthread_mutex_t();
			*serialize_open_map[layer] = PTHREAD_MUTEX_INITIALIZER;
			pthread_mutex_lock(serialize_open_map[layer]);
			openLists[layer] = new map<unsigned int, vector<T> *>();
			(*openLists[layer])[cost] = new vector<T>();
			pthread_mutex_unlock(serialize_open_map[layer]);
		}
		pthread_mutex_unlock(&serialize_mutexes);
		}

	assert(!cost);
	pthread_mutex_lock(&serialize_mutexes);
	elements+=elementCount;
	pthread_mutex_unlock(&serialize_mutexes);
	pthread_mutex_lock(serialize_open_map[layer]);
	(*openLists[layer])[cost]->push_back(element) ;
	pthread_mutex_unlock(serialize_open_map[layer]);
	return true;
}

template <class T> unsigned int openListIntern<T>::get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize){
	assert(dst);
	assert(openLists[layer]);
	assert((*openLists[layer])[cost]);
	int c = 0;
	myState state(model);
	//deleting until layer
	typename map<unsigned int,map<unsigned int, vector<T> *>* >::iterator it1; // 2 dimensional array of vectors (depth, costs)
	it1 = openLists.begin();
	while ((*it1).first != layer) {
		cout << "deleting vector " << (*it1).first << endl;
		typename map<unsigned int, vector<T> * >::iterator it2 ;
		it2 = (*it1).second->begin();
		while (it2 != (*it1).second->end()) {
			assert((*it2).second->begin() == (*it2).second->end());
			(*it2).second->clear();
			delete((*it2).second);
			(*it1).second->erase(it2);
			it2++;
		}
		delete((*it1).second);
		openLists.erase(it1);
		it1++;
	}

	cout << " reading from  open["<< layer << ","<< cost << "] size of ["<< layer << ","<< cost << "] " << (*openLists[layer])[cost]->size() << " , elments " << elements << endl;
	cout << "openlistsize " << openLists.size() << " lists and "  << elements << "=" << elements *8 /1024/1024 << " MB openlist" << endl;
	if ((*openLists[layer])[cost]->begin() == (*openLists[layer])[cost]->end() ) return 0;
#ifdef bufferfilling
	do {
#endif
		while (c < bufferSize && (*openLists[layer])[cost]->begin() != (*openLists[layer])[cost]->end() ) {
			state = (*openLists[layer])[cost]->back();
			if (state.cost() == layer ) {
				memcpy(&dst[c*elementLength],state.vector,elementLength);
				c++;
			}
			(*openLists[layer])[cost]->pop_back();
		}
#ifdef bufferfilling
		layer = getNextCosts(layer,cost);
	} while (c < bufferSize && layer != -1 && layer <= best_cost);
#endif
	cout << "read " << c << " elements now in layer " << layer << endl;
	elements -= c;
	cout << "openlistsize " << openLists.size() << " lists and "  << elements << "=" << elements *8 /1024/1024 << " MB openlist" << endl;

	return c;
}

template <class T> unsigned int openListIntern<T>::getNextCosts(unsigned int layer,unsigned int current_costs){
//	cout << "getting next costs, starting with [" << layer << "][" << current_costs << "] size  " << (*openLists[layer])[current_costs]->size()<< endl;
	assert(openLists[layer]);
	typename map<unsigned int,map<unsigned int, vector<T> *>* >::iterator it1; // 2 dimensional array of vectors (depth, costs)
	it1 = openLists.find(layer);
	typename map<unsigned int, vector<T> * >::iterator it2 ;
	it2 = (*it1).second->find(current_costs);
//	if ((*it1).second.second->size() != 0) it2++;
	do{	
		if (it2 != (*it1).second->end() && (*it2).second->size()) return (*it1).first;
		// else it2 is at the end of the list so go on to the next depth
		it1++;
		if (it1 != openLists.end()) {
			it2 = (*it1).second->begin();
		}
	}while (it1 != openLists.end()) ;

	return -1;
}

template <class T> bool openListIntern<T>::clear(){
	elements=0;
	return true;
}

