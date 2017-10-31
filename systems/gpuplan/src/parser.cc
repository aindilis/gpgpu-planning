#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <assert.h>
#include <math.h>

#include <map>



#include "defines.h"
#include "GPUCheck.h"
#include "StatesContainer.h"
#include "openList.h"

using namespace std;

int compare_hashes( const void* a, const void* b ) {  // compare function
	unsigned int* arg1 = (unsigned int*) a;
	unsigned int* arg2 = (unsigned int*) b;
	if( *arg1 < *arg2 ) return -1;
	else if( *arg1 == *arg2 ) return 0;
	else return 1;
}


typedef struct {
		int id;
} parm;

myModel * model = new myModel();

vector<unsigned char> openvector; //open list
unsigned int child_counter ; //counter for generated children
vector<unsigned char> childvector; //vector for generated children

unsigned int states ;

unsigned char  openlist;
StatesContainer * closed ;

void *check(void *arg)
{
		parm *p=(parm *)arg;
		//printf("Started node %d\n", p->id);
		//store children in the closed list
		for (unsigned int i = 0;  i <= child_counter / PTHREADS; i++ ) { //iterate over all children
		
			unsigned char * child = &childvector[((p->id*((child_counter / PTHREADS)+1))+i)*(model->initial->size+model->sizetTransitions)];
			if (closed->insert(child)) { //if new child count it and store it in the open list
				states++;
			}
			else {
//				printf("%i deleting child at pos %i \n",p->id,(p->id*(child_counter / PTHREADS))+i);
				memset(child,0,model->initial->size+1);
			}
		}
		return (NULL);
}

const char * getOpenFileName(unsigned int id1, unsigned int id2) {
	ostringstream  * name = new ostringstream();
	*name << "/media/raid/open_" << id1 << "-" << id2 << ".dat";
	cout << (*name).str() << endl;
	return (*name).str().c_str();
}

int main(int argc, char *argv[]) {

#ifdef PTHREADS_

	pthread_t *threads;
	pthread_attr_t pthread_custom_attr;
	parm *p;

	threads=(pthread_t *)malloc(PTHREADS*sizeof(*threads));
	pthread_attr_init(&pthread_custom_attr);

	p=(parm *)malloc(sizeof(parm)*PTHREADS);

	for (int i=0; i<PTHREADS; i++) 
		p[i].id=i;
	

#endif

	unsigned long long starttime = time(0);
	//yydebug=1;
	if (argc != 2) {
		cout << " no file for parsing given!" << endl;
		exit(0);
	}

	model->parse(argv[1]);

	printf("stateSize %i, processes %i , transitions %i  ",model->initial->size,model->numOfProcesses,model->numOfTransitions);
	cout << " transitionSize " << model->transitionSize << endl;
	cout << "initial state " << model->initial;



	model->generatePostfixRepresentation();

	printf("generating state space ! "); 

	closed = new StatesContainer(model);

	GPUCheck(model);

  map<int, fstream * > open_of_map;
	map<int,unsigned long long> gpointer;
	map<int,unsigned long long> ppointer;
 // map<int, ifstream * > open_if_map;
	cout << "inserting into " ;
	open_of_map[0] = new fstream();
	open_of_map[0]->open(getOpenFileName(0,0),fstream::out | fstream::in | fstream::trunc);
	assert(open_of_map[0]->is_open());
	//open_if_map[0] = new ifstream(getOpenFileName(0,0));


	open_of_map[0]->write((const char *) model->state,model->initial->size);
	open_of_map[0]->flush();
	ppointer[0] = open_of_map[0]->tellp();
	//cout << " ppointer[0] " << ppointer[0] << endl;
	closed->insert(model->state);
	unsigned int next_layersize = 1;

	unsigned int openvectorsize = VRAM / model->checkingSpace-1;
	printf("openvectorsize = %i \n",openvectorsize);
	unsigned int childopenvectorsize = VRAM / (model->initial->size+model->sizetTransitions)-1;

	cout << "sizetTransitions " << model->sizetTransitions << endl;
	printf("childopenvectorsize = %i \n",childopenvectorsize);
	cout << "heuristic value called " << model->heuristic_value->name << " at offset " << model->heuristic_value->offset << endl;	

	vector<unsigned char> enabledvector; //vector containing bits with enabled transitions

	openvector.reserve(VRAM);
	enabledvector.reserve(VRAM);
	childvector.reserve(VRAM);

#ifdef _CHECK
	cout << "CHECK: generating test States " << endl;
	memset(&childvector[0],0,VRAM);
	for (int i = 0 ; i < model->numOfTransitions-1 ;i++) {
		memcpy(&childvector[(i+1)*(model->initial->size+model->sizetTransitions)-model->sizetTransitions],&i,model->sizetTransitions); //set transition number for expansion
	}
	enableEffectsPostfix((unsigned char *) &childvector[0],model->numOfTransitions-1,model);
	vector<unsigned char *> teststates;
	teststates.reserve(model->numOfTransitions-1);
	for (int i =0; i < model->numOfTransitions-1; i++) {
		unsigned char * state = new unsigned char[model->initial->size];
		memcpy(state,&childvector[i*(model->initial->size+model->sizetTransitions)],model->initial->size); //copy parent into child set
		teststates.push_back(state);
	} 
	cout << "CHECK: test States generated " << endl;
#endif

		

	int bfsdepth = 0;
	openlist=0;
	states = 1;
	printf("start expanding \n");


	unsigned int openvectorcounter =0 ;
	unsigned int current_cost = 0;
	unsigned int max_cost = 0;

	while (next_layersize) {
		next_layersize=0;
		unsigned long long layertime = time(0);


		open_of_map[current_cost]->sync();
		open_of_map[current_cost]->seekg(0, ios::beg);
		open_of_map[current_cost]->read((char *) &openvector[0],openvectorsize*model->initial->size);
		openvectorcounter += open_of_map[current_cost]->gcount() / model->initial->size;
		if (open_of_map[current_cost]->rdstate() & ifstream::failbit) open_of_map[current_cost]->clear();
		gpointer[current_cost] = open_of_map[current_cost]->tellg();
		cout << "read " << openvectorcounter << " states " << " gpointer[" << current_cost << "] = " << gpointer[current_cost] << endl;
		open_of_map[current_cost]->seekp(ppointer[current_cost]);

		while (openvectorcounter) {

			unsigned char stateBuffer[model->initial->size];
			if (model->checkingSpace > model->initial->size) 
				for (unsigned int i = openvectorcounter-1 ; i > 0 ; i--) {
#ifdef _CHECK
					myState test(model);
					test = &openvector[i*model->initial->size];
					assert(test.cost() == current_cost);
#endif
					memcpy(stateBuffer,&openvector[i*model->initial->size],model->initial->size);
					memcpy(&openvector[i*model->checkingSpace],stateBuffer,model->initial->size);
#ifdef _CHECK
					test = &openvector[i*model->checkingSpace];
					if(test.cost() != current_cost){
						cout << "copied " << model->initial->size << " bytes from " << i*model->initial->size << " to " << i*model->checkingSpace << endl;
						cout << "states " << openvectorcounter << " cost of state " << i << " cost " << test.cost() << " current_cost " << current_cost << endl;
						cout << &test ;
						assert(0);
					}
#endif
				}
#ifdef _DEBUGING
				for (unsigned int i = 0; i < openvectorcounter; i++){
					myState _child(model);
					_child = &openvector[i*model->checkingSpace];
					cout << "expanding state " << i << &_child;
				}
#endif

			cout << time(0) - starttime << " checking active transitions " << endl;
			//find active transitions
			checkGuardsPostfix((unsigned char *) &openvector[0], (unsigned char*) &enabledvector[0], openvectorcounter,model); //enabled transitions
			cout << time(0) - starttime << " done for " << openvectorcounter << " states copying for child generation" << endl;
			assert(openvectorcounter);


			//generate children and store in open and closed list

			unsigned int parent_counter = 0; //counter for expanded parents

			while (parent_counter < openvectorcounter ) { //expand all parents

				child_counter = 0; //counter for generated children

#ifdef _CHECK
				vector<unsigned int >transitions_to_enable;
#endif
				myState _parent(model);
				myState _child(model);
				memset(&childvector[0],0,VRAM);
				//copy parent for each enabled transition to the child buffer for the gpu
				while(parent_counter < openvectorcounter && child_counter < childopenvectorsize) {
					_parent = &openvector[(parent_counter)*model->checkingSpace]; //the current parent
#ifdef _DEBUGING
					cout << "parent: " << &_parent << endl;
#endif
					unsigned char * enabled = &enabledvector[(parent_counter)*model->checkingSpace]; //the parents enables bits

					for (unsigned int i = 0 ;i < model->numOfTransitions; i++ ) { //check all transitions
						if (enabled[i>>3] & ((unsigned char) 128 >> (i&7))) { //if transition enabled, prepare for child generation
#ifdef _DEBUGING
							printf("parent %i child %i - transition %i enabled \n",parent_counter,child_counter,i);
#endif
							if (i == model->active_transition) {
								cout << endl << endl << time(0)-starttime << " sek goal state found, optimal cost " << current_cost << " !!!! " << endl << &_parent <<endl;
								exit(0);
							}
#ifdef _CHECK
							transitions_to_enable.push_back(i);
							assert(_parent.cost() >= current_cost);
#endif
							memcpy(&childvector[child_counter*(model->initial->size+model->sizetTransitions)],_parent.vector,model->initial->size); //copy parent into child set
							memcpy(&childvector[(child_counter+1)*(model->initial->size+model->sizetTransitions)-model->sizetTransitions],&i,model->sizetTransitions); //set transition number for expansion
							child_counter++; //increment child counter
							if (child_counter == childopenvectorsize){
								break; //check if buffer full
							}
						}
					}
					if (child_counter < childopenvectorsize) parent_counter++; //set on next parent if its children will fit into the buffer
					//while space in child buffer && parents left continue with next parent
				}
				//either child buffer full or no parents left, call kernel
				//

				cout << time(0) - starttime << " sec done, enabling transitions, for " << child_counter << " states " << endl ;
				enableEffectsPostfix((unsigned char *) &childvector[0],child_counter,model);
				cout << time(0) - starttime << " done for " << child_counter << " states" << endl;
				//assert(child_counter < 30000);

#ifdef _CHECK
{
				unsigned int transition_after =0 ; 
				for (int c = 0; c<child_counter; c++) { 
					_child = &childvector[c*(model->initial->size+model->sizetTransitions)];
					memcpy(&transition_after,&childvector[(c+1)*(model->initial->size+model->sizetTransitions)-model->sizetTransitions],model->sizetTransitions);
					if (_child.cost() < current_cost) {
						cout << "transition " << transition_after << endl;
						cout << &_child;
						assert(0);
					}
					assert(transitions_to_enable[c] == transition_after);
				}
}
#endif
#ifdef _DEBUGING
{
				myState child(model);
				for( unsigned int c = 0; c < child_counter; c++ ){
					child = &childvector[c*(model->initial->size+model->sizetTransitions)];
					int transition_num ; 
					memcpy(&transition_num,&childvector[(c+1)*(model->initial->size+model->sizetTransitions)-model->sizetTransitions],model->sizetTransitions);
					cout << "enabled transition " << transition_num << " generated " << endl ;
					cout << &child;
#ifdef _CHECK
					myState teststate(model);
					teststate = teststates[transition_num];
					cout << &teststate;
					for (int i = 0; i < model->initial->size ; i ++) {
						if ((child.vector[i] & teststates[transition_num][i]) != teststates[transition_num][i]){
							cout << " test failed at " << i << endl;
							assert(0);
						}
					}
#endif
					if (child.vector[model->heuristic_value->offset/8] ) {
						cout << "enabled transition " << transition_num << " generated " << &child;
						assert(0);
					}
				}
}
#endif
#ifndef PTHREADS_
{

				for (unsigned int i = 0;  i < child_counter; i++ ) { //iterate over all children
					_child = &childvector[i*(model->initial->size+model->sizetTransitions)];
					if (closed->insert(_child.vector)) { //if new child count it and store it in the open list
						states++;
						if(_child.cost() > current_cost) next_layersize++;
						//cout << "one thread inserting into " << (int)_child.cost() << endl;
						if (max_cost < _child.cost()) max_cost = _child.cost();
						if (open_of_map.find(_child.cost()) == open_of_map.end())
							open_of_map[_child.cost()] = new fstream(getOpenFileName(openlist,_child.cost()),fstream::out | fstream::in | fstream::trunc);
						open_of_map[_child.cost()]->write((const char *) _child.vector,model->initial->size);
						assert(!(open_of_map[_child.cost()]->rdstate() & fstream::badbit));
						if(_child.cost() < current_cost) {
							cout << &_child << endl;
							assert(0);
						}
					}
				}
}
#else //defined PTHREADS_

				unsigned int new_child_counter =0;
				unsigned char zerochild[model->initial->size+1];
				memset(zerochild,0,model->initial->size+1);

#ifdef GPUHASHING
				cout << time(0) -starttime << " sec getHashesGPU started " << endl;
				vector<unsigned char> * hashes = new vector<unsigned char>();
				hashes->reserve(VRAM);
				getHashesGPU(&(*hashes)[0],child_counter,model);
				cout << time(0) -starttime << " sec " << child_counter << " hashes generated, sorting " << endl;
				//cout <<(int)  (*hashes)[0] << " - " << (int) (*hashes)[0] << endl;
				//qsort(&(*hashes)[0],child_counter,model->initial->size+model->sizetTransitions,compare_hashes);
				//cout << time(0) -starttime << " sec " << child_counter << " sorted " << endl;
				unsigned long long hash[2];
				for (unsigned int i = 0;  i < child_counter; i++ ) { //iterate over all children
					_child = &childvector[i*(model->initial->size+model->sizetTransitions)];
					//cout << " inserting " << *(unsigned int *) &(*hashes)[i*(model->initial->size+model->sizetTransitions)] << endl;
				
					if (closed->insertBool(_child.vector,(unsigned long long *) &(*hashes)[i*(model->initial->size+model->sizetTransitions)])) {
						next_layersize++;
						if (max_cost < _child.cost()) max_cost = _child.cost();
						new_child_counter++;
					}
					else
						memcpy(_child.vector,zerochild,model->initial->size);
				}
				//assert(0);
				delete(hashes);
				cout << time(0) -starttime << " sec checked , compacting " << endl;
#else
				cout << time(0) -starttime << " sec thread started " << endl;
				for (int i=0; i < PTHREADS && i <child_counter; i++){
					pthread_create(&threads[i], &pthread_custom_attr, check, (void *)(p+i));
				}
				/* Synchronize the completion of each thread. */
				for (int i=0; i<PTHREADS && i <  child_counter; i++){
					pthread_join(threads[i],NULL);
				}
				cout << time(0) -starttime << " sec thread deleted duplicates " << endl;
#endif

				new_child_counter =0;

				for (unsigned int i = 0;  i < child_counter; i++ ) { //iterate over all children
					_child = &childvector[i*(model->initial->size+model->sizetTransitions)];
					if (int test = memcmp(_child.vector,zerochild,model->initial->size)) {
					  if (max_cost < _child.cost()) max_cost = _child.cost();
						next_layersize++;
						memcpy(&childvector[new_child_counter*model->initial->size],_child.vector,model->initial->size);
						//cout << "inserting into ";
						new_child_counter++;
					}
				}

				cout << time(0) -starttime << " sec compacted " << new_child_counter << " states " << " max cost " << max_cost << endl;

				unsigned int write_cost;
				unsigned int write_elements = 0;
				unsigned int write_child_counter=0;
				while (write_child_counter < new_child_counter) {
					_child = &childvector[write_child_counter*(model->initial->size)];
					write_cost = _child.cost();
					//assert(write_cost ==0);
					write_elements  = 0;
					while(_child.cost() == write_cost && write_child_counter+write_elements < new_child_counter) {
						_child = &childvector[(write_child_counter+write_elements)*(model->initial->size)];
						write_elements++;
					}
#ifdef _DEBUGING
					cout << "writing " << write_elements << " elements with cost " << write_cost << endl;
#endif
					if (open_of_map.find(write_cost) == open_of_map.end())
						open_of_map[write_cost] = new fstream(getOpenFileName(openlist,write_cost),fstream::out | fstream::in | fstream::trunc);
					open_of_map[write_cost]->write((const char *) &childvector[write_child_counter*model->initial->size],write_elements*model->initial->size);
					write_child_counter+=write_elements;
				}
				assert(write_child_counter == new_child_counter);
#endif
				cout << time(0) -starttime << " sec written" << endl;

			}
			openvectorcounter = 0;
			while (!openvectorcounter && current_cost <= max_cost) {
				open_of_map[current_cost]->flush();
				cout << "\t trying to read more from " << current_cost << " seeking g to " << gpointer[current_cost] << " max cost =" << max_cost << endl;
				if (open_of_map[current_cost]->rdstate() & ifstream::failbit) open_of_map[current_cost]->clear();
				ppointer[current_cost] = open_of_map[current_cost]->tellp();
				//cout << " ppointer[current_cost] " << ppointer[current_cost] << endl;

				open_of_map[current_cost]->seekg(gpointer[current_cost]);
				assert(open_of_map[current_cost]->tellg() == gpointer[current_cost]);
				open_of_map[current_cost]->read((char *) &openvector[0],openvectorsize*model->initial->size);
				openvectorcounter += open_of_map[current_cost]->gcount() / model->initial->size;
				if (open_of_map[current_cost]->rdstate() & ifstream::failbit) open_of_map[current_cost]->clear();
				gpointer[current_cost] = open_of_map[current_cost]->tellg();
				open_of_map[current_cost]->seekp(ppointer[current_cost]);

				cout << "\t read " << openvectorcounter << " states " << " tellg at " << gpointer[current_cost] << endl;
#ifdef _DEBUGING
				for (unsigned int i = 0;  i < openvectorcounter; i++){
					myState _child(model);
					_child = &openvector[i*model->initial->size];
					cout << "state " << i << &_child;
				}
#endif

				cout << "\t statesContainer insert counter " << closed->insertCounter << endl;
#ifdef _CHECK
				for (unsigned int i = 0; i < openvectorcounter; i++){
					myState _child(model);
					_child = &openvector[i*model->initial->size];
					assert(_child.cost() == current_cost);
				}
#endif
					
				if ( !openvectorcounter) {
					//open_if_map[current_cost]->close();
					map<int,fstream * >::iterator it = open_of_map.find(current_cost);
					it++;
					current_cost = (*it).first;
					gpointer[current_cost] = 0;
					//open_of_map[current_cost] = new ifstream(getOpenFileName(0,current_cost));
				}
			}

		} 
		//closed->clear();
		openlist++;
		openlist %=2;
		bfsdepth++;
		cout << time(0)-starttime ;
		printf(" next layersize %i ",next_layersize);
		printf("states %u layer %i  layer time %llu \n",states , bfsdepth, time(0)-layertime);
	}
	printf("states %u time %llu \n\n",states,time(0)-starttime);

}


