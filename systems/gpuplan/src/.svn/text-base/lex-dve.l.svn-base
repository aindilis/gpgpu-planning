
%{     
     int num_lines = 0, num_chars = 0;
     int arraysize = 0;
     int open_paren = 0;
     int lexInProcess = false; 
     int lexInArrayValues = false;
          
%}
  

%x ARRAY_SEC
%x IGNORE
%x READVALUES

%x READPNAME
%x INPROCESS
%x READSTATES
%x READINIT
%x TRANSITION
%x INTRANSITION
%x READFORMULA

%x SYSTEM

%x INCOMMENT

%%
[ ]
\n      ++num_lines; ++num_chars;
.       ++num_chars;
"//".*  
"/*"	BEGIN INCOMMENT;

const
process		BEGIN READPNAME; return PROCESS_TOK;
system[ \t\n\r]*	{BEGIN SYSTEM; return SYSTEM_TOK;}
[a-zA-Z_]+	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); BEGIN ARRAY_SEC; return TYPE;}


<ARRAY_SEC>{
[a-zA-Z_]+[0-9a-zA-Z_]*	{arraysize = 1;yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return NAME;}
"["[0-9]+"]" {char num[yyleng-2]; memcpy(num,yytext+1,yyleng-2); yylval.number = atoi(num); return SIZE;}
=	BEGIN READVALUES;
;	{if (lexInProcess) BEGIN INPROCESS; else BEGIN INITIAL; return END_TOK;}
[ \t\n\r]
}

<READVALUES>{
[{]		{lexInArrayValues = true;}
[a-zA-Z0-9]*	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return VALUE;}
;	{if (lexInProcess) BEGIN INPROCESS; else BEGIN INITIAL; return END_TOK;}
[}]	{lexInArrayValues = false; BEGIN ARRAY_SEC;}
,	{if (!lexInArrayValues) BEGIN ARRAY_SEC;}
[ \n\t\r{]
}

<READPNAME>{
[a-zA-Z_]+[0-9a-zA-Z_]*	{lexInProcess = true; yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return PNAME;}
\{		{open_paren++;BEGIN INPROCESS;}
[ \n\t\r]
}

<INPROCESS>{
state	{BEGIN READSTATES; return STATE_TOK;}
init	BEGIN READINIT;
accept  BEGIN READINIT;
trans	{BEGIN TRANSITION; return TRANS_TOK;}
[a-zA-Z_]+	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); BEGIN ARRAY_SEC; return TYPE;}
\{		open_paren++;
\}		{open_paren--; if (open_paren == 0) {lexInProcess = false; BEGIN INITIAL;}}
.
[ \n\t\r]
}

<READSTATES>{
[ ,\n\t\r]
[a-zA-Z_]+[0-9a-zA-Z_]*	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return NAME;}
; 		{BEGIN INPROCESS; return END_TOK;}
.
}
<READINIT>{
[ \n\t\r]
[a-zA-Z_]+[0-9a-zA-Z_]*	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return INAME;}
; 		BEGIN INPROCESS;
}

<TRANSITION>{
"//".*	
[a-zA-Z_]+[0-9a-zA-Z_]*	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return TNAME;}
->	return TO_TOK;
[ ,\n\t\r]
\{	BEGIN INTRANSITION;
; 	BEGIN INPROCESS; 
}
	
<INTRANSITION>{
guard	{BEGIN READFORMULA; return GUARD_TOK;}
effect	{BEGIN READFORMULA; return EFFECT_TOK;}
\}	BEGIN TRANSITION;
[ ,\n\t\r]
}

<READFORMULA>{
;	BEGIN INTRANSITION;
[ ,\n\t\r]
[+\-*/()=\[\]<>%]	{return yytext[0];}
"!="			{return NEQ_TOK;}
"=="			{return EQ_TOK;}
"<="			{return LE_TOK;}
">="			{return GE_TOK;}
"&&"			{return AND_TOK;}
"||"			{return OR_TOK;}
"&"			{return BINAND_TOK;}
"and"			{return BINAND_TOK;}
"|"			{return BINOR_TOK;}
"or"			{return BINOR_TOK;}
"not"			{return NOT_TOK;}
[0-9]+	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return VALUE;}
[a-zA-Z_0-9]+	{yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return STRING;}
}

<SYSTEM>{
[a-zA-Z_0-9]* {if (!open_paren) {yylval.strings = (char*) malloc(sizeof(char) * (yyleng + 1));sprintf(yylval.strings, "%s\0", yytext); return TYPE;}}
;	BEGIN INITIAL;
[ \n\t\r] 
}

<INCOMMENT>{
"*/"	BEGIN INITIAL;
.
[ \n\t\r]
}

<IGNORE>{
.
[ \n\t\r]
}

%%

int yywrap(void) {
	return 1;
}


