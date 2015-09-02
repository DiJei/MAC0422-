#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_THREADS 100
#define MAX_LINE 100
/*Estrutura para tabela de processo*/
typedef struct 
{
	unsigned int init;
	char *name;
	unsigned int dt;
	unsigned int deadline;
	char prior; /*-19 a 20*/
}trace;
/*---------------------------------*/

void showPT(trace *processTable);

trace processTable[MAX_THREADS];

int main(int argc, char *argv[]) {
    int x;
    int y = 0;
    char line[MAX_LINE];
    char *token;
    /*Verifica entrada*/
    if (argc < 3) {
    	printf("USAGE: ./ep1 x(1 to 6) traceFile resultFile -d(optional)\n");
    	exit(0);
    }
    FILE *trace;
    if ((trace = fopen(argv[2],"r")) == NULL) {
       	printf("arquivo:%s nao encontrado\n",argv[2]);
        exit(0);
    }
	/*---------------*/
    for (x = 0; x < MAX_LINE; x++)
    	line[x] = 0;
	while (1) {
       if (fgets(line, 100, trace) == NULL)
          break;
       token = strtok(line," ");
       processTable[y].init = atoi(token);	
       token = strtok(line," ");
       processTable[y].name = token;
       token = strtok(line, " ");
       processTable[y].dt = atoi(token);	
	   token = strtok(line, " ");
	   processTable[y].deadline = atoi(token);
	   token = strtok(line, " ");
	   processTable[y].prior = atoi(token);
	}
	showPT(processTable);
	return (0);
}

void showPT(trace *processTable) {
	printf("init |  name |  dt  | deadline  |  prior |\n");
	int x = 0;
	for (x; x <3; x++)
		printf("%d  | %s  | %d  | %d |  %d |\n",processTable[x].init,processTable[x].name,processTable[x].deadline, processTable[x].prior );
}