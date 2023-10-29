#include "analex.h"

#define TAM_LEXEMA 50
#define TAM_NUM 20

const char BLANK = ' ';
const char NEW_LINE = '\n';
const char TAB = '\t';

void error(char msg[]) {
    printf("%s\n", msg);
    exit(1);
}

enum PALAVRAS_RESERVADAS verificaPalavraReservada(const char *lexema) {
    for (int i = 0; i < sizeof(PRTable) / sizeof(PRTable[0]); i++) {
        if (strcmp(lexema, PRTable[i]) == 0) {
            return i;
        }
    }
    return -1; // Se não encontrar, retorne -1
    }
TOKEN AnaLex(FILE *fd) {
    int estado;
    char lexema[TAM_LEXEMA] = "";
    int tamL = 0;
    char digitos[TAM_NUM] = "";
    int tamD = 0;

    TOKEN t;
    estado = 0;

  while (true) 
  { 
    char c = fgetc(fd); 
    switch (estado) 
    { 

      case 0: if (c == BLANK || c == TAB|| c == NEW_LINE) estado = 0; 
        else if (isalpha(c)) 
        {
            estado = 1; 
            lexema[tamL] = c;  
            lexema[++tamL] = '\0'; 
        } 
        else if (isdigit(c)) 
        {
            estado = 2;
            digitos[tamD] = c;
            digitos[++tamD] = '\0';
        }
        else if (c == '+')
        {
            estado = 3;
            t.cat = SN;
            t.codigo = ADICAO;
            return t;
        } 
        else if (c == '-')
        {
            estado = 4;
            t.cat = SN;
            t.codigo = SUBTRACAO;
            return t;
        }  
        else if (c == '*')
        {
            estado = 5;
            t.cat = SN;
            t.codigo = MULTIPLIC;
            return t;
        }
        else if (c == '/')
        {
            estado = 6;
        }    
        else if (c == '=')
        {
            estado = 7;
        } 
        else if (c == '(')
        {
            estado = 8;
            t.cat = SN;
            t.codigo = ABRE_PAR;
            return t;
        }          
        else if (c == ')')
        {
            estado = 9;
            t.cat = SN;
            t.codigo = FECHA_PAR;
            return t;
        }  
        else if (c == '[')
        {
            estado = 10;
            t.cat = SN;
            t.codigo = ABRE_COL;
            return t;
        }
        else if (c == ']')
        {
            estado = 11;
            t.cat = SN;
            t.codigo = FECHA_COL;
            return t;
        }
        else if (c == '{')
        {
            estado = 12;
            t.cat = SN;
            t.codigo = ABRE_CHAVE;
            return t;
        }          
        else if (c == '}')
        {
            estado = 13;
            t.cat = SN;
            t.codigo = FECHA_CHAVE;
            return t;
        }
        else if (c == ',')
        {
            estado = 14;
            t.cat = SN;
            t.codigo = VIRGULA;
            return t;
        }
        else if (c == '\'')
        {
            estado = 15;
            t.cat = SN;
            t.codigo = ASPAS_SIMP;
            return t;
        }          
        
        else if (c == '\"')
        {
            estado = 16;
            t.cat = SN;
            t.codigo = ASPAS_DUP;
            return t;
        }          
        else if (c == '&')
        {
            estado = 17;
            t.cat = SN;
            t.codigo = ECOMERCIAL;
            return t;
        }          
        else if (c == '|')
        {
            estado = 18;
            t.cat = SN;
            t.codigo = BARA;
            return t;
        }
        else if (c == '<')
        {
            estado = 19;
            t.cat = SN;
            t.codigo = MENORQ;
            return t;
        }              
        else if (c == '>')
        {
            estado = 20;
            t.cat = SN;
            t.codigo = MAIORQ;
            return t;
        }
        else if (c == '!')
        {
            estado = 21;
            t.cat = SN;
            t.codigo = EXCLAMACAO;
            return t;
        }
        else if (c == '_')
        {
            estado = 22;
            t.cat = SN;
            t.codigo = UNDERSCORE;
            return t;
        }             
        else if (c == 'EOF')
        {
            t.cat = FIM_ARQ;
            return t;
        }
        else
            error("Caracter invalido na expressao!");
            break;
    case 1: if((isalpha(c) || isdigit(c) || c == '_'))  
            {
                estado = 1;
                lexema[tamL] = c;
                lexema[++tamL]= '\0';
            }
            else
            {
                estado = 23;
                ungetc(c, fd);
                enum PALAVRAS_RESERVADAS palavraReservada = verificaPalavraReservada(lexema);
                    if (palavraReservada != -1) {
                        t.cat = palavraReservada;
                    } else {
                        t.cat = ID;
                    }
                    strcpy(t.lexema, lexema);
                    return t;
                }
                break;
    case 2: if(isdigit(c) )
            {
                estado = 2;
                digitos[tamD] = c;
                digitos[++tamD] = '\0';
            }
            else if( c = '.')
            {
                estado = 24;
                digitos[tamD] = c;
                digitos[++tamD] = '\0';
            }
            else
            {
                estado = 25;
                ungetc(c, fd);
                t.cat = INTCON;
                t.valInt = atoi(digitos);
                return t;
            }
            break;
    case 6: if( c == '/')
            {
                estado = 26;
            }
            else
            {
                estado =27;
                t.cat = SN;
                t.codigo = DIVISAO;
                ungetc(c, fd);
            }
    case 7: if( c == '=')
            {
                    estado = 28;
                    t.cat = SN;
                    t.codigo = IGUAL;
                    return t;
            }
            else
            {
                estado = 29;
                t.cat = SN;
                t.codigo = ATRIB;
                ungetc(c, fd);
                return t;
            }
    case 15:if (c == '\\') 
            {
                // Transição para o estado 30 (caractere de escape)
                   estado = 30;
            } 
            else if (c != '\'' && isprint(c)) {
                // Caractere imprimível (exceto '\')
                t.cat = CHARCON;
                t.valChar = c; // Armazena o caractere na estrutura do token                    return t;
            }
            else
                error("Caracter invalido na expressao!");
                break;
    case 16:  if(c == "\"")
            {
                estado =33;
                t.cat = STRCON;
                lexema[tamL] = '\0';
                return t;
            }
             else if(isprint(c))
            {
                estado = 16;
                lexema[tamL] = c; // Anexe o caractere ao lexema
                lexema[++tamL] = '\0'; // Atualiza o término do lexema            }
    }
 }
}