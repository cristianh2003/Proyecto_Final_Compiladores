%{
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

%}

%code requires {
    typedef enum TipoSimbolo {
        TIPO_DESCONOCIDO, TIPO_INT_VAR, TIPO_CHAR_PTR_VAR, TIPO_VOID_VAR,
        TIPO_VOID_FUNC, TIPO_INT_FUNC, TIPO_BUILTIN_FUNC
    } TipoSimbolo;
}

%code {
    typedef struct Simbolo {
        char *nombre; TipoSimbolo tipo; int es_funcion_externa;
        int valor_int; char* valor_sval; int inicializado;
    } Simbolo;

    Simbolo tabla_simbolos[MAX_SIMBOLOS];
    int num_simbolos = 0;
    static char* lvalue_nombre_actual = NULL;
    static TipoSimbolo tipo_especificado_actual;
}

%union {
    char *sval;
    int ival;
    struct { char* nombre; TipoSimbolo tipo; } decl_info;
}

// --- TOKENS ---
%token <sval> IDENTIFICADOR_TOKEN CONSTANTE_ENTERA_TOKEN CONSTANTE_CARACTER_TOKEN STRING_LITERAL_TOKEN
%token INT_TOKEN CHAR_TOKEN VOID_TOKEN IF_TOKEN ELSE_TOKEN WHILE_TOKEN RETURN_TOKEN
%token ASIGNACION_TOKEN OPERADOR_SUMA_TOKEN OPERADOR_RESTA_TOKEN OPERADOR_MULTIPLICACION_TOKEN OPERADOR_DIVISION_TOKEN
%token COMPARACION_IGUAL_TOKEN COMPARACION_DIFERENTE_TOKEN OPERADOR_MENOR_TOKEN OPERADOR_MAYOR_TOKEN
%token OPERADOR_MENOR_IGUAL_TOKEN OPERADOR_MAYOR_IGUAL_TOKEN
%token PARENTESIS_IZQ_TOKEN PARENTESIS_DER_TOKEN LLAVE_IZQ_TOKEN LLAVE_DER_TOKEN
%token PUNTO_COMA_TOKEN COMA_TOKEN PUNTOS_SUSPENSIVOS_TOKEN

// --- PRECEDENCIA Y ASOCIATIVIDAD ---
%right ASIGNACION_TOKEN
%left COMPARACION_IGUAL_TOKEN COMPARACION_DIFERENTE_TOKEN
%left OPERADOR_MENOR_TOKEN OPERADOR_MAYOR_TOKEN OPERADOR_MENOR_IGUAL_TOKEN OPERADOR_MAYOR_IGUAL_TOKEN
%left OPERADOR_SUMA_TOKEN OPERADOR_RESTA_TOKEN
%left OPERADOR_MULTIPLICACION_TOKEN OPERADOR_DIVISION_TOKEN
%right UNARY_MINUS_PREC
%nonassoc IFX_NO_ELSE
%nonassoc ELSE_TOKEN

// --- TIPOS PARA NO TERMINALES ---
%type <ival> expresion expresion_asignacion expresion_condicional
%type <ival> expresion_logica_or expresion_logica_and expresion_igualdad
%type <ival> expresion_relacional expresion_aditiva expresion_multiplicativa
%type <ival> expresion_unaria expresion_postfix primaria constante_entera_valor
%type <ival> expresion_opc

%type <decl_info> declarador_con_tipo
%type <ival> sentencia sentencia_seleccion sentencia_iteracion sentencia_salto
%type <ival> if_condition_setup

%start unidad_compilacion

%% // INICIO DE LAS REGLAS GRAMATICALES 

unidad_compilacion
    : lista_declaraciones_externas_opc
    ;

lista_declaraciones_externas_opc : | lista_declaraciones_externas ;
lista_declaraciones_externas : declaracion_externa | lista_declaraciones_externas declaracion_externa ;

declaracion_externa : definicion_funcion | declaracion_global ;

declaracion_global : especificador_tipo lista_init_declaradores_opc PUNTO_COMA_TOKEN ;
lista_init_declaradores_opc : | lista_init_declaradores ;
lista_init_declaradores : init_declarador | lista_init_declaradores COMA_TOKEN init_declarador ;

init_declarador
    : declarador_con_tipo {
        declarar_simbolo($1.nombre, $1.tipo, ($1.tipo == TIPO_INT_FUNC || $1.tipo == TIPO_VOID_FUNC || $1.tipo == TIPO_BUILTIN_FUNC));
      }
    | declarador_con_tipo ASIGNACION_TOKEN expresion_asignacion {
        if ($1.tipo != TIPO_INT_VAR) { yyerror("Solo se pueden inicializar variables enteras en declaracion."); free($1.nombre); }
        else { declarar_simbolo($1.nombre, $1.tipo, 0); asignar_valor_int_variable($1.nombre, $3); }
      }
    ;

declarador_con_tipo
    : punteros_opc IDENTIFICADOR_TOKEN {
        $$.nombre = $2;
        $$.tipo = tipo_especificado_actual;
      }
    | punteros_opc IDENTIFICADOR_TOKEN PARENTESIS_IZQ_TOKEN decl_parametros_funcion PARENTESIS_DER_TOKEN {
        $$.nombre = $2;
        if (tipo_especificado_actual == TIPO_INT_VAR) $$.tipo = TIPO_INT_FUNC;
        else if (tipo_especificado_actual == TIPO_VOID_VAR) $$.tipo = TIPO_VOID_FUNC;
        else if (tipo_especificado_actual == TIPO_CHAR_PTR_VAR) { $$.tipo = TIPO_DESCONOCIDO; }
        else $$.tipo = TIPO_DESCONOCIDO;
      }
    ;

punteros_opc : | OPERADOR_MULTIPLICACION_TOKEN { tipo_especificado_actual = TIPO_CHAR_PTR_VAR; } punteros_opc ;

decl_parametros_funcion : | VOID_TOKEN | lista_real_parametros_decl ;
lista_real_parametros_decl : param_declaracion_funcion | lista_real_parametros_decl COMA_TOKEN param_declaracion_funcion ;
param_declaracion_funcion : especificador_tipo declarador_con_tipo { free($2.nombre); }
                           | especificador_tipo
                           | PUNTOS_SUSPENSIVOS_TOKEN
                           ;

definicion_funcion: especificador_tipo declarador_con_tipo cuerpo_funcion;

especificador_tipo
    : VOID_TOKEN { tipo_especificado_actual = TIPO_VOID_VAR; }
    | CHAR_TOKEN { tipo_especificado_actual = TIPO_CHAR_PTR_VAR; }
    | INT_TOKEN  { tipo_especificado_actual = TIPO_INT_VAR; }
    ;

cuerpo_funcion
    : LLAVE_IZQ_TOKEN { push_modo(get_modo()); }
      lista_elementos_bloque_opc
      LLAVE_DER_TOKEN { pop_modo(); }
    ;

lista_elementos_bloque_opc : | lista_elementos_bloque ;
lista_elementos_bloque : elemento_bloque | lista_elementos_bloque elemento_bloque ;
elemento_bloque : declaracion_global | sentencia ;

sentencia
    : sentencia_expresion        { $$ = 0; }
    | sentencia_compuesta        { $$ = 0; }
    | sentencia_seleccion        { $$ = 0; }
    | sentencia_iteracion        { $$ = 0; }
    | sentencia_salto            { $$ = 0; }
    ;

sentencia_expresion : expresion_opc PUNTO_COMA_TOKEN ;
expresion_opc : { $$ = 0; } | expresion { $$ = $1; } ;
sentencia_compuesta : cuerpo_funcion ;

sentencia_seleccion
    : if_condition_setup
      sentencia
      { pop_modo(); $$ = 0; }
      %prec IFX_NO_ELSE
    | if_condition_setup
      sentencia
      ELSE_TOKEN
      {
          pop_modo();
          int outer_can_execute = get_modo();
          push_modo(outer_can_execute && !($1));
      }
      sentencia
      { pop_modo(); $$ = 0; }
    ;

if_condition_setup
    : IF_TOKEN PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN
      {
          int outer_can_execute = get_modo();
          int condition_is_true = 0;
          if (outer_can_execute) { condition_is_true = ($3 != 0); }
          push_modo(outer_can_execute && condition_is_true);
          $$ = condition_is_true;
      }
    ;

sentencia_iteracion : WHILE_TOKEN PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN sentencia { $$ = 0;} ;
sentencia_salto : RETURN_TOKEN expresion_opc PUNTO_COMA_TOKEN { $$ = 0;} ;

expresion : expresion_asignacion { $$ = $1; } ;
expresion_asignacion
    : expresion_condicional { $$ = $1; }
    | primaria ASIGNACION_TOKEN expresion_asignacion {
        if (get_modo()) {
            if (lvalue_nombre_actual != NULL) {
                asignar_valor_int_variable(lvalue_nombre_actual, $3); $$ = $3;
                free(lvalue_nombre_actual); lvalue_nombre_actual = NULL;
            } else { yyerror("Error Semantico: L-value requerido para asignacion."); $$ = 0; }
        } else { $$ = 0; if (lvalue_nombre_actual) {free(lvalue_nombre_actual); lvalue_nombre_actual=NULL;} }
      }
    ;

expresion_condicional : expresion_logica_or { $$ = $1; } ;
expresion_logica_or   : expresion_logica_and { $$ = $1; } ;
expresion_logica_and  : expresion_igualdad { $$ = $1; } ;

expresion_igualdad
    : expresion_relacional { $$ = $1; }
    | expresion_igualdad COMPARACION_IGUAL_TOKEN expresion_relacional     { $$ = get_modo() ? ($1 == $3) : 0; }
    | expresion_igualdad COMPARACION_DIFERENTE_TOKEN expresion_relacional { $$ = get_modo() ? ($1 != $3) : 0; }
    ;
expresion_relacional
    : expresion_aditiva { $$ = $1; }
    | expresion_relacional OPERADOR_MENOR_TOKEN expresion_aditiva          { $$ = get_modo() ? ($1 < $3) : 0; }
    | expresion_relacional OPERADOR_MAYOR_TOKEN expresion_aditiva          { $$ = get_modo() ? ($1 > $3) : 0; }
    | expresion_relacional OPERADOR_MENOR_IGUAL_TOKEN expresion_aditiva    { $$ = get_modo() ? ($1 <= $3) : 0; }
    | expresion_relacional OPERADOR_MAYOR_IGUAL_TOKEN expresion_aditiva    { $$ = get_modo() ? ($1 >= $3) : 0; }
    ;
expresion_aditiva
    : expresion_multiplicativa { $$ = $1; }
    | expresion_aditiva OPERADOR_SUMA_TOKEN expresion_multiplicativa       { $$ = get_modo() ? ($1 + $3) : 0; }
    | expresion_aditiva OPERADOR_RESTA_TOKEN expresion_multiplicativa      { $$ = get_modo() ? ($1 - $3) : 0; }
    ;
expresion_multiplicativa
    : expresion_unaria { $$ = $1; }
    | expresion_multiplicativa OPERADOR_MULTIPLICACION_TOKEN expresion_unaria { $$ = get_modo() ? ($1 * $3) : 0; }
    | expresion_multiplicativa OPERADOR_DIVISION_TOKEN expresion_unaria {
        if (get_modo()) { if ($3 == 0) { yyerror("Error Semantico: Division por cero."); $$ = 0; } else { $$ = $1 / $3; } } else { $$ = 0; }
      }
    ;
expresion_unaria
    : expresion_postfix { $$ = $1; }
    | OPERADOR_RESTA_TOKEN expresion_unaria %prec UNARY_MINUS_PREC { $$ = get_modo() ? (-$2) : 0; }
    | OPERADOR_SUMA_TOKEN expresion_unaria                         { $$ = get_modo() ? $2 : 0; }
    ;

expresion_postfix
    : primaria { $$ = $1; }
    | IDENTIFICADOR_TOKEN PARENTESIS_IZQ_TOKEN lista_argumentos_opc PARENTESIS_DER_TOKEN {
        if (get_modo()) {
            Simbolo* func = buscar_simbolo($1);
            if (func) {
                yyerror("Llamadas a funciones definidas por el usuario (con o sin argumentos) no implementadas completamente para ejecucion."); $$ = 0;
            } else {
                char msg[256]; sprintf(msg, "Error Semantico: Funcion '%s' no declarada.", $1); yyerror(msg); $$ = 0;
            }
            if ($1) free($1); // Liberar nombre de función
        } else {
            $$ = 0;
            if ($1) free($1);
        }
      }
    ;

primaria
    : IDENTIFICADOR_TOKEN {
        $$ = obtener_valor_int_variable($1);
        if (lvalue_nombre_actual) free(lvalue_nombre_actual);
        lvalue_nombre_actual = $1;
      }
    | constante_entera_valor { $$ = $1; }
    | PARENTESIS_IZQ_TOKEN expresion PARENTESIS_DER_TOKEN { $$ = $2; }
    ;

constante_entera_valor : CONSTANTE_ENTERA_TOKEN { $$ = atoi($1); free($1); } ;

lista_argumentos_opc :  ; // Las llamadas a función ahora solo soportan cero argumentos 

%% // SECCIÓN DE CÓDIGO C ADICIONAL 

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