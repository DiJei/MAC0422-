#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ep1_util.h>
#include <pthread.h>


pthread_mutex_t mutex;

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



void *counter(void *arguments) {
  struct arg_struct *args = arguments;
  /*Espera a anterior acabar..*/
  clock_t t,now;

       pthread_mutex_lock (&mutex);
       t = clock();
       while (1) {
         now =  (double)(clock() - t) / CLOCKS_PER_SEC;
         if ( now >= args->delay) 
           break; 
       }
       printf("---Thread[%d] Acabada!---\n",(args->id));
       pthread_mutex_unlock (&mutex);
   
  pthread_exit(NULL);
}

void jobs_init(trace *processTable,pthread_t *threadID, int size, pthread_attr_t *attr) {
    clock_t t;
    long now;
    int y;
    y = 0;
    t = clock();
    struct arg_struct args; 
    while (y < size) {
      now =  (long)(clock() - t) / CLOCKS_PER_SEC; 
      if ( now == processTable[y].init ) {
          args.id = y;
          args.delay = processTable[y].dt;
          printf("---Thread[%d] inicializada---\n",y);
          if (pthread_create(&threadID[y], attr, counter, (void *) &args) != 0) {
           printf("ERROR\n");
           exit(0);
          }
          y++;
      }
    }
}