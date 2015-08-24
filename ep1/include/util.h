 /*------------------------------------------*
  |                 util.h                   |
  *------------------------------------------* 
  | Este arquivo contem os prototipos das    |
  | funcoes usadas no ep1sh.c assim como     |
  | as definocoes de cada uma, para ver a    |
  |  implemetacoes consulte ep1shFunc.c      |
  *------------------------------------------*/

/*Macro que define quantidade maxima de caracteres 
em um comando*/
#define MAXCOMMAND 70

 /*------------------------------------------*
  |            commandClean                  |
  *------------------------------------------*/
void commandClean(char *buffer, int size);
 /*recebe um vetor de caractes de tamanho size 
 e preenche com valores vazios(0) nao nulos*/
 /*------------------------------------------*/
 
 /*------------------------------------------*
  |             argumentsClean               |
  *------------------------------------------*/
void argumentsClean(char **list);                   
 /*recebe uma matriz de caracteres(vetor de    
 strings) de tamanho pre determinado e         
 preenche com valores vazios(0)*/              
 /*------------------------------------------*/
 
 /*------------------------------------------*
  |              getArguments                |
  *------------------------------------------*/
void getArguments(char *line,char command[], char **arguments);
 /*Recebe vetor caracteres com a entrada do
 ep1sh e separa o comando dos argumentos*/
 /*------------------------------------------*/

 /*------------------------------------------*
  |                striComp                  |
  *------------------------------------------*/
int striComp(char *str, char *comp, int size);
 /*versao simplificada do strcmp devolve 1(true)
 se os primeiros sizes carateres de str forem 
 igual aos de comp */
 /*------------------------------------------*/