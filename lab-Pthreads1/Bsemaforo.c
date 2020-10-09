#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

long double sum;
long flag;
int thread_count;
int n=0;

int counter = 0;
sem_t count_sem;
sem_t barrier_sem;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * thread_sum(void * rank){
	long my_rank = (long) rank;
	double factor;
	long long my_n = n / thread_count;
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;
	double my_sum = 0.0;

	if(my_first_i % 2 == 0){
		factor = 1.0;
	}
	else{
		factor = -1.0;
	}

	for(long long i = my_first_i; i < my_last_i; i++, factor = -factor){
		my_sum += factor/(2 * i + 1);
	}
	
	pthread_mutex_lock(&mutex);
	sum += my_sum;
	pthread_mutex_unlock(&mutex);
	/* barrera*/
	sem_wait(&count_sem);
	if(counter == thread_count-1){
		counter =0;
		sem_post(&count_sem);
		for(int j=0 ;j<thread_count-1;j++)
			sem_post(&barrier_sem);	
	}else{
		counter++;
		sem_post(&count_sem);
		sem_wait(&barrier_sem);	
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