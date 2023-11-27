#ifndef _ANASINT_
#define _ANASINT_

#include <stdio.h>
#include <stdbool.h>
#include "analex.h"
#include "TabSimbs.h"

extern TOKEN t;
extern FILE *fd;
extern int contLinha;
extern TOKEN lookahead;
extern TAB_IDENTIF tabIdentif;

extern bool mostraArvore;
extern char TABS[200];

void Prog();
void Decl_list_var();
void Dec_block_prot();
void Block_main();
void Decl_var();
void Tipo();
void Block_def();
void Cmd();
void Atrib();
void Expr();
void Expr_simp();
void Termo();
void Fator();
void Op_rel();



#endif