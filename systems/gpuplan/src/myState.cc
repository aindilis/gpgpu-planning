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
