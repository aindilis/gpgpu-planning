
#include "openListExtern.h"

template <class T> openListExtern<T>::openListExtern(unsigned int elementLength_){
	elementLength= elementLength_;
	elements=0;
}

template <class T> string openListExtern<T>::getOpenFileNamePrivate(unsigned int id1, unsigned int id2) {
	ostringstream  name;
	name << "/media/raid/open_private_" << id1 << "-" << id2 << ".dat";
	return name.str();
}


template <class T> bool openListExtern<T>::insert(unsigned int layer, unsigned int cost, T element, unsigned int elementCount) {
	if(!openLists[layer]) openLists[layer] = new map<unsigned int, fstream *>();
	if (!(*openLists[layer])[cost]){
		(*openLists[layer])[cost] = new fstream();
		(*openLists[layer])[cost]->open(getOpenFileNamePrivate(layer,cost).c_str(),fstream::out | fstream::in | fstream::trunc);
		added[layer][cost]=0;
		removed[layer][cost]=0;
	}
	fstream  *ol = (*openLists[layer])[cost];
	assert(ol->is_open());
	ol->write((const char*) element,elementCount*elementLength);
	ol->flush();
	added[layer][cost]+=elementCount;
	elements+=elementCount;
	//for (int i = 0; i < elementLength; i++) cout << (unsigned int) element[i] << "," ;
	//cout << " inserted " << elementCount << " into open["<< layer << ","<< cost << "] size of ["<< layer << ","<< cost << "] " << added[layer][cost] << " , elments " << elements << endl;
	return true;
}

template <class T> unsigned int openListExtern<T>::get(char * dst, unsigned int layer, unsigned int cost, unsigned int bufferSize){
	assert(dst);
	assert(openLists[layer]);
	fstream * ol = (*openLists[layer])[cost];
	assert(ol->is_open());
	ol->seekg(removed[layer][cost]*elementLength, ios::beg);
	ol->read(dst,bufferSize*elementLength);
	unsigned int c = ol->gcount() / elementLength;
	removed[layer][cost] += c;
	//cout << "read form open[" << layer << "," << cost << "] " << c << " elements " << endl;
	if (ol->rdstate() & ifstream::failbit) ol->clear();
	return c;
}

template <class T> unsigned int openListExtern<T>::getNextCosts(unsigned int layer,unsigned int current_costs){
	assert(openLists[layer]);
	map<unsigned int, fstream * > * ol = openLists[layer];
	map<unsigned int,fstream * >::iterator it = ol->find(current_costs);
	it++;
	if (it == ol->end()) return -1;
	return (*it).first;
}

template <class T> bool openListExtern<T>::clear(){
	elements=0;
	return true;
}

