
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AnaLex.h"
#include "anasint.h"
#include "Funcaux.h"

char nomeId[TAM_MAX_LEXEMA];
char blockAux[TAM_MAX_LEXEMA];
int catId;
int escopo = GLOBAL;
int tipo;
bool t_const = 0;
bool zombie = 0;
bool ref = 0;
int parametros = 0;

//prog ::= {decl_list_var} {decl_block_prot} block_main {block_def}
void Prog()
{
    catId =VG;
    while(t.cat == PALAVRAS_RESERVADAS &&( t.codigo = PR_INT || t.codigo == PR_CHAR || t.codigo == PR_FLOAT ||  
    t.codigo == PR_BOOL || t.codigo == CONST))
    {
      decl_list_var();
    }
    if(t.cat!= PALAVRAS_RESERVADAS || t.codigo!= BLOCK)
    { 
        Erro(1);
    }
    t = AnaLex(fd);
    while(t.cat == ID)
    {
        catId == BLK;
        strcpy(nomeId, t.lexema);
        escopo =GLOBAL;
        InsereTabIdentif(nomeId, catId, escopo, tipo, t_const, zombie, ref, parametros);
        strcpy(blockAux, t.lexema);
        t =AnaLex(fd);
        decl_block_prot();
        if(t.cat != PALAVRAS_RESERVADAS && t.codigo  ==  BLOCK)
        {
         erro(2);        
        }
        t = AnaLex(fd);
    }
    escopo = GLOBAL;
    catId = BLOCK;
     Block_main();
    catId =BLK;
    t =AnaLex(fd);
    while (t.cat ==PALAVRAS_RESERVADAS && t.codigo == BLOCK)
    {
        Block_def();
    }
}

//decl_list_var ::= [const] tipo decl_var { , decl_var}
void Decl_list_var()
{
    if(t.cat ==PALAVRAS_RESERVADAS && t.codigo == CONST)
    {
        t = AnaLex(fd);
         t_const=1;
    }
    Tipo();
    t = AnaLex(fd);
    Decl_var(); 

    while (t.cat  == SINAIS && t.codigo == VIRGULA)
    {
        t = AnaLex(fd);
        Decl_var();
    }
}

//decl_block_prot ::= block id [with [&] tipo { [ ] } { , [&] tipo { [ ] } }]
void Dec_block_prot()
{

    if(t.cat ==PALAVRAS_RESERVADAS && t.codigo == WITH)
    {   
        catId =ARG;
        escopo = LOCAL;
        parametros = 1;
        t = AnaLex (fd);
        if(t.cat == SINAIS && t.codigo == ECOMERCIAL)
        {
            t =AnaLex(fd);
            ref = 1;
        }
        Tipo();
        strcpy(nomeId, "");
        t =AnaLex(fd);
        while (t.cat ==SINAIS && t.codigo == ABRE_COL)
        {
          t= AnaLex(fd);
          if(t.cat !=SINAIS || t.codigo != FECHA_COL)
          {
            Erro(2);
          }
          t =AnaLex(fd);
        }
        InsereTabIdentif(nomeId, catId, escopo, tipo, t_const, zombie, ref, parametros);
        while (t.cat ==SINAIS && t.codigo ==VIRGULA)
        {   
            parametros ++;
            ref = 0;
            t =AnaLex(fd);
            if(t.cat ==SINAIS && t.codigo == ECOMERCIAL)
            {
                ref =1;
                t =AnaLex(fd);
            }
        
            Tipo();
            strcpy(nomeId, "");
            t =AnaLex(fd);
            while (t.cat ==SINAIS && t.codigo == ABRE_COL)
            {
            t= AnaLex(fd);
            if(t.cat !=SINAIS || t.codigo != FECHA_COL)
            {
                Erro(2);
            }
            t =AnaLex(fd);
            }
                  InsereTabIdentif(nomeId, catId, escopo, tipo, t_const, zombie, ref, parametros);
        } 
    }
}

//block_main ::= block main {decl_list_var} { cmd } endblock
void Block_main()
{
    if(t.cat != PALAVRAS_RESERVADAS || t.codigo != MAIN)
    {
        Erro(3);
    }
    t = AnaLex(fd);
    while (t.cat == PALAVRAS_RESERVADAS && (t.codigo == CONST || t.codigo == PR_CHAR || t.codigo == PR_INT || t.codigo == PR_FLOAT || t.codigo == PR_BOOL))
    {
        Decl_list_var();
    }
    while (t.cat == ID || t.cat ==PALAVRAS_RESERVADAS && (t.codigo == DO|| t.codigo == IF || t.codigo == WHILE || t.codigo == GOBACK || t.codigo == GETINT || t.codigo == GETREAL || t.codigo == GETCHAR || t.codigo == PUTINT || t.codigo == PUTREAL || t.codigo == PUTCHAR))
    {
        Cmd();
    }
    

    if(t.cat != PALAVRAS_RESERVADAS || t.codigo != ENDBLOCK)
    {
        Erro(4);
    }

}


//decl_var ::= id {[ intcon | idconst ]} [ = (intcon | realcon | charcon | stringcon |
//{ (intcon | realcon | charcon | stringcon) {, (intcon | realcon |charcon | stringcon) } } ) ]
void Decl_var()
{
    if(t.cat != ID)
    {
        Erro(5);
    }
    t = AnaLex(fd);
    while (t.cat == SINAIS && t.codigo == ABRE_COL)
    {
    
       t= AnaLex(fd);
       while (t.cat != INTCON && t.cat !=ID)
       {
        Erro(6);
       }
       t =AnaLex(fd);
       if(t.cat !=SINAIS || t.codigo != FECHA_COL)
       {
        Erro(2);
       }
       t= AnaLex(fd);
    }
    if(t.cat == SINAIS && t.codigo == ATRIB)
    {
        t = AnaLex(fd);

    }
    

}


// tipo ::= char
//         | int
//         | real
//         | bool
void Tipo()
{
    if(t.cat != PALAVRAS_RESERVADAS || !(t.codigo == PR_CHAR || t.codigo == PR_INT || t.codigo == PR_FLOAT || t.codigo == PR_BOOL))
    {
        Erro(3);
    }
    if(t.codigo == PR_CHAR)
    {
        tipo = T_CHAR;
    }else if (t.codigo== PR_INT)
    {
        tipo = t_INT;
    }else if (t.codigo == PR_FLOAT)
    {
        tipo = T_REAL;
    }
    else if (t.codigo == PR_BOOL)
    {
        tipo= T_BOOL;
    }
    
    
    

}

//block_def ::= block id [with tipo id1{ [intcon1 | idconst1] } { , tipo id2 { [intcon2| idconst2] } }] {decl_list_var} { cmd } endblock
void Block_def()
{
    t=AnaLex(fd);
    if(t.cat != ID)
    {
        Erro(5);
    }

    strcpy(blockAux, t.lexema);
    int i = BuscaTabIdetifBlk(blockAux);
    i++;
    t =AnaLex(fd);
    if(t.cat == PALAVRAS_RESERVADAS && t.codigo == WITH)
    {
        t= AnaLex(fd);
        Tipo();
        t=AnaLex(fd);
        if(t.cat!=ID)
        {
            Erro(5);
        }

        while (t.cat == SINAIS && t.codigo == ABRE_COL)
        {
            t= AnaLex(fd);
            if(t.cat != INTCON && t.cat != ID)
            {
                Erro(5);
            }
            t=AnaLex(fd);
            if(t.cat != SinaisTable ||  t.codigo != FECHA_COL)
            {
                Erro(10);

            }
            t = AnaLex(fd);   
        }
        while (t.cat==SINAIS && t.codigo == VIRGULA)
        {
            t = AnaLex(fd);
            Tipo();
            t=AnaLex(fd);
            if(t.cat!=ID)
            {
                Erro(5);
            }
        }
         while (t.cat == SINAIS && t.codigo == ABRE_COL)
        {
            t= AnaLex(fd);
            if(t.cat != INTCON && t.cat != ID)
            {
                Erro(5);
            }
            t=AnaLex(fd);
            if(t.cat != SinaisTable ||  t.codigo != FECHA_COL)
            {
                Erro(10);

            }
            t = AnaLex(fd);   
        }
    }
}

// cmd ::= do (id1 [with tipo id1 { , tipo id2 }] | cmd ) varying id2 from expr1(to 
//     | downto) expr2
//     | do (id [with tipo id1 { , tipo id2 }] | cmd ) while ( expr )
//     | do (id [with tipo id1 { , tipo id2 }] | cmd ) [for expr times ]
//     | if ( expr ) { cmd }{ elseif ( expr ) { cmd } } [ else { cmd }] endif
//     | while ( expr ) { cmd } endwhile
//     | atrib
//     | goback
//     | getint id
//     |getreal id
//     | getchar id
//     | putint id
//     | putreal id
//    | putchar id
void Cmd()
{
    if(t.cat == PALAVRAS_RESERVADAS && t.codigo == DO )
    {
        t = AnaLex(fd);
        if(t.cat ==ID)
        {
            if(lookahead.cat == SINAIS && lookahead.codigo == ABRE_COL || lookahead.codigo == ATRIB)
            {
                Cmd();
            }
            else
            {
                t =AnaLex(fd);
                if(t.cat = PALAVRAS_RESERVADAS && t.codigo ==WITH)
                {
                    t =AnaLex(fd);
                    if(t.cat != ID)
                    {
                        Erro(5);
                    }
                    t = AnaLex(fd);
                    if (t.cat == SINAIS && t.codigo == VIRGULA)
                    {
                        t =AnaLex(fd);
                        if(t.cat!=ID)
                        {
                            Erro(5);
                        }
                        t=AnaLex(fd);
                    }
                }
            }
        }
        else if(t.cat == PALAVRAS_RESERVADAS && (t.codigo == DO || t.codigo == IF || t.codigo == WHILE || t.codigo == GOBACK || t.codigo == GETINT || t.codigo == GETREAL || t.codigo == GETCHAR || t.codigo == PUTINT || t.codigo == PUTREAL || t.codigo == PUTCHAR))
        {
            Cmd();
        }else
        {
            Erro(14);
        }
        if(t.cat ==PALAVRAS_RESERVADAS && t.codigo == VARYING)
        {
            t =AnaLex(fd);
            if(t.cat !=ID)
            {
                Erro(5);
            }
            t=AnaLex(fd);
            if (t.cat!= PALAVRAS_RESERVADAS || t.codigo != FROM)
            {
                Erro(16); //esperando from
            }
            t=AnaLex(fd);
            Expr();
            if (t.cat!=PALAVRAS_RESERVADAS || t.codigo != TO && t.codigo != DOWNTO)
            {
                Erro(10);//esperando to ou downto
            }
            t=AnaLex(fd);
            Expr();
        }else if (t.cat == PALAVRAS_RESERVADAS && t.codigo == WHILE)
        {
            t=AnaLex(fd);
            if(t.cat !=SINAIS || t.codigo!=ABRE_PAR )
            {
                Erro(8); //ESPERANDO ABRE PARENTESES
            }
            t=AnaLex(fd);
            Expr();
            if (t.cat != SINAIS || t.codigo != FECHA_PAR)
            {
                Erro(9); //ESPERANDO fecha PARENTESES
            }
            t=AnaLex(fd);
        }else if (t.cat ==PALAVRAS_RESERVADAS && t.codigo == FOR)
        {
            t=AnaLex(fd);
            Expr();
            if(t.cat != PALAVRAS_RESERVADAS || t.codigo != TIMES)
            {
                Erro(15);//esperandp times
            }
            t=AnaLex(fd);
        }
        else if (t.cat ==PALAVRAS_RESERVADAS && t.codigo == IF)
        {
            t=AnaLex(fd);
            if(t.cat != SINAIS || t.codigo != ABRE_PAR)
            {
                Erro(8);
            }
            t=AnaLex(fd);
            Expr();
            if (t.cat  !=SINAIS || t.codigo != FECHA_PAR)
            {
                Erro(9);
            }
            t=AnaLex(fd);
            while((t.cat == PALAVRAS_RESERVADAS && (t.codigo == DO || t.codigo == IF || t.codigo == WHILE || t.codigo == GOBACK || t.codigo == GETINT || t.codigo == GETREAL || t.codigo == GETCHAR || t.codigo == PUTINT || t.codigo == PUTREAL || t.codigo == PUTCHAR )) || t.cat == ID)
            {
                Cmd();
            }
        }
        if (t.cat != PALAVRAS_RESERVADAS || t.codigo != ENDIF)
        {
           Erro(13); //esoerando endif
        }
        t=AnaLex(fd);
    }else if (t.cat == PALAVRAS_RESERVADAS && t.codigo != WHILE)
    {
        t=AnaLex(fd);
        if(t.cat != SINAIS || t.codigo != ABRE_PAR)
        {
            Erro(8);
        }
        t=AnaLex(fd);
        Expr();

        if(t.cat != SINAIS || t.codigo != FECHA_PAR)
        {
            Erro(9);
        }
        t=AnaLex(fd);
         while((t.cat == PALAVRAS_RESERVADAS && (t.codigo == DO || t.codigo == IF || t.codigo == WHILE || t.codigo == GOBACK || t.codigo == GETINT || t.codigo == GETREAL || t.codigo == GETCHAR || t.codigo == PUTINT || t.codigo == PUTREAL || t.codigo == PUTCHAR )) || t.cat == ID)
        {
            Cmd();
        }
        if(t.cat != PALAVRAS_RESERVADAS || t.codigo != ENDWHILE)
        {
            Erro(11);//esperando endwhile
        }
        t=AnaLex(fd);
    }
    else if (t.cat!=ID)
    {
        Atrib();
    }else if (t.cat == PALAVRAS_RESERVADAS && t.codigo == GOBACK)
    {
        t=AnaLex(fd);
    }else if (t.cat ==PALAVRAS_RESERVADAS && t.codigo == GETINT || t.codigo ==GETREAL || t.codigo == GETCHAR|| t.codigo == PUTINT || t.codigo == PUTREAL||t.codigo == PUTCHAR )
    {
        if (t.cat != ID)
        {
            Erro(5);
        }
        t=AnaLex(fd);
        
    }else
    {
        Erro(12);//esperando imputs ou outputs
    }
    


}

// atrib ::= id { [ expr ] } = expr
void Atrib()
{
    if(t.cat != ID)
    {
        Erro(5);
    }
    t = AnaLex(fd);
    while (t.cat == SINAIS && t.codigo == ABRE_COL )
    {
        t = AnaLex(fd);
        Expr();

        if(t.cat != SINAIS || t.codigo != FECHA_COL)
        {
            Erro(8);
        }
        t = AnaLex(fd);
    }
    if(t.cat != SINAIS || t.codigo != ATRIB)
    {
        Erro(9);
    }
    Expr();

}

//expr ::= expr_simp [ op_rel expr_simp ]
void Expr()
{
      Expr_simp();

  if(t.cat == SINAIS && (t.codigo == IGUAL || t.codigo == DIFERENCA || t.codigo == MENOR_IG || t.codigo == MAIOR_IG|| t.codigo == MENORQ  || t.codigo == MAIORQ)){
    Op_rel();

    t = AnaLex(fd);
    Expr_simp();
  }

}

// [+ | – ] termo {(+ | – | ||) termo}
void Expr_simp()
{
    if(t.cat == SINAIS && t.codigo == ADICAO || t.codigo == SUBTRACAO)
    {
        t = AnaLex(fd);
    }
    Termo();
    while (t.cat == SINAIS && (t.codigo == ADICAO || t.codigo == SUBTRACAO || t.codigo == OU))
    {
        t = AnaLex(fd);
    }
    Termo();
    
}

// termo ::= fator {(* | / | &&) fator}
void Termo()
{
    Fator();
    while (t.cat ==SINAIS && (t.codigo == MULTIPLIC || t.codigo == BARA || t.codigo == AND))
    {
        t= AnaLex(fd);
        Fator();
    }
    

}

//fator ::= id { [ expr ] } | intcon | realcon | charcon |( expr ) | ! fator
void Fator()
{
    if(t.cat == ID)
    {
        t = AnaLex(fd);
        while (t.cat == SINAIS && t.codigo == ABRE_COL)
        {
            t = AnaLex(fd);
            Expr();
            if(t.cat != SINAIS && t.codigo != FECHA_COL)
            {
                Erro(6);
            }
            t = AnaLex(fd);
        } 
    }
    else if (t.cat == INTCON || t.cat == REALCON || t.cat == REALCON || t.cat == CHARCON)
    {
        t = AnaLex(fd);
    }
    else if (t.cat == SINAIS && t.codigo == ABRE_PAR)
    {
        t = AnaLex(fd);
        Expr();
        if(t.cat ==SINAIS && t.codigo!=FECHA_PAR)
        {
            Erro(6);
        }
        t = AnaLex(fd);
    }    
    else if(t.cat == SINAIS && t.codigo == EXCLAMACAO)
    {
        t = AnaLex(fd);
        Fator();

    }
    else
    {
        Erro(7);
    }
    

}

// op_rel ::= ==
//         | !=
//         | <=
//         | <
//         | >=
//         | >
void Op_rel()
{
    if(t.cat != SINAIS || (t.codigo != IGUAL && t.codigo != DIFERENCA && t.codigo != MENOR_IG &&
    t.codigo != MENORQ && t.codigo != MAIOR_IG && t.codigo != MAIORQ))
    {
        Erro(7);
    }    
}


