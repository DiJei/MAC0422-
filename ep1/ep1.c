#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_THREADS 100
#define MAX_LINE 100
/*Estrutura para tabela de processo*/
typedef struct 
{
	unsigned int init;
	char name[20];
	unsigned int dt;
	unsigned int deadline;
	char prior; /*-19 a 20*/
}trace;
/*---------------------------------*/
trace processTable[MAX_THREADS];


void showPT(trace processTable[], int size);
void getTokens(char *line, trace *process);
void *counter(void *void_delay);


int main(int argc, char *argv[]) {
    int x;
    int y = 0;
    int size = 0;
    char line[MAX_LINE];
    char *token;
    int id;
    
    clock_t t,now;
    t = clock();

    /*Verifica entrada*/
    if (argc < 4) {
    	printf("USAGE: ./ep1 x(1 to 6) traceFile resultFile -d(optional)\n");
    	exit(0);
    }
    id = atoi(argv[1]);

    FILE *trace;
    if ((trace = fopen(argv[2],"r")) == NULL) {
       	printf("arquivo:%s nao encontrado\n",argv[2]);
        exit(0);
    }
	/*---------------*/
  /*Ler o arquivo trace e monta a tabela de processo*/
  for (x = 0; x < MAX_LINE; x++)
    	line[x] = 0;
  while (1) {
       if (fgets(line, 100, trace) == NULL)
          break;
       size++;
       getTokens(line, &processTable[size -1]);
  }
  /*---------------------------------------------------*/
  pthread_t threadID[size + 1];

  switch(id) {
    /*Escalanador first in first out*/
    case 1:
    y = 0;
    while (1) {
    now =  (double)(clock() - t) / CLOCKS_PER_SEC;
    if ( now == processTable[y].init) {
       if (pthread_create(&threadID, NULL, counter, &processTable[y].dt) == 0) {
          printf("DEU RUIM\n");
          exit(0);
       }
    }
    }
    break;
    }  
  } 
  return (0);
 
}


void showPT(trace processTable[], int size) {
	printf("init |  name |  dt  | deadline  |  prior |\n");
	int x = 0;
	for (x; x < size; x++)
		printf("%d  | %s  | %d  | %d |  %d |\n",processTable[x].init,processTable[x].name,processTable[x].dt,processTable[x].deadline, processTable[x].prior );
}


void getTokens(char *line, trace *process) {
  int x;
  int y;
  int z;
  char buffer[20];

  for (x = 0; x < 20; x++)
    buffer[x] = 0;
  
  for (x = 0; line[x] != ' '; x++)
    buffer[x] = line[x];
    process->init = atoi(buffer);
    x++;
  
  for (y = 0; line[x] != ' '; x++) {
    buffer[y] = line[x];
    y++;
  }
  strcpy (process->name, buffer);
  
  x++;
  for (y = 0; line[x] != ' '; x++) {
    buffer[y] = line[x];
    y++;
  }
  process->dt = atoi(buffer);

 
  x++;
  for (y = 0; line[x] != ' '; x++) {
    buffer[y] = line[x];
    y++;
  }
  process->deadline = atoi(buffer);

  x++;
  for (y = 0;  line[x] != '\n' && line[x] != 0; x++) {
    buffer[y] = line[x];
    y++;
  }
  process->prior = atoi(buffer);  
  
}

void *counter(void *void_delay) {
  float *delay = (float *)void_delay; 
  clock_t t,now;
  t = clock();
  while (1) {
    now =  (double)(clock() - t) / CLOCKS_PER_SEC;
    if ( (float *)now >= delay) {
     break; 
        }
   }
  printf("Thread Acabada!\n");
  return NULL;
}