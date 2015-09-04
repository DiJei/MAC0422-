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
  pthread_t threadID[MAX_THREADS];

struct arg_struct {
    int delay;
    int id;
};
trace processTable[MAX_THREADS];
pthread_mutex_t *mutex;

void showPT(trace processTable[], int size);
void getTokens(char *line, trace *process);
void *first_counter(void *void_delay);
void *counter(void *arguments);


int main(int argc, char *argv[]) {
    int x;
    int y = 0;
    int size = 0;
    char line[MAX_LINE];
    char *token;
    int id;
    
    clock_t t;
    long now;
    
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
  //pthread_t threadID[size + 1];

  switch(id) {
    /*Escalanador first in first out*/
    case 1:
    y = 0;
    t = clock();
    while (1) {
      now =  (long)(clock() - t) / CLOCKS_PER_SEC; 
       
      if ( now == processTable[y].init && y == 0) {
         if (pthread_create(&threadID[y], NULL, first_counter, (void *) &processTable[y].dt) != 0) {
           printf("ERROR\n");
           exit(0);
         }
          
         printf("Thread[%d] inicializada\n",y);
      
         y++;
      }
      if ( now == processTable[y].init && y > 0) {
          args.delay = processTable[y].dt;
          args.id = (y - 1);
          if (pthread_create(&threadID[y], NULL, counter, (void *) &args) != 0) {
           printf("ERROR\n");
           exit(0);
         }
          
         printf("Thread[%d] inicializada\n",y); 
         y++;
      }
    if ( y == size) {
       printf("Ultimo, vou esperar...\n");
       for (x = 0; x < size; x ++)
          pthread_join(threadID[x],NULL);
       printf(".....Vixes ja foi\n");
       break;
    } 
    
    }
    
    break;
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

void *first_counter(void *void_delay) {
  float delay = *((float *)(void_delay)); 
  clock_t t,now;
  t = clock();
  while (1) {
    now =  (double)(clock() - t) / CLOCKS_PER_SEC;
    if ( now >= delay) {
     break; 
        }
   }
  printf("---Thread[0] Acabou!---\n");
  return NULL;
}

void *counter(void *arguments) {
  struct arg_struct *args = arguments;
  /*Espera a anterior acabar..*/
  printf("Esperando a  thread[%d] acabar...\n", args->id);
  if (pthread_join(threadID[args->id],NULL) != 0) { 
    printf("DEU RUIM\n");
    pthread_exit(NULL);
  }
  printf("Acabou\n");
  clock_t t,now;
  t = clock();
  pthread_mutex_lock(&mutex);
  while (1) {
    now =  (double)(clock() - t) / CLOCKS_PER_SEC;
    if ( now >= args->delay) {
     break; 
        }
   }
  pthread_mutex_unlock(&mutex);
  printf("---Thread[%d] Acabada!---\n",(args->id + 1));
  pthread_exit(NULL);
  return NULL;
}