<<<<<<< .mine
#include "myState.h"

myState::myState(myModel * _model){
	model = _model;
	size = 0;
	freeBit = 0;
}

myState & myState::operator=(unsigned char * _vector){
	vector= _vector;
	size = model->initial->size;
	return *this;
}

void myState::print(ostream& ostr){
	cout << "state size :" << model->initial->size << " (not shown variables are zero) " << endl;
	list<array *>::iterator ait = model->global_arrays.begin();
	for( ; ait != model->global_arrays.end(); ait++) {
		assert((*ait)->offset < model->initial->size);
		if (vector[(*ait)->offset]) 
			cout << " global - " << (*ait)->name << " = " << (int)vector[(*ait)->offset] << endl;
	}
	list<process *>::iterator pit= model->processes.begin();
	for( ; pit != model->processes.end(); pit++) {
		for( ait =(*pit)->arrays.begin(); ait != (*pit)->arrays.end(); ait++) {
			//cout << "checking " << (*ait)->name << " at " << (*ait)->offset << " size in bits " << model->getSize((*ait)->type) << endl;
			if (model->getSize((*ait)->type) == 1 && (vector[(*ait)->offset/8] & 128 >> ((*ait)->offset%8))) 
				cout << "[" << (*ait)->offset << "]" << (*pit)->name << " - " << (*ait)->name << " = true " << endl;
			else if (model->getSize((*ait)->type) > 1 && vector[(*ait)->offset/8]) 
				cout << "[" << (*ait)->offset/8 << "]" << (*pit)->name << " - " << (*ait)->name << " = " << (int)vector[(*ait)->offset/8] << endl;
		}
	}
	for (int i = 0; i< model->initial->size ; i++) { cout << (int) vector[i] << ","; } cout << endl;
}

unsigned int myState::cost(){
	return (unsigned int) vector[model->heuristic_value->offset/8];
}

unsigned int myState::nextFreeBit(unsigned int bitLength){
	if (!(bitLength % 8 )) freeBit = size *8; //allocating whole bytes 
	unsigned int offset = freeBit;
	freeBit += bitLength;
	size = freeBit / 8 + 1;
	return offset;
}


std::ostream &operator<<(std::ostream &ostr, myState * s) {
	s->print(ostr);
	return ostr; 
}
=======
#include "myState.h"

myState::myState(myModel * _model){
	model = _model;
	size = 0;
	freeBit = 0;
	vector =0;
}

myState & myState::operator=(unsigned char * _vector){
	vector= _vector;
	size = model->initial->size;
	return *this;
}

void myState::print(ostream& ostr){
	cout << "state size :" << model->initial->size << " (not shown variables are zero) " << endl;
	list<array *>::iterator ait = model->global_arrays.begin();
	for( ; ait != model->global_arrays.end(); ait++) {
			if (model->getSize((*ait)->type) == 1 && (vector[(*ait)->offset/8] & 128 >> ((*ait)->offset%8))) 
				cout << "[" << (*ait)->offset << "]" << "global " << " - " << (*ait)->name << " = true " << endl;
			else if (model->getSize((*ait)->type) > 1 && vector[(*ait)->offset/8]) 
				cout << "[" << (*ait)->offset/8 << "]" << "global " << " - " << (*ait)->name << " = " << (int)vector[(*ait)->offset/8] << endl;
	}
	list<process *>::iterator pit= model->processes.begin();
	for( ; pit != model->processes.end(); pit++) {
		for( ait =(*pit)->arrays.begin(); ait != (*pit)->arrays.end(); ait++) {
			//cout << "checking " << (*ait)->name << " at " << (*ait)->offset << " size in bits " << model->getSize((*ait)->type) << endl;
			if (model->getSize((*ait)->type) == 1 && (vector[(*ait)->offset/8] & 128 >> ((*ait)->offset%8))) {
				cout << "[" << (*ait)->offset << "]" << (*pit)->name << " - " << (*ait)->name << " = true " << endl;
				cout << "action(s) " ;
				std::vector<unsigned int>::iterator it;
			 	it 	= model->precondition_predicates[(*ait)->offset].begin();
				while (it!= model->precondition_predicates[(*ait)->offset].end()) {
					cout << (*it) <<  ",";
					it++;
				}
				cout << "possibly true " << endl;
			}
			else if (model->getSize((*ait)->type) == 8 && vector[(*ait)->offset/8]) 
				cout << "[" << (*ait)->offset/8 << "]" << (*pit)->name << " - " << (*ait)->name << " = " << (int)vector[(*ait)->offset/8] << endl;
			else if (model->getSize((*ait)->type) == 32 && vector[(*ait)->offset/8]) 
				cout << "[" << (*ait)->offset/8 << "]" << (*pit)->name << " - " << (*ait)->name << " = " << *(int*)&vector[(*ait)->offset/8] << endl;
		}
	}
	for (int i = 0; i< model->initial->size ; i++) { cout << (int) vector[i] << ","; } cout << endl;
}

unsigned int myState::cost(){
	if (model->heuristic_value) 
		return *(unsigned int *)&vector[model->heuristic_value->offset/8];
	else 
		return 0;
}

bool myState::setCost(unsigned int newCost){
	if (model->heuristic_value) {
		unsigned int * cost = (unsigned int*) &vector[model->heuristic_value->offset/8];
		*cost = newCost;
	}
	else 
		return 0;
}

unsigned int myState::nextFreeBit(unsigned int bitLength){
#ifdef _DEBUGING
	cout << "freeBit " << freeBit << " allocating " << bitLength << "bits size " << size << endl;
#endif
	if (!(bitLength % 8 )) freeBit = size *8; //allocating whole bytes 
	unsigned int offset = freeBit;
	freeBit += bitLength;
	size = freeBit / 8 ;
	if (freeBit %8) size++;
	return offset;
}

bool myState::addArray(array * a){
	a->offset = nextFreeBit(a->size*model->getSize(a->type));
	list<char *>::iterator it;
	int i = 0;
	for (it = a->values.begin() ; it != a->values.end(); it++) {
		setValue(a,atoi(*it),i);
		i++;
		if (i == a->size) break;
	}
#ifdef _DEBUGING
		cout << "added array " << a->name << " type \"" << a->type << "\" offset " << a->offset << " size " << a->size << endl;
		i =0;
		for (it = a->values.begin() ; it != a->values.end(); it++) {
			cout << "\t value[" << i << "]= " << getValue(a,i) << endl;
			i++;
		if (i == a->size) break;
		}
#endif
}

int myState::getValue(array * a, unsigned int index) {
	if (model->getSize(a->type) == 1 ) {
		return (int) (vector[(a->offset+index)/8] & (128 >> ((a->offset+index)%8))); 
	}
	else if (model->getSize(a->type) == 8 ) 
		return *(unsigned char *) &vector[(a->offset+index*model->getSize(a->type))/8];
	else if (model->getSize(a->type) == 32 ) 
		return *(int*) &vector[(a->offset+index*model->getSize(a->type))/8];
}

bool myState::setValue(array * a, int value , unsigned int index) {
	if (model->getSize(a->type) == 1 ) {
		if (value) 
			vector[(a->offset+index)/8] |= (128 >> ((a->offset+index)%8)); 
		else
			vector[(a->offset+index)/8] &= ~(128 >> ((a->offset+index)%8)); 
	}
	else if (model->getSize(a->type) == 8 ) 
		vector[(a->offset+index*model->getSize(a->type))/8]= value;
	else if (model->getSize(a->type) == 32 ) 
		memcpy(&vector[(a->offset+index*model->getSize(a->type))/8],&value,4);
	return true;
}

std::ostream &operator<<(std::ostream &ostr, myState * s) {
	s->print(ostr);
	return ostr; 
}
>>>>>>> .r254
