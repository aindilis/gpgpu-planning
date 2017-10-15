%{

#include <stdio.h>
#define YYDEBUG 1



#include <list>
#include <vector>

#include "myModel.h"

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
	list<form_node *>* node_list;
	char * strings;
	int number;
};

%start starting

%token PROCESS_TOK
%token SYSTEM_TOK
%token INITIAL_TOK
%token TRANS_TOK
%token TO_TOK
%token GUARD_TOK
%token EFFECT_TOK
%token STATE_TOK
%token END_TOK


%token <strings> NAME
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

%type <node_list> guards
%type <node_list> effects
%type <node> formula
%type <node>	variable
%type <trans> transition

%left '=' NOT_TOK
%left AND_TOK OR_TOK BINAND_TOK BINOR_TOK 
%left EQ_TOK NEQ_TOK 
%left '<' '>' LE_TOK GE_TOK
%left '+' '-'
%left '*' '/' '%'

%%

starting: model

model: arrayStar processPlus system

processPlus: process processStar
processStar: {} | processPlus

arrayStar:  /* empty */ {} | arrayPlus
arrayPlus: array arrayStar

array: TYPE nameSizeValueStar END_TOK {
	list<array *>::iterator it;
	for (it = parsed_arrays.begin() ; it != parsed_arrays.end(); it++) {
		((array*) *it)->type = $1;
		if (inProcess)
			parsed_processes.back()->arrays.push_back(*it);
		else
			model->addArray(*it);
	}
	parsed_arrays.clear();
}

nameSizeValueStar: {} | nameSizeValuePlus
nameSizeValuePlus: nameSizePlus valueStar nameSizeValueStar

nameSizeStar: {} | nameSizePlus 
nameSizePlus: namePlus sizeStar nameSizeStar 

nameStar: /* empty */ {} | namePlus
namePlus: name nameStar

sizeStar: /* empty */ {} | sizePlus
sizePlus: size sizeStar

valueStar: {} | valuePlus
valuePlus: value valueStar

name: NAME{
	array * a = new array();	
	a->name = $1;
	a->size = 1;
	parsed_arrays.push_back(a);
}

size: SIZE{
	parsed_arrays.back()->size = $1;
}

value: VALUE {
	parsed_arrays.back()->values.push_back($1);
}

process: PROCESS_TOK pname arrayStar statePlus initState acceptStar TRANS_TOK transPlus{
	list<process *>::iterator it;
		for (it = parsed_processes.begin() ; it != parsed_processes.end(); it++) {
			model->addProcess(*it);
		}
		parsed_processes.clear();
}

pname: PNAME {
	process * p = new process();
	p->name = $1;
	parsed_processes.push_back(p);
	inProcess = true;
}

statePlus: state stateStar
stateStar:  {} | statePlus

state: STATE_TOK snamePlus END_TOK

snamePlus: NAME snameStar{
	parsed_processes.back()->states.push_front($1);
}
snameStar: {} | snamePlus

initState: INAME{
	parsed_processes.back()->initial = $1;
}

acceptStar: {} | acceptState
acceptState: INAME{
}

transPlus: transition transStar {
	parsed_processes.back()->transitions.push_front($1);
}
transStar: {} | transPlus

transition: TNAME TO_TOK TNAME guards effects{
	$$ = new transition();
	list<char *>::iterator sit;
	int c = 0;
	for (sit = parsed_processes.back()->states.begin(); sit  !=  parsed_processes.back()->states.end(); sit++){
		if (!strncmp((*sit),$1,20)) $$->from = c;
		if (!strncmp((*sit),$3,20)) $$->to = c;
		c++;
	}
		
	$$->guards = $4;	
	$$->effects = $5;
	//printf("transition found from %s:%i to %s:%i ",$1,$$->from,$3,$$->to);
	//printf("guards %i effects %i \n",$4->size(),$5->size());
}

guards: /* empty */ {$$ = new list<form_node *>;} | GUARD_TOK formulaPlus{
	$$ = new list<form_node *>;
	$$->splice($$->begin(),formula_list);
}

effects: /* empty */ {$$ = new list<form_node *>;} | EFFECT_TOK formulaPlus{
	$$ = new list<form_node *>;
	$$->splice($$->begin(),formula_list);
}

formulaPlus: formula formulaStar {
	formula_list.push_front($1);
}

formulaStar: {} | formulaPlus;

formula:
/* assignment */ 
	variable '=' variable { $$ = new form_node(); $$->type = ASSIGN;  $$->left = $1;	$$->right = $3;	}
/* arithmetic operators */	
	| variable '+' variable { $$ = new form_node(); $$->type = PLUS;  $$->left = $1;	$$->right = $3;	}
	| variable '-' variable { $$ = new form_node(); $$->type = MINUS;  $$->left = $1;	$$->right = $3;	}
	| '-' variable { $$ = new form_node(); $$->type = NEG;  $$->left = $2;	$$->right = 0;	}
	| variable '*' variable { $$ = new form_node(); $$->type = MULT; $$->left = $1;	$$->right = $3;	}
	| variable '/' variable { $$ = new form_node(); $$->type = DIV; $$->left = $1;	$$->right = $3;	}
	| variable '%' variable { $$ = new form_node(); $$->type = MOD; $$->left = $1;	$$->right = $3;	}
/* parentheses grouping */
	| '(' variable ')' {$$ = $2}
/* relational operators */
	| variable EQ_TOK variable { $$ = new form_node(); $$->type = EQ;  $$->left = $1;	$$->right = $3;	}
	| variable NEQ_TOK variable { $$ = new form_node(); $$->type = NEQ;  $$->left = $1;	$$->right = $3;	}
	| variable LE_TOK variable { $$ = new form_node(); $$->type = LE;  $$->left = $1;	$$->right = $3;	}
	| variable GE_TOK variable { $$ = new form_node(); $$->type = GE;  $$->left = $1;	$$->right = $3;	}
	| variable AND_TOK variable { $$ = new form_node(); $$->type = AND;  $$->left = $1;	$$->right = $3;	}
	| variable OR_TOK variable { $$ = new form_node(); $$->type = OR;  $$->left = $1;	$$->right = $3;	}
	| variable BINAND_TOK variable { $$ = new form_node(); $$->type = BINAND;  $$->left = $1;	$$->right = $3;	}
	| variable BINOR_TOK variable { $$ = new form_node(); $$->type = BINOR;  $$->left = $1;	$$->right = $3;	}
	| variable '<' variable { $$ = new form_node(); $$->type = LESS;  $$->left = $1;	$$->right = $3;	}
	| variable '>' variable { $$ = new form_node(); $$->type = GREATER;  $$->left = $1;	$$->right = $3;	}
	| NOT_TOK variable { $$ = new form_node(); $$->type = NOT;  $$->left = $2; $$->right = 0;}
/* array operators */
	| variable '[' variable ']' {$1->left = $3;}
	
	
	
variable: 
	formula {$$ = $1; } 
	| STRING {	$$ = new form_node();	$$->type = VARIABLE_BYTE; $$->string = $1; $$->left = 0; $$->right =0;}
	| VALUE  {	$$ = new form_node();	$$->type = CONSTANT; $$->string = 0; $$->value= atoi($1) ; $$->left = 0; $$->right =0;}

system: SYSTEM_TOK TYPE{
	model->system = $2;
}


%%


#include "lex.dve.cc"

void yyerror (char const *s) {
	  printf ("Error: %s\n", s);
	  exit(1);
	}
