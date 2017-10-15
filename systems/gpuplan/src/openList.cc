<<<<<<< .mine

#include "openList.h"

openList::openList(unsigned int _id){
	id = _id;

}

string openList::getOpenFileName(unsigned int num) {
	ostringstream  name;
	name << "/media/raid/open_" << num << ".dat";
	return name.str();
}

bool openList::insert(myState * state) {
	outputFile->write((const char *) state->vector,state->size);
	elements++;
	return true;
}

bool openList::clear(){
	elements=0;
	outputFile = new ofstream(getOpenFileName(id).c_str());
	return true;
}

=======

#include "openList.h"
extern myModel * model;

template <class T> openList<T>::openList(unsigned int elementLength_){
	elementLength= elementLength_;
	elements=0;
	serialize_mutexes = PTHREAD_MUTEX_INITIALIZER;
}

template <class T> bool openList<T>::insert(unsigned int layer, unsigned int cost, T element, unsigned int elementCount) {
	if (openLists.find(layer) == openLists.end()) {
		pthread_mutex_lock(&serialize_mutexes);
		if (serialize_open_map.find(layer) == serialize_open_map.end()) {
			//if (openLists.find(layer) == openLists.end()) {
			serialize_open_map[layer] = new pthread_mutex_t();
			*serialize_open_map[layer] = PTHREAD_MUTEX_INITIALIZER;
			pthread_mutex_lock(serialize_open_map[layer]);
			openElements[layer] = new map<unsigned int, unsigned int>();
			(*openElements[layer])[cost]= 0;
			openLists[layer] = new map<unsigned int, vector<T> *>();
			(*openLists[layer])[cost] = new vector<T>();
			openFiles[layer] = new map<unsigned int, fstream *>();
			(*openFiles[layer])[cost] = new fstream(); 
			openFilesRead[layer] = new map<unsigned int, fstream *>();
			(*openFilesRead[layer])[cost] = new fstream(); 
			ostringstream  name;
			name << "/media/raid/open_" << layer << "-" << cost << ".dat";
			cout << "creating " << name.str() << endl;
			(*openFiles[layer])[cost]->open(name.str().c_str(),fstream::out | fstream::trunc | ios::binary);
			openBuffers[layer] = new map<unsigned int, filebuf * >();
			(*openBuffers[layer])[cost] = (*openFiles[layer])[cost]->rdbuf();
			pthread_mutex_unlock(serialize_open_map[layer]);
		}
		pthread_mutex_unlock(&serialize_mutexes);
		}

	assert(!cost);
	pthread_mutex_lock(&serialize_mutexes);
	elements+=elementCount;
	pthread_mutex_unlock(&serialize_mutexes);
	pthread_mutex_lock(serialize_open_map[layer]);
//	(*openLists[layer])[cost]->push_back(element) ;
	assert((*openFiles[layer])[cost]->is_open());
	(*openFiles[layer])[cost]->write((const char*) element,elementLength);
	(*openElements[layer])[cost]++;
	pthread_mutex_unlock(serialize_open_map[layer]);
	return true;
}

template <class T> unsigned int openList<T>::get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize){
	assert(dst);
	assert(openLists[layer]);
	assert((*openLists[layer])[cost]);
	int c = 0;
	myState state(model);
	//deleting until layer
	//typename map<unsigned int,map<unsigned int, vector<T> *>* >::iterator it1; // 2 dimensional array of vectors (depth, costs)
	typename map<unsigned int,map<unsigned int,unsigned int> *>::iterator elementIt1;
	typename map<unsigned int, unsigned int >::iterator elementIt2 ;
	elementIt1 = openElements.begin();
	while ((*elementIt1).first != layer) {
		cout << "deleting vector " << (*elementIt1).first << " size " << (*elementIt1).second->size() << endl;
		elementIt2 = (*elementIt1).second->begin();
		while (elementIt2 != (*elementIt1).second->end() && (*elementIt2).first) {
			cout << "deleting layer " << (*elementIt1).first << " cost " << (*elementIt2).first << endl;
			assert((*elementIt2).second == 0 );
			(*elementIt1).second->erase(elementIt2);
			openElements.erase(elementIt1);
//			(*openFiles[(*elementIt1).first])[(*elementIt2).first]->close();
			delete(openLists[(*elementIt1).first]);
			//delete list
			elementIt2++;
		}
		elementIt1++;
	}

	cout << " reading from  open["<< layer << ","<< cost << "] "<< (*openElements[layer])[cost] << " elments " << endl;
	cout << "openlistsize " << openLists.size() << " lists and "  << elements << " elements =" << elements *8 /1024/1024 << " MB openlist" << endl;
	if ((*openElements[layer])[cost] == 0 ) return 0;
	//do {
	fstream * ol = (*openFilesRead[layer])[cost];
	if(!ol->is_open()) {
		ostringstream  name;
		name << "/media/raid/open_" << layer << "-" << cost << ".dat";
		cout << "opening " << name.str() << endl;
		ol->open(name.str().c_str(),fstream::in | ios::binary);
	}
	assert(ol->is_open());
	//while (c < bufferSize && (*openElements[layer])[cost]) {
		//cout << " reading " << elementLength << " bytes from " << layer << ":" << cost << " starting at " << ol->tellg() << endl;
	//	state = (unsigned char *) &dst[c*elementLength];
	//	ol->read((char *) state.vector,elementLength);
	//	c++;
		//(*openElements[layer])[cost]--;
	//}
	fstream * olWrite = (*openFiles[layer])[cost];
	olWrite->flush();
	if (bufferSize < (*openElements[layer])[cost]) ol->read(dst,bufferSize*elementLength);
	else ol->read(dst,(*openElements[layer])[cost]*elementLength);
	c=ol->gcount()/elementLength;
	(*openElements[layer])[cost]-=c;
	//} while (c < bufferSize && layer != -1);
	cout << "read " << c << "  left  " << (*openElements[layer])[cost] << " elments " << endl;
	//layer = getNextCosts(layer,cost);
	elements -= c;
	cout << "openlistsize " << openLists.size() << " lists and "  << elements << "=" << elements *8 /1024/1024 << " MB openlist" << endl;
	return c;
}

template <class T> unsigned int openList<T>::getNextCosts(unsigned int layer,unsigned int current_costs){
//	cout << "getting next costs, starting with [" << layer << "][" << current_costs << "] size  " << (*openLists[layer])[current_costs]->size()<< endl;
	assert(openLists[layer]);
	typename map<unsigned int,map<unsigned int, unsigned int>* >::iterator it1;
	it1 = openElements.find(layer);
	typename map<unsigned int, unsigned int >::iterator it2 ;
	it2 = (*it1).second->find(current_costs);
	do{	
		if (it2 != (*it1).second->end() && (*it2).second) return (*it1).first;
		// else it2 is at the end of the list so go on to the next depth
		it1++;
		if (it1 != openElements.end()) {
			it2 = (*it1).second->begin();
		}
	}while (it1 != openElements.end()) ;

	return -1;
}

template <class T> bool openList<T>::clear(){
	elements=0;
	return true;
}

>>>>>>> .r254
