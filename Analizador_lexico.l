%{
#include <stdio.h>
#include <string.h>
#include "analizador_sintactico.tab.h"
%}

%option yylineno

/* ---------- DEFINICIONES REGULARES ---------- */
LETRA             [a-zA-Z_]
DIGITO            [0-9]
CARACTERES_IGNORADOS [ \t\n\r]+
COMENTARIO_BLOQUE  "/*"([^*]|\*+[^*/])*\*+"/"
IDENTIFICADOR_PATRON {LETRA}({LETRA}|{DIGITO})*
CONSTANTE_ENTERA_PATRON (0|[1-9]{DIGITO}*)
CONSTANTE_CARACTER_PATRON \'([^'\\]|\\.)\'
STRING_LITERAL_PATRON \"([^"\\]|\\.)*\"


%%
{CARACTERES_IGNORADOS}   
{COMENTARIO_BLOQUE}    

"if"                    { return IF_TOKEN; }
"else"                  { return ELSE_TOKEN; }
"while"                 { return WHILE_TOKEN; } 
"return"                { return RETURN_TOKEN; }
"int"                   { return INT_TOKEN; }
"char"                  { return CHAR_TOKEN; } 
"void"                  { return VOID_TOKEN; }

"+"                     { return OPERADOR_SUMA_TOKEN; }
"-"                     { return OPERADOR_RESTA_TOKEN; }
"*"                     { return OPERADOR_MULTIPLICACION_TOKEN; }
"/"                     { return OPERADOR_DIVISION_TOKEN; }

"="                     { return ASIGNACION_TOKEN; }
"=="                    { return COMPARACION_IGUAL_TOKEN; }
"!="                    { return COMPARACION_DIFERENTE_TOKEN; }
"<"                     { return OPERADOR_MENOR_TOKEN; }
">"                     { return OPERADOR_MAYOR_TOKEN; }
"<="                    { return OPERADOR_MENOR_IGUAL_TOKEN; }
">="                    { return OPERADOR_MAYOR_IGUAL_TOKEN; }

";"                     { return PUNTO_COMA_TOKEN; }
","                     { return COMA_TOKEN; }
"("                     { return PARENTESIS_IZQ_TOKEN; }
")"                     { return PARENTESIS_DER_TOKEN; }
"{"                     { return LLAVE_IZQ_TOKEN; }
"}"                     { return LLAVE_DER_TOKEN; }
"..."                   { return PUNTOS_SUSPENSIVOS_TOKEN; } 

{IDENTIFICADOR_PATRON} {
    yylval.sval = strdup(yytext);
    return IDENTIFICADOR_TOKEN;
}

{CONSTANTE_ENTERA_PATRON} {
    yylval.sval = strdup(yytext);
    return CONSTANTE_ENTERA_TOKEN;
}

{CONSTANTE_CARACTER_PATRON} {
    yylval.sval = strdup(yytext);
    return CONSTANTE_CARACTER_TOKEN;
}

{STRING_LITERAL_PATRON} {
    yylval.sval = strdup(yytext);
    return STRING_LITERAL_TOKEN;
}

.   { fprintf(stderr, "LEX_ERROR: Unknown char '%c' (ASCII: %d) en linea %d\n", yytext[0], yytext[0], yylineno); }


%%

int yywrap(void) {
    return 1;
}