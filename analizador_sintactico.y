%{
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

%}

%union {
    char *sval; // Para identificadores, strings literales
    int ival;   // Para los valores de las expresiones enteras
}

%token <sval> IDENTIFICADOR_TOKEN
%token <sval> CONSTANTE_ENTERA_TOKEN CONSTANTE_CARACTER_TOKEN /* CARACTER no se usa para valor aún */
%token <sval> STRING_LITERAL_TOKEN CONSTANTE_FLOTANTE_TOKEN /* FLOTANTE no se usa para valor aún */

%token INT_TOKEN CHAR_TOKEN VOID_TOKEN
%token IF_TOKEN ELSE_TOKEN WHILE_TOKEN RETURN_TOKEN
%token PRINT_TOKEN /* NUEVO TOKEN */

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

/* No terminales que devuelven un valor entero */
%type <ival> expresion expresion_asignacion expresion_condicional
%type <ival> expresion_logica_or expresion_logica_and expresion_igualdad
%type <ival> expresion_relacional expresion_aditiva expresion_multiplicativa
%type <ival> expresion_unaria expresion_postfix primaria constante

/* Precedencia y asociatividad */
%right ASIGNACION_TOKEN
%left COMPARACION_IGUAL_TOKEN COMPARACION_DIFERENTE_TOKEN
%left OPERADOR_MENOR_TOKEN OPERADOR_MAYOR_TOKEN OPERADOR_MENOR_IGUAL_TOKEN OPERADOR_MAYOR_IGUAL_TOKEN
%left OPERADOR_SUMA_TOKEN OPERADOR_RESTA_TOKEN
%left OPERADOR_MULTIPLICACION_TOKEN OPERADOR_DIVISION_TOKEN
%right UNARY_MINUS_PREC
%nonassoc THEN
%nonassoc ELSE_TOKEN


%start unidad_compilacion

%%

unidad_compilacion
    : lista_declaraciones_externas_opc
    ;

lista_declaraciones_externas_opc
    : /* vacio */
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

declaracion_global // ej: int a, b;
    : especificador_tipo lista_init_declaradores_opc PUNTO_COMA_TOKEN
    ;

lista_init_declaradores_opc
    : /* vacio */
    | lista_init_declaradores
    ;

lista_init_declaradores
    : init_declarador
    | lista_init_declaradores COMA_TOKEN init_declarador
    ;

init_declarador // ej: a o a = 5
    : declarador {
        // El nombre del declarador ($1, que es IDENTIFICADOR_TOKEN) ya fue procesado
        // y la variable declarada por la acción en 'declarador'.
        // Si hubiera un inicializador como 'int a = expr;', se manejaría aquí.
      }
    | declarador ASIGNACION_TOKEN expresion_asignacion {
        // lvalue_nombre_actual fue establecido por la regla 'declarador'
        if (lvalue_nombre_actual != NULL) {
            asignar_valor_variable(lvalue_nombre_actual, $3);
            // No liberamos lvalue_nombre_actual aquí porque declarador lo hizo.
        } else {
            yyerror("Error interno: lvalue_nombre_actual no establecido en inicializacion de declaracion.");
        }
      }
    ;

declarador // ej: a (para int a;) o *p
    : punteros_opc IDENTIFICADOR_TOKEN { // $2 es el nombre de la variable
        declarar_variable($2, tipo_declaracion_actual);
        // Guardar nombre para posible asignación en init_declarador
        if(lvalue_nombre_actual) free(lvalue_nombre_actual); // Liberar el anterior si existe
        lvalue_nombre_actual = $2; // $2 viene de yylval.sval, es strdup'd por lexer.
                                   // La asignación o el final de init_declarador debería liberarlo.
                                   // O, mejor, 'declarar_variable' hace su propio strdup, y aquí liberamos $2.
                                   // Asumiendo que declarar_variable hace strdup:
        // free($2); // No, porque lvalue_nombre_actual lo apunta.
        // Se liberará cuando lvalue_nombre_actual se reasigne o al final.
      }
    ;

punteros_opc
    : /* vacio */
    | OPERADOR_MULTIPLICACION_TOKEN punteros_opc { /* Manejo de punteros omitido por simplicidad */ }
    ;


definicion_funcion
    : especificador_tipo declarador PARENTESIS_IZQ_TOKEN contenido_parametros_funcion PARENTESIS_DER_TOKEN cuerpo_funcion
    ;

especificador_tipo
    : VOID_TOKEN  { tipo_declaracion_actual = TIPO_VOID_VAR; }
    | CHAR_TOKEN  { /* tipo_declaracion_actual = TIPO_CHAR_VAR; */ yyerror("Tipo char no implementado para variables aun"); }
    | INT_TOKEN   { tipo_declaracion_actual = TIPO_INT_VAR; }
    ;

contenido_parametros_funcion
    : /* vacio */
    | VOID_TOKEN
    | lista_real_parametros
    ;

lista_real_parametros
    : param_declaracion
    | lista_real_parametros COMA_TOKEN param_declaracion
    ;

param_declaracion
    : especificador_tipo declarador { /* Parametros de funcion no manejan almacenamiento aun */ }
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
    : declaracion_global /* Declaraciones locales */
    | sentencia
    ;

sentencia
    : sentencia_expresion
    | sentencia_compuesta
    | sentencia_seleccion
    | sentencia_iteracion
    | sentencia_salto
    | PRINT_TOKEN expresion PUNTO_COMA_TOKEN { printf("%d\n", $2); } /* ACCION PARA PRINT */
    ;

sentencia_expresion
    : expresion_opc PUNTO_COMA_TOKEN
    ;

expresion_opc
    : 
    | expresion
    ;

sentencia_compuesta
    : LLAVE_IZQ_TOKEN lista_elementos_bloque_opc LLAVE_DER_TOKEN
    ;

sentencia_seleccion
    : IF_TOKEN PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN sentencia %prec THEN { /* Logica IF no implementada */ }
    | IF_TOKEN PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN sentencia ELSE_TOKEN sentencia { /* Logica IF-ELSE no implementada */ }
    ;

sentencia_iteracion
    : WHILE_TOKEN PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN sentencia { /* Logica WHILE no implementada */ }
    ;

sentencia_salto
    : RETURN_TOKEN expresion_opc PUNTO_COMA_TOKEN { /* Logica RETURN no implementada */ }
    ;

/* Expresiones */
expresion
    : expresion_asignacion { $$ = $1; }
    ;

expresion_asignacion
    : expresion_condicional { $$ = $1; }
    // Para la asignación, el lado izquierdo (expresion_unaria) debe evaluarse a un IDENTIFICADOR
    // cuyo nombre se almacena en lvalue_nombre_actual por la regla 'primaria'.
    | expresion_unaria ASIGNACION_TOKEN expresion_asignacion {
        if (lvalue_nombre_actual != NULL) {
            asignar_valor_variable(lvalue_nombre_actual, $3);
            $$ = $3; // El resultado de una asignación es el valor asignado
            free(lvalue_nombre_actual); // Liberar el nombre que fue strdup'd
            lvalue_nombre_actual = NULL;
        } else {
            yyerror("Error: L-value requerido para asignacion.");
            $$ = 0; // Valor de error
        }
      }
    ;

expresion_condicional /* No implementado el ternario ?: */
    : expresion_logica_or { $$ = $1; }
    ;

expresion_logica_or /* No implementado OR */
    : expresion_logica_and { $$ = $1; }
    ;

expresion_logica_and /* No implementado AND */
    : expresion_igualdad { $$ = $1; }
    ;

expresion_igualdad // Solo devuelve el valor, no evalúa booleanos aún
    : expresion_relacional { $$ = $1; }
    | expresion_igualdad COMPARACION_IGUAL_TOKEN expresion_relacional { $$ = ($1 == $3); /* Lógica booleana simple */ }
    | expresion_igualdad COMPARACION_DIFERENTE_TOKEN expresion_relacional { $$ = ($1 != $3); }
    ;

expresion_relacional
    : expresion_aditiva { $$ = $1; }
    | expresion_relacional OPERADOR_MENOR_TOKEN expresion_aditiva          { $$ = ($1 < $3); }
    | expresion_relacional OPERADOR_MAYOR_TOKEN expresion_aditiva          { $$ = ($1 > $3); }
    | expresion_relacional OPERADOR_MENOR_IGUAL_TOKEN expresion_aditiva    { $$ = ($1 <= $3); }
    | expresion_relacional OPERADOR_MAYOR_IGUAL_TOKEN expresion_aditiva    { $$ = ($1 >= $3); }
    ;

expresion_aditiva
    : expresion_multiplicativa { $$ = $1; }
    | expresion_aditiva OPERADOR_SUMA_TOKEN expresion_multiplicativa { $$ = $1 + $3; }
    | expresion_aditiva OPERADOR_RESTA_TOKEN expresion_multiplicativa { $$ = $1 - $3; }
    ;

expresion_multiplicativa
    : expresion_unaria { $$ = $1; }
    | expresion_multiplicativa OPERADOR_MULTIPLICACION_TOKEN expresion_unaria { $$ = $1 * $3; }
    | expresion_multiplicativa OPERADOR_DIVISION_TOKEN expresion_unaria {
        if ($3 == 0) {
            yyerror("Error: Division por cero");
            $$ = 0; // O algún valor de error
        } else {
            $$ = $1 / $3;
        }
      }
    ;

expresion_unaria
    : expresion_postfix { $$ = $1; }
    | OPERADOR_RESTA_TOKEN expresion_unaria %prec UNARY_MINUS_PREC { $$ = -$2; }
    | OPERADOR_SUMA_TOKEN expresion_unaria { $$ = $2; /* + unario */ }
    ;

expresion_postfix
    : primaria { $$ = $1; }
    | IDENTIFICADOR_TOKEN PARENTESIS_IZQ_TOKEN lista_argumentos_opc PARENTESIS_DER_TOKEN {
        /* Llamada a función no implementada para devolver valor */
        yyerror("Llamadas a funcion no devuelven valor aun.");
        $$ = 0;
        free($1); // Liberar nombre de función
      }
    ;

primaria
    : IDENTIFICADOR_TOKEN { // $1 es el nombre (char*)
        // Para R-value (uso en expresión)
        $$ = obtener_valor_variable($1);

        // Para L-value (lado izquierdo de asignación)
        // Guardamos el nombre para la regla 'expresion_asignacion'
        if (lvalue_nombre_actual) free(lvalue_nombre_actual);
        lvalue_nombre_actual = $1; // $1 fue strdup'd por el lexer. La regla de asignación lo liberará.
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
      }
    | constante           { $$ = $1; }
    | PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN { $$ = $2; }
    ;

constante
    : CONSTANTE_ENTERA_TOKEN { // $1 es char*
        $$ = atoi($1);
        free($1); // Liberar el string que vino de yylval.sval
      }
    | CONSTANTE_CARACTER_TOKEN { /* No implementado para valor int */
        yyerror("Constantes char no se usan como int aun.");
        $$ = 0;
        free($1);
      }
    ;

lista_argumentos_opc
    : /* vacio */
    | lista_argumentos
    ;

lista_argumentos
    : expresion_asignacion
    | lista_argumentos COMA_TOKEN expresion_asignacion
    ;

%%
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
