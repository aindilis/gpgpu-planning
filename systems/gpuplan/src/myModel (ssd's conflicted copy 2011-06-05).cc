


#include "myModel.h"
#include <assert.h>

//#define yyoverflow
# define YYMAXDEPTH 10000000

#ifdef _PLANER 
	#include "gdl.tab.cc"
#else
	#include "dve.tab.cc"
#endif



using namespace std;

bool transition_compare(const transition * t1, const transition * t2) {
  return t1->from < t2->from;
}

void printOpType(int type, char * st) {
	return ;
	//printf("%i:",type);
	if (type == ASSIGN ) printf("=");

	else if (type == PLUS ) printf("+");
	else if (type == MINUS ) printf("-");
	else if (type == MULT ) printf("*");
	else if (type == DIV ) printf("/");

	else if (type == EQ ) printf("==");
	else if (type == NEQ ) printf("!=");
	else if (type == AND ) printf("&&");
	else if (type == OR ) printf("||");
	else if (type == NOT ) printf("not");


	else if (type == VARIABLE_BYTE ) printf("%s",st);
	else printf("=uk!");

	printf(" ");
}

form_node::form_node(){
	name=0;
	left=right=0;
	type=0;
}

form_node::form_node(int _type){
	name=0;
	left=right=0;
	type = _type;
}

form_node::form_node(form_node * src){
	name=0;
	left=right=0;
	type=src->type;
	value=src->value;
	if (src->string) {
		string =  (char *) malloc(strlen(src->string)+1);
		memcpy(string,src->string,strlen(src->string)+1);
	}
}

void form_node::print(ostream& ostr){
		if (this->left) this->left->print(ostr);
		if (this->right) this->right->print(ostr);
		switch (this->type) {
			case CONSTANT:
				ostr << " " << (int)value;
				break;
			case VARIABLE_BYTE:
				ostr << " " << string;
				break;
			case ASSIGN:
				ostr << " ASSIGN " ;
				break;
			case PLUS:
				ostr << " + " ;
				break;
			case AND:
				ostr << " AND " ;
				break;
			case NOT:
				ostr << " NOT " ;
				break;
			case GE:
				ostr << " >= " ;
				break;
			case MULT:
				ostr << " * ";
				break;
			default:
				ostr << "t: " <<(int) this->type << " v: " << (int) this->value ;
		}
}

form_node::~form_node(){
	if (type == VARIABLE_BYTE) free(string);
}

myModel::myModel(){
	metric_transition = active_transition = -1;
	numOfTransitions = 0;
	numOfProcesses = 0;
	initial = new myState(this);
	*initial = state;
	initial->size = 0;
	heuristic_value = 0;
}

unsigned int myModel::getSize(char * type){
	if (!(memcmp(type,"byte",4))) return 8;
	if (!(memcmp(type,"integer",7))) return (4*8);
	if (!(memcmp(type,"int",3))) return (4*8);
	if (!(memcmp(type,"bool",4))) return 1;
	printf("type %s not supported!",type);
	exit(0);
}

bool myModel::addArray(array * a){
	global_arrays.push_back(a);
	return initial->addArray(a);
}

bool myModel::addProcess(process * p){
#ifdef _DEBUGING
	printf("adding process %s \n",p->name);
#endif
	p->offset = initial->nextFreeBit(8)/8; //process offset in bytes
	p->transitions.sort(transition_compare);
	processes.push_back(p);
	numOfProcesses++;
	list<array *>::iterator it;
	for (it = p->arrays.begin() ; it != p->arrays.end(); it++) {
		initial->addArray(*it);
		if (!memcmp((*it)->name,"total-cost",10)) {
#ifdef _DEBUGING
			cout << "setting cost to " << (*it)->name << endl;
#endif
			heuristic_value= (*it);
		}
	}
	int i = 0;
	list<char *>::iterator sit;
	sit = p->states.begin();
	while (sit !=  p->states.end() && strncmp(p->initial,(*sit),20)){
		sit++;
		i++;
	}
	state[p->offset] = i;
	printf("initial = %i \n",i);
	list<transition *>::iterator t;
	unsigned int transition_counter = 0;
	for (t = p->transitions.begin(); t != p->transitions.end();t++){
		this->transitions.push_back(*t);
		numOfTransitions++;
		list<form_node *>::iterator n;
		(*t)->postfix_guards = new list<vector<POSTFIX_EFFECTS_TYPE>* >();
		for (n = (*t)->guards->begin(); n != (*t)->guards->end(); n++){
#ifdef _DEBUGING
			cout << "\t guard :" << *n << endl;;
#endif

			vector<POSTFIX_EFFECTS_TYPE > * pf = new vector<POSTFIX_EFFECTS_TYPE>();
			postfixParse(*n,pf);
			vector<POSTFIX_EFFECTS_TYPE>::iterator it = pf->begin();
			//assert(transition_counter < 2048);
			while(it != pf->end()) {
				if ((*it) == VARIABLE_BIT) {
					precondition_predicates[*(it+1)].push_back(transition_counter);
				}
				it++;
			}
			
			(*t)->postfix_guards->push_back(pf);
		}
		if((*t)->to == 255) {
			active_transition=transition_counter;
			initState((*t)->effects);
		} 
		if ((*t)->to == 254) {
			metric_transition = transition_counter;
		}
		(*t)->postfix_effects = new list<vector<POSTFIX_EFFECTS_TYPE>* >();
		for (n = (*t)->effects->begin(); n != (*t)->effects->end(); n++){
#ifdef _DEBUGING
			cout << "\t effect :" << *n << endl;
#endif
			vector<POSTFIX_EFFECTS_TYPE > * pf = new vector<POSTFIX_EFFECTS_TYPE>();
			postfixParse(*n,pf);
			(*t)->postfix_effects->push_back(pf);
		 }
		transition_counter++;
	}

	//if(numOfTransitions < 256) sizetTransitions = 1;
	//else if(numOfTransitions < 256*256) sizetTransitions = 2;
	//else sizetTransitions = 4;
	sizetTransitions = 4;

	transitionSize = numOfTransitions/8+1;


	printf("\n added process states %i transitions %i \n",(int)p->states.size(),(int)p->transitions.size());
}

int myModel::findVarPos(char * name){
	assert(strlen(name));
	list<array *>::iterator ai;
	for (ai = global_arrays.begin(); ai != global_arrays.end(); ai++){
		if (!strncmp((*ai)->name,name,255)) return (*ai)->offset;
	}
	for (ai = processes.back()->arrays.begin(); ai != processes.back()->arrays.end(); ai++){
			if (!strncmp((*ai)->name,name,255)) return (*ai)->offset;
		}
	printf("Error: variable %s not found \n",name); exit(0);
	return 0;
}

array * myModel::findArray(char * name){
	assert(strlen(name));
	list<array *>::iterator ai;
	for (ai = global_arrays.begin(); ai != global_arrays.end(); ai++){
		if (!strncmp((*ai)->name,name,255)) return (*ai);
	}
	for (ai = processes.back()->arrays.begin(); ai != processes.back()->arrays.end(); ai++){
			if (!strncmp((*ai)->name,name,255)) return (*ai);
		}
	printf("Error: variable %s not found \n",name); exit(0);
	return 0;
}

vector<POSTFIX_EFFECTS_TYPE> * myModel::postfixParse(form_node * n, vector<POSTFIX_EFFECTS_TYPE> * pf){
	if (n->left) postfixParse(n->left,pf);
	if (n->right) postfixParse(n->right,pf);
	if (n->type == VARIABLE_BYTE) {
		array * a = findArray(n->string);
		if (getSize(a->type) == 1) {
			pf->push_back(VARIABLE_BIT);
			pf->push_back(a->offset);
		}
		else if (getSize(a->type) == 8) { 
			if (a->size == 1) pf->push_back(VARIABLE_BYTE);
			else  pf->push_back(ARRAY_BYTE); //currently only byte arrays are supported
			pf->push_back(a->offset/8);
		}
		else if (getSize(a->type) == 32) {
			if (a->size == 1) pf->push_back(VARIABLE_INT);
			else  pf->push_back(ARRAY_INT); 
			pf->push_back(a->offset/8);
		}
	}
	else pf->push_back(n->type);
	if (n->type == CONSTANT) pf->push_back(n->value);
}

bool myModel::parse(char * filename) {

	cout << "parsing: " << filename << endl;

	yyin = fopen(filename, "r");
	if (!yyin) { printf("Could not open file ! \n"); exit(0); }
	//yydebug=1;
	yyparse();
	fclose(yyin);


	*initial = state;
	cout << " parsed " << endl;
	return true;

}

bool myModel::generatePostfixRepresentation(){
	//number and offsets of processes
	postfix_representation.push_back((unsigned int)this->processes.size());
	list<process * >::iterator pit;
	for (pit = this->processes.begin(); pit != this->processes.end(); pit++){
		postfix_representation.push_back((*pit)->offset);
		//postfix_representation.push_back((*pit)->transitions.size());
		postfix_representation.push_back(0); // just a placeholder. Will contain number of different states  with outgoing transitions
	}
	unsigned int first_trans = 0;
	unsigned int guard_offset = 0;
	unsigned int effect_offset = 0;
	unsigned int pcount =0;
	unsigned int pushed = 0;
	for (pit = this->processes.begin(); pit != this->processes.end(); pit++){
		printf("process %s \n",(*pit)->name);
		list<transition *>::iterator tit;
		tit = (*pit)->transitions.begin();
#ifdef VERBOSE
		printf("adding first transition from %i to %i number of guards %i effects %i \n",(*tit)->from,(*tit)->to,(int)(*tit)->postfix_guards->size(),(int)(*tit)->effects->size());
#endif

		unsigned int tstate = (*tit)->from;
		for (int i = 0 ; i < tstate; i++) {
			postfix_representation.push_back(0);
			postfix_representation.push_back(0);
			postfix_representation.push_back(0);
			pushed++;
		}
		unsigned int tcount = 1;
		unsigned int gsize = 0;
		unsigned int esize = 0;
		if ((*tit)->postfix_guards->size()) {
			gsize = (*(*tit)->postfix_guards->begin())->size()+1;
			postfix_guards.push_back((*(*tit)->postfix_guards->begin())->size());
			postfix_guards.insert(postfix_guards.end(),(*(*tit)->postfix_guards->begin())->begin(),(*(*tit)->postfix_guards->begin())->end());
		}
		else {
			postfix_guards.push_back(0);
			gsize++;
		}
		transition_offsets.push_back(effect_offset);
		postfix_effects.push_back((*pit)->offset);
		esize++;
		postfix_effects.push_back((*tit)->to);
		esize++;
		if ((*tit)->postfix_effects->size()) {
			postfix_effects.push_back((*tit)->postfix_effects->size());
			esize++;
			list<vector<POSTFIX_EFFECTS_TYPE >* >::iterator eit;
			for (eit = (*tit)->postfix_effects->begin(); eit != (*tit)->postfix_effects->end(); eit++ ){
				esize += (*eit)->size()+1;
				postfix_effects.push_back((*eit)->size());
				postfix_effects.insert(postfix_effects.end(),(*eit)->begin(),(*eit)->end());
			}
		}
		else {
			postfix_effects.push_back(0);
			esize++;
		}
		effect_offset += esize; esize = 0;
		for (tit++;tit != (*pit)->transitions.end(); tit++){
#ifdef VERBOSE
			printf("adding transition  from %i to %i number of guards %i effects %i \n",(*tit)->from,(*tit)->to,(int)(*tit)->postfix_guards->size(),(int)(*tit)->effects->size());
#endif
			transition_offsets.push_back(effect_offset);
			postfix_effects.push_back((*pit)->offset);
			esize++;
			postfix_effects.push_back((*tit)->to);
			esize++;
			if ((*tit)->postfix_effects->size()) {
				postfix_effects.push_back((*tit)->postfix_effects->size());
				esize++;
				list<vector<POSTFIX_EFFECTS_TYPE >* >::iterator eit;
				for (eit = (*tit)->postfix_effects->begin(); eit != (*tit)->postfix_effects->end(); eit++ ){
					esize += (*eit)->size()+1;
					postfix_effects.push_back((*eit)->size());
					postfix_effects.insert(postfix_effects.end(),(*eit)->begin(),(*eit)->end());
				}
			}
			else {
				postfix_effects.push_back(0);
				esize++;
			}
			effect_offset += esize; esize = 0;
			if ((*tit)->from == tstate) {
				tcount++;
				if((*tit)->postfix_guards->size()) {
					gsize += (*(*tit)->postfix_guards->begin())->size()+1;
					postfix_guards.push_back((*(*tit)->postfix_guards->begin())->size());
					postfix_guards.insert(postfix_guards.end(),(*(*tit)->postfix_guards->begin())->begin(),(*(*tit)->postfix_guards->begin())->end());
				}
				else {
					postfix_guards.push_back(0);
					gsize++;
				}
			}else {

				pushed++;
				postfix_representation.push_back(first_trans);
				postfix_representation.push_back(tcount);
				postfix_representation.push_back(guard_offset);
				cout << "transition " << tcount << " offset " << guard_offset << endl;
				if (tstate+1 != (*tit)->from) {
					for (int i = tstate+1 ; i < (*tit)->from; i++) {
						postfix_representation.push_back(0);
						postfix_representation.push_back(0);
						postfix_representation.push_back(0);
						pushed++;
					}
				}
				tstate = (*tit)->from;
				first_trans += tcount; tcount = 1;
				guard_offset += gsize;
				if ((*tit)->postfix_guards->size()) {
					gsize = (*(*tit)->postfix_guards->begin())->size()+1;
					postfix_guards.push_back((*(*tit)->postfix_guards->begin())->size());
					postfix_guards.insert(postfix_guards.end(),(*(*tit)->postfix_guards->begin())->begin(),(*(*tit)->postfix_guards->begin())->end());
				}
				else {
					postfix_guards.push_back(0);
					gsize = 1;
				}
			}
		}
		pushed++;
		postfix_representation.push_back(first_trans);
		postfix_representation.push_back(tcount);
		postfix_representation.push_back(guard_offset);
		first_trans += tcount; tcount = 1;
		guard_offset += gsize;
		if (tstate+1 != (*pit)->states.size()) {
			for (int i = tstate+1 ; i < (*pit)->states.size(); i++) {
				postfix_representation.push_back(0);
				postfix_representation.push_back(0);
				postfix_representation.push_back(0);
				pushed++;
			}
		}
		postfix_representation[1+pcount*2+1] = pushed;
		pcount++;
	}

	checkingSpace = initial->size;
	if (transitionSize > checkingSpace ) checkingSpace = transitionSize;

	//compress precondition_predicates by removing double entries in the lists
	vector<bool> appeared;
	appeared.reserve(numOfTransitions);
	for ( int i = 0 ; i < numOfTransitions; i++) appeared[i] =0;
	map<unsigned int, vector<unsigned int> >::iterator it = precondition_predicates.begin();
	while (it != precondition_predicates.end() ) {
		vector<unsigned int>::iterator it2 = (*it).second.begin();
		while(it2 != (*it).second.end()) {
			if (appeared[(*it2)]) (*it).second.erase(it2);
			else {
				appeared[(*it2)] = 1;
				it2++;
			}
		}
		it++;
	}

#ifdef SHOWPOSTFIX

	vector<unsigned int >::iterator it;
	printf("transitions (pr): ");
	for (it = postfix_representation.begin(); it != postfix_representation.end();it++)
		printf("%i ",*it);
	puts("");
	printf("guards (pg): ");
	for (it = postfix_guards.begin(); it != postfix_guards.end();it++)
		printf("%i ",*it);
	puts("");
	printf("transition offsets (to): ");
	for (it = transition_offsets.begin(); it != transition_offsets.end();it++)
			printf("%i ",*it);
		puts("");
	printf("effects (pe): ");
	for (it = postfix_effects.begin(); it != postfix_effects.end();it++)
		printf("%i ",*it);
	puts("");
#endif
}

bool myModel::showState(){
	for (int i = 0; i < initial->size; i++){
		printf("%i;",state[i]);
	}
	puts("");

}

bool myModel::initState(list<form_node *> * variables) {
	list<form_node *>::iterator fit;
	cout << "enabling state " << endl;
	for (fit = variables->begin(); fit != variables->end(); fit++) {
			if ((*fit)->type > VARIABLE_BIT ) {
				cout << "enabling " << (*fit)->string << " at " << findVarPos((*fit)->string)<< endl;
				if (getSize(findArray((*fit)->string)->type) == 1 ) {
					state[findVarPos((*fit)->string)/8] |= (128 >> (findVarPos((*fit)->string)%8)); 
				}
				else
					state[findVarPos((*fit)->string)]=1;
			}
			else if ((*fit)->type == 0 ) { //we have an assign node here
				if (getSize(findArray((*fit)->left->string)->type) == 32) {
					cout << "[" << findVarPos((*fit)->left->string)/8 << "] integer " << (*fit) << endl;
					int * i= (int *) &state[findVarPos((*fit)->left->string)/8];
					*i = (*fit)->right->value;
				}
				else if (getSize(findArray((*fit)->left->string)->type) == 8) {
					cout << "[" << findVarPos((*fit)->left->string)/8 << "] byte " << (*fit) << endl;
					char * i= (char *) &state[findVarPos((*fit)->left->string)/8];
					*i = (*fit)->right->value;
				} else {
					cout << "unsuported size " << getSize(findArray((*fit)->left->string)->type) << endl;
					assert(0);
				}
			}else{
				cout << "\t\t\t TODO: implement formulas in intital state!!!! " << endl;
				assert(0);
			}
	}
	cout << "enabled " << endl;
	return true;
}

void myModel::print(ostream& ostr){
#ifdef _PLANER
	ostr << "Printing " << transitions.size() << " transitions" << endl;
	for (int i = 0; i < transitions.size() ; i++) 
		ostr << "Transition " << i << ":" << transitions[i] << endl;
#else
	ostr << "Not implemented" << endl;
#endif

}

myModel::~myModel(){
}

void transition::print(ostream& ostr){
	if (to == 255) ostr << " INITIAL AND GOAL " ;
	if (to == 254) ostr << " METRIC " ;
	else 	ostr << "from " << from << " to " << to ;
	ostr << "," << guards->size() << " guards and " << effects->size() << " effects" << endl;
	list<form_node *>::iterator n;
	for (n = guards->begin(); n != guards->end(); n++)
			cout << "\t guard :" << *n << endl;;
	for (n = effects->begin(); n != effects->end(); n++)
			cout << "\t effect :" << *n << endl;;
	list<vector<POSTFIX_EFFECTS_TYPE>* >::iterator p;
	for (p = postfix_guards->begin(); p != postfix_guards->end(); p++){
			vector<POSTFIX_EFFECTS_TYPE> *v = *p;
			cout << "\t postfix guard size "<< v->size() << "::" ; 
			for (int i = 0; i < v->size() ; i++)
				cout << (*v)[i] << ";";
			cout << endl;
	}
	for (p = postfix_effects->begin(); p != postfix_effects->end(); p++){
			vector<POSTFIX_EFFECTS_TYPE> *v = *p;
			cout << "\t postfix effect size "<< v->size() << "::" ; 
			for (int i = 0; i < v->size() ; i++)
				cout << (*v)[i] << ";";
			cout << endl;
	}
}

std::ostream &operator<<(std::ostream &ostr, transition * t) {
	t->print(ostr);
	return ostr; 
}

std::ostream &operator<<(std::ostream &ostr, form_node * n) {
	n->print(ostr);
	return ostr; 
}

std::ostream &operator<<(std::ostream &ostr, myModel * m) {
	m->print(ostr);
	return ostr; 
}

