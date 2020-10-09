#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 1000

int thread_count = 2;
sem_t* sems;

void *Tokenize(void* rank) {
   long my_rank = (long) rank;
   int count;
   int next = (my_rank + 1) % thread_count;
   char *fg_rv;
   char my_line[MAX];
   char *my_string;

   sem_wait(&sems[my_rank]);
   fg_rv = fgets(my_line, MAX, stdin);
   sem_post(&sems[next]);
   while (fg_rv != NULL) {
      printf("Thread %ld > my line = %s", my_rank, my_line);

      count = 0;
      my_string = strtok(my_line, " \t\n");
      while ( my_string != NULL ) {
         count++;
         printf("Thread %ld > string %d = %s\n", my_rank, count, my_string);
         my_string = strtok(NULL, " \t\n");
      }
      sem_wait(&sems[my_rank]);
      fg_rv = fgets(my_line, MAX, stdin);
      sem_post(&sems[next]);
   }

   return NULL;
}
int main(int argc, char* argv[]) {

    	pthread_t *threads = (pthread_t *)malloc(thread_count*sizeof(pthread_t));
    	sems = (sem_t *)malloc(thread_count*sizeof(sem_t));
    	sem_init(&sems[0], 0, 1);

    	printf("Insertar Texto: ");
    	for (long thread = 0; thread < thread_count; thread++){
        	pthread_create(&threads[thread], NULL,Tokenize, (void*) thread);
    	}
    	for (long thread = 0; thread < thread_count; thread++){
        	pthread_join(threads[thread], NULL);
    	}
    return 0;
}
