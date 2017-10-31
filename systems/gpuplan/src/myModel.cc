


#include "myModel.h"
#include <assert.h>

#include "gdl.tab.cc"

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
	left=right=0;
}

form_node::form_node(int _type){
	left=right=0;
	type = _type;
}

form_node::form_node(form_node * src){
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
				ostr << " PLUS " ;
				break;
			case AND:
				ostr << " AND " ;
				break;
			case NOT:
				ostr << " NOT " ;
				break;
			default:
				ostr << "t: " <<(int) this->type << " v: " << (int) this->value ;
		}
}

form_node::~form_node(){
	if (type == VARIABLE_BYTE) free(string);
}


myModel::myModel(){
	active_transition = -1;
	numOfTransitions = 0;
	numOfProcesses = 0;
	initial = new myState(this);
	initial->size = 0;
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
	a->offset == initial->nextFreeBit(a->size*getSize(a->type));
	list<char *>::iterator it;
	int i = 0;
	for (it = a->values.begin() ; it != a->values.end(); it++) {
		state[a->offset+i] = atoi(*it);
		i+=getSize(a->type);
	}
	//printf("added array type %s name %s size %i \n",a->type,a->name,a->size);
}

bool myModel::addProcess(process * p){
#ifdef _DEBUGING
	printf("adding process %s \n",p->name);
#endif
	p->offset = initial->nextFreeBit(8);
	p->transitions.sort(transition_compare);
	processes.push_back(p);
	numOfProcesses++;
	list<array *>::iterator it;
	for (it = p->arrays.begin() ; it != p->arrays.end(); it++) {
	  (*it)->offset = initial->nextFreeBit((*it)->size*getSize((*it)->type));
		list<char *>::iterator vit;
		int i = 0;
		for (vit = (*it)->values.begin() ; vit != (*it)->values.end(); vit++) {
			state[(*it)->offset+i] = atoi(*vit);
			i+=getSize((*it)->type);
		}
#ifdef _DEBUGING
		cout << "added array " << (*it)->name << " offset " << (*it)->offset << " size " << (*it)->size << " stateSize " << initial->size << endl;
#endif
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
		numOfTransitions++;
#ifdef _DEBUGING
		printf("transition %i from %i to %i guards = %i effects %i\n",transition_counter,(*t)->from,(*t)->to,(int)(*t)->guards->size(),(int)(*t)->effects->size());
#endif
		list<form_node *>::iterator n;
		(*t)->postfix_guards = new list<vector<POSTFIX_EFFECTS_TYPE>* >();
		for (n = (*t)->guards->begin(); n != (*t)->guards->end(); n++){
#ifdef _DEBUGING
			cout << "\t guard :" << *n << endl;;
#endif
			(*t)->postfix_guards->push_back(postfixParse(*n));
		}
		if((*t)->to == 255) {
			active_transition=transition_counter;
			initState((*t)->effects);
		} 
		(*t)->postfix_effects = new list<vector<POSTFIX_EFFECTS_TYPE>* >();
		for (n = (*t)->effects->begin(); n != (*t)->effects->end(); n++){
#ifdef _DEBUGING
			cout << "\t effect :" << *n << endl;
#endif
			(*t)->postfix_effects->push_back(postfixParse(*n));
		}
		transition_counter++;
	}

	if(numOfTransitions < 256) sizetTransitions = 1;
	else if(numOfTransitions < 256*256) sizetTransitions = 2;
	else sizetTransitions = 4;

	transitionSize = numOfTransitions/8+1;


	//printf("\n added process states %i transitions %i \n",(int)p->states.size(),(int)p->transitions.size());
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

vector<POSTFIX_EFFECTS_TYPE> * myModel::postfixParse(form_node * root){
	list<form_node *> node_stack;
	vector<POSTFIX_EFFECTS_TYPE > * temp_storage = new vector<POSTFIX_EFFECTS_TYPE>();
	node_stack.push_back(root);
		while (node_stack.size() && node_stack.size() < 100){
			form_node * suc = 0;
			suc = node_stack.back()->left;
			//if(suc) printf("suc ype = %i \n",suc->type);
			node_stack.back()->left = 0;
			if (suc && suc->left == 0 ) {
					if (suc->type ==VARIABLE_BYTE) {
						array * a = findArray(suc->string);
					  if (getSize(a->type) == 1) temp_storage->push_back(VARIABLE_BIT);
						else temp_storage->push_back(VARIABLE_BYTE);
						temp_storage->push_back(a->offset);
					}
					else temp_storage->push_back(suc->type);
				if (suc->type ==CONSTANT) temp_storage->push_back(suc->value);
				printOpType(suc->type,suc->string);
				delete(suc);
			}
			else if(suc) {
				node_stack.push_back(suc);
			} else {
				suc = node_stack.back()->right;
			//if(suc) printf("suc ype = %i \n",suc->type);
				node_stack.back()->right =0;
				if (suc && suc->left == 0 ) {
					if (suc->type ==VARIABLE_BYTE) {
						array * a = findArray(suc->string);
					  if (getSize(a->type) == 1) temp_storage->push_back(VARIABLE_BIT);
						else temp_storage->push_back(VARIABLE_BYTE);
						temp_storage->push_back(a->offset);
					}
					else temp_storage->push_back(suc->type);
					if (suc->type ==CONSTANT) temp_storage->push_back(suc->value);
					printOpType(suc->type,suc->string);
					delete(suc);
				}
				else if(suc){
					node_stack.push_back(suc);
				}
			}

			if (!suc) {
				printOpType(node_stack.back()->type,node_stack.back()->string);
				//printf("root type %i \n",node_stack.back()->type);
				temp_storage->push_back(node_stack.back()->type);
				if (node_stack.back()->type == VARIABLE_BYTE) { // we have an array here storing the starting position
					temp_storage->back() = ARRAY;
					temp_storage->push_back(findVarPos(node_stack.back()->string));
				}
				if (node_stack.back()->type ==CONSTANT) temp_storage->push_back(node_stack.back()->value);
				delete(node_stack.back());
				node_stack.pop_back();
			}
		}
//		puts("");
//		for (int i = 0; i < temp_storage->size(); i++) printf("%i ",(*temp_storage)[i]);
//		puts("");
		return temp_storage;
}

bool myModel::parse(char * filename) {

	cout << "parsing: " << filename ;

	yyin = fopen(filename, "r");
	if (!yyin) { printf("Could not open file ! \n"); exit(0); }
	yyparse();
	fclose(yyin);

	*initial = state;
	return true;

}

bool myModel::generatePostfixRepresentation(){
	//number and offsets of processes
	postfix_representation.push_back((unsigned int)this->processes.size());
	list<process * >::iterator pit;
	for (pit = this->processes.begin(); pit != this->processes.end(); pit++){
		postfix_representation.push_back((*pit)->offset);
		postfix_representation.push_back((*pit)->transitions.size());
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
		//printf("adding transition from %i to %i number of guards %i effects %i \n",(*tit)->from,(*tit)->to,(int)(*tit)->postfix_guards->size(),(int)(*tit)->effects->size());


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
			//printf("adding transition  from %i to %i number of guards %i effects %i \n",(*tit)->from,(*tit)->to,(int)(*tit)->postfix_guards->size(),(int)(*tit)->effects->size());
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

#ifdef SHOWPOSTFIX

	vector<unsigned int >::iterator it;
	printf("transitions: ");
	for (it = postfix_representation.begin(); it != postfix_representation.end();it++)
		printf("%i ",*it);
	puts("");
	printf("guards: ");
	for (it = postfix_guards.begin(); it != postfix_guards.end();it++)
		printf("%i ",*it);
	puts("");
	printf("transition offsets: ");
	for (it = transition_offsets.begin(); it != transition_offsets.end();it++)
			printf("%i ",*it);
		puts("");
	printf("effects: ");
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
	for (fit = variables->begin(); fit != variables->end(); fit++) {
			//cout << "enabling " << (*fit)->string << " at " << findVarPos((*fit)->string)<< endl;
			if (getSize(findArray((*fit)->string)->type) == 1 ) {
				state[findVarPos((*fit)->string)/8] |= (128 >> (findVarPos((*fit)->string)%8)); 
			}
			else
				state[findVarPos((*fit)->string)]=1;
	}

	return true;
}

myModel::~myModel(){
}


std::ostream &operator<<(std::ostream &ostr, form_node * n) {
	n->print(ostr);
	return ostr; 
}

