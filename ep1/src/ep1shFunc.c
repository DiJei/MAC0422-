#include <stdio.h>
#include <unistd.h>
#include <util.h>

void bufferClean(char *buffer, int size) {
    int x;
    for (x = 0; x < size; x++)
       buffer[x] = 0; 
}

void listClean(char **list) {
    int x;
    for (x = 0; x < MAXCOMMAND; x++) {
      
       list[1][x] = 0; 
       list[2][x] = 0; 
       list[3][x] = 0;
       list[4][x] = 0;   
    }
}
 

int  striComp(char *str, char *comp, int size) {
    int x = 0;
    for (x; x < size; x++)
        if (str[x] != comp[x])
            return 0;
    return 1;
}

void getArguments(char *line,char command[],char **arguments) {
  int x ;
  int y = 1;
  int z = 0;
  
  for (x = 0; line[x] != 0 && line[x] != ' '; x++)
       command[x] = line[x];
  if (line[x] == ' ')
    x++;
  for (x; line[x] != 0; x++) {
    if (line[x] == ' ') {
      y++;
      z = 0;
    }
    else {
      arguments[y][z] = line[x];
      z++;
    }
  }
}