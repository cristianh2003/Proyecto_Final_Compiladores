
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
#line 1 "analizador_sintactico.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int yylex(void);
void yyerror(const char *s);

extern char *yytext;        // Texto actual del token analizado
extern int yylineno;        // Número de línea actual del analizador léxico
extern FILE *yyin;          // Archivo de entrada para el analizador léxico
 
#define MAX_SIMBOLOS 100    // Número máximo de símbolos que se pueden declarar
#define MODO_STACK_SIZE 100 // Tamaño máximo de la pila de modo de ejecución

int modo_ejecucion_stack[MODO_STACK_SIZE];
int modo_ejecucion_stack_ptr = 0;

int get_modo(void);
void push_modo(int nuevo_modo);
void pop_modo(void);

typedef enum TipoSimbolo TipoSimbolo;
typedef struct Simbolo Simbolo;

Simbolo* buscar_simbolo(const char *nombre);
void declarar_simbolo(char *nombre_sim, TipoSimbolo tipo, int es_externa);
void asignar_valor_int_variable(const char *nombre_var, int valor_nuevo);
int obtener_valor_int_variable(const char *nombre_var);



/* Line 189 of yacc.c  */
#line 107 "analizador_sintactico.tab.c"

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

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 34 "analizador_sintactico.y"

    typedef enum TipoSimbolo {
        TIPO_DESCONOCIDO, TIPO_INT_VAR, TIPO_CHAR_PTR_VAR, TIPO_VOID_VAR,
        TIPO_VOID_FUNC, TIPO_INT_FUNC, TIPO_BUILTIN_FUNC
    } TipoSimbolo;



/* Line 209 of yacc.c  */
#line 140 "analizador_sintactico.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFICADOR_TOKEN = 258,
     CONSTANTE_ENTERA_TOKEN = 259,
     CONSTANTE_CARACTER_TOKEN = 260,
     STRING_LITERAL_TOKEN = 261,
     INT_TOKEN = 262,
     CHAR_TOKEN = 263,
     VOID_TOKEN = 264,
     IF_TOKEN = 265,
     ELSE_TOKEN = 266,
     WHILE_TOKEN = 267,
     RETURN_TOKEN = 268,
     ASIGNACION_TOKEN = 269,
     OPERADOR_SUMA_TOKEN = 270,
     OPERADOR_RESTA_TOKEN = 271,
     OPERADOR_MULTIPLICACION_TOKEN = 272,
     OPERADOR_DIVISION_TOKEN = 273,
     COMPARACION_IGUAL_TOKEN = 274,
     COMPARACION_DIFERENTE_TOKEN = 275,
     OPERADOR_MENOR_TOKEN = 276,
     OPERADOR_MAYOR_TOKEN = 277,
     OPERADOR_MENOR_IGUAL_TOKEN = 278,
     OPERADOR_MAYOR_IGUAL_TOKEN = 279,
     PARENTESIS_IZQ_TOKEN = 280,
     PARENTESIS_DER_TOKEN = 281,
     LLAVE_IZQ_TOKEN = 282,
     LLAVE_DER_TOKEN = 283,
     PUNTO_COMA_TOKEN = 284,
     COMA_TOKEN = 285,
     PUNTOS_SUSPENSIVOS_TOKEN = 286,
     UNARY_MINUS_PREC = 287,
     IFX_NO_ELSE = 288
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 53 "analizador_sintactico.y"

    char *sval;
    int ival;
    struct { char* nombre; TipoSimbolo tipo; } decl_info;



/* Line 214 of yacc.c  */
#line 198 "analizador_sintactico.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 210 "analizador_sintactico.tab.c"
/* Unqualified %code blocks.  */

/* Line 265 of yacc.c  */
#line 41 "analizador_sintactico.y"

    typedef struct Simbolo {
        char *nombre; TipoSimbolo tipo; int es_funcion_externa;
        int valor_int; char* valor_sval; int inicializado;
    } Simbolo;

    Simbolo tabla_simbolos[MAX_SIMBOLOS];
    int num_simbolos = 0;
    static char* lvalue_nombre_actual = NULL;
    static TipoSimbolo tipo_especificado_actual;



/* Line 265 of yacc.c  */
#line 229 "analizador_sintactico.tab.c"

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNRULES -- Number of states.  */
#define YYNSTATES  123

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    10,    13,    15,    17,
      21,    22,    24,    26,    30,    32,    36,    39,    45,    46,
      47,    51,    52,    54,    56,    58,    62,    65,    67,    69,
      73,    75,    77,    79,    80,    85,    86,    88,    90,    93,
      95,    97,    99,   101,   103,   105,   107,   110,   111,   113,
     115,   118,   119,   125,   130,   136,   140,   142,   144,   148,
     150,   152,   154,   156,   160,   164,   166,   170,   174,   178,
     182,   184,   188,   192,   194,   198,   202,   204,   207,   210,
     212,   217,   219,   221,   225,   227
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    36,    -1,    -1,    37,    -1,    38,    -1,
      37,    38,    -1,    49,    -1,    39,    -1,    50,    40,    29,
      -1,    -1,    41,    -1,    42,    -1,    41,    30,    42,    -1,
      43,    -1,    43,    14,    66,    -1,    44,     3,    -1,    44,
       3,    25,    46,    26,    -1,    -1,    -1,    17,    45,    44,
      -1,    -1,     9,    -1,    47,    -1,    48,    -1,    47,    30,
      48,    -1,    50,    43,    -1,    50,    -1,    31,    -1,    50,
      43,    51,    -1,     9,    -1,     8,    -1,     7,    -1,    -1,
      27,    52,    53,    28,    -1,    -1,    54,    -1,    55,    -1,
      54,    55,    -1,    39,    -1,    56,    -1,    57,    -1,    59,
      -1,    60,    -1,    63,    -1,    64,    -1,    58,    29,    -1,
      -1,    65,    -1,    51,    -1,    62,    56,    -1,    -1,    62,
      56,    11,    61,    56,    -1,    10,    25,    65,    26,    -1,
      12,    25,    65,    26,    56,    -1,    13,    58,    29,    -1,
      66,    -1,    67,    -1,    76,    14,    66,    -1,    68,    -1,
      69,    -1,    70,    -1,    71,    -1,    70,    19,    71,    -1,
      70,    20,    71,    -1,    72,    -1,    71,    21,    72,    -1,
      71,    22,    72,    -1,    71,    23,    72,    -1,    71,    24,
      72,    -1,    73,    -1,    72,    15,    73,    -1,    72,    16,
      73,    -1,    74,    -1,    73,    17,    74,    -1,    73,    18,
      74,    -1,    75,    -1,    16,    74,    -1,    15,    74,    -1,
      76,    -1,     3,    25,    78,    26,    -1,     3,    -1,    77,
      -1,    25,    65,    26,    -1,     4,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,    97,    97,    98,    98,   100,   100,   102,
     103,   103,   104,   104,   107,   110,   117,   121,   130,   130,
     130,   132,   132,   132,   133,   133,   134,   135,   136,   139,
     142,   143,   144,   148,   148,   153,   153,   154,   154,   155,
     155,   158,   159,   160,   161,   162,   165,   166,   166,   167,
     170,   177,   174,   187,   197,   198,   200,   202,   203,   213,
     214,   215,   218,   219,   220,   223,   224,   225,   226,   227,
     230,   231,   232,   235,   236,   237,   242,   243,   244,   248,
     249,   266,   271,   272,   275,   277
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFICADOR_TOKEN",
  "CONSTANTE_ENTERA_TOKEN", "CONSTANTE_CARACTER_TOKEN",
  "STRING_LITERAL_TOKEN", "INT_TOKEN", "CHAR_TOKEN", "VOID_TOKEN",
  "IF_TOKEN", "ELSE_TOKEN", "WHILE_TOKEN", "RETURN_TOKEN",
  "ASIGNACION_TOKEN", "OPERADOR_SUMA_TOKEN", "OPERADOR_RESTA_TOKEN",
  "OPERADOR_MULTIPLICACION_TOKEN", "OPERADOR_DIVISION_TOKEN",
  "COMPARACION_IGUAL_TOKEN", "COMPARACION_DIFERENTE_TOKEN",
  "OPERADOR_MENOR_TOKEN", "OPERADOR_MAYOR_TOKEN",
  "OPERADOR_MENOR_IGUAL_TOKEN", "OPERADOR_MAYOR_IGUAL_TOKEN",
  "PARENTESIS_IZQ_TOKEN", "PARENTESIS_DER_TOKEN", "LLAVE_IZQ_TOKEN",
  "LLAVE_DER_TOKEN", "PUNTO_COMA_TOKEN", "COMA_TOKEN",
  "PUNTOS_SUSPENSIVOS_TOKEN", "UNARY_MINUS_PREC", "IFX_NO_ELSE", "$accept",
  "unidad_compilacion", "lista_declaraciones_externas_opc",
  "lista_declaraciones_externas", "declaracion_externa",
  "declaracion_global", "lista_init_declaradores_opc",
  "lista_init_declaradores", "init_declarador", "declarador_con_tipo",
  "punteros_opc", "$@1", "decl_parametros_funcion",
  "lista_real_parametros_decl", "param_declaracion_funcion",
  "definicion_funcion", "especificador_tipo", "cuerpo_funcion", "$@2",
  "lista_elementos_bloque_opc", "lista_elementos_bloque",
  "elemento_bloque", "sentencia", "sentencia_expresion", "expresion_opc",
  "sentencia_compuesta", "sentencia_seleccion", "$@3",
  "if_condition_setup", "sentencia_iteracion", "sentencia_salto",
  "expresion", "expresion_asignacion", "expresion_condicional",
  "expresion_logica_or", "expresion_logica_and", "expresion_igualdad",
  "expresion_relacional", "expresion_aditiva", "expresion_multiplicativa",
  "expresion_unaria", "expresion_postfix", "primaria",
  "constante_entera_valor", "lista_argumentos_opc", 0
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
     285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    38,    39,
      40,    40,    41,    41,    42,    42,    43,    43,    44,    45,
      44,    46,    46,    46,    47,    47,    48,    48,    48,    49,
      50,    50,    50,    52,    51,    53,    53,    54,    54,    55,
      55,    56,    56,    56,    56,    56,    57,    58,    58,    59,
      60,    61,    60,    62,    63,    64,    65,    66,    66,    67,
      68,    69,    70,    70,    70,    71,    71,    71,    71,    71,
      72,    72,    72,    73,    73,    73,    74,    74,    74,    75,
      75,    76,    76,    76,    77,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     1,     2,     1,     1,     3,
       0,     1,     1,     3,     1,     3,     2,     5,     0,     0,
       3,     0,     1,     1,     1,     3,     2,     1,     1,     3,
       1,     1,     1,     0,     4,     0,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     1,     1,
       2,     0,     5,     4,     5,     3,     1,     1,     3,     1,
       1,     1,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     2,     2,     1,
       4,     1,     1,     3,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    32,    31,    30,     0,     2,     4,     5,     8,     7,
      10,     1,     6,    19,     0,    11,    12,    14,     0,    18,
       9,    18,     0,    33,    29,    16,    20,    13,    14,    81,
      84,     0,     0,     0,    15,    57,    59,    60,    61,    62,
      65,    70,    73,    76,    79,    82,    35,    21,    85,    78,
      79,    77,     0,    56,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,    39,    10,
      49,     0,    36,    37,    40,    41,     0,    42,    43,    47,
      44,    45,    48,    30,    28,     0,    23,    24,    27,     0,
      83,    63,    64,    66,    67,    68,    69,    71,    72,    74,
      75,    58,     0,     0,     0,    34,    38,    46,    50,    17,
       0,    26,    80,     0,     0,    55,    51,    25,    53,    47,
      47,    54,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    14,    15,    16,    28,
      18,    19,    85,    86,    87,     9,    10,    70,    46,    71,
      72,    73,    74,    75,    76,    77,    78,   120,    79,    80,
      81,    82,    53,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    50,    45,    89
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int8 yypact[] =
{
      92,   -72,   -72,   -72,    20,   -72,    92,   -72,   -72,   -72,
       9,   -72,   -72,   -72,    -6,    -5,   -72,    13,    25,    15,
     -72,    15,    79,   -72,   -72,     5,   -72,   -72,    22,    14,
     -72,    79,    79,    79,   -72,   -72,   -72,   -72,    83,    63,
      50,    88,   -72,   -72,    27,   -72,     6,    46,   -72,   -72,
     -72,   -72,     8,   -72,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    19,    21,    79,   -72,     9,
     -72,    28,     6,   -72,   -72,   -72,    30,   -72,   -72,    48,
     -72,   -72,   -72,    36,   -72,    52,    44,   -72,     9,    67,
     -72,    63,    63,    50,    50,    50,    50,    88,    88,   -72,
     -72,   -72,    79,    79,    47,   -72,   -72,   -72,    85,   -72,
      61,   -72,   -72,    86,    87,   -72,   -72,   -72,   -72,    48,
      48,   -72,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -72,   -72,   -72,   -72,   105,   -29,   -72,   -72,    93,    -9,
      96,   -72,   -72,   -72,     7,   -72,   -43,    99,   -72,   -72,
     -72,    51,   -71,   -72,    54,   -72,   -72,   -72,   -72,   -72,
     -72,   -31,   -17,   -72,   -72,   -72,   -72,    53,    32,    49,
     -25,   -72,   -22,   -72,   -72
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -48
static const yytype_int8 yytable[] =
{
      44,    17,    52,    69,    88,    34,    49,    51,   108,    29,
      30,    44,   -18,     1,     2,     3,    65,    68,    66,    67,
      11,    31,    32,    20,    44,    21,    13,    22,    25,    69,
      47,    33,    13,    23,    90,   -47,    22,    99,   100,    48,
      23,    64,    44,    68,   102,    44,   103,   101,   121,   122,
      44,    29,    30,     1,     2,    83,   105,    44,    65,   107,
      66,    67,   -22,    31,    32,    60,    61,    88,     1,     2,
       3,   113,   114,    33,   110,    23,   115,    84,   109,   111,
      44,    44,    29,    30,    56,    57,    58,    59,    93,    94,
      95,    96,    84,   112,    31,    32,   116,    44,    44,     1,
       2,     3,    54,    55,    33,    62,    63,    91,    92,    97,
      98,    12,   118,   119,    27,    26,    24,   117,     0,     0,
       0,   104,     0,   106
};

static const yytype_int8 yycheck[] =
{
      22,    10,    33,    46,    47,    22,    31,    32,    79,     3,
       4,    33,     3,     7,     8,     9,    10,    46,    12,    13,
       0,    15,    16,    29,    46,    30,    17,    14,     3,    72,
      25,    25,    17,    27,    26,    29,    14,    62,    63,    25,
      27,    14,    64,    72,    25,    67,    25,    64,   119,   120,
      72,     3,     4,     7,     8,     9,    28,    79,    10,    29,
      12,    13,    26,    15,    16,    15,    16,   110,     7,     8,
       9,   102,   103,    25,    30,    27,    29,    31,    26,    88,
     102,   103,     3,     4,    21,    22,    23,    24,    56,    57,
      58,    59,    31,    26,    15,    16,    11,   119,   120,     7,
       8,     9,    19,    20,    25,    17,    18,    54,    55,    60,
      61,     6,    26,    26,    21,    19,    17,   110,    -1,    -1,
      -1,    67,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    35,    36,    37,    38,    39,    49,
      50,     0,    38,    17,    40,    41,    42,    43,    44,    45,
      29,    30,    14,    27,    51,     3,    44,    42,    43,     3,
       4,    15,    16,    25,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    52,    25,    25,    74,
      76,    74,    65,    66,    19,    20,    21,    22,    23,    24,
      15,    16,    17,    18,    14,    10,    12,    13,    39,    50,
      51,    53,    54,    55,    56,    57,    58,    59,    60,    62,
      63,    64,    65,     9,    31,    46,    47,    48,    50,    78,
      26,    71,    71,    72,    72,    72,    72,    73,    73,    74,
      74,    66,    25,    25,    58,    28,    55,    29,    56,    26,
      30,    43,    26,    65,    65,    29,    11,    48,    26,    26,
      61,    56,    56
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
        case 14:

/* Line 1455 of yacc.c  */
#line 107 "analizador_sintactico.y"
    {
        declarar_simbolo((yyvsp[(1) - (1)].decl_info).nombre, (yyvsp[(1) - (1)].decl_info).tipo, ((yyvsp[(1) - (1)].decl_info).tipo == TIPO_INT_FUNC || (yyvsp[(1) - (1)].decl_info).tipo == TIPO_VOID_FUNC || (yyvsp[(1) - (1)].decl_info).tipo == TIPO_BUILTIN_FUNC));
      ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 110 "analizador_sintactico.y"
    {
        if ((yyvsp[(1) - (3)].decl_info).tipo != TIPO_INT_VAR) { yyerror("Solo se pueden inicializar variables enteras en declaracion."); free((yyvsp[(1) - (3)].decl_info).nombre); }
        else { declarar_simbolo((yyvsp[(1) - (3)].decl_info).nombre, (yyvsp[(1) - (3)].decl_info).tipo, 0); asignar_valor_int_variable((yyvsp[(1) - (3)].decl_info).nombre, (yyvsp[(3) - (3)].ival)); }
      ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 117 "analizador_sintactico.y"
    {
        (yyval.decl_info).nombre = (yyvsp[(2) - (2)].sval);
        (yyval.decl_info).tipo = tipo_especificado_actual;
      ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 121 "analizador_sintactico.y"
    {
        (yyval.decl_info).nombre = (yyvsp[(2) - (5)].sval);
        if (tipo_especificado_actual == TIPO_INT_VAR) (yyval.decl_info).tipo = TIPO_INT_FUNC;
        else if (tipo_especificado_actual == TIPO_VOID_VAR) (yyval.decl_info).tipo = TIPO_VOID_FUNC;
        else if (tipo_especificado_actual == TIPO_CHAR_PTR_VAR) { (yyval.decl_info).tipo = TIPO_DESCONOCIDO; }
        else (yyval.decl_info).tipo = TIPO_DESCONOCIDO;
      ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 130 "analizador_sintactico.y"
    { tipo_especificado_actual = TIPO_CHAR_PTR_VAR; ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 134 "analizador_sintactico.y"
    { free((yyvsp[(2) - (2)].decl_info).nombre); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 142 "analizador_sintactico.y"
    { tipo_especificado_actual = TIPO_VOID_VAR; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 143 "analizador_sintactico.y"
    { tipo_especificado_actual = TIPO_CHAR_PTR_VAR; ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 148 "analizador_sintactico.y"
    { push_modo(get_modo()); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 150 "analizador_sintactico.y"
    { pop_modo(); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 158 "analizador_sintactico.y"
    { (yyval.ival) = 0; ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 159 "analizador_sintactico.y"
    { (yyval.ival) = 0; ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 160 "analizador_sintactico.y"
    { (yyval.ival) = 0; ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 161 "analizador_sintactico.y"
    { (yyval.ival) = 0; ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 162 "analizador_sintactico.y"
    { (yyval.ival) = 0; ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 166 "analizador_sintactico.y"
    { (yyval.ival) = 0; ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 166 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 172 "analizador_sintactico.y"
    { pop_modo(); (yyval.ival) = 0; ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 177 "analizador_sintactico.y"
    {
          pop_modo();
          int outer_can_execute = get_modo();
          push_modo(outer_can_execute && !((yyvsp[(1) - (3)].ival)));
      ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 183 "analizador_sintactico.y"
    { pop_modo(); (yyval.ival) = 0; ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 188 "analizador_sintactico.y"
    {
          int outer_can_execute = get_modo();
          int condition_is_true = 0;
          if (outer_can_execute) { condition_is_true = ((yyvsp[(3) - (4)].ival) != 0); }
          push_modo(outer_can_execute && condition_is_true);
          (yyval.ival) = condition_is_true;
      ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 197 "analizador_sintactico.y"
    { (yyval.ival) = 0;;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 198 "analizador_sintactico.y"
    { (yyval.ival) = 0;;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 200 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 202 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 203 "analizador_sintactico.y"
    {
        if (get_modo()) {
            if (lvalue_nombre_actual != NULL) {
                asignar_valor_int_variable(lvalue_nombre_actual, (yyvsp[(3) - (3)].ival)); (yyval.ival) = (yyvsp[(3) - (3)].ival);
                free(lvalue_nombre_actual); lvalue_nombre_actual = NULL;
            } else { yyerror("Error Semantico: L-value requerido para asignacion."); (yyval.ival) = 0; }
        } else { (yyval.ival) = 0; if (lvalue_nombre_actual) {free(lvalue_nombre_actual); lvalue_nombre_actual=NULL;} }
      ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 213 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 214 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 215 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 218 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 219 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) == (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 220 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) != (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 223 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 224 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) < (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 225 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) > (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 226 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) <= (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 227 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) >= (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 230 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 231 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) + (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 232 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) - (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 235 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 236 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? ((yyvsp[(1) - (3)].ival) * (yyvsp[(3) - (3)].ival)) : 0; ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 237 "analizador_sintactico.y"
    {
        if (get_modo()) { if ((yyvsp[(3) - (3)].ival) == 0) { yyerror("Error Semantico: Division por cero."); (yyval.ival) = 0; } else { (yyval.ival) = (yyvsp[(1) - (3)].ival) / (yyvsp[(3) - (3)].ival); } } else { (yyval.ival) = 0; }
      ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 242 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 243 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? (-(yyvsp[(2) - (2)].ival)) : 0; ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 244 "analizador_sintactico.y"
    { (yyval.ival) = get_modo() ? (yyvsp[(2) - (2)].ival) : 0; ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 248 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 249 "analizador_sintactico.y"
    {
        if (get_modo()) {
            Simbolo* func = buscar_simbolo((yyvsp[(1) - (4)].sval));
            if (func) {
                yyerror("Llamadas a funciones definidas por el usuario (con o sin argumentos) no implementadas completamente para ejecucion."); (yyval.ival) = 0;
            } else {
                char msg[256]; sprintf(msg, "Error Semantico: Funcion '%s' no declarada.", (yyvsp[(1) - (4)].sval)); yyerror(msg); (yyval.ival) = 0;
            }
            if ((yyvsp[(1) - (4)].sval)) free((yyvsp[(1) - (4)].sval)); // Liberar nombre de función
        } else {
            (yyval.ival) = 0;
            if ((yyvsp[(1) - (4)].sval)) free((yyvsp[(1) - (4)].sval));
        }
      ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 266 "analizador_sintactico.y"
    {
        (yyval.ival) = obtener_valor_int_variable((yyvsp[(1) - (1)].sval));
        if (lvalue_nombre_actual) free(lvalue_nombre_actual);
        lvalue_nombre_actual = (yyvsp[(1) - (1)].sval);
      ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 271 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 272 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(2) - (3)].ival); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 275 "analizador_sintactico.y"
    { (yyval.ival) = atoi((yyvsp[(1) - (1)].sval)); free((yyvsp[(1) - (1)].sval)); ;}
    break;



/* Line 1455 of yacc.c  */
#line 1974 "analizador_sintactico.tab.c"
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
#line 279 "analizador_sintactico.y"
 // SECCIÓN DE CÓDIGO C ADICIONAL 

int get_modo(void) {
    if (modo_ejecucion_stack_ptr > 0) return modo_ejecucion_stack[modo_ejecucion_stack_ptr - 1];
    return 1;
}
void push_modo(int nuevo_modo) {
    if (modo_ejecucion_stack_ptr < MODO_STACK_SIZE) modo_ejecucion_stack[modo_ejecucion_stack_ptr++] = nuevo_modo;
    else yyerror("Desbordamiento de la pila de modo de ejecucion");
}
void pop_modo(void) {
    if (modo_ejecucion_stack_ptr > 0) modo_ejecucion_stack_ptr--;
}

Simbolo* buscar_simbolo(const char *nombre) {
    for (int i = num_simbolos - 1; i >= 0; i--) {
        if (tabla_simbolos[i].nombre && strcmp(tabla_simbolos[i].nombre, nombre) == 0) return &tabla_simbolos[i];
    }
    return NULL;
}
void declarar_simbolo(char *nombre_sim, TipoSimbolo tipo, int es_externa) {
    Simbolo* existente = buscar_simbolo(nombre_sim);
    if (existente != NULL) {
        if (es_externa && existente->es_funcion_externa && existente->tipo == tipo) { free(nombre_sim); return; } 
        char msg[256]; sprintf(msg, "Error Semantico: Redeclaracion de '%s'", nombre_sim); yyerror(msg); free(nombre_sim); return;
    }
    if (num_simbolos >= MAX_SIMBOLOS) { yyerror("Tabla de simbolos llena"); free(nombre_sim); exit(1); }
    tabla_simbolos[num_simbolos].nombre = nombre_sim;
    tabla_simbolos[num_simbolos].tipo = tipo;
    tabla_simbolos[num_simbolos].es_funcion_externa = es_externa;
    tabla_simbolos[num_simbolos].inicializado = 0;
    tabla_simbolos[num_simbolos].valor_int = 0;
    tabla_simbolos[num_simbolos].valor_sval = NULL;
    num_simbolos++;
}
void asignar_valor_int_variable(const char *nombre_var, int valor_nuevo) {
    if (!get_modo()) return;
    Simbolo* s = buscar_simbolo(nombre_var);
    if (!s) { char msg[256]; sprintf(msg, "Error Semantico: Variable '%s' no declarada (asignacion)", nombre_var); yyerror(msg); return; }
    if (s->tipo != TIPO_INT_VAR) { char msg[256]; sprintf(msg, "Error Semantico: Variable '%s' no es int (asignacion)", nombre_var); yyerror(msg); return; }
    s->valor_int = valor_nuevo; s->inicializado = 1;
}
int obtener_valor_int_variable(const char *nombre_var) {
    Simbolo* s = buscar_simbolo(nombre_var);
    if (!s) { char msg[256]; sprintf(msg, "Error Semantico: Variable '%s' no declarada (uso)", nombre_var); yyerror(msg); return 0; }
    if (s->tipo != TIPO_INT_VAR) { char msg[256]; sprintf(msg, "Error Semantico: Variable '%s' no es int (uso)", nombre_var); yyerror(msg); return 0; }
    return s->valor_int;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s cerca de '%s' (Linea: %d)\n", s, yytext, yylineno);
    while(modo_ejecucion_stack_ptr > 0) pop_modo(); // Limpiar pila de modo para evitar ejecución incorrecta
    push_modo(0); // Poner en modo "no ejecutar"
}

int main(int argc, char *argv[]) {
    lvalue_nombre_actual = NULL;
    modo_ejecucion_stack_ptr = 0;
    push_modo(1); // Iniciar en modo ejecución


    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror("No se pudo abrir el archivo"); return 1; }
    } else { yyin = stdin; }

    yyparse();

    // Limpieza de la tabla de símbolos
    for (int i = 0; i < num_simbolos; i++) {
        if (tabla_simbolos[i].nombre != NULL) { free(tabla_simbolos[i].nombre); tabla_simbolos[i].nombre = NULL; }
        if (tabla_simbolos[i].valor_sval != NULL) { free(tabla_simbolos[i].valor_sval); tabla_simbolos[i].valor_sval = NULL; }
    }
    if (lvalue_nombre_actual != NULL) { free(lvalue_nombre_actual); lvalue_nombre_actual = NULL; }

    if (yyin != stdin && yyin != NULL) fclose(yyin);
    
    if (modo_ejecucion_stack_ptr > 0) pop_modo(); // Asegurarse de que la pila de modo quede balanceada
    return 0;
}
