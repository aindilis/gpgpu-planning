<<<<<<< .mine
%{

#include <stdio.h>
#define YYDEBUG 1



#include <list>
#include <vector>

extern myModel * model;

list<array *> parsed_arrays;
bool inProcess = false;
list<process *> parsed_processes;

list<form_node *> formula_list;

	
int yylex(void);
void yyerror(char const*);

%}

%union {
	form_node * node;
	transition * trans;
	process * proc;
	list<form_node *>* node_list;
	char * strings;
	int number;

	array * arrays;
	list<array *>* array_list;
	list<transition *>* transition_list;
};

%start pddl

%token OBRACKET
%token CBRACKET
%token DEFINE
%token REQUIREMENTS_TOK
%token PREDICATES_TOK
%token FUNCTIONS_TOK
%token ACTION_TOK;
%token PARAMETERS_TOK;
%token PRECONDITION_TOK;
%token EFFECT_TOK;
%token INIT_TOK;
%token GOAL_TOK;


%token <strings> NAME
%token <strings> DNAME
%token <strings> PNAME
%token <strings> SNAME
%token <strings> INAME
%token <strings> TNAME
%token <strings> TYPE
%token <strings> VALUE
%token <strings> FORMULA
%token <strings> STRING
%token <strings> OPERATOR
%token <number> SIZE
%token <number> NUMBER
%type <strings> domainName
%type <strings> requirement
%type <arrays> predicate
%type <array_list> predicatePlus
%type <array_list> predicateStar
%type <array_list> predicates
%type <array_list> functions
%type <trans> action
%type <transition_list> actionStar
%type <transition_list> actionPlus
%type <node_list> preconditions
%type <node_list> effects
%type <node_list> formulaStar
%type <node_list> formulaPlus
%type <node_list> init
%type <node_list> goal
%type <node> formula
%type <trans> problem
%type <proc> domain

//%type <node>	variable
//%type <trans> transition

%left INC_TOK
%left '=' NOT_TOK
%left AND_TOK OR_TOK BINAND_TOK BINOR_TOK 
%left EQ_TOK NEQ_TOK 
%left '<' '>' LE_TOK GE_TOK
%left '+' '-'
%left '*' '/' '%'

%%

pddl: domain problem {
	$1->transitions.push_back($2);
	model->addProcess($1);
}


problem: OBRACKET DEFINE problemName domainName init goal CBRACKET  {
	//printf("initializing domain %s \n",$4);
	//printf("adding %i goals \n",(int)$6->size());
	$$ = new transition();
	$$->from = 0 ; $$->to = 255;
	$$->guards = $6;
	$$->effects = $5; // hack, we store the initial state in the effects ;-)

}

domain: OBRACKET DEFINE  domainName requirements predicates functions actionStar CBRACKET {
	//printf("domain found, name = %s \n",$3);
	$$ = new process();
	$$->name = $3;
	$$->states.push_front((char *) "stateless");
	$$->initial = (char *) "stateless";
	list<array *>::iterator ait;
	//printf("found %i predicates \n",(int)$5->size());
	for (ait = $5->begin() ; ait != $5->end(); ait++) {
		$$->arrays.push_back(*ait);
	}
	//printf("found %i functions \n",(int)$6->size());
	for (ait = $6->begin() ; ait != $6->end(); ait++) {
		(*ait)->type=(char *)"integer";
		$$->arrays.push_back(*ait);
	}
	//printf("found %i actions \n",(int)$7->size());
	list<transition *>::iterator tit;
	for (tit = $7->begin() ; tit != $7->end(); tit++) {
		$$->transitions.push_back(*tit);
	}
}

problemName: OBRACKET PNAME STRING CBRACKET

domainName: OBRACKET DNAME STRING CBRACKET{ $$ = $3; }

requirements: OBRACKET REQUIREMENTS_TOK requirementStar CBRACKET

requirementStar: /* empty */ {} | requirementPlus
requirementPlus: requirement requirementStar 

functions: OBRACKET FUNCTIONS_TOK predicateStar CBRACKET{ $$ = $3; }

predicates: OBRACKET PREDICATES_TOK predicateStar CBRACKET { $$ = $3; }

predicateStar: /* empty */ {$$ = new list<array *>;} | predicatePlus{ $$ = $1; }

predicatePlus: predicate predicateStar {
	$$ = $2;
	$$->push_back($1);
}

predicate: OBRACKET STRING CBRACKET {
	array * a = new array();
	a->name = $2;
	a->size = 1;
	a->type = (char *) "bool";
	$$ = a;
}

actionStar: /* empy */ {$$ = new list<transition *>;} | actionPlus { $$ = $1; }

actionPlus: action actionStar {
	$$ = $2;
	$$->push_back($1);
}

requirement: STRING

action: OBRACKET ACTION_TOK STRING parameters preconditions effects CBRACKET{
	$$ = new transition();
	$$->from = $$->to = 0;
	$$->guards = $5;
	$$->effects = $6;
}

parameters: PARAMETERS_TOK OBRACKET CBRACKET

init: OBRACKET INIT_TOK formulaStar CBRACKET {
		$$ = $3;
}

goal: OBRACKET GOAL_TOK formulaStar CBRACKET {
		$$ = $3;
}

preconditions: PRECONDITION_TOK formulaStar {
	$$ = $2;
	if ($$->size() == 1 && !(*$$->begin())->right) {
		form_node * and_helper = new form_node(CONSTANT);
		and_helper->value=1;
		(*$$->begin())->right= and_helper;
	}

}

effects: EFFECT_TOK formulaStar{
  $$ = new list<form_node *>;
	list<form_node *>::iterator fit;
	list<form_node *> stack;
	//printf("parsing %i effects \n",(int)$2->size());
	for (fit = $2->begin(); fit != $2->end(); fit++) {
		stack.push_back(*fit);
		while (stack.size()) {
			form_node * node = stack.back();
			stack.pop_back();
			//printf("node type %i \n",node->type);
			//printf("left %llu right %llu \n",(unsigned long long)node->left,(unsigned long long) node->right);
//			if (node->type == VARIABLE_BYTE) printf("node string %s \n",node->string);
//			if (node->type == CONSTANT) printf("node value %i \n",node->value);
			if (node->left && node->left->type == VARIABLE_BYTE) { //assignemnt!
				form_node * assign_node = new form_node(ASSIGN);
				if (node->type != PLUS) {
					form_node * const_node = new form_node(CONSTANT);
					switch (node->type) {
						case AND:
							const_node->value=1;
						break;
						case NOT:
							const_node->value=0;
						break;
					}
					assign_node->right=const_node;
					assign_node->left=node->left;
					//printf("adding effect (%i)%s = (%i)%i \n",assign_node->left->type,assign_node->left->string,assign_node->right->type,assign_node->right->value);
					$$->push_back(assign_node);
				}
				else if (node->type == PLUS) {
					form_node * assign_node = new form_node(ASSIGN);
					form_node * target_node = new form_node(node->left);
					assign_node->left=target_node;
					assign_node->right = node;
					//printf("adding effect %s = %s + %i \n",assign_node->left->string, assign_node->right->left->string, assign_node->right->right->value);
					$$->push_back(assign_node);
				}
			}
			if (node->right && node->right->type == VARIABLE_BYTE) { //assignemnt!
				form_node * assign_node = new form_node(ASSIGN);
				if (node->type != PLUS) {
					form_node * const_node = new form_node(CONSTANT);
					switch (node->type) {
						case AND:
							const_node->value=1;
						break;
						case NOT:
							const_node->value=0;
						break;
					}
					assign_node->right=const_node;
					assign_node->left=node->right;
					//printf("adding effect %s = %i \n",assign_node->left->string,assign_node->right->value);
					$$->push_back(assign_node);
				}
				else if (node->type == PLUS) {
					form_node * assign_node = new form_node(ASSIGN);
					form_node * target_node = new form_node(node->right);
					assign_node->left=target_node;
					assign_node->right = node;
					//printf("adding effect %s = %s + %i \n",assign_node->left->string, assign_node->right->left->string, assign_node->right->right->value);
					$$->push_back(assign_node);
				}
			}
			if (node->left) stack.push_back(node->left);
			if (node->right) stack.push_back(node->right);
		}
	}
}

formulaStar: /* empy */ {$$ = new list<form_node *>;} | formulaPlus { $$ = $1}

formulaPlus: formula formulaStar {
	$$ = $2;
	$$->push_back($1);
}

formula: OBRACKET AND_TOK formulaStar CBRACKET { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		$$ = new form_node(); $$->type = AND;
		$$->left=$$->right=0;
		for (fit = $3->begin(); fit != $3->end(); fit++) {
			if (!$$->left) $$->left = *fit;
			else if (!$$->right) $$->right = *fit;
			else {
				tmp_node = $$;
				$$ = new form_node(); $$->type = AND;
				$$->left=$$->right=0;
				$$->left = tmp_node;
				$$->right=*fit;
			}
		}	
	}
	|OBRACKET NOT_TOK formulaStar CBRACKET { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		$$ = new form_node(); $$->type = NOT;
		$$->left=$$->right=0;
		for (fit = $3->begin(); fit != $3->end(); fit++) {
			if (!$$->left) $$->left = *fit;
			else if (!$$->right) $$->right = *fit;
			else {
				tmp_node = $$;
				$$ = new form_node(); $$->type = NOT;
				$$->left=$$->right=0;
				$$->left = tmp_node;
				$$->right=*fit;
			}
		}	
	}
	|OBRACKET INC_TOK formulaStar NUMBER CBRACKET { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		$$ = new form_node(); $$->type = PLUS;
		$$->right = new form_node();
		$$->right->type = CONSTANT;
		$$->right->value =$4;
		$$->left=0;
		for (fit = $3->begin(); fit != $3->end(); fit++) {
			if (!$$->left) $$->left = *fit;
			else if (!$$->right) $$->right = *fit;
			else {
				tmp_node = $$;
				$$ = new form_node(); $$->type = PLUS;
				$$->left=$$->right=0;
				$$->left = tmp_node;
				$$->right=*fit;
			}
		}	
	}
	|OBRACKET STRING CBRACKET { $$ = new form_node(); $$->type = VARIABLE_BYTE; $$->string = $2 ; $$->left = $$->right = 0;};

%%


#include "lex.gdl.cc"

void yyerror (char const *s) {
	  printf ("Error: %s\n", s);
	  exit(1);
}

=======
%{

#include <stdio.h>
#define YYDEBUG 1



#include <list>
#include <vector>

extern myModel * model;

list<array *> parsed_arrays;
bool inProcess = false;
list<process *> parsed_processes;

list<form_node *> formula_list;

	
int yylex(void);
void yyerror(char const*);

form_node *  complete_metric_node(form_node * n, list<form_node *> * goals) ;

%}

%union {
	form_node * node;
	transition * trans;
	process * proc;
	list<form_node *>* node_list;
	char * strings;
	int number;

	array * arrays;
	list<array *>* array_list;
	list<transition *>* transition_list;
};

%start pddl

%token OBRACKET
%token CBRACKET
%token DEFINE
%token REQUIREMENTS_TOK
%token PREDICATES_TOK
%token FUNCTIONS_TOK
%token ACTION_TOK;
%token PARAMETERS_TOK;
%token PRECONDITION_TOK;
%token EFFECT_TOK;
%token PREFERENCE_TOK;
%token INIT_TOK;
%token GOAL_TOK;
%token METRIC_TOK;


%token <strings> NAME
%token <strings> DNAME
%token <strings> PNAME
%token <strings> SNAME
%token <strings> INAME
%token <strings> TNAME
%token <strings> TYPE
%token <strings> VALUE
%token <strings> FORMULA
%token <strings> STRING
%token <number> SIZE
%token <number> NUMBER
%type <number> OPERATOR
%type <strings> domainName
%type <strings> requirement
%type <arrays> predicate
%type <array_list> predicatePlus
%type <array_list> predicateStar
%type <array_list> predicates
%type <array_list> functions
%type <trans> action
%type <transition_list> actionStar
%type <transition_list> actionPlus
%type <transition_list> problem
%type <node_list> preconditions
%type <node_list> effects
%type <node_list> formulaStar
%type <node_list> formulaPlus
%type <node_list> init
%type <node_list> goal
%type <node> formula
%type <node> metric
%type <node> metricStar
%type <proc> domain

//%type <node>	variable
//%type <trans> transition

%left INC_TOK DEC_TOK
%left '=' NOT_TOK
%left AND_TOK OR_TOK BINAND_TOK BINOR_TOK 
%left EQ_TOK NEQ_TOK 
%left '<' '>' LE_TOK GE_TOK
%left '+' '-'
%left '*' '/' '%'

%%

pddl: domain problem {
	//$1->transitions.push_back($2);
	list<transition *>::iterator tit;
	for (tit = $2->begin() ; tit != $2->end(); tit++) {
		$1->transitions.push_back(*tit);
	}
	model->addProcess($1);
}


problem: OBRACKET DEFINE problemName domainName init goal metricStar CBRACKET  {
			 //printf("initializing domain %s \n",$4);
	//printf("adding %i goals \n",(int)$6->size());
	$$ = new list<transition*>;
	transition * t  = new transition();
	t->from = 0 ; 
	t->to = 255;
	t->guards = $6;
	t->effects = $5; // hack, we store the initial state in the effects ;-)
	$$->push_back(t);
	if ($7->left == $7->right == 0) { //threre is a metric, we need to find the variables in the goal and concatenate them
		t= new transition();
		t->from = 0 ; 
		t->to = 254;
		t->guards=new list<form_node*>;
		t->effects = new list <form_node*>;
		complete_metric_node($7,$6);
		t->effects->push_back($7);
		$$->push_back(t);
	}

}

domain: OBRACKET DEFINE  domainName requirements predicates functions actionStar CBRACKET {
	//printf("domain found, name = %s \n",$3);
	$$ = new process();
	$$->name = $3;
	$$->states.push_front((char *) "stateless");
	$$->initial = (char *) "stateless";
	list<array *>::iterator ait;
	//printf("found %i predicates \n",(int)$5->size());
	for (ait = $5->begin() ; ait != $5->end(); ait++) {
		$$->arrays.push_back(*ait);
	}
	//printf("found %i functions \n",(int)$6->size());
	for (ait = $6->begin() ; ait != $6->end(); ait++) {
		(*ait)->type=(char *)"integer";
		$$->arrays.push_back(*ait);
	}
	//printf("found %i actions \n",(int)$7->size());
	list<transition *>::iterator tit;
	for (tit = $7->begin() ; tit != $7->end(); tit++) {
		$$->transitions.push_back(*tit);
	}
}

problemName: OBRACKET PNAME STRING CBRACKET

domainName: OBRACKET DNAME STRING CBRACKET{ $$ = $3; }

requirements: OBRACKET REQUIREMENTS_TOK requirementStar CBRACKET

requirementStar: /* empty */ {} | requirementPlus
requirementPlus: requirement requirementStar 


functions: {} | OBRACKET FUNCTIONS_TOK predicateStar CBRACKET{ $$ = $3; } 

predicates: OBRACKET PREDICATES_TOK predicateStar CBRACKET { $$ = $3; }
predicateStar: /* empty */ {$$ = new list<array *>;} | predicatePlus{ $$ = $1; }
predicatePlus: predicate predicateStar {
	$$ = $2;
	$$->push_front($1);
}

predicate: OBRACKET STRING CBRACKET {
	array * a = new array();
	a->name = $2;
	a->size = 1;
	a->type = (char *) "bool";
	$$ = a;
}

actionStar: /* empy */ {$$ = new list<transition *>;} | actionPlus { $$ = $1; }

actionPlus: action actionStar {
	$$ = $2;
	$$->push_back($1);
}

requirement: STRING

action: OBRACKET ACTION_TOK STRING parametersStar preconditions effects CBRACKET{
	$$ = new transition();
	$$->from = $$->to = 0;
	$$->guards = $5;
	$$->effects = $6;
}

parametersStar: /* empty*/ {} | parameter;

parameter: PARAMETERS_TOK OBRACKET CBRACKET

init: OBRACKET INIT_TOK formulaStar CBRACKET {
		$$ = $3;
}

goal: OBRACKET GOAL_TOK formulaStar CBRACKET {
		$$ = $3;
}

metricStar: /* empty*/ {$$ = new form_node(); $$->left = $$->right =0;} | metric{$$=$1};

metric: OBRACKET METRIC_TOK STRING formula CBRACKET{
			$$ = $4; 
}

preconditions: PRECONDITION_TOK formulaStar {
	$$ = $2;
	if ($$->size() == 1 && !(*$$->begin())->right) {
		form_node * and_helper = new form_node(CONSTANT);
		and_helper->value=1;
		(*$$->begin())->right= and_helper;
	}

}

effects: EFFECT_TOK formulaStar{
  $$ = new list<form_node *>;
	list<form_node *>::iterator fit;
	list<form_node *> stack;
	//printf("parsing %i effects \n",(int)$2->size());
	for (fit = $2->begin(); fit != $2->end(); fit++) {
		stack.push_back(*fit);
		while (stack.size()) {
			form_node * node = stack.back();
			stack.pop_back();
			//printf("node type %i \n",node->type);
			//printf("left %llu right %llu \n",(unsigned long long)node->left,(unsigned long long) node->right);
//			if (node->type == VARIABLE_BYTE) printf("node string %s \n",node->string);
//			if (node->type == CONSTANT) printf("node value %i \n",node->value);
			if (node->left && node->left->type == VARIABLE_BYTE) { //assignemnt!
				form_node * assign_node = new form_node(ASSIGN);
				if (node->type != PLUS && node->type != MINUS) {
					form_node * const_node = new form_node(CONSTANT);
					switch (node->type) {
						case AND:
							const_node->value=1;
						break;
						case NOT:
							const_node->value=0;
						break;
					}
					assign_node->right=const_node;
					assign_node->left=node->left;
					//printf("adding effect (%i)%s = (%i)%i \n",assign_node->left->type,assign_node->left->string,assign_node->right->type,assign_node->right->value);
					$$->push_back(assign_node);
				}
				else if (node->type == PLUS || node->type == MINUS) {
					form_node * assign_node = new form_node(ASSIGN);
					form_node * target_node = new form_node(node->left);
					assign_node->left=target_node;
					assign_node->right = node;
					//printf("adding effect %s = %s + %i \n",assign_node->left->string, assign_node->right->left->string, assign_node->right->right->value);
					$$->push_back(assign_node);
				}
			}
			if (node->right && node->right->type == VARIABLE_BYTE) { //assignemnt!
				form_node * assign_node = new form_node(ASSIGN);
				if (node->type != PLUS && node->type != MINUS) {
					form_node * const_node = new form_node(CONSTANT);
					switch (node->type) {
						case AND:
							const_node->value=1;
						break;
						case NOT:
							const_node->value=0;
						break;
					}
					assign_node->right=const_node;
					assign_node->left=node->right;
					//printf("adding effect %s = %i \n",assign_node->left->string,assign_node->right->value);
					$$->push_back(assign_node);
				}
				else if (node->type == PLUS || node->type == MINUS) {
					form_node * assign_node = new form_node(ASSIGN);
					form_node * target_node = new form_node(node->right);
					assign_node->left=target_node;
					assign_node->right = node;
					//printf("adding effect %s = %s + %i \n",assign_node->left->string, assign_node->right->left->string, assign_node->right->right->value);
					$$->push_back(assign_node);
				}
			}
			if (node->left) stack.push_back(node->left);
			if (node->right) stack.push_back(node->right);
		}
	}
}

formulaStar: /* empy */ {$$ = new list<form_node *>;} | formulaPlus { $$ = $1}

formulaPlus: formula formulaStar {
	$$ = $2;
	$$->push_back($1);
}

OPERATOR: 
		INC_TOK {$$=PLUS} 
	| '+' {$$=PLUS}
	| '*' {$$=MULT}
	| GE_TOK {$$=GE}
	| EQ_TOK {$$=ASSIGN}
	| DEC_TOK {$$=MINUS}
	| LE_TOK {$$=LESS};

formula: OBRACKET AND_TOK formulaStar CBRACKET { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		$$ = new form_node(); $$->type = AND;
		$$->left=$$->right=0;
		for (fit = $3->begin(); fit != $3->end(); fit++) {
			if (!$$->left) $$->left = *fit;
			else if (!$$->right) $$->right = *fit;
			else {
				tmp_node = $$;
				$$ = new form_node(); $$->type = AND;
				$$->left=$$->right=0;
				$$->left = tmp_node;
				$$->right=*fit;
			}
		}	
	}
	|OBRACKET NOT_TOK formulaStar CBRACKET { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		$$ = new form_node(); $$->type = NOT;
		$$->left=$$->right=0;
		for (fit = $3->begin(); fit != $3->end(); fit++) {
			if (!$$->left) $$->left = *fit;
			else if (!$$->right) $$->right = *fit;
			else {
				tmp_node = $$;
				$$ = new form_node(); $$->type = NOT;
				$$->left=$$->right=0;
				$$->left = tmp_node;
				$$->right=*fit;
			}
		}	
	}
	|OBRACKET OPERATOR formula formula CBRACKET { 
		$$ = new form_node(); 
		$$->type = $2;
		$$->left= $3;
		$$->right = $4;
	}
	|OBRACKET PREFERENCE_TOK STRING formula CBRACKET { 
		$$ = $4;
		$$->name = $3;
	}
	|OBRACKET STRING CBRACKET { 
		$$ = new form_node(); 
		$$->type = VARIABLE_BYTE; 
		$$->string = $2 ; 
		$$->left = $$->right = 0;
	}
	|NUMBER { 
		$$ = new form_node(); 
		$$->type = CONSTANT;
		$$->value = $1 ; 
		$$->left = $$->right = 0;
	};

%%


#include "lex.gdl.cc"

void yyerror (char const *s) {
	  printf ("Error: %s\n", s);
	  exit(1);
}

form_node * findGoalDefinition(form_node * n , char * name){
	form_node * retNode = 0 ;
	if (n->left) retNode = findGoalDefinition(n->left, name);
	if (!retNode) {
		if(n->right) retNode = findGoalDefinition(n->right, name);
		if(retNode) return retNode;
		if (n->name && !strncmp(n->name,name,strlen(name))) return n;
		return 0;
	}
	return retNode;
}

form_node * complete_metric_node(form_node * n , list<form_node *> * goals) {
	form_node * g = 0;
	if (n->left) g = complete_metric_node(n->left,goals);
	if (g) {
		delete(n->left);
		n->left=g;
		return 0;
		}
	if (n->right) g = complete_metric_node(n->right,goals);
	if (g) {
		delete(n->right);
		n->right=g;
		 return 0;
		}
		
	if (!n->left && !n->right && n->type ==VARIABLE_BYTE ) {
//		cout << "completing " << n << endl;
		char name[255];
		if (!strncmp(n->string,"is-violated-",12))
			memcpy(name,&n->string[12],strlen(n->string)-11);
			else assert(0);
//		cout << "searching for " << name << endl;
 		list<form_node *>::iterator it = goals->begin();
		while (it != goals->end()){
			//cout << " checking " << (*it) << endl;
			form_node * g = findGoalDefinition(*it,name);
			if(g) {
//				cout << " node found " << g << endl;
				form_node * notNode = new form_node();
				notNode->type = NOT;
				notNode->left=0;
				notNode->right=g;
				return notNode;
				}
			it++;
		}
	}
	return 0;
}




>>>>>>> .r254
