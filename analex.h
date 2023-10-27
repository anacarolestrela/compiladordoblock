#ifndef ANALEX
#define ANALEX

#define TAM_MAX_LEXEMA 31

enum TOKEN_CAT {ID=1, SN, INTCON, REALCON, CHARCON, STRCON, FIM_EXPR, FIM_ARQ};
enum SINAIS {
    ATRIB = 1, ADICAO, SUBTRACAO, // =, +, - 
    MULTIPLIC, DIVISAO, //*, /
    ABRE_PAR, FECHA_PAR,  ABRE_COL,FECHA_COL,ABRE_CHAVE, FECHA_CHAVE, //(,), [,],{,}
    ECOMERCIAL, INV_BAR, EXCLAMACAO, // &, \, !
    BARA, MAIORQ, MENORQ, // \, >,<
    MAIOR_IG, MENOR_IG, IGUAL, DIFERENCA, OU, AND // >=, <=, ==, !=, ||, &&
    ASPAS_SIMP, ASPAS_DUP, // ', "
    UNDERSCORE, VIRGULA, COMMENT // _, ,, //
};

enum PALAVRAS_RESERVADAS {
    PG_CHAR, PG_INT, PG_FLOAT, PG_BOOL,
    IF, ELSE, ELSEIF, ENDIF, WHILE, ENDWHILE,
    RETURN, GOBACK, FOR, TIMES, BLOCK, MAIN, ENDBLOCK
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
};

static const char * const PGTable[] = {
    [PG_CHAR] = "CHAR",
    [PG_INT] = "INT",
    [PG_FLOAT] = "FLOAT",
    [PG_BOOL] = "BOOL",
    [IF] = "IF",
    [ELSE] = "ELSE",
    [ELSEIF] = "ELSEIF",
    [ENDIF] = "ENDIF",
    [WHILE] = "WHILE",
    [ENDWHILE] = "ENDWHILE",
    [RETURN] = "RETURN",
    [GOBACK] = "GOBACK",
    [FOR] = "FOR",
    [TIMES] = "TIMES",
    [BLOCK] = "BLOCK",
    [MAIN] = "MAIN",
    [ENDBLOCK] = "ENDBLOCK",
};

#endif

int contLinha = 1;
