#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <util.h>

int main(int argc, char *argv[]) {
  int x;
  char *line;
  char *buff;
  char command[MAXCOMMAND];
  char **list;
  pid_t pid;
  int status;

  list = malloc( 6 * sizeof (char *));
  for(x = 0; x < 6; x++)
    list[x] = malloc(MAXCOMMAND * sizeof(char));
  
  
  while (1) {
    
    listClean(list);
    
    bufferClean(command, MAXCOMMAND);
    
    getcwd(command,MAXCOMMAND);
    printf("[%s]",command);
    bufferClean(command, MAXCOMMAND);
   
    line = readline (" ");
    add_history(line);
    getArguments(line, command, list);

    if (striComp(command,"pwd",3)) {
      getcwd(command,MAXCOMMAND);
      printf("%s\n",command);
    }
    if (striComp(command,"cd",2)) 
      chdir(list[1]);
    if (striComp(command,"/bin/ls",7)) {
     //--------------------------------
     switch ( pid = fork() ) {
       case -1:
         perror("fork()");
         exit(EXIT_FAILURE);
       case 0: // in the child
         list[0] = "ls";
         list[2] = NULL;
         status = execv(command,list);
         exit(status); // only happens if execve(2) fails
       default: // in parent
         if ( waitpid(pid, &status, 0) < 0 ) {
           perror("waitpid()");
           exit(EXIT_FAILURE);
         }

     //---------------------------------
     
    }
    }
    if (striComp(command,"-q",2))
      break;
  }
 
   for (x = 0; x < 6; x++)
      free(list[x]);
   
   free(list);
    
   return(0);
}