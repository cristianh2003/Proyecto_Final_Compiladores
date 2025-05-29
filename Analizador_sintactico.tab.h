
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 34 "analizador_sintactico.y"

    typedef enum TipoSimbolo {
        TIPO_DESCONOCIDO, TIPO_INT_VAR, TIPO_CHAR_PTR_VAR, TIPO_VOID_VAR,
        TIPO_VOID_FUNC, TIPO_INT_FUNC, TIPO_BUILTIN_FUNC
    } TipoSimbolo;



/* Line 1676 of yacc.c  */
#line 49 "analizador_sintactico.tab.h"

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

/* Line 1676 of yacc.c  */
#line 53 "analizador_sintactico.y"

    char *sval;
    int ival;
    struct { char* nombre; TipoSimbolo tipo; } decl_info;



/* Line 1676 of yacc.c  */
#line 107 "analizador_sintactico.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


