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
                return t;
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
                estado = 31;
                t.cat = CHARCON;
                t.valChar = c; // Armazena o caractere na estrutura do token                    return t;
            }
            else
                error("Caracter invalido na expressao!");
                break;
    case 16:  if(c == "\"")
            {
                estado =32;
                t.cat = STRCON;
                lexema[tamL] = '\0';
                return t;
            }
             else if(isprint(c))
            {
                estado = 16;
                lexema[tamL] = c; // Anexe o caractere ao lexema
                lexema[++tamL] = '\0'; // Atualiza o término do lexema            
            }
            else
                error("Caracter invalido na expressao!");
                break;
    case 17: if(c == '&')
            {
                estado = 33;
                t.cat = AND;
                lexema[tamL] = '\0';
                return t;
            }    
            else
            {
                estado = 34;
                t.cat = ECOMERCIAL;
                lexema[tamL] = '\0';
                ungetc(c, fd);
                return t;
            }
        case 18: if(c == '|')
                {
                    estado = 35;
                    t.cat = OU;
                    lexema[tamL] = '\0';
                    return t;
                }
                else
                    error("Caracter invalido na expressao!");
                    break;
        case 19: if(c == '=')
                {
                    estado = 36;
                    t.cat = MAIOR_IG;
                    lexema[tamL]= '\0';
                    return t;
                }
                else
                {
                    estado = 37;
                    t.cat = MAIORQ;
                    lexema[tamL] = '\0';
                    ungetc(c, fd);
                    return t;
                }
                break;
        case 20: if(c == '=')
                {
                    estado = 38;
                    t.cat = MENOR_IG;
                    lexema[tamL]= '\0';
                    return t;
                }
                else
                {
                    estado = 39;
                    t.cat = MENORQ;
                    lexema[tamL] = '\0';
                    ungetc(c, fd);
                    return t;
                }
                break;
        case 21: if(c == '=')
                {
                    estado = 40;
                    t.cat = DIFERENCA;
                    lexema[tamL]= '\0';
                    return t;
                }
                else
                {
                    estado = 41;
                    t.cat = EXCLAMACAO;
                    lexema[tamL] = '\0';
                    ungetc(c, fd);
                    return t;
                }
                break;
        case 22: if(isalpha(c)) 
                {
                    estado = 1; 
                    lexema[tamL] = c;  
                    lexema[++tamL] = '\0'; 
                }
                else
                    error("Caracter invalido na expressao!");
                    break;
        case 24: if (isdigit(c)) 
                {
                    estado = 42;
                    digitos[tamD] = c;
                    digitos[++tamD] = '\0';
                }
                else
                    error("Caracter invalido na expressao!");
                    break;
     /////REVER!!!!!!!!!!!!!!!!!!!!
        case 26:if(isprint(c))
            {
                estado = 26;
                lexema[tamL] = c; // Anexe o caractere ao lexema
                lexema[++tamL] = '\0'; // Atualiza o término do lexema            
            }
            else if( c == '\\')
            {
                estado = 0;
            }
            break;
        case 30:if(c == '0')
                {
                    estado = 43;
                    lexema[tamL] = c;
                    lexema[++tamL] = '\0';
                }
                else if(c =='n')
                {
                    estado = 44;
                lexema[tamL] = c;
                lexema[++tamL] = '\0';
                }
                else
                    error("Caracter invalido na expressao!");
                    break;  
        case 31: if(c == '\'')
                {
                    estado = 45;
                    t.cat =CHARCON;
                    strcpy(t.lexema, lexema);
                    return t;
                }  
                else
                    error("Caracter invalido na expressao!");
                    break;
        case 42: if(isdigit(c))
                {
                    estado = 42;
                    digitos[tamD] = c;
                    digitos[++tamD] = '\0';        
                }
                else
                {
                  estado = 46;
                  t.cat = REALCON;
                  t.valReal = atof(digitos);
                  ungetc(c, fd);
                  return t;  
                }
                break;
        case 43: if(c == '\'')
                {
                    estado = 47;
                    lexema[tamL]= c;
                    lexema[++tamL]='\0';
                    t.cat =CHARCON;
                    t.valChar = '\0';
                    return t;
                }
                else
                    error("Caracter invalido na expressao!");
                        break;
        case 44: if(c =='\'')
                {
                    estado = 48;
                    lexema[tamL]= c;
                    lexema[++tamL]='\0';
                    t.cat =CHARCON;
                    t.valChar = 'n';
                    return t;
                }
                else
                    error("Caracter invalido na expressao!");
                    break;
  }
 }
}

int main(){
    FILE *fd;
    TOKEN TK;
    if ((fd=fopen("expressao.dat", "r")) == NULL) 
         error("Arquivo de entrada da expressao nao encontrado!"); 
}