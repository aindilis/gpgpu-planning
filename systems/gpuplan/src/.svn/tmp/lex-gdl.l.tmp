<<<<<<< .mine

%{     
     int num_lines = 0, num_chars = 0;
     int arraysize = 0;
     int open_paren = 0;
     int lexInArrayValues = false;
          
%}
  

%x ARRAY_SEC
%x IGNORE
%x READVALUES

%x READSTRING
%x INPROCESS
%x READSTATES
%x READINIT
%x TRANSITION
%x INTRANSITION
%x READFORMULA

%x SYSTEM

%x INCOMMENT

%%

\(	return OBRACKET;
\) 	return CBRACKET;
define 	return DEFINE;
[:]*domain 	return DNAME;
problem return PNAME;
:requirements	return REQUIREMENTS_TOK;
:predicates	return PREDICATES_TOK;
:functions 	return FUNCTIONS_TOK;
:action		return ACTION_TOK;
:parameters	return PARAMETERS_TOK;
:precondition	return PRECONDITION_TOK;
:effect		return EFFECT_TOK;
:init return INIT_TOK;
:goal return GOAL_TOK;

"and"		return AND_TOK;
"not"		return NOT_TOK;
"increase"	return INC_TOK;
[a-zA-Z_]+[\.0-9a-zA-Z_-]*	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return STRING;}
[0-9]*	{yylval.number = atoi(yytext);return NUMBER;}
[ \n\t\r]


%%

int yywrap(void) {
	return 1;
}
=======

%{     
     int num_lines = 0, num_chars = 0;
     int arraysize = 0;
     int open_paren = 0;
     int lexInArrayValues = false;
          
%}
  

%x ARRAY_SEC
%x IGNORE
%x READVALUES

%x READSTRING
%x INPROCESS
%x READSTATES
%x READINIT
%x TRANSITION
%x INTRANSITION
%x READFORMULA

%x SYSTEM

%x INCOMMENT

%%

\(	return OBRACKET;
\) 	return CBRACKET;
define 	return DEFINE;
[:]*domain 	return DNAME;
problem return PNAME;
:requirements	return REQUIREMENTS_TOK;
:predicates	return PREDICATES_TOK;
:functions 	return FUNCTIONS_TOK;
:action		return ACTION_TOK;
:parameters	return PARAMETERS_TOK;
:precondition	return PRECONDITION_TOK;
:effect		return EFFECT_TOK;
:init return INIT_TOK;
:goal return GOAL_TOK;
:metric return METRIC_TOK;

"and"		return AND_TOK;
"not"		return NOT_TOK;
"="		return EQ_TOK;
">="		return GE_TOK;
"<"			return LE_TOK;
"increase"	return INC_TOK;
"decrease"	return DEC_TOK;
"preference" return PREFERENCE_TOK;
[+\-*/()=\[\]<>%;]	{return yytext[0];}
[a-zA-Z_]+[\.0-9a-zA-Z_-]*	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return STRING;}
[0-9\.]*	{yylval.number = atoi(yytext);return NUMBER;}
[ \n\t\r]


%%

int yywrap(void) {
	return 1;
}
>>>>>>> .r254
