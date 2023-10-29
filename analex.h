#ifndef ANALEX
#define ANALEX
#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 
#include <stdbool.h> 

#define TAM_MAX_LEXEMA 31

enum TOKEN_CAT {ID=1, SN, INTCON, REALCON, CHARCON, STRCON, FIM_EXPR, FIM_ARQ};
enum SINAIS {
    ATRIB = 1, ADICAO, SUBTRACAO, // =, +, - 
    MULTIPLIC, DIVISAO, //*, /
    ABRE_PAR, FECHA_PAR,  ABRE_COL,FECHA_COL,ABRE_CHAVE, FECHA_CHAVE, //(,), [,],{,}
    ECOMERCIAL, INV_BAR, EXCLAMACAO, // &, \, !
    BARA, MAIORQ, MENORQ, // \, >,<
    MAIOR_IG, MENOR_IG, IGUAL, DIFERENCA, OU, AND, // >=, <=, ==, !=, ||, &&
    ASPAS_SIMP, ASPAS_DUP, // ', "
    UNDERSCORE, VIRGULA, COMMENT, PONTO // _, ,, //, .
};

enum PALAVRAS_RESERVADAS {
    PR_CHAR, PR_INT, PR_FLOAT, PR_BOOL,
    IF, ELSE, ELSEIF, ENDIF, WHILE, ENDWHILE,
    RETURN, GOBACK, FOR, TIMES, BLOCK, MAIN, ENDBLOCK,
    VARYING, FROM
};

typedef struct {
    enum TOKEN_CAT cat;
    union {
        int codigo;
        char lexema[TAM_MAX_LEXEMA];
        int valInt;
        double valReal;
        char valChar;
    };
} TOKEN;

static const char * const tokenCatNames[] = {
    [ID] = "ID",
    [SN] = "SN",
    [INTCON] = "INTCON",
    [REALCON] = "REALCON",
    [CHARCON] = "CHARCON",
    [STRCON] = "STRCON",
    [FIM_EXPR] = "FIM_EXPR",
    [FIM_ARQ] = "FIM_ARQ",
    [PR] = 'PR';//PALAVRA RESERV
};

static const char * const SinaisTable[] = {
    [ATRIB] = "ATRIB",
    [ADICAO] = "ADICAO",
    [SUBTRACAO] = "SUBTRACAO",
    [MULTIPLIC] = "MULTIPLIC",
    [DIVISAO] = "DIVISAO",
    [ABRE_PAR] = "ABRE_PAR",
    [FECHA_PAR] = "FECHA_PAR",
    [ABRE_COL] = "ABRE_COL",
    [FECHA_COL] = "FECHA_COL",
    [ABRE_CHAVE] = "ABRE_CHAVE",
    [FECHA_CHAVE] = "FECHA_CHAVE",
    [ECOMERCIAL] = "ECOMERCIAL",
    [INV_BAR] = "INV_BAR",
    [EXCLAMACAO] = "EXCLAMACAO",
    [BARA] = "BARA",
    [MAIORQ] = "MAIORQ",
    [MENORQ] = "MENORQ",
    [MAIOR_IG] = "MAIOR_IG",
    [MENOR_IG] = "MENOR_IG",
    [IGUAL] = "IGUAL",
    [DIFERENCA] = "DIFERENCA",
    [OU] = "OU",
    [AND] = "AND",
    [ASPAS_SIMP] = "ASPAS_SIMP",
    [ASPAS_DUP] = "ASPAS_DUP",
    [UNDERSCORE] = "UNDERSCORE",
    [VIRGULA] = "VIRGULA",
    [COMMENT] = "COMMENT",
    [PONTO] = "PONTO"
};

static const char * const PRTable[] = {
    [PG_CHAR] = "char",
    [PG_INT] = "int",
    [PG_FLOAT] = "float",
    [PG_BOOL] = "bool",
    [IF] = "if",
    [ELSE] = "else",
    [ELSEIF] = "elseif",
    [ENDIF] = "endif",
    [WHILE] = "while",
    [ENDWHILE] = "endwhile",
    [RETURN] = "return",
    [GOBACK] = "goback",
    [FOR] = "for",
    [TIMES] = "times",
    [BLOCK] = "block",
    [MAIN] = "main",
    [ENDBLOCK] = "endblock",
    [VARYING] = "varying",
    [FROM] = "from"


#endif

int contLinha = 1;
