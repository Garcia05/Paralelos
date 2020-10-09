#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
//#include "timer.h"

long double sum;
long flag;
int thread_count;
int n;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * thread_sum(void * rank){
	long my_rank = (long) rank;
	double factor;
	long long my_n = n / thread_count;
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;

	if(my_first_i % 2 == 0){
		factor = 1.0;
	}
	else{
		factor = -1.0;
	}

	for(long long i = my_first_i; i < my_last_i; i++, factor = -factor){
		while(flag != my_rank);
		sum +=factor/(2*i+1);
		flag = (flag+1) % thread_count;
	}

	return NULL;
}

int main(int argc, char ** argv){
	long thread;
	clock_t t;
	clock_t start,end;
	
	thread_count = 1;
	while(thread_count < 1000){
		pthread_t *threads;
		threads = malloc(thread_count*sizeof(pthread_t));
		
		start=clock();
		for(thread= 0; thread < thread_count; thread++){
			pthread_create(&threads[thread], NULL, thread_sum,&thread);
		}
		//printf("Hello from main thread\n");
		for(thread = 0; thread < thread_count; thread++){
			pthread_join(threads[thread],NULL);
		}
		end=clock();
		free(threads);
		
		t = end-start;
		printf("No de Threads : %i ,Tiempo Tomado es %f seconds \n",thread_count,((float)t)/CLOCKS_PER_SEC);
		thread_count=thread_count*2;
	}
	
}