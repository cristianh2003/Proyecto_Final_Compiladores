%{
#include <stdio.h>
#include <string.h>
#include "Analizador_sintactico.tab.h" // Asegúrate que el nombre coincida
%}

%option yylineno

/* ---------- DEFINICIONES REGULARES ---------- */

LETRA             [a-zA-Z_]
DIGITO            [0-9]
CARACTERES_IGNORADOS [ \t\n\r]+
COMENTARIO_BLOQUE  "/*"([^*]|\*+[^*/])*\*+"/"
IDENTIFICADOR_PATRON {LETRA}({LETRA}|{DIGITO})*
CONSTANTE_ENTERA_PATRON (0|[1-9]{DIGITO}*)
CONSTANTE_FLOTANTE_PATRON ({DIGITO}+\.{DIGITO}*([eE][+-]?{DIGITO}+)? | {DIGITO}*\.{DIGITO}+([eE][+-]?{DIGITO}+)? | {DIGITO}+[eE][+-]?{DIGITO}+)
CONSTANTE_CARACTER_PATRON \'([^'\\]|\\.)\'
STRING_LITERAL_PATRON \"([^"\\]|\\.)*\"


%%
{CARACTERES_IGNORADOS}   { /* Ignorar */ }
{COMENTARIO_BLOQUE}    { /* Ignorar */ }

"if"                    { return IF_TOKEN; }
"else"                  { return ELSE_TOKEN; }
"while"                 { return WHILE_TOKEN; }
"return"                { return RETURN_TOKEN; }
"int"                   { return INT_TOKEN; }
"char"                  { return CHAR_TOKEN; }
"void"                  { return VOID_TOKEN; }
"print"                 { return PRINT_TOKEN; } // NUEVO TOKEN 


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
    if (yyleng > 100) {
        fprintf(stderr, "ERROR_LEXICO: Identificador '%.*s' excede 100 caracteres.\n", yyleng, yytext);
    }
    yylval.sval = strdup(yytext);
    return IDENTIFICADOR_TOKEN;
}

{CONSTANTE_ENTERA_PATRON} {
    yylval.sval = strdup(yytext); // Se envía como string, se convertirá en el parser
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

.   { fprintf(stderr, "ERROR_LEXICO: Caracter desconocido '%c' (ASCII: %d)\n", yytext[0], yytext[0]); }

%%

int yywrap(void) {
    return 1;
}