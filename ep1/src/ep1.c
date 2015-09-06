#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ep1_util.h>
#include <pthread.h>




int main(int argc, char *argv[]) {
    int x;
    int y = 0;
    int size = 0;
    char line[MAX_LINE];
    char *token;
    int id;
    pthread_attr_t attr;
    pthread_mutex_t *mutex;
    pthread_t threadID[MAX_THREADS];
    trace processTable[MAX_THREADS];
    struct arg_struct args;  
 
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
  

  switch(id) {
    /*Escalanador first in first out*/
    case 1:
    /*Atributos inicias*/
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    /*Inicializa todos os jobs*/
    jobs_init(processTable,threadID, size, &attr);
    pthread_attr_destroy(&attr);
    break;
  }  
   
  return (0);
 
}