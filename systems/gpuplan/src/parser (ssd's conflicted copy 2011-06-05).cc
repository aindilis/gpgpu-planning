#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <pthread.h>
#include <assert.h>
#include <math.h>

#include <map>
#include <sys/mman.h>




#include "defines.h"
#include "GPUCheck.h"
#include "StatesContainer.h"
#include "StatesContainerLockFree.h"
#include "Timer.h"

using namespace std;

class ThousandGrouping : public std::numpunct< char > { 
	protected: 
		virtual std::string do_grouping() const 
		{ 
			return "\003"; // alle 3 Dezimalstellen den Tausendertrenner 
		} 
}; 

typedef struct {
		int id;
} parm;

myModel * model = new myModel();

Timer runningTime; //timer for complete running time
Timer readingOpen; //timer for getting states from the open list
Timer checkingTime_; //timer for transition checking
Timer enablingTime_; //timer for transition enabling
Timer duplicateTime_; //timer for duplicate detection

vector<unsigned char> openvector; //open list
unsigned int child_counter ; //counter for generated children
vector<unsigned char> childvector; //vector for generated children

unsigned int states ;
unsigned int pstates[PTHREADS] ;
unsigned int max_cost = 0;
unsigned int best_cost = 100000000;
unsigned int pmax_costs[PTHREADS] ;

unsigned char  openlist;
StatesContainer * storage ;
unsigned int bfsdepth = 0;
unsigned int current_cost = 0;
int current_best_metric = 1000000000;

void *check(void *arg)
{
		parm *p=(parm *)arg;
		myState child(model);
		pmax_costs[p->id] =0 ;
		pstates[p->id] = 0;
		//store children in the closed list
		//cout << " thread " << p->id << " started " << endl;
		for (unsigned int i = p->id;  i < child_counter; i+=PTHREADS ) { //iterate over all children
			child = &childvector[i*(model->initial->size+model->sizetTransitions)];
			if (storage->insert(bfsdepth,&child)) { //if new child count it 
				pstates[p->id]++;
				if (max_cost < child.cost() ) pmax_costs[p->id] = child.cost();
			}
		}
		//cout << " thread " << p->id << " done " << endl;
		return (NULL);
}

void endit(){
						cout << "END: " << states << " unique states generated " ; 
						//cout << "in depth " << iterations ; 
						cout << ", open list: " << ((unsigned long long) states*model->initial->size) << " bytes " ;
						cout << ((unsigned long long)states*model->initial->size)/1024/1024 << " MB " ;
						cout << runningTime << " running Time, detailed: checking: " << checkingTime_ << " enabling: " << enablingTime_ << " duplicate detection: " << duplicateTime_ ;
						cout << " reading from open" << readingOpen ;
						if (current_best_metric != 1000000000) cout << " current_best_metric " << current_best_metric;
						else cout << " best cost " << best_cost ;
						cout << endl;
					 	exit(0);
}

int main(int argc, char *argv[]) {
	mlockall(MCL_CURRENT | MCL_FUTURE); //prevent from paging
	  


	//overload cout function for integers 
cout.imbue( locale( cout.getloc(), new ThousandGrouping ) ); 
cout << fixed << setprecision(2); 


//allocate memory for threads
	pthread_t *threads;
	pthread_attr_t pthread_custom_attr;
	parm *p;

	threads=(pthread_t *)malloc(PTHREADS*sizeof(*threads));

	pthread_attr_init(&pthread_custom_attr);

	p=(parm *)malloc(sizeof(parm)*PTHREADS);

	for (int i=0; i<PTHREADS; i++) 
		p[i].id=i;

	runningTime.start();
	if (argc != 2) {
		cout << " no file for parsing given!" << endl;
		exit(0);
	}

	model->parse(argv[1]);
	model->generatePostfixRepresentation();

	//cout << model << endl;

	printf("stateSize %i, processes %i , transitions %i  ",model->initial->size,model->numOfProcesses,model->numOfTransitions);
	cout << " transitionBitvectorSize " << model->transitionSize ;
	cout << " sizetTransitions " << model->sizetTransitions << endl;
	cout << "initial state " << model->initial;
	if (model->heuristic_value) cout << "heuristic value called " << model->heuristic_value->name << " at offset " << model->heuristic_value->offset << endl;	

	unsigned int openvectorsize = VRAM / model->checkingSpace-1;
	unsigned int childopenvectorsize = VRAM / (model->initial->size+model->sizetTransitions)-1;
	cout << "openvectorsize = " << openvectorsize << endl ;
	cout << "childopenvectorsize = " << childopenvectorsize << endl ;

	vector<unsigned char> enabledvector; //vector containing bits with enabled transitions

	openvector.reserve(VRAM);
	enabledvector.reserve(VRAM);
	childvector.reserve(VRAM);

	storage = new StatesContainerLockFree(model); //closed list
	//exit(0);

	cout << runningTime << " Initializing GPU" << endl;
	GPUCheck(model);
	cout << runningTime << " generating state space ! " << endl << endl; 

	unsigned int next_layersize = 1;

	cout << "inserting initial state into open and closed list" ;
	myState initial(model);
	initial=model->state;
	storage->insert(bfsdepth,&initial);
	assert(!storage->insert(bfsdepth,&initial));


	openlist=0;
	states = 1;
	cout << runningTime ;
	printf("starting reachability \n");

	unsigned int openvectorcounter =0 ;
	unsigned int iterations =0;

	while (next_layersize) {
		next_layersize=0;

		readingOpen.start();
		openvectorcounter += storage->get((char *) &openvector[0],bfsdepth,current_cost,openvectorsize);
		readingOpen.stop();

		while (openvectorcounter) {

			unsigned char stateBuffer[model->initial->size];
			if (model->checkingSpace > model->initial->size) 
				for (unsigned int i = openvectorcounter-1 ; i > 0 ; i--) {
					memcpy(stateBuffer,&openvector[i*model->initial->size],model->initial->size);
					memcpy(&openvector[i*model->checkingSpace],stateBuffer,model->initial->size);
				}


			cout << "\t checking active transitions " << endl;
			checkingTime_.start();
			checkGuardsPostfix((unsigned char *) &openvector[0], (unsigned char*) &enabledvector[0], openvectorcounter,model); //enabled transitions
			checkingTime_.stop();
			assert(openvectorcounter);


			//generate children and store in open and closed list

			unsigned int parent_counter = 0; //counter for expanded parents
			while (parent_counter < openvectorcounter ) { //expand all parents

				child_counter = 0; //counter for generated children
				myState _parent(model);
				myState _child(model);
				memset(&childvector[0],0,VRAM);
				//copy parent for each enabled transition to the child buffer for the gpu
				while(parent_counter < openvectorcounter && child_counter < childopenvectorsize) {
					//get a bitvector of enabled transitions
					unsigned char * enabled = &enabledvector[(parent_counter)*model->checkingSpace]; //the parents enables bits
					//get the corresponding parrent state
					_parent = &openvector[(parent_counter)*model->checkingSpace]; //the current parent

					//cout << &_parent << "transitions " ;

					for (unsigned int i = 0 ;i < model->numOfTransitions; i++ ) { //check all transitions
						if (enabled[i>>3] && enabled[i>>3] & ((unsigned char) 128 >> (i&7))) { //if transition enabled, prepare for child generation
					//		cout << i << "," ; 
								
							if (model->metric_transition == -1 && i == model->active_transition) {
								cout << endl << endl << " goal state found, optimal cost " << _parent.cost() << " !!!! " << endl << &_parent <<endl;
								if (best_cost > _parent.cost()) best_cost = _parent.cost();						
								if (bfsdepth >= best_cost) endit();
							}
							if (i == model->active_transition || i == model->metric_transition) continue;

							memcpy(&childvector[child_counter*(model->initial->size+model->sizetTransitions)],_parent.vector,model->initial->size); //copy parent into child set
							memcpy(&childvector[(child_counter+1)*(model->initial->size+model->sizetTransitions)-model->sizetTransitions],&i,model->sizetTransitions); //set transition number for expansion
							child_counter++; //increment child counter
							if (child_counter == childopenvectorsize){
								break; //check if buffer full
							}
						}
					}
					//cout << " enabled " << endl;
					if (child_counter < childopenvectorsize) parent_counter++; //set on next parent if its children will fit into the buffer
					//while space in child buffer && parents left continue with next parent
				}
				//either child buffer full or no parents left, call kernel
				//
				cout << "\t enabling transitions, for " << child_counter << " states "<< endl	;
				enablingTime_.start();
				enableEffectsPostfix((unsigned char *) &childvector[0],child_counter,model);
				enablingTime_.stop();


				cout <<"\t analyzing duplicate elimination started "<< endl;
				duplicateTime_.start();

				if ( model->metric_transition != -1 ) {
					for (unsigned int i = 0;  i < child_counter; i++ ) { //iterate over all children
						int metric = 0;
						memcpy(&metric,&childvector[(i+1)*(model->initial->size+model->sizetTransitions)-model->sizetTransitions],model->sizetTransitions); //set transition number for expansion
						_child = &childvector[i*(model->initial->size+model->sizetTransitions)];
						//assert(_child.cost());
						metric += _child.cost();
						if ( metric < current_best_metric && _child.cost()) {
							if (best_cost < _parent.cost()) best_cost = _parent.cost();
							cout << " new best metric " << metric << endl;
							cout << "child cost " << _child.cost() << endl;
							current_best_metric = metric;
							cout << &_child << endl;
						}
					}
				}

				unsigned int new_child_counter =0;
				unsigned char zerochild[model->initial->size+1];
				memset(zerochild,0,model->initial->size+1);

#ifdef GPUHASHING
{
				cout << " GPU hashing started " << endl;
				vector<unsigned char> * hashes = new vector<unsigned char>();
				hashes->reserve(VRAM);
				getHashesGPU(&(*hashes)[0],child_counter,model);
				cout << child_counter << " hashes generated, sorting " << endl;
				//cout <<(int)  (*hashes)[0] << " - " << (int) (*hashes)[0] << endl;
				//qsort(&(*hashes)[0],child_counter,model->initial->size+model->sizetTransitions,compare_hashes);
				//cout <<  child_counter << " sorted " << endl;
				unsigned long long hash[2];
				for (unsigned int i = 0;  i < child_counter; i++ ) { //iterate over all children
					_child = &childvector[i*(model->initial->size+model->sizetTransitions)];
					//cout << " inserting " << *(unsigned int *) &(*hashes)[i*(model->initial->size+model->sizetTransitions)] << endl;
				
					if (storage->insertBool(_child.vector,(unsigned long long *) &(*hashes)[i*(model->initial->size+model->sizetTransitions)])) {
						next_layersize++;
						if (max_cost < _child.cost()) max_cost = _child.cost();
						new_child_counter++;
					}
					else
						memcpy(_child.vector,zerochild,model->initial->size);
				}
				//assert(0);
				delete(hashes);
				cout << " checked , compacting " << endl;
}
#else
{
#ifndef VERBOSE
				cout << runningTime << " CPU hashing for " << child_counter << " states  started " << endl;
#endif
				for (int i=0; i < PTHREADS && i <child_counter; i++){
					pthread_create(&threads[i], &pthread_custom_attr, check, (void *)&p[i]);
//					pthread_join(threads[i],NULL);
				}
				/* Synchronize the completion of each thread. */
				for (int i=0; i<PTHREADS && i <  child_counter; i++){
					pthread_join(threads[i],NULL);
					states+=pstates[i];
					if (max_cost < pmax_costs[i]) max_cost = pmax_costs[i];
				}
				duplicateTime_.stop();
#ifdef VERBOSE
				cout << PTHREADS << " thread(s) deleted duplicates " << endl;
#endif
}
#endif

				new_child_counter =0;
#ifdef oldcode
				for (unsigned int i = 0;  i < child_counter; i++ ) { //iterate over all children
					_child = &childvector[i*(model->initial->size+model->sizetTransitions)];
					if (int test = memcmp(_child.vector,zerochild,model->initial->size)) {
					  if (max_cost < _child.cost()) max_cost = _child.cost();
					}
				}

#ifndef VERBOSE
				cout << " compacted " << new_child_counter << " states " << " max cost " << max_cost << endl;
#endif

				unsigned int write_cost;
				unsigned int write_elements = 0;
				unsigned int write_child_counter=0;
				while (write_child_counter < new_child_counter) {
					_child = &childvector[write_child_counter*(model->initial->size)];
					write_cost = _child.cost();//costs of chldren to write
					write_elements  = 0; //count children with equal costs
					while(_child.cost() == write_cost && write_child_counter+write_elements < new_child_counter) {
						_child = &childvector[(write_child_counter+write_elements)*(model->initial->size)];
						write_elements++;
					}
#ifdef _DEBUGING
					cout << "writing " << write_elements << " elements with cost " << write_cost << endl;
#endif
					//write all children with equal costs
					//storage->open->insert(bfsdepth,write_cost,(unsigned char *) &childvector[write_child_counter*model->initial->size],write_elements);
					write_child_counter+=write_elements;
				}
				//assert all childern are written
				assert(write_child_counter == new_child_counter);

#endif //oldcode


				cout << states << " unique states generated " ; 
				cout << "in depth " << iterations ; 
				cout << runningTime << " running Time, detailed: checking: " << checkingTime_ << " enabling: " << enablingTime_ << " duplicate detection: " << duplicateTime_ ;
						cout << "reading from open" << readingOpen ;
						cout << " current best goal " << best_cost << endl;
//				assert(states < 150);
			}

			openvectorcounter = 0;

			while (!openvectorcounter && current_cost <= max_cost) {
#ifdef VERBOSE
				cout << "\t trying to read more from " << current_cost << " max cost =" << max_cost << endl;
#endif
				openvectorcounter += storage->get((char *) &openvector[0],bfsdepth,current_cost,openvectorsize);
				iterations++;
#ifdef VERBOSE
				cout << " read " << openvectorcounter << " states " << " tellg at " << gpointer[current_cost] << endl;
#endif
			
				if (bfsdepth > current_best_metric) endit();
				if (!openvectorcounter) {
					bfsdepth=storage->getNextCosts(bfsdepth,current_cost);
					cout << "new cost " << bfsdepth << endl;
					if (bfsdepth == -1) endit();
				}
			}

		} 
		//storage->clear();
		openlist++;
		openlist %=2;
		bfsdepth++;
		printf(" next layersize %i ",next_layersize);
		printf("states %u layer %i \n",states , bfsdepth );
	}

}


