<<<<<<< .mine

/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "gdl.y"


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



/* Line 189 of yacc.c  */
#line 98 "gdl.tab.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OBRACKET = 258,
     CBRACKET = 259,
     DEFINE = 260,
     REQUIREMENTS_TOK = 261,
     PREDICATES_TOK = 262,
     FUNCTIONS_TOK = 263,
     ACTION_TOK = 264,
     PARAMETERS_TOK = 265,
     PRECONDITION_TOK = 266,
     EFFECT_TOK = 267,
     INIT_TOK = 268,
     GOAL_TOK = 269,
     NAME = 270,
     DNAME = 271,
     PNAME = 272,
     SNAME = 273,
     INAME = 274,
     TNAME = 275,
     TYPE = 276,
     VALUE = 277,
     FORMULA = 278,
     STRING = 279,
     OPERATOR = 280,
     SIZE = 281,
     NUMBER = 282,
     INC_TOK = 283,
     NOT_TOK = 284,
     BINOR_TOK = 285,
     BINAND_TOK = 286,
     OR_TOK = 287,
     AND_TOK = 288,
     NEQ_TOK = 289,
     EQ_TOK = 290,
     GE_TOK = 291,
     LE_TOK = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 25 "gdl.y"

	form_node * node;
	transition * trans;
	process * proc;
	list<form_node *>* node_list;
	char * strings;
	int number;

	array * arrays;
	list<array *>* array_list;
	list<transition *>* transition_list;



/* Line 214 of yacc.c  */
#line 186 "gdl.tab.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 198 "gdl.tab.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   66

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  33
/* YYNRULES -- Number of states.  */
#define YYNSTATES  91

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    45,     2,     2,
       2,     2,    43,    41,     2,    42,     2,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    29,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    30,    31,    32,    33,    34,    35,
      36,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    14,    23,    28,    33,    38,    39,
      41,    44,    49,    54,    55,    57,    60,    64,    65,    67,
      70,    72,    80,    84,    89,    94,    97,   100,   101,   103,
     106,   111,   116,   122
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    49,    48,    -1,     3,     5,    50,    51,
      65,    66,     4,    -1,     3,     5,    51,    52,    56,    55,
      60,     4,    -1,     3,    17,    24,     4,    -1,     3,    16,
      24,     4,    -1,     3,     6,    53,     4,    -1,    -1,    54,
      -1,    62,    53,    -1,     3,     8,    57,     4,    -1,     3,
       7,    57,     4,    -1,    -1,    58,    -1,    59,    57,    -1,
       3,    24,     4,    -1,    -1,    61,    -1,    63,    60,    -1,
      24,    -1,     3,     9,    24,    64,    67,    68,     4,    -1,
      10,     3,     4,    -1,     3,    13,    69,     4,    -1,     3,
      14,    69,     4,    -1,    11,    69,    -1,    12,    69,    -1,
      -1,    70,    -1,    71,    69,    -1,     3,    34,    69,     4,
      -1,     3,    30,    69,     4,    -1,     3,    28,    69,    27,
       4,    -1,     3,    24,     4,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   106,   116,   139,   141,   143,   145,   145,
     146,   148,   150,   152,   152,   154,   159,   167,   167,   169,
     174,   176,   183,   185,   189,   193,   203,   275,   275,   277,
     282,   299,   316,   336
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OBRACKET", "CBRACKET", "DEFINE",
  "REQUIREMENTS_TOK", "PREDICATES_TOK", "FUNCTIONS_TOK", "ACTION_TOK",
  "PARAMETERS_TOK", "PRECONDITION_TOK", "EFFECT_TOK", "INIT_TOK",
  "GOAL_TOK", "NAME", "DNAME", "PNAME", "SNAME", "INAME", "TNAME", "TYPE",
  "VALUE", "FORMULA", "STRING", "OPERATOR", "SIZE", "NUMBER", "INC_TOK",
  "'='", "NOT_TOK", "BINOR_TOK", "BINAND_TOK", "OR_TOK", "AND_TOK",
  "NEQ_TOK", "EQ_TOK", "'<'", "'>'", "GE_TOK", "LE_TOK", "'+'", "'-'",
  "'*'", "'/'", "'%'", "$accept", "pddl", "problem", "domain",
  "problemName", "domainName", "requirements", "requirementStar",
  "requirementPlus", "functions", "predicates", "predicateStar",
  "predicatePlus", "predicate", "actionStar", "actionPlus", "requirement",
  "action", "parameters", "init", "goal", "preconditions", "effects",
  "formulaStar", "formulaPlus", "formula", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    61,
     284,   285,   286,   287,   288,   289,   290,    60,    62,   291,
     292,    43,    45,    42,    47,    37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    49,    50,    51,    52,    53,    53,
      54,    55,    56,    57,    57,    58,    59,    60,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    69,    70,
      71,    71,    71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     7,     8,     4,     4,     4,     0,     1,
       2,     4,     4,     0,     1,     2,     3,     0,     1,     2,
       1,     7,     3,     4,     4,     2,     2,     0,     1,     2,
       4,     4,     5,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     0,
       0,     0,     6,    20,     0,     9,     8,    13,     0,    17,
       0,     0,     0,     7,    10,     0,     0,    14,    13,    13,
       0,     0,    18,    17,     5,    27,     0,     0,     0,    12,
      15,     0,     0,     4,    19,     0,     0,    28,    27,    27,
       3,    16,    11,     0,     0,    27,    27,    27,    23,    29,
       0,     0,     0,    33,     0,     0,     0,    24,     0,    27,
       0,     0,    31,    30,    22,    25,    27,     0,    32,    26,
      21
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,     3,    15,     9,    13,    24,    25,    29,
      19,    36,    37,    38,    41,    42,    26,    43,    72,    32,
      47,    80,    87,    56,    57,    58
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -59
static const yytype_int8 yypact[] =
{
       1,     0,    11,    10,    12,   -59,     9,   -59,     2,    14,
      16,    -4,    17,    19,     7,    12,    21,     3,    22,    23,
       6,    28,   -59,   -59,    29,   -59,     3,    31,    24,    32,
      33,    25,    36,   -59,   -59,    18,    37,   -59,    31,    31,
      27,    39,   -59,    32,   -59,    41,    26,    42,    43,   -59,
     -59,    44,    30,   -59,   -59,   -18,    45,   -59,    41,    41,
     -59,   -59,   -59,    35,    46,    41,    41,    41,   -59,   -59,
      47,    49,    48,   -59,    34,    51,    52,   -59,    53,    41,
      50,    54,   -59,   -59,   -59,   -59,    41,    56,   -59,   -59,
     -59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -59,   -59,   -59,   -59,   -59,    38,   -59,    40,   -59,   -59,
     -59,   -36,   -59,   -59,    20,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,   -59,   -58,   -59,   -59
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      69,    70,    50,    51,     1,     4,    64,    74,    75,    76,
      65,     5,    66,     6,    10,     8,    67,    12,    11,    14,
      16,    85,    18,    17,    20,    22,    28,    23,    89,    27,
      30,    31,    39,    33,    35,    40,    52,    44,    45,    46,
      59,    49,    48,    53,    55,    71,    60,    61,    62,    68,
      73,    77,    78,    21,    63,    82,    83,    84,    88,    79,
      90,    81,    86,    54,     0,     0,    34
};

static const yytype_int8 yycheck[] =
{
      58,    59,    38,    39,     3,     5,    24,    65,    66,    67,
      28,     0,    30,     3,     5,     3,    34,     3,    16,     3,
      24,    79,     3,     6,    17,     4,     3,    24,    86,     7,
      24,     3,     8,     4,     3,     3,     9,     4,    13,     3,
      14,     4,    24,     4,     3,    10,     4,     4,     4,     4,
       4,     4,     3,    15,    24,     4,     4,     4,     4,    11,
       4,    27,    12,    43,    -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    47,    49,     5,     0,     3,    48,     3,    51,
       5,    16,     3,    52,     3,    50,    24,     6,     3,    56,
      17,    51,     4,    24,    53,    54,    62,     7,     3,    55,
      24,     3,    65,     4,    53,     3,    57,    58,    59,     8,
       3,    60,    61,    63,     4,    13,     3,    66,    24,     4,
      57,    57,     9,     4,    60,     3,    69,    70,    71,    14,
       4,     4,     4,    24,    24,    28,    30,    34,     4,    69,
      69,    10,    64,     4,    69,    69,    69,     4,     3,    11,
      67,    27,     4,     4,     4,    69,    12,    68,     4,    69,
       4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 100 "gdl.y"
    {
	(yyvsp[(1) - (2)].proc)->transitions.push_back((yyvsp[(2) - (2)].trans));
	model->addProcess((yyvsp[(1) - (2)].proc));
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 106 "gdl.y"
    {
	//printf("initializing domain %s \n",$4);
	//printf("adding %i goals \n",(int)$6->size());
	(yyval.trans) = new transition();
	(yyval.trans)->from = 0 ; (yyval.trans)->to = 255;
	(yyval.trans)->guards = (yyvsp[(6) - (7)].node_list);
	(yyval.trans)->effects = (yyvsp[(5) - (7)].node_list); // hack, we store the initial state in the effects ;-)

;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 116 "gdl.y"
    {
	//printf("domain found, name = %s \n",$3);
	(yyval.proc) = new process();
	(yyval.proc)->name = (yyvsp[(3) - (8)].strings);
	(yyval.proc)->states.push_front((char *) "stateless");
	(yyval.proc)->initial = (char *) "stateless";
	list<array *>::iterator ait;
	//printf("found %i predicates \n",(int)$5->size());
	for (ait = (yyvsp[(5) - (8)].array_list)->begin() ; ait != (yyvsp[(5) - (8)].array_list)->end(); ait++) {
		(yyval.proc)->arrays.push_back(*ait);
	}
	//printf("found %i functions \n",(int)$6->size());
	for (ait = (yyvsp[(6) - (8)].array_list)->begin() ; ait != (yyvsp[(6) - (8)].array_list)->end(); ait++) {
		(*ait)->type=(char *)"integer";
		(yyval.proc)->arrays.push_back(*ait);
	}
	//printf("found %i actions \n",(int)$7->size());
	list<transition *>::iterator tit;
	for (tit = (yyvsp[(7) - (8)].transition_list)->begin() ; tit != (yyvsp[(7) - (8)].transition_list)->end(); tit++) {
		(yyval.proc)->transitions.push_back(*tit);
	}
;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 141 "gdl.y"
    { (yyval.strings) = (yyvsp[(3) - (4)].strings); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 145 "gdl.y"
    {;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 148 "gdl.y"
    { (yyval.array_list) = (yyvsp[(3) - (4)].array_list); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 150 "gdl.y"
    { (yyval.array_list) = (yyvsp[(3) - (4)].array_list); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 152 "gdl.y"
    {(yyval.array_list) = new list<array *>;;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 152 "gdl.y"
    { (yyval.array_list) = (yyvsp[(1) - (1)].array_list); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 154 "gdl.y"
    {
	(yyval.array_list) = (yyvsp[(2) - (2)].array_list);
	(yyval.array_list)->push_back((yyvsp[(1) - (2)].arrays));
;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 159 "gdl.y"
    {
	array * a = new array();
	a->name = (yyvsp[(2) - (3)].strings);
	a->size = 1;
	a->type = (char *) "bool";
	(yyval.arrays) = a;
;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 167 "gdl.y"
    {(yyval.transition_list) = new list<transition *>;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 167 "gdl.y"
    { (yyval.transition_list) = (yyvsp[(1) - (1)].transition_list); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 169 "gdl.y"
    {
	(yyval.transition_list) = (yyvsp[(2) - (2)].transition_list);
	(yyval.transition_list)->push_back((yyvsp[(1) - (2)].trans));
;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 176 "gdl.y"
    {
	(yyval.trans) = new transition();
	(yyval.trans)->from = (yyval.trans)->to = 0;
	(yyval.trans)->guards = (yyvsp[(5) - (7)].node_list);
	(yyval.trans)->effects = (yyvsp[(6) - (7)].node_list);
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 185 "gdl.y"
    {
		(yyval.node_list) = (yyvsp[(3) - (4)].node_list);
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 189 "gdl.y"
    {
		(yyval.node_list) = (yyvsp[(3) - (4)].node_list);
;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 193 "gdl.y"
    {
	(yyval.node_list) = (yyvsp[(2) - (2)].node_list);
	if ((yyval.node_list)->size() == 1 && !(*(yyval.node_list)->begin())->right) {
		form_node * and_helper = new form_node(CONSTANT);
		and_helper->value=1;
		(*(yyval.node_list)->begin())->right= and_helper;
	}

;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 203 "gdl.y"
    {
  (yyval.node_list) = new list<form_node *>;
	list<form_node *>::iterator fit;
	list<form_node *> stack;
	//printf("parsing %i effects \n",(int)$2->size());
	for (fit = (yyvsp[(2) - (2)].node_list)->begin(); fit != (yyvsp[(2) - (2)].node_list)->end(); fit++) {
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
					(yyval.node_list)->push_back(assign_node);
				}
				else if (node->type == PLUS) {
					form_node * assign_node = new form_node(ASSIGN);
					form_node * target_node = new form_node(node->left);
					assign_node->left=target_node;
					assign_node->right = node;
					//printf("adding effect %s = %s + %i \n",assign_node->left->string, assign_node->right->left->string, assign_node->right->right->value);
					(yyval.node_list)->push_back(assign_node);
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
					(yyval.node_list)->push_back(assign_node);
				}
				else if (node->type == PLUS) {
					form_node * assign_node = new form_node(ASSIGN);
					form_node * target_node = new form_node(node->right);
					assign_node->left=target_node;
					assign_node->right = node;
					//printf("adding effect %s = %s + %i \n",assign_node->left->string, assign_node->right->left->string, assign_node->right->right->value);
					(yyval.node_list)->push_back(assign_node);
				}
			}
			if (node->left) stack.push_back(node->left);
			if (node->right) stack.push_back(node->right);
		}
	}
;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 275 "gdl.y"
    {(yyval.node_list) = new list<form_node *>;;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 275 "gdl.y"
    { (yyval.node_list) = (yyvsp[(1) - (1)].node_list);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 277 "gdl.y"
    {
	(yyval.node_list) = (yyvsp[(2) - (2)].node_list);
	(yyval.node_list)->push_back((yyvsp[(1) - (2)].node));
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 282 "gdl.y"
    { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		(yyval.node) = new form_node(); (yyval.node)->type = AND;
		(yyval.node)->left=(yyval.node)->right=0;
		for (fit = (yyvsp[(3) - (4)].node_list)->begin(); fit != (yyvsp[(3) - (4)].node_list)->end(); fit++) {
			if (!(yyval.node)->left) (yyval.node)->left = *fit;
			else if (!(yyval.node)->right) (yyval.node)->right = *fit;
			else {
				tmp_node = (yyval.node);
				(yyval.node) = new form_node(); (yyval.node)->type = AND;
				(yyval.node)->left=(yyval.node)->right=0;
				(yyval.node)->left = tmp_node;
				(yyval.node)->right=*fit;
			}
		}	
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 299 "gdl.y"
    { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		(yyval.node) = new form_node(); (yyval.node)->type = NOT;
		(yyval.node)->left=(yyval.node)->right=0;
		for (fit = (yyvsp[(3) - (4)].node_list)->begin(); fit != (yyvsp[(3) - (4)].node_list)->end(); fit++) {
			if (!(yyval.node)->left) (yyval.node)->left = *fit;
			else if (!(yyval.node)->right) (yyval.node)->right = *fit;
			else {
				tmp_node = (yyval.node);
				(yyval.node) = new form_node(); (yyval.node)->type = NOT;
				(yyval.node)->left=(yyval.node)->right=0;
				(yyval.node)->left = tmp_node;
				(yyval.node)->right=*fit;
			}
		}	
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 316 "gdl.y"
    { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		(yyval.node) = new form_node(); (yyval.node)->type = PLUS;
		(yyval.node)->right = new form_node();
		(yyval.node)->right->type = CONSTANT;
		(yyval.node)->right->value =(yyvsp[(4) - (5)].number);
		(yyval.node)->left=0;
		for (fit = (yyvsp[(3) - (5)].node_list)->begin(); fit != (yyvsp[(3) - (5)].node_list)->end(); fit++) {
			if (!(yyval.node)->left) (yyval.node)->left = *fit;
			else if (!(yyval.node)->right) (yyval.node)->right = *fit;
			else {
				tmp_node = (yyval.node);
				(yyval.node) = new form_node(); (yyval.node)->type = PLUS;
				(yyval.node)->left=(yyval.node)->right=0;
				(yyval.node)->left = tmp_node;
				(yyval.node)->right=*fit;
			}
		}	
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 336 "gdl.y"
    { (yyval.node) = new form_node(); (yyval.node)->type = VARIABLE_BYTE; (yyval.node)->string = (yyvsp[(2) - (3)].strings) ; (yyval.node)->left = (yyval.node)->right = 0;;}
    break;



/* Line 1455 of yacc.c  */
#line 1828 "gdl.tab.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 338 "gdl.y"



#include "lex.gdl.cc"

void yyerror (char const *s) {
	  printf ("Error: %s\n", s);
	  exit(1);
}


=======

/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "gdl.y"


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



/* Line 189 of yacc.c  */
#line 100 "gdl.tab.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OBRACKET = 258,
     CBRACKET = 259,
     DEFINE = 260,
     REQUIREMENTS_TOK = 261,
     PREDICATES_TOK = 262,
     FUNCTIONS_TOK = 263,
     ACTION_TOK = 264,
     PARAMETERS_TOK = 265,
     PRECONDITION_TOK = 266,
     EFFECT_TOK = 267,
     PREFERENCE_TOK = 268,
     INIT_TOK = 269,
     GOAL_TOK = 270,
     METRIC_TOK = 271,
     NAME = 272,
     DNAME = 273,
     PNAME = 274,
     SNAME = 275,
     INAME = 276,
     TNAME = 277,
     TYPE = 278,
     VALUE = 279,
     FORMULA = 280,
     STRING = 281,
     SIZE = 282,
     NUMBER = 283,
     DEC_TOK = 284,
     INC_TOK = 285,
     NOT_TOK = 286,
     BINOR_TOK = 287,
     BINAND_TOK = 288,
     OR_TOK = 289,
     AND_TOK = 290,
     NEQ_TOK = 291,
     EQ_TOK = 292,
     GE_TOK = 293,
     LE_TOK = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 27 "gdl.y"

	form_node * node;
	transition * trans;
	process * proc;
	list<form_node *>* node_list;
	char * strings;
	int number;

	array * arrays;
	list<array *>* array_list;
	list<transition *>* transition_list;



/* Line 214 of yacc.c  */
#line 190 "gdl.tab.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 202 "gdl.tab.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   81

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNRULES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    47,     2,     2,
       2,     2,    45,    43,     2,    44,     2,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    31,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    32,    33,    34,    35,
      36,    37,    38,    41,    42
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    15,    24,    29,    34,    39,    40,
      42,    45,    46,    51,    56,    57,    59,    62,    66,    67,
      69,    72,    74,    82,    83,    85,    89,    94,    99,   100,
     102,   108,   111,   114,   115,   117,   120,   122,   124,   126,
     128,   130,   132,   134,   139,   144,   150,   156,   160
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    51,    50,    -1,     3,     5,    52,    53,
      68,    69,    70,     4,    -1,     3,     5,    53,    54,    58,
      57,    62,     4,    -1,     3,    19,    26,     4,    -1,     3,
      18,    26,     4,    -1,     3,     6,    55,     4,    -1,    -1,
      56,    -1,    64,    55,    -1,    -1,     3,     8,    59,     4,
      -1,     3,     7,    59,     4,    -1,    -1,    60,    -1,    61,
      59,    -1,     3,    26,     4,    -1,    -1,    63,    -1,    65,
      62,    -1,    26,    -1,     3,     9,    26,    66,    72,    73,
       4,    -1,    -1,    67,    -1,    10,     3,     4,    -1,     3,
      14,    74,     4,    -1,     3,    15,    74,     4,    -1,    -1,
      71,    -1,     3,    16,    26,    77,     4,    -1,    11,    74,
      -1,    12,    74,    -1,    -1,    75,    -1,    77,    74,    -1,
      30,    -1,    43,    -1,    45,    -1,    41,    -1,    38,    -1,
      29,    -1,    42,    -1,     3,    36,    74,     4,    -1,     3,
      32,    74,     4,    -1,     3,    76,    77,    77,     4,    -1,
       3,    13,    26,    77,     4,    -1,     3,    26,     4,    -1,
      28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   116,   139,   162,   164,   166,   168,   168,
     169,   172,   172,   174,   175,   175,   176,   181,   189,   189,
     191,   196,   198,   205,   205,   207,   209,   213,   217,   217,
     219,   223,   233,   305,   305,   307,   313,   314,   315,   316,
     317,   318,   319,   321,   338,   355,   361,   365,   371
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OBRACKET", "CBRACKET", "DEFINE",
  "REQUIREMENTS_TOK", "PREDICATES_TOK", "FUNCTIONS_TOK", "ACTION_TOK",
  "PARAMETERS_TOK", "PRECONDITION_TOK", "EFFECT_TOK", "PREFERENCE_TOK",
  "INIT_TOK", "GOAL_TOK", "METRIC_TOK", "NAME", "DNAME", "PNAME", "SNAME",
  "INAME", "TNAME", "TYPE", "VALUE", "FORMULA", "STRING", "SIZE", "NUMBER",
  "DEC_TOK", "INC_TOK", "'='", "NOT_TOK", "BINOR_TOK", "BINAND_TOK",
  "OR_TOK", "AND_TOK", "NEQ_TOK", "EQ_TOK", "'<'", "'>'", "GE_TOK",
  "LE_TOK", "'+'", "'-'", "'*'", "'/'", "'%'", "$accept", "pddl",
  "problem", "domain", "problemName", "domainName", "requirements",
  "requirementStar", "requirementPlus", "functions", "predicates",
  "predicateStar", "predicatePlus", "predicate", "actionStar",
  "actionPlus", "requirement", "action", "parametersStar", "parameter",
  "init", "goal", "metricStar", "metric", "preconditions", "effects",
  "formulaStar", "formulaPlus", "OPERATOR", "formula", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    61,   286,   287,   288,   289,   290,   291,   292,    60,
      62,   293,   294,    43,    45,    42,    47,    37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    51,    52,    53,    54,    55,    55,
      56,    57,    57,    58,    59,    59,    60,    61,    62,    62,
      63,    64,    65,    66,    66,    67,    68,    69,    70,    70,
      71,    72,    73,    74,    74,    75,    76,    76,    76,    76,
      76,    76,    76,    77,    77,    77,    77,    77,    77
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     8,     8,     4,     4,     4,     0,     1,
       2,     0,     4,     4,     0,     1,     2,     3,     0,     1,
       2,     1,     7,     0,     1,     3,     4,     4,     0,     1,
       5,     2,     2,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     5,     5,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,    11,
       0,     0,     6,    21,     0,     9,     8,    14,     0,    18,
       0,     0,     0,     7,    10,     0,     0,    15,    14,    14,
       0,     0,    19,    18,     5,    33,     0,    28,     0,    13,
      16,     0,     0,     4,    20,     0,    48,     0,    34,    33,
      33,     0,     0,    29,    17,    12,    23,     0,     0,    41,
      36,    33,    33,    40,    39,    42,    37,    38,     0,    26,
      35,     0,     0,     3,     0,     0,    24,     0,    47,     0,
       0,     0,    27,     0,     0,    33,     0,     0,    44,    43,
       0,     0,    25,    31,    33,     0,    46,    45,    30,    32,
      22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,     3,    15,     9,    13,    24,    25,    29,
      19,    36,    37,    38,    41,    42,    26,    43,    85,    86,
      32,    47,    62,    63,    96,   105,    57,    58,    78,    59
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int8 yypact[] =
{
       3,     4,     8,     7,    11,   -72,     6,   -72,    -1,    20,
      21,     9,    23,    30,    18,    11,    22,    12,    32,    37,
      15,    39,   -72,   -72,    40,   -72,    12,    43,    35,    44,
      45,    34,    47,   -72,   -72,    25,    48,   -72,    43,    43,
      46,    49,   -72,    44,   -72,     0,    41,    51,    53,   -72,
     -72,    54,    33,   -72,   -72,   -11,   -72,    56,   -72,     0,
       0,    50,    57,   -72,   -72,   -72,    52,    38,    59,   -72,
     -72,     0,     0,   -72,   -72,   -72,   -72,   -72,     0,   -72,
     -72,    61,    42,   -72,    64,    58,   -72,     0,   -72,    66,
      67,     0,   -72,     0,    68,     0,    62,    69,   -72,   -72,
      71,    72,   -72,   -72,     0,    73,   -72,   -72,   -72,   -72,
     -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -72,   -72,   -72,   -72,   -72,    63,   -72,    55,   -72,   -72,
     -72,   -34,   -72,   -72,    36,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -59,   -72,   -72,   -71
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      80,    81,    67,    55,    50,    51,     1,    91,     5,     4,
       6,    10,    89,    90,     8,    68,    97,    11,    69,    70,
     100,    71,   101,    12,    14,    72,    22,    73,    56,    17,
      74,    75,    76,    18,    77,    16,   103,    20,    23,    27,
      28,    30,    31,    39,    33,   109,    35,    40,    45,    44,
      46,    48,    49,    53,    61,    52,    60,    64,    65,    66,
      79,    83,    84,    88,    87,    92,    82,    94,    93,    95,
      98,    99,   102,   106,   104,   107,   108,   110,    21,    54,
       0,    34
};

static const yytype_int8 yycheck[] =
{
      59,    60,    13,     3,    38,    39,     3,    78,     0,     5,
       3,     5,    71,    72,     3,    26,    87,    18,    29,    30,
      91,    32,    93,     3,     3,    36,     4,    38,    28,     6,
      41,    42,    43,     3,    45,    26,    95,    19,    26,     7,
       3,    26,     3,     8,     4,   104,     3,     3,    14,     4,
       3,    26,     4,     4,     3,     9,    15,     4,     4,    26,
       4,     4,    10,     4,    26,     4,    16,     3,    26,    11,
       4,     4,     4,     4,    12,     4,     4,     4,    15,    43,
      -1,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    49,    51,     5,     0,     3,    50,     3,    53,
       5,    18,     3,    54,     3,    52,    26,     6,     3,    58,
      19,    53,     4,    26,    55,    56,    64,     7,     3,    57,
      26,     3,    68,     4,    55,     3,    59,    60,    61,     8,
       3,    62,    63,    65,     4,    14,     3,    69,    26,     4,
      59,    59,     9,     4,    62,     3,    28,    74,    75,    77,
      15,     3,    70,    71,     4,     4,    26,    13,    26,    29,
      30,    32,    36,    38,    41,    42,    43,    45,    76,     4,
      74,    74,    16,     4,    10,    66,    67,    26,     4,    74,
      74,    77,     4,    26,     3,    11,    72,    77,     4,     4,
      77,    77,     4,    74,    12,    73,     4,     4,     4,    74,
       4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 106 "gdl.y"
    {
	//$1->transitions.push_back($2);
	list<transition *>::iterator tit;
	for (tit = (yyvsp[(2) - (2)].transition_list)->begin() ; tit != (yyvsp[(2) - (2)].transition_list)->end(); tit++) {
		(yyvsp[(1) - (2)].proc)->transitions.push_back(*tit);
	}
	model->addProcess((yyvsp[(1) - (2)].proc));
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 116 "gdl.y"
    {
			 //printf("initializing domain %s \n",$4);
	//printf("adding %i goals \n",(int)$6->size());
	(yyval.transition_list) = new list<transition*>;
	transition * t  = new transition();
	t->from = 0 ; 
	t->to = 255;
	t->guards = (yyvsp[(6) - (8)].node_list);
	t->effects = (yyvsp[(5) - (8)].node_list); // hack, we store the initial state in the effects ;-)
	(yyval.transition_list)->push_back(t);
	if ((yyvsp[(7) - (8)].node)->left == (yyvsp[(7) - (8)].node)->right == 0) { //threre is a metric, we need to find the variables in the goal and concatenate them
		t= new transition();
		t->from = 0 ; 
		t->to = 254;
		t->guards=new list<form_node*>;
		t->effects = new list <form_node*>;
		complete_metric_node((yyvsp[(7) - (8)].node),(yyvsp[(6) - (8)].node_list));
		t->effects->push_back((yyvsp[(7) - (8)].node));
		(yyval.transition_list)->push_back(t);
	}

;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 139 "gdl.y"
    {
	//printf("domain found, name = %s \n",$3);
	(yyval.proc) = new process();
	(yyval.proc)->name = (yyvsp[(3) - (8)].strings);
	(yyval.proc)->states.push_front((char *) "stateless");
	(yyval.proc)->initial = (char *) "stateless";
	list<array *>::iterator ait;
	//printf("found %i predicates \n",(int)$5->size());
	for (ait = (yyvsp[(5) - (8)].array_list)->begin() ; ait != (yyvsp[(5) - (8)].array_list)->end(); ait++) {
		(yyval.proc)->arrays.push_back(*ait);
	}
	//printf("found %i functions \n",(int)$6->size());
	for (ait = (yyvsp[(6) - (8)].array_list)->begin() ; ait != (yyvsp[(6) - (8)].array_list)->end(); ait++) {
		(*ait)->type=(char *)"integer";
		(yyval.proc)->arrays.push_back(*ait);
	}
	//printf("found %i actions \n",(int)$7->size());
	list<transition *>::iterator tit;
	for (tit = (yyvsp[(7) - (8)].transition_list)->begin() ; tit != (yyvsp[(7) - (8)].transition_list)->end(); tit++) {
		(yyval.proc)->transitions.push_back(*tit);
	}
;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 164 "gdl.y"
    { (yyval.strings) = (yyvsp[(3) - (4)].strings); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 168 "gdl.y"
    {;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 172 "gdl.y"
    {;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 172 "gdl.y"
    { (yyval.array_list) = (yyvsp[(3) - (4)].array_list); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 174 "gdl.y"
    { (yyval.array_list) = (yyvsp[(3) - (4)].array_list); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 175 "gdl.y"
    {(yyval.array_list) = new list<array *>;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 175 "gdl.y"
    { (yyval.array_list) = (yyvsp[(1) - (1)].array_list); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 176 "gdl.y"
    {
	(yyval.array_list) = (yyvsp[(2) - (2)].array_list);
	(yyval.array_list)->push_front((yyvsp[(1) - (2)].arrays));
;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 181 "gdl.y"
    {
	array * a = new array();
	a->name = (yyvsp[(2) - (3)].strings);
	a->size = 1;
	a->type = (char *) "bool";
	(yyval.arrays) = a;
;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 189 "gdl.y"
    {(yyval.transition_list) = new list<transition *>;;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 189 "gdl.y"
    { (yyval.transition_list) = (yyvsp[(1) - (1)].transition_list); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 191 "gdl.y"
    {
	(yyval.transition_list) = (yyvsp[(2) - (2)].transition_list);
	(yyval.transition_list)->push_back((yyvsp[(1) - (2)].trans));
;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 198 "gdl.y"
    {
	(yyval.trans) = new transition();
	(yyval.trans)->from = (yyval.trans)->to = 0;
	(yyval.trans)->guards = (yyvsp[(5) - (7)].node_list);
	(yyval.trans)->effects = (yyvsp[(6) - (7)].node_list);
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 205 "gdl.y"
    {;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 209 "gdl.y"
    {
		(yyval.node_list) = (yyvsp[(3) - (4)].node_list);
;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 213 "gdl.y"
    {
		(yyval.node_list) = (yyvsp[(3) - (4)].node_list);
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 217 "gdl.y"
    {(yyval.node) = new form_node(); (yyval.node)->left = (yyval.node)->right =0;;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 217 "gdl.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 219 "gdl.y"
    {
			(yyval.node) = (yyvsp[(4) - (5)].node); 
;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 223 "gdl.y"
    {
	(yyval.node_list) = (yyvsp[(2) - (2)].node_list);
	if ((yyval.node_list)->size() == 1 && !(*(yyval.node_list)->begin())->right) {
		form_node * and_helper = new form_node(CONSTANT);
		and_helper->value=1;
		(*(yyval.node_list)->begin())->right= and_helper;
	}

;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 233 "gdl.y"
    {
  (yyval.node_list) = new list<form_node *>;
	list<form_node *>::iterator fit;
	list<form_node *> stack;
	//printf("parsing %i effects \n",(int)$2->size());
	for (fit = (yyvsp[(2) - (2)].node_list)->begin(); fit != (yyvsp[(2) - (2)].node_list)->end(); fit++) {
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
					(yyval.node_list)->push_back(assign_node);
				}
				else if (node->type == PLUS || node->type == MINUS) {
					form_node * assign_node = new form_node(ASSIGN);
					form_node * target_node = new form_node(node->left);
					assign_node->left=target_node;
					assign_node->right = node;
					//printf("adding effect %s = %s + %i \n",assign_node->left->string, assign_node->right->left->string, assign_node->right->right->value);
					(yyval.node_list)->push_back(assign_node);
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
					(yyval.node_list)->push_back(assign_node);
				}
				else if (node->type == PLUS || node->type == MINUS) {
					form_node * assign_node = new form_node(ASSIGN);
					form_node * target_node = new form_node(node->right);
					assign_node->left=target_node;
					assign_node->right = node;
					//printf("adding effect %s = %s + %i \n",assign_node->left->string, assign_node->right->left->string, assign_node->right->right->value);
					(yyval.node_list)->push_back(assign_node);
				}
			}
			if (node->left) stack.push_back(node->left);
			if (node->right) stack.push_back(node->right);
		}
	}
;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 305 "gdl.y"
    {(yyval.node_list) = new list<form_node *>;;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 305 "gdl.y"
    { (yyval.node_list) = (yyvsp[(1) - (1)].node_list);}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 307 "gdl.y"
    {
	(yyval.node_list) = (yyvsp[(2) - (2)].node_list);
	(yyval.node_list)->push_back((yyvsp[(1) - (2)].node));
;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 313 "gdl.y"
    {(yyval.number)=PLUS;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 314 "gdl.y"
    {(yyval.number)=PLUS;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 315 "gdl.y"
    {(yyval.number)=MULT;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 316 "gdl.y"
    {(yyval.number)=GE;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 317 "gdl.y"
    {(yyval.number)=ASSIGN;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 318 "gdl.y"
    {(yyval.number)=MINUS;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 319 "gdl.y"
    {(yyval.number)=LESS;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 321 "gdl.y"
    { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		(yyval.node) = new form_node(); (yyval.node)->type = AND;
		(yyval.node)->left=(yyval.node)->right=0;
		for (fit = (yyvsp[(3) - (4)].node_list)->begin(); fit != (yyvsp[(3) - (4)].node_list)->end(); fit++) {
			if (!(yyval.node)->left) (yyval.node)->left = *fit;
			else if (!(yyval.node)->right) (yyval.node)->right = *fit;
			else {
				tmp_node = (yyval.node);
				(yyval.node) = new form_node(); (yyval.node)->type = AND;
				(yyval.node)->left=(yyval.node)->right=0;
				(yyval.node)->left = tmp_node;
				(yyval.node)->right=*fit;
			}
		}	
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 338 "gdl.y"
    { 
		list<form_node *>::iterator fit;
		form_node * tmp_node;
		(yyval.node) = new form_node(); (yyval.node)->type = NOT;
		(yyval.node)->left=(yyval.node)->right=0;
		for (fit = (yyvsp[(3) - (4)].node_list)->begin(); fit != (yyvsp[(3) - (4)].node_list)->end(); fit++) {
			if (!(yyval.node)->left) (yyval.node)->left = *fit;
			else if (!(yyval.node)->right) (yyval.node)->right = *fit;
			else {
				tmp_node = (yyval.node);
				(yyval.node) = new form_node(); (yyval.node)->type = NOT;
				(yyval.node)->left=(yyval.node)->right=0;
				(yyval.node)->left = tmp_node;
				(yyval.node)->right=*fit;
			}
		}	
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 355 "gdl.y"
    { 
		(yyval.node) = new form_node(); 
		(yyval.node)->type = (yyvsp[(2) - (5)].number);
		(yyval.node)->left= (yyvsp[(3) - (5)].node);
		(yyval.node)->right = (yyvsp[(4) - (5)].node);
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 361 "gdl.y"
    { 
		(yyval.node) = (yyvsp[(4) - (5)].node);
		(yyval.node)->name = (yyvsp[(3) - (5)].strings);
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 365 "gdl.y"
    { 
		(yyval.node) = new form_node(); 
		(yyval.node)->type = VARIABLE_BYTE; 
		(yyval.node)->string = (yyvsp[(2) - (3)].strings) ; 
		(yyval.node)->left = (yyval.node)->right = 0;
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 371 "gdl.y"
    { 
		(yyval.node) = new form_node(); 
		(yyval.node)->type = CONSTANT;
		(yyval.node)->value = (yyvsp[(1) - (1)].number) ; 
		(yyval.node)->left = (yyval.node)->right = 0;
	;}
    break;



/* Line 1455 of yacc.c  */
#line 1967 "gdl.tab.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 378 "gdl.y"



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
