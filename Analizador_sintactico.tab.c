
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
#include <stdlib.h> // Para atoi, free

int yylex(void);
void yyerror(const char *s);
extern char *yytext;
extern FILE *yyin;
extern int yylineno;

#define MAX_SIMBOLOS 100

// --- Estructuras para la Tabla de Símbolos y Valores ---
typedef enum {
    TIPO_DESCONOCIDO, // Para errores o antes de la asignación de tipo
    TIPO_INT_VAR,     // Para distinguir de TIPO_INT_LITERAL si fuera necesario
    TIPO_VOID_VAR     // Podrías tener TIPO_CHAR_VAR, etc.
} TipoSimbolo;

typedef struct {
    char *nombre;
    TipoSimbolo tipo; // Por ahora, solo int
    int valor;        // Solo para variables int
    int inicializado; // Flag para saber si se le ha asignado un valor
} Simbolo;

Simbolo tabla_simbolos[MAX_SIMBOLOS];
int num_simbolos = 0;

// Variable global para L-value (nombre del identificador en el lado izquierdo de una asignación)
// ¡Este es un HACK y tiene limitaciones! Una mejor solución implicaría un AST.
static char* lvalue_nombre_actual = NULL;

// --- Funciones Auxiliares para la Tabla de Símbolos ---
Simbolo* buscar_simbolo(char *nombre) {
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabla_simbolos[i].nombre, nombre) == 0) {
            return &tabla_simbolos[i];
        }
    }
    return NULL;
}

void declarar_variable(char *nombre, TipoSimbolo tipo) {
    if (buscar_simbolo(nombre) != NULL) {
        char msg[256];
        sprintf(msg, "Error semantico: Redeclaracion de variable '%s'", nombre);
        yyerror(msg);
        return; // O manejar más robustamente
    }
    if (num_simbolos >= MAX_SIMBOLOS) {
        yyerror("Tabla de simbolos llena");
        exit(1); // Error fatal
    }
    tabla_simbolos[num_simbolos].nombre = strdup(nombre); // strdup crea una copia
    tabla_simbolos[num_simbolos].tipo = tipo;
    tabla_simbolos[num_simbolos].valor = 0; // Inicializar a 0 por defecto
    tabla_simbolos[num_simbolos].inicializado = 0;
    num_simbolos++;
}

void asignar_valor_variable(char *nombre, int valor_nuevo) {
    Simbolo* s = buscar_simbolo(nombre);
    if (s == NULL) {
        char msg[256];
        sprintf(msg, "Error semantico: Variable '%s' no declarada (en asignacion)", nombre);
        yyerror(msg);
        return;
    }
    if (s->tipo != TIPO_INT_VAR) { // Comprobación de tipo simple
        char msg[256];
        sprintf(msg, "Error semantico: Tipo incorrecto en asignacion a '%s'", nombre);
        yyerror(msg);
        return;
    }
    s->valor = valor_nuevo;
    s->inicializado = 1;
}

int obtener_valor_variable(char *nombre) {
    Simbolo* s = buscar_simbolo(nombre);
    if (s == NULL) {
        char msg[256];
        sprintf(msg, "Error semantico: Variable '%s' no declarada (al usar)", nombre);
        yyerror(msg);
        return 0; // Valor de error o por defecto
    }
    if (!s->inicializado) {
        char msg[256];
        sprintf(msg, "Advertencia: Variable '%s' usada sin inicializar, valor es %d", nombre, s->valor);
        yyerror(msg); // Informar, pero continuar con el valor por defecto (0)
    }
    if (s->tipo != TIPO_INT_VAR) {
         char msg[256];
        sprintf(msg, "Error semantico: Variable '%s' no es de tipo entero (al usar)", nombre);
        yyerror(msg);
        return 0;
    }
    return s->valor;
}

TipoSimbolo tipo_declaracion_actual; // Para pasar el tipo de la declaración



/* Line 189 of yacc.c  */
#line 180 "analizador_sintactico.tab.c"

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
     IDENTIFICADOR_TOKEN = 258,
     CONSTANTE_ENTERA_TOKEN = 259,
     CONSTANTE_CARACTER_TOKEN = 260,
     STRING_LITERAL_TOKEN = 261,
     CONSTANTE_FLOTANTE_TOKEN = 262,
     INT_TOKEN = 263,
     CHAR_TOKEN = 264,
     VOID_TOKEN = 265,
     IF_TOKEN = 266,
     ELSE_TOKEN = 267,
     WHILE_TOKEN = 268,
     RETURN_TOKEN = 269,
     PRINT_TOKEN = 270,
     ASIGNACION_TOKEN = 271,
     OPERADOR_SUMA_TOKEN = 272,
     OPERADOR_RESTA_TOKEN = 273,
     OPERADOR_MULTIPLICACION_TOKEN = 274,
     OPERADOR_DIVISION_TOKEN = 275,
     COMPARACION_IGUAL_TOKEN = 276,
     COMPARACION_DIFERENTE_TOKEN = 277,
     OPERADOR_MENOR_TOKEN = 278,
     OPERADOR_MAYOR_TOKEN = 279,
     OPERADOR_MENOR_IGUAL_TOKEN = 280,
     OPERADOR_MAYOR_IGUAL_TOKEN = 281,
     PARENTESIS_IZQ_TOKEN = 282,
     PARENTESIS_DER_TOKEN = 283,
     LLAVE_IZQ_TOKEN = 284,
     LLAVE_DER_TOKEN = 285,
     PUNTO_COMA_TOKEN = 286,
     COMA_TOKEN = 287,
     PUNTOS_SUSPENSIVOS_TOKEN = 288,
     UNARY_MINUS_PREC = 289,
     THEN = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 107 "analizador_sintactico.y"

    char *sval; // Para identificadores, strings literales
    int ival;   // Para los valores de las expresiones enteras



/* Line 214 of yacc.c  */
#line 258 "analizador_sintactico.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 270 "analizador_sintactico.tab.c"

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
#define YYLAST   122

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNRULES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    10,    13,    15,    17,
      21,    22,    24,    26,    30,    32,    36,    39,    40,    43,
      50,    52,    54,    56,    57,    59,    61,    63,    67,    70,
      74,    75,    77,    79,    82,    84,    86,    88,    90,    92,
      94,    96,   100,   103,   104,   106,   110,   116,   124,   130,
     134,   136,   138,   142,   144,   146,   148,   150,   154,   158,
     160,   164,   168,   172,   176,   178,   182,   186,   188,   192,
     196,   198,   201,   204,   206,   211,   213,   215,   219,   221,
     223,   224,   226,   228
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    38,    -1,    -1,    39,    -1,    40,    -1,
      39,    40,    -1,    47,    -1,    41,    -1,    48,    42,    31,
      -1,    -1,    43,    -1,    44,    -1,    43,    32,    44,    -1,
      45,    -1,    45,    16,    64,    -1,    46,     3,    -1,    -1,
      19,    46,    -1,    48,    45,    27,    49,    28,    52,    -1,
      10,    -1,     9,    -1,     8,    -1,    -1,    10,    -1,    50,
      -1,    51,    -1,    50,    32,    51,    -1,    48,    45,    -1,
      29,    53,    30,    -1,    -1,    54,    -1,    55,    -1,    54,
      55,    -1,    41,    -1,    56,    -1,    57,    -1,    59,    -1,
      60,    -1,    61,    -1,    62,    -1,    15,    63,    31,    -1,
      58,    31,    -1,    -1,    63,    -1,    29,    53,    30,    -1,
      11,    27,    63,    28,    56,    -1,    11,    27,    63,    28,
      56,    12,    56,    -1,    13,    27,    63,    28,    56,    -1,
      14,    58,    31,    -1,    64,    -1,    65,    -1,    72,    16,
      64,    -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,
      68,    21,    69,    -1,    68,    22,    69,    -1,    70,    -1,
      69,    23,    70,    -1,    69,    24,    70,    -1,    69,    25,
      70,    -1,    69,    26,    70,    -1,    71,    -1,    70,    17,
      71,    -1,    70,    18,    71,    -1,    72,    -1,    71,    19,
      72,    -1,    71,    20,    72,    -1,    73,    -1,    18,    72,
      -1,    17,    72,    -1,    74,    -1,     3,    27,    76,    28,
      -1,     3,    -1,    75,    -1,    27,    63,    28,    -1,     4,
      -1,     5,    -1,    -1,    77,    -1,    64,    -1,    77,    32,
      64,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   154,   154,   157,   159,   163,   164,   168,   169,   173,
     176,   178,   182,   183,   187,   192,   204,   217,   219,   224,
     228,   229,   230,   233,   235,   236,   240,   241,   245,   249,
     252,   254,   258,   259,   263,   264,   268,   269,   270,   271,
     272,   273,   277,   280,   282,   286,   290,   291,   295,   299,
     304,   308,   311,   325,   329,   333,   337,   338,   339,   343,
     344,   345,   346,   347,   351,   352,   353,   357,   358,   359,
     370,   371,   372,   376,   377,   386,   421,   422,   426,   430,
     437,   439,   443,   444
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFICADOR_TOKEN",
  "CONSTANTE_ENTERA_TOKEN", "CONSTANTE_CARACTER_TOKEN",
  "STRING_LITERAL_TOKEN", "CONSTANTE_FLOTANTE_TOKEN", "INT_TOKEN",
  "CHAR_TOKEN", "VOID_TOKEN", "IF_TOKEN", "ELSE_TOKEN", "WHILE_TOKEN",
  "RETURN_TOKEN", "PRINT_TOKEN", "ASIGNACION_TOKEN", "OPERADOR_SUMA_TOKEN",
  "OPERADOR_RESTA_TOKEN", "OPERADOR_MULTIPLICACION_TOKEN",
  "OPERADOR_DIVISION_TOKEN", "COMPARACION_IGUAL_TOKEN",
  "COMPARACION_DIFERENTE_TOKEN", "OPERADOR_MENOR_TOKEN",
  "OPERADOR_MAYOR_TOKEN", "OPERADOR_MENOR_IGUAL_TOKEN",
  "OPERADOR_MAYOR_IGUAL_TOKEN", "PARENTESIS_IZQ_TOKEN",
  "PARENTESIS_DER_TOKEN", "LLAVE_IZQ_TOKEN", "LLAVE_DER_TOKEN",
  "PUNTO_COMA_TOKEN", "COMA_TOKEN", "PUNTOS_SUSPENSIVOS_TOKEN",
  "UNARY_MINUS_PREC", "THEN", "$accept", "unidad_compilacion",
  "lista_declaraciones_externas_opc", "lista_declaraciones_externas",
  "declaracion_externa", "declaracion_global",
  "lista_init_declaradores_opc", "lista_init_declaradores",
  "init_declarador", "declarador", "punteros_opc", "definicion_funcion",
  "especificador_tipo", "contenido_parametros_funcion",
  "lista_real_parametros", "param_declaracion", "cuerpo_funcion",
  "lista_elementos_bloque_opc", "lista_elementos_bloque",
  "elemento_bloque", "sentencia", "sentencia_expresion", "expresion_opc",
  "sentencia_compuesta", "sentencia_seleccion", "sentencia_iteracion",
  "sentencia_salto", "expresion", "expresion_asignacion",
  "expresion_condicional", "expresion_logica_or", "expresion_logica_and",
  "expresion_igualdad", "expresion_relacional", "expresion_aditiva",
  "expresion_multiplicativa", "expresion_unaria", "expresion_postfix",
  "primaria", "constante", "lista_argumentos_opc", "lista_argumentos", 0
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
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    40,    40,    41,
      42,    42,    43,    43,    44,    44,    45,    46,    46,    47,
      48,    48,    48,    49,    49,    49,    50,    50,    51,    52,
      53,    53,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    56,    57,    58,    58,    59,    60,    60,    61,    62,
      63,    64,    64,    65,    66,    67,    68,    68,    68,    69,
      69,    69,    69,    69,    70,    70,    70,    71,    71,    71,
      72,    72,    72,    73,    73,    74,    74,    74,    75,    75,
      76,    76,    77,    77
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     1,     2,     1,     1,     3,
       0,     1,     1,     3,     1,     3,     2,     0,     2,     6,
       1,     1,     1,     0,     1,     1,     1,     3,     2,     3,
       0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     0,     1,     3,     5,     7,     5,     3,
       1,     1,     3,     1,     1,     1,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     2,     2,     1,     4,     1,     1,     3,     1,     1,
       0,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    22,    21,    20,     0,     2,     4,     5,     8,     7,
      10,     1,     6,    17,     0,    11,    12,    14,     0,    18,
       9,    17,     0,    23,    16,    13,    14,    75,    78,    79,
       0,     0,     0,    15,    51,    53,    54,    55,    56,    59,
      64,    67,    70,    73,    76,    20,    17,     0,    25,    26,
      80,    72,    71,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,     0,    82,
       0,    81,    77,    57,    67,    58,    60,    61,    62,    63,
      65,    66,    68,    69,    52,    30,    19,    27,    74,     0,
       0,     0,    43,     0,    30,    34,    10,     0,    31,    32,
      35,    36,     0,    37,    38,    39,    40,    44,    83,     0,
       0,     0,     0,     0,    29,    33,    42,     0,     0,    49,
      41,    45,    43,    43,    46,    48,    43,    47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    95,    14,    15,    16,    26,
      18,     9,    96,    47,    48,    49,    86,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,    54,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      70,    71
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -84
static const yytype_int8 yypact[] =
{
      20,   -84,   -84,   -84,     4,   -84,    20,   -84,   -84,   -84,
       2,   -84,   -84,    16,     6,    15,   -84,   -10,    57,   -84,
     -84,    16,    71,    58,   -84,   -84,    64,    60,   -84,   -84,
      71,    71,    71,   -84,   -84,   -84,   -84,    23,    39,    -6,
      22,    78,   -84,   -84,   -84,    56,    16,    73,    70,   -84,
      71,   -84,   -84,    75,   -84,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,   -84,    67,    20,   -84,
      76,    74,   -84,    39,   -84,    39,    -6,    -6,    -6,    -6,
      22,    22,   -84,   -84,   -84,     5,   -84,   -84,   -84,    71,
      80,    81,    71,    71,     5,   -84,     2,    79,     5,   -84,
     -84,   -84,    82,   -84,   -84,   -84,   -84,   -84,   -84,    71,
      71,    83,    84,    86,   -84,   -84,   -84,    77,    89,   -84,
     -84,   -84,    68,    68,    98,   -84,    68,   -84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,   -84,   105,    27,   -84,   -84,    91,    -8,
     106,   -84,     1,   -84,   -84,    50,   -84,    26,   -84,    24,
     -83,   -84,    29,   -84,   -84,   -84,   -84,   -32,   -19,   -84,
     -84,   -84,   -84,    -7,    33,    38,    -5,   -84,   -84,   -84,
     -84,   -84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -44
static const yytype_int8 yytable[] =
{
      53,    10,    17,    33,    11,   -17,    22,    10,    27,    28,
      29,    61,    62,     1,     2,     3,    90,    23,    91,    92,
      93,    13,    30,    31,    46,    51,    52,     8,     1,     2,
       3,    69,    32,     8,    94,    13,   -43,    20,    66,   124,
     125,    63,    64,   127,    55,    56,    84,    21,    73,    75,
      74,    74,    74,    74,    74,    74,    74,    74,    82,    83,
      24,   112,    57,    58,    59,    60,     1,     2,    45,    46,
     108,    27,    28,    29,    27,    28,    29,   117,   118,    90,
      22,    91,    92,    93,   -24,    30,    31,    50,    30,    31,
      76,    77,    78,    79,    65,    32,    85,    94,    32,    80,
      81,    67,    68,    72,    88,   122,    89,   109,   110,   114,
     126,    12,    25,   116,   119,   120,   121,   123,    87,    19,
     113,   111,   115
};

static const yytype_uint8 yycheck[] =
{
      32,     0,    10,    22,     0,     3,    16,     6,     3,     4,
       5,    17,    18,     8,     9,    10,    11,    27,    13,    14,
      15,    19,    17,    18,    23,    30,    31,     0,     8,     9,
      10,    50,    27,     6,    29,    19,    31,    31,    46,   122,
     123,    19,    20,   126,    21,    22,    65,    32,    55,    56,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       3,    93,    23,    24,    25,    26,     8,     9,    10,    68,
      89,     3,     4,     5,     3,     4,     5,   109,   110,    11,
      16,    13,    14,    15,    28,    17,    18,    27,    17,    18,
      57,    58,    59,    60,    16,    27,    29,    29,    27,    61,
      62,    28,    32,    28,    28,    28,    32,    27,    27,    30,
      12,     6,    21,    31,    31,    31,    30,    28,    68,    13,
      94,    92,    98
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,     9,    10,    37,    38,    39,    40,    41,    47,
      48,     0,    40,    19,    42,    43,    44,    45,    46,    46,
      31,    32,    16,    27,     3,    44,    45,     3,     4,     5,
      17,    18,    27,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    10,    48,    49,    50,    51,
      27,    72,    72,    63,    64,    21,    22,    23,    24,    25,
      26,    17,    18,    19,    20,    16,    45,    28,    32,    64,
      76,    77,    28,    69,    72,    69,    70,    70,    70,    70,
      71,    71,    72,    72,    64,    29,    52,    51,    28,    32,
      11,    13,    14,    15,    29,    41,    48,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    27,
      27,    58,    63,    53,    30,    55,    31,    63,    63,    31,
      31,    30,    28,    28,    56,    56,    12,    56
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
#line 187 "analizador_sintactico.y"
    {
        // El nombre del declarador ($1, que es IDENTIFICADOR_TOKEN) ya fue procesado
        // y la variable declarada por la acción en 'declarador'.
        // Si hubiera un inicializador como 'int a = expr;', se manejaría aquí.
      ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 192 "analizador_sintactico.y"
    {
        // lvalue_nombre_actual fue establecido por la regla 'declarador'
        if (lvalue_nombre_actual != NULL) {
            asignar_valor_variable(lvalue_nombre_actual, (yyvsp[(3) - (3)].ival));
            // No liberamos lvalue_nombre_actual aquí porque declarador lo hizo.
        } else {
            yyerror("Error interno: lvalue_nombre_actual no establecido en inicializacion de declaracion.");
        }
      ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 204 "analizador_sintactico.y"
    { // $2 es el nombre de la variable
        declarar_variable((yyvsp[(2) - (2)].sval), tipo_declaracion_actual);
        // Guardar nombre para posible asignación en init_declarador
        if(lvalue_nombre_actual) free(lvalue_nombre_actual); // Liberar el anterior si existe
        lvalue_nombre_actual = (yyvsp[(2) - (2)].sval); // $2 viene de yylval.sval, es strdup'd por lexer.
                                   // La asignación o el final de init_declarador debería liberarlo.
                                   // O, mejor, 'declarar_variable' hace su propio strdup, y aquí liberamos $2.
                                   // Asumiendo que declarar_variable hace strdup:
        // free($2); // No, porque lvalue_nombre_actual lo apunta.
        // Se liberará cuando lvalue_nombre_actual se reasigne o al final.
      ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 219 "analizador_sintactico.y"
    { /* Manejo de punteros omitido por simplicidad */ ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 228 "analizador_sintactico.y"
    { tipo_declaracion_actual = TIPO_VOID_VAR; ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 229 "analizador_sintactico.y"
    { /* tipo_declaracion_actual = TIPO_CHAR_VAR; */ yyerror("Tipo char no implementado para variables aun"); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 230 "analizador_sintactico.y"
    { tipo_declaracion_actual = TIPO_INT_VAR; ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 245 "analizador_sintactico.y"
    { /* Parametros de funcion no manejan almacenamiento aun */ ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 273 "analizador_sintactico.y"
    { printf("%d\n", (yyvsp[(2) - (3)].ival)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 290 "analizador_sintactico.y"
    { /* Logica IF no implementada */ ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 291 "analizador_sintactico.y"
    { /* Logica IF-ELSE no implementada */ ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 295 "analizador_sintactico.y"
    { /* Logica WHILE no implementada */ ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 299 "analizador_sintactico.y"
    { /* Logica RETURN no implementada */ ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 304 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 308 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 311 "analizador_sintactico.y"
    {
        if (lvalue_nombre_actual != NULL) {
            asignar_valor_variable(lvalue_nombre_actual, (yyvsp[(3) - (3)].ival));
            (yyval.ival) = (yyvsp[(3) - (3)].ival); // El resultado de una asignación es el valor asignado
            free(lvalue_nombre_actual); // Liberar el nombre que fue strdup'd
            lvalue_nombre_actual = NULL;
        } else {
            yyerror("Error: L-value requerido para asignacion.");
            (yyval.ival) = 0; // Valor de error
        }
      ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 325 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 329 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 333 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 337 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 338 "analizador_sintactico.y"
    { (yyval.ival) = ((yyvsp[(1) - (3)].ival) == (yyvsp[(3) - (3)].ival)); /* Lógica booleana simple */ ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 339 "analizador_sintactico.y"
    { (yyval.ival) = ((yyvsp[(1) - (3)].ival) != (yyvsp[(3) - (3)].ival)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 343 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 344 "analizador_sintactico.y"
    { (yyval.ival) = ((yyvsp[(1) - (3)].ival) < (yyvsp[(3) - (3)].ival)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 345 "analizador_sintactico.y"
    { (yyval.ival) = ((yyvsp[(1) - (3)].ival) > (yyvsp[(3) - (3)].ival)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 346 "analizador_sintactico.y"
    { (yyval.ival) = ((yyvsp[(1) - (3)].ival) <= (yyvsp[(3) - (3)].ival)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 347 "analizador_sintactico.y"
    { (yyval.ival) = ((yyvsp[(1) - (3)].ival) >= (yyvsp[(3) - (3)].ival)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 351 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 352 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) + (yyvsp[(3) - (3)].ival); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 353 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) - (yyvsp[(3) - (3)].ival); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 357 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 358 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) * (yyvsp[(3) - (3)].ival); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 359 "analizador_sintactico.y"
    {
        if ((yyvsp[(3) - (3)].ival) == 0) {
            yyerror("Error: Division por cero");
            (yyval.ival) = 0; // O algún valor de error
        } else {
            (yyval.ival) = (yyvsp[(1) - (3)].ival) / (yyvsp[(3) - (3)].ival);
        }
      ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 370 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 371 "analizador_sintactico.y"
    { (yyval.ival) = -(yyvsp[(2) - (2)].ival); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 372 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(2) - (2)].ival); /* + unario */ ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 376 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 377 "analizador_sintactico.y"
    {
        /* Llamada a función no implementada para devolver valor */
        yyerror("Llamadas a funcion no devuelven valor aun.");
        (yyval.ival) = 0;
        free((yyvsp[(1) - (4)].sval)); // Liberar nombre de función
      ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 386 "analizador_sintactico.y"
    { // $1 es el nombre (char*)
        // Para R-value (uso en expresión)
        (yyval.ival) = obtener_valor_variable((yyvsp[(1) - (1)].sval));

        // Para L-value (lado izquierdo de asignación)
        // Guardamos el nombre para la regla 'expresion_asignacion'
        if (lvalue_nombre_actual) free(lvalue_nombre_actual);
        lvalue_nombre_actual = (yyvsp[(1) - (1)].sval); // $1 fue strdup'd por el lexer. La regla de asignación lo liberará.
                                   // Si no hay asignación, este $1 se pierde si no lo usa obtener_valor_variable
                                   // y no hay lvalue.
                                   // Esto es complicado. 'obtener_valor_variable' no debe liberar $1.
                                   // La regla que consume IDENTIFICADOR_TOKEN es responsable de su yylval.sval.
                                   // Si esta regla es la única que usa $1 y no hay asignación, $1 se pierde.
                                   // Solución: lvalue_nombre_actual = strdup($1); free($1);
                                   // y la asignación libera lvalue_nombre_actual.
                                   // Pero $1 ya es un strdup.
                                   // La regla de asignación debe ser la dueña de liberar lvalue_nombre_actual.
                                   // Si no es una asignación, ¿quién libera lvalue_nombre_actual? Nadie.
                                   // Por eso, lvalue_nombre_actual se limpia en la regla de asignación.
                                   // Si no hay asignación, el $1 de IDENTIFICADOR_TOKEN se debería liberar aquí.
                                   // A MENOS que lvalue_nombre_actual lo "capture".

        // Revisión de la lógica de lvalue_nombre_actual y free($1):
        // 1. Lexer: yylval.sval = strdup(yytext); return IDENTIFICADOR_TOKEN; ($1 es esta copia)
        // 2. En esta regla 'primaria':
        //    $$ = obtener_valor_variable($1); // $1 (nombre) se usa para buscar.
        //    if (lvalue_nombre_actual) free(lvalue_nombre_actual); // Liberar el anterior lvalue si había.
        //    lvalue_nombre_actual = $1; // Ahora lvalue_nombre_actual apunta a la misma memoria que $1.
        //                               // NO SE DEBE HACER free($1) aquí.
        //                               // La regla de asignación usará lvalue_nombre_actual y lo liberará.
        //                               // Si no hay asignación, y este es el último uso de este ID,
        //                               // lvalue_nombre_actual podría quedar "colgando" con esta memoria
        //                               // hasta el próximo ID o el final.
        // Esto sigue siendo el punto más delicado.
      ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 421 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 422 "analizador_sintactico.y"
    { (yyval.ival) = (yyvsp[(2) - (3)].ival); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 426 "analizador_sintactico.y"
    { // $1 es char*
        (yyval.ival) = atoi((yyvsp[(1) - (1)].sval));
        free((yyvsp[(1) - (1)].sval)); // Liberar el string que vino de yylval.sval
      ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 430 "analizador_sintactico.y"
    { /* No implementado para valor int */
        yyerror("Constantes char no se usan como int aun.");
        (yyval.ival) = 0;
        free((yyvsp[(1) - (1)].sval));
      ;}
    break;



/* Line 1455 of yacc.c  */
#line 1988 "analizador_sintactico.tab.c"
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
#line 447 "analizador_sintactico.y"

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s cerca de '%s' (Linea aprox: %d)\n", s, yytext, yylineno);
    // yylineno es una variable global de Flex si se configura %option yylineno
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("No se pudo abrir el archivo");
            return 1;
        }
        yyin = file;
    } else {
        yyin = stdin;
    }
    // Inicializar lvalue_nombre_actual
    lvalue_nombre_actual = NULL;

    yyparse(); // Solo una llamada para un programa completo

    // Liberar memoria de la tabla de símbolos (nombres)
    for (int i = 0; i < num_simbolos; i++) {
        free(tabla_simbolos[i].nombre);
    }
    if (lvalue_nombre_actual) { // Liberar si quedó algo sin asignar
        free(lvalue_nombre_actual);
    }


    if (yyin != stdin && yyin != NULL) {
        fclose(yyin);
    }
    printf("Interpretacion finalizada.\n");
    return 0;
}

