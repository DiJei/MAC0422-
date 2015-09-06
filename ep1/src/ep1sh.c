 /*------------------------------------------*
  |                 ep1sh.c                  |
  *------------------------------------------* 
  | Este arquivo contem a implementacao do   |
  | pequeno shell pedido na primeira parte da|
  | descricao do ep1 para consultar as       |
  | funcoes usadas no programa consulte      |
  | util.h e ep1shFunc.h                     |
  *------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ep1sh_util.h>

int main(int argc, char *argv[]) {
  int x;
  char *line;
  char command[MAXCOMMAND];
  char **arguments;
  pid_t pid;
  int status;
  
  /*---Inicializa vetor de argumentos---*/
  arguments = malloc( 6 * sizeof (char *));
  for(x = 0; x < 6; x++)
    arguments[x] = malloc(MAXCOMMAND * sizeof(char));
  /*------------------------------------*/
  
  while (1) {
    argumentsClean(arguments);
    commandClean(command, MAXCOMMAND);
    getcwd(command,MAXCOMMAND);
    printf("[%s]",command);
    commandClean(command, MAXCOMMAND);
    line = readline (" ");
    add_history(line);
    getArguments(line, command, arguments);

    if (striComp(command,"pwd",3)) {
      getcwd(command,MAXCOMMAND);
      printf("%s\n",command);
    } 
      
    if (striComp(command,"cd",2)) 
      chdir(arguments[1]);
    
    if (striComp(command,"/bin/ls",7)) {
      switch ( pid = fork() ) {
       case -1:
         perror("fork()");
         exit(EXIT_FAILURE);
       case 0: 
         arguments[0] = "ls";
         arguments[2] = NULL;
         status = execv(command,arguments);
         exit(status); 
       default: 
         if ( waitpid(pid, &status, 0) < 0 ) {
           perror("waitpid()");
           exit(EXIT_FAILURE);
         }
      }
    }
    
    if (striComp(command,"./ep1",5)) {
      switch ( pid = fork() ) {
       case -1:
         perror("fork()");
         exit(EXIT_FAILURE);
       case 0: 
         arguments[0] = "ep1";
         arguments[5] = NULL;
         status = execv(command,arguments);
         exit(status); 
       default: 
         if ( waitpid(pid, &status, 0) < 0 ) {
           perror("waitpid()");
           exit(EXIT_FAILURE);
         }
      }
    }

    if (striComp(command,"-q",2))
      break;
  }
  /*---Libera memoria alocada para arguments---*/
  for (x = 0; x < 6; x++)
    free(arguments[x]);
  free(arguments);
  /*-------------------------------------------*/ 
   return(0);
}