
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

