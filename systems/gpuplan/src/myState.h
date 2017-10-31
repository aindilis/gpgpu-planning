
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#ifndef MYSTATE_H_
#define MYSTATE_H_

class myModel;

#include "myModel.h"

class myState{
public:
	myModel * model;
	unsigned char * vector;
	unsigned int size;
	unsigned int freeBit; //next bit which can be allocated

	myState(myModel * _model);
	myState & operator=(unsigned char * _vector);
	void print(ostream& ostr);
	unsigned int cost();
	unsigned int nextFreeBit(unsigned int bitLength);
};

std::ostream &operator<<(std::ostream &ostr, myState * s);

#endif  /* MYSTATE_H_ */
