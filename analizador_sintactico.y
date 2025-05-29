%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para free

int yylex(void);
void yyerror(const char *s);
extern char *yytext; // Para acceder al texto del token si es necesario
extern int yylineno; // Para número de línea
extern FILE *yyin;
%}

/* 
  Si usas valores semánticos (ej. para construir un AST), define %union.
  Por ahora, lo mantendremos simple para solo verificar la sintaxis.
  Si se usa yylval en el .l, se necesita una %union aquí.
*/
%union {
    char *sval; // Para identificadores, constantes string
     int ival; // Para enteros, si los conviertes 
    // double dval; // Para flotantes 
}

%token <sval> IDENTIFICADOR_TOKEN
%token <sval> CONSTANTE_ENTERA_TOKEN CONSTANTE_CARACTER_TOKEN
%token <sval> STRING_LITERAL_TOKEN CONSTANTE_FLOTANTE_TOKEN // Añadido 

%token INT_TOKEN CHAR_TOKEN VOID_TOKEN // FLOAT_TOKEN 
%token IF_TOKEN ELSE_TOKEN WHILE_TOKEN RETURN_TOKEN

%token ASIGNACION_TOKEN
%token OPERADOR_SUMA_TOKEN OPERADOR_RESTA_TOKEN
%token OPERADOR_MULTIPLICACION_TOKEN OPERADOR_DIVISION_TOKEN
%token COMPARACION_IGUAL_TOKEN COMPARACION_DIFERENTE_TOKEN
%token OPERADOR_MENOR_TOKEN OPERADOR_MAYOR_TOKEN
%token OPERADOR_MENOR_IGUAL_TOKEN OPERADOR_MAYOR_IGUAL_TOKEN

%token PARENTESIS_IZQ_TOKEN PARENTESIS_DER_TOKEN
%token LLAVE_IZQ_TOKEN LLAVE_DER_TOKEN
%token PUNTO_COMA_TOKEN COMA_TOKEN
%token PUNTOS_SUSPENSIVOS_TOKEN

// Precedencia y asociatividad para resolver ambigüedades en expresiones 
%right ASIGNACION_TOKEN
%left COMPARACION_IGUAL_TOKEN COMPARACION_DIFERENTE_TOKEN
%left OPERADOR_MENOR_TOKEN OPERADOR_MAYOR_TOKEN OPERADOR_MENOR_IGUAL_TOKEN OPERADOR_MAYOR_IGUAL_TOKEN
%left OPERADOR_SUMA_TOKEN OPERADOR_RESTA_TOKEN
%left OPERADOR_MULTIPLICACION_TOKEN OPERADOR_DIVISION_TOKEN
%right UNARY_MINUS_PREC // Precedencia para el menos unario 
%nonassoc THEN // Para resolver el "dangling else" 
%nonassoc ELSE_TOKEN


%start unidad_compilacion

%%

unidad_compilacion
    : lista_declaraciones_externas_opc
    ;

lista_declaraciones_externas_opc
    : 
    | lista_declaraciones_externas
    ;

lista_declaraciones_externas
    : declaracion_externa
    | lista_declaraciones_externas declaracion_externa
    ;

declaracion_externa
    : definicion_funcion
    | declaracion_global
    ;

declaracion_global
    : especificador_tipo lista_init_declaradores_opc PUNTO_COMA_TOKEN
    ;

lista_init_declaradores_opc
    : 
    | lista_init_declaradores
    ;

lista_init_declaradores
    : init_declarador
    | lista_init_declaradores COMA_TOKEN init_declarador
    ;

init_declarador
    : declarador
    | declarador ASIGNACION_TOKEN expresion_asignacion // Simplificado, debería ser inicializador 
    ;

declarador
    : punteros_opc IDENTIFICADOR_TOKEN
    ;

punteros_opc
    : 
    | OPERADOR_MULTIPLICACION_TOKEN punteros_opc
    ;


definicion_funcion
    : especificador_tipo declarador PARENTESIS_IZQ_TOKEN contenido_parametros_funcion PARENTESIS_DER_TOKEN cuerpo_funcion
    ;

contenido_parametros_funcion // Renombrado desde def_parametros para claridad
    : 
    | VOID_TOKEN                
    | lista_real_parametros     // Para func(int a, char b) 
    ;

especificador_tipo
    : VOID_TOKEN
    | CHAR_TOKEN
    | INT_TOKEN
    ;

lista_real_parametros
    : param_declaracion
    | lista_real_parametros COMA_TOKEN param_declaracion
    ;    

param_declaracion
    : especificador_tipo declarador
    | especificador_tipo // Para parámetros sin nombre, más avanzado 
    ;

cuerpo_funcion
    : LLAVE_IZQ_TOKEN lista_elementos_bloque_opc LLAVE_DER_TOKEN
    ;

lista_elementos_bloque_opc
    : /* vacio */
    | lista_elementos_bloque
    ;

lista_elementos_bloque
    : elemento_bloque
    | lista_elementos_bloque elemento_bloque
    ;

elemento_bloque 
    : declaracion_global 
    | sentencia
    ;



// Sentencias (basado en tu 'declaracion' dentro de cuerpo_funcion) 
sentencia
    : sentencia_expresion
    | sentencia_compuesta
    | sentencia_seleccion
    | sentencia_iteracion
    | sentencia_salto
    ;

sentencia_expresion
    : expresion_opc PUNTO_COMA_TOKEN
    ;

expresion_opc
    : /* vacio, para permitir solo ; */
    | expresion
    ;

sentencia_compuesta // alias cuerpo_funcion para bloques anidados */
    : LLAVE_IZQ_TOKEN lista_elementos_bloque_opc LLAVE_DER_TOKEN
    ;

sentencia_seleccion
    : IF_TOKEN PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN sentencia %prec THEN
    | IF_TOKEN PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN sentencia ELSE_TOKEN sentencia
    ;

sentencia_iteracion
    : WHILE_TOKEN PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN sentencia
    ;

sentencia_salto
    : RETURN_TOKEN expresion_opc PUNTO_COMA_TOKEN
    ;


// Expresiones */
expresion
    : expresion_asignacion
    /* | expresion COMA_TOKEN expresion_asignacion // Operador coma, opcional */
    ;

expresion_asignacion
    : expresion_condicional /* C permite que una expresión condicional sea una expresión de asignación */
    | expresion_unaria ASIGNACION_TOKEN expresion_asignacion /* x = y = z */
    ;

expresion_condicional /* No implementado el ternario ?: para simplificar */
    : expresion_logica_or
    ;

expresion_logica_or /* No hay OR en tu léxico, así que se salta al AND */
    : expresion_logica_and
    /* | expresion_logica_or OR_TOKEN expresion_logica_and */
    ;

expresion_logica_and /* No hay AND en tu léxico, así que se salta a igualdad */
    : expresion_igualdad
    /* | expresion_logica_and AND_TOKEN expresion_igualdad */
    ;

expresion_igualdad
    : expresion_relacional
    | expresion_igualdad COMPARACION_IGUAL_TOKEN expresion_relacional
    | expresion_igualdad COMPARACION_DIFERENTE_TOKEN expresion_relacional
    ;

expresion_relacional
    : expresion_aditiva
    | expresion_relacional OPERADOR_MENOR_TOKEN expresion_aditiva
    | expresion_relacional OPERADOR_MAYOR_TOKEN expresion_aditiva
    | expresion_relacional OPERADOR_MENOR_IGUAL_TOKEN expresion_aditiva
    | expresion_relacional OPERADOR_MAYOR_IGUAL_TOKEN expresion_aditiva
    ;

expresion_aditiva
    : expresion_multiplicativa
    | expresion_aditiva OPERADOR_SUMA_TOKEN expresion_multiplicativa
    | expresion_aditiva OPERADOR_RESTA_TOKEN expresion_multiplicativa
    ;

expresion_multiplicativa
    : expresion_unaria
    | expresion_multiplicativa OPERADOR_MULTIPLICACION_TOKEN expresion_unaria
    | expresion_multiplicativa OPERADOR_DIVISION_TOKEN expresion_unaria
    ;

expresion_unaria
    : expresion_postfix
    | OPERADOR_RESTA_TOKEN expresion_unaria %prec UNARY_MINUS_PREC
    | OPERADOR_SUMA_TOKEN expresion_unaria /* + unario, misma precedencia que el unario menos */
    /* Otros unarios como ++, --, !, ~, sizeof, etc. irían aquí */
    ;

expresion_postfix
    : primaria
    | IDENTIFICADOR_TOKEN PARENTESIS_IZQ_TOKEN lista_argumentos_opc PARENTESIS_DER_TOKEN /* Llamada a función */
    /* Faltan accesos a arrays x[y], miembros x.y, x->y */
    ;

primaria
    : IDENTIFICADOR_TOKEN
    | constante
    | PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN
    ;

constante
    : CONSTANTE_ENTERA_TOKEN
    | CONSTANTE_CARACTER_TOKEN
    | STRING_LITERAL_TOKEN
    | CONSTANTE_FLOTANTE_TOKEN
    ;

lista_argumentos_opc
    : /* vacio */
    | lista_argumentos
    ;

lista_argumentos
    : expresion_asignacion /* En C, los argumentos de función son expresiones de asignación */
    | lista_argumentos COMA_TOKEN expresion_asignacion
    ;


%%
void yyerror(const char *s) {
    fprintf(stderr, "Error Sintactico: %s cerca de '%s'\n", s, yytext);
    // Podrías añadir yylineno si lo gestionas en el lexer
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

    do {
        yyparse();
    } while (!feof(yyin)); // Para parsear múltiples unidades si estuvieran en el mismo stream (no estándar para C)
                           // O simplemente llamar yyparse() una vez.

    if (yyin != stdin && yyin != NULL) {
        fclose(yyin);
    }
    return 0;
}
