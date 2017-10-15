<<<<<<< .mine
/*
 * myModel.h
 *
 *  Created on: 22.12.2009
 *      Author: damian
 */

#include <list>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


#ifndef MYMODEL_H_
#define MYMODEL_H_

#include "myState.h"

#define ASSIGN 		0

#define PLUS		1
#define MINUS		2
#define MULT		3
#define	DIV			4
#define MOD 		5
#define NEG			6

#define EQ			7
#define NEQ 		8
#define LE  		9
#define GE  		10
#define AND 		11
#define OR  		12
#define BINAND 		13
#define BINOR  		14
#define LESS	 	15
#define GREATER		16
#define NOT 		17

#define ARRAY		251
#define VARIABLE_BIT 	252
#define VARIABLE_BYTE 	253
#define VARIABLE_INT 	254
#define CONSTANT 	255

class form_node{
public:
	form_node();
	form_node(int _type); //auto init
	form_node(form_node * source); //copy constructor
	~form_node();
	unsigned char type ; // 255 = value ...type
	char * string;
	int value;
	form_node * left;
	form_node * right;
	void print(ostream& ostr);
};


struct array{
	char * type;
	char * name;
	int size;
	list<char*> values;
	int offset; //in the state
};

#define POSTFIX_EFFECTS_TYPE unsigned int

class transition {
public:
	int from;
	int to;
	list<form_node *> * guards;
	list<vector<POSTFIX_EFFECTS_TYPE>* > * postfix_guards;
	list<form_node *> * effects;
	list<vector<POSTFIX_EFFECTS_TYPE >* > * postfix_effects;

	bool compare(const transition * t1, const transition * t2);

};

struct process{
	char * name;
	int offset;	//start of process in state
	list<array*> arrays;
	list<char *> states;
	char * initial;
	list<transition *> transitions;
};
class myState;

class myModel{
private:

public:
	unsigned int getSize(char * type);
	list<array *> global_arrays;
	list<process *> processes;
	char * system;

	vector<unsigned int> postfix_representation;
	vector<POSTFIX_EFFECTS_TYPE> postfix_guards;
	vector<unsigned int> transition_offsets;
	vector<POSTFIX_EFFECTS_TYPE> postfix_effects;

	unsigned int active_transition; //index of transition which defines this state as active.
	array * heuristic_value; //a variable can be defined as a heuristic value

	unsigned char state[200];
	myState * initial;
	unsigned int transitionSize; // number of bytes for transitions bitvector
	unsigned int numOfTransitions;
	unsigned int sizetTransitions; //how many bytes do we need to store numOfTransitions;
	unsigned int numOfProcesses;


	unsigned int checkingSpace; //minimal space needed for checking, transition size or state size

	myModel();
	~myModel();

	int findVarPos(char * name);
	array * findArray(char * name);

	vector<POSTFIX_EFFECTS_TYPE> * postfixParse(form_node * root);

	bool parse(char * filename);

	bool generatePostfixRepresentation();

	bool addArray(array * a); //adds an array to the state
	bool addProcess(process * p); //adds a process to the state

	bool initState(list<form_node *> * variables);

	bool showState();

};


std::ostream &operator<<(std::ostream &ostr, form_node * n) ;

#endif /* MYMODEL_H_ */
=======
/*
 * myModel.h
 *
 *  Created on: 22.12.2009
 *      Author: damian
 */

#include <list>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


#ifndef MYMODEL_H_
#define MYMODEL_H_

struct array{
	char * type;
	char * name;
	int size;
	list<char*> values;
	int offset; //in the state
};

#include "myState.h"


#define ASSIGN 		0

#define PLUS		1
#define MINUS		2
#define MULT		3
#define	DIV			4
#define MOD 		5
#define NEG			6

#define EQ			7
#define NEQ 		8
#define LE  		9
#define GE  		10
#define AND 		11
#define OR  		12
#define BINAND 		13
#define BINOR  		14
#define LESS	 	15
#define GREATER		16
#define NOT 		17

#define ARRAY_BYTE		250
#define ARRAY_INT		251
#define VARIABLE_BIT 	252
#define VARIABLE_BYTE 	253
#define VARIABLE_INT 	254
#define CONSTANT 	255

class form_node{
public:
	form_node();
	form_node(int _type); //auto init
	form_node(form_node * source); //copy constructor
	~form_node();
	unsigned char type ; // 255 = value ...type
	char * string;
	char * name; // used e.g. for prefered goals in planning, where bolean formulas may have "names"
	int value;
	form_node * left;
	form_node * right;
	void print(ostream& ostr);
};



#define POSTFIX_EFFECTS_TYPE unsigned int

class transition {
public:
	int from;
	int to;
	list<form_node *> * guards;
	list<string> guard_strings;
	list<vector<POSTFIX_EFFECTS_TYPE>* > * postfix_guards;
	list<form_node *> * effects;
	list<string> effect_strings;
	list<vector<POSTFIX_EFFECTS_TYPE >* > * postfix_effects;

	bool compare(const transition * t1, const transition * t2);
	void print(ostream& ostr);

};

struct process{
	char * name;
	int offset;	//start of process in state
	list<array*> arrays;
	list<char *> states;
	char * initial;
	list<transition *> transitions;
};
class myState;

class myModel{
private:

public:
	unsigned int getSize(char * type);
	list<array *> global_arrays;
	list<process *> processes;
	char * system;

	vector<unsigned int> postfix_representation;
	vector<POSTFIX_EFFECTS_TYPE> postfix_guards;
	vector<unsigned int> transition_offsets;
	vector<POSTFIX_EFFECTS_TYPE> postfix_effects;
	map<unsigned int, vector<unsigned int> > precondition_predicates;

	vector<transition*> transitions; //shortcut vector containing links to all transitions

	unsigned int active_transition; //index of transition which defines this state as active.
	unsigned int metric_transition; //index of transition which defines the metric in planning
	array * heuristic_value; //a variable can be defined as a heuristic value

	unsigned char state[200];
	myState * initial;
	unsigned int transitionSize; // number of bytes for transitions bitvector
	unsigned int numOfTransitions;
	unsigned int sizetTransitions; //how many bytes do we need to store numOfTransitions;
	unsigned int numOfProcesses;


	unsigned int checkingSpace; //minimal space needed for checking, transition size or state size

	myModel();
	~myModel();

	int findVarPos(char * name);
	array * findArray(char * name);

	vector<POSTFIX_EFFECTS_TYPE> * postfixParse(form_node * root);
  vector<POSTFIX_EFFECTS_TYPE> * postfixParse(form_node * n, vector<POSTFIX_EFFECTS_TYPE> * pf);

	bool parse(char * filename);

	bool generatePostfixRepresentation();

	bool addArray(array * a); //adds an array to the state
	bool addProcess(process * p); //adds a process to the state

	bool initState(list<form_node *> * variables);

	bool showState();

	void print(ostream& ostr);

};


std::ostream &operator<<(std::ostream &ostr, form_node * n) ;
std::ostream &operator<<(std::ostream &ostr, transition * t) ;
std::ostream &operator<<(std::ostream &ostr, myModel *m) ;

#endif /* MYMODEL_H_ */
>>>>>>> .r254
