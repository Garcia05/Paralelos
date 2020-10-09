#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "../utils.h"
#include "../timer.h"

int * vector;
int * res;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
	int local_fil;
	int colum;
	int * local_matrix;
	int rank;
} MethodArgs;

void * matrixVectorMultiplication(void * args){
	MethodArgs m_args = *((MethodArgs*) args);
	//int * res = (int *) malloc(sizeof(int) * m_args.local_fil);
	for(int i = 0; i < m_args.local_fil; i++){
		res[m_args.rank * m_args.local_fil + i] = 0;
		for(int j = 0; j < m_args.colum; j++){
			res[m_args.rank * m_args.local_fil + i] += m_args.local_matrix[i * m_args.colum + j] * vector[j];
		}
	}
	return (void *) res;
}

int main(int argv, char ** argc){
	if(argv != 4){
		printf("Faltan Argumentos <numThreads> <tamMatrixFil> <tamMatrixCol>\n");
		return 0;
	}
	double ini, end;
	int numThreads = atoi(argc[1]);
	int tamMatrixFil = atoi(argc[2]);
	int tamMatrixCol = atoi(argc[3]);
	int * matrix = getRandomVector(tamMatrixFil * tamMatrixCol);
	int local_fil = tamMatrixFil / numThreads;
	vector = getRandomVector(tamMatrixCol);
	pthread_t threads[numThreads];
	MethodArgs threads_args[numThreads];
	//printVector(vector,tamMatrixCol);
	//printVectorMatrix(matrix,tamMatrixFil,tamMatrixCol);
	int pedazos = 10;
	int memSize = tamMatrixCol / pedazos;
	res = malloc(sizeof(int) * tamMatrixFil);
	GET_TIME(ini);
	for(int i = 0; i < numThreads; i++){
		threads_args[i].local_matrix = (int *) malloc(sizeof(int) * local_fil * tamMatrixCol);
		/*
		for(int j = 0; j < local_fil; j++){
			size_t tam = sizeof(int) * tamMatrixCol;
			threads_args[i].local_matrix[j] = (int *) malloc(tam);
			/*
			memcpy((void*) &(threads_args[i].local_matrix[j]),(void*) &(matrix[i * local_fil + j]),
					tam);
			*/
			
			/*for(int k = 0; k < pedazos; k++){
				memcpy((void*) &(threads_args[i].local_matrix[j][k * pedazos]),
						(void*) &(matrix[i*local_fil + j][k * pedazos]),
							memSize * sizeof(int));
			}
			
			
		}
		*/
		memcpy(threads_args[i].local_matrix,&matrix[i * local_fil * tamMatrixCol],local_fil * tamMatrixCol * sizeof(int));
		//printVector(threads_args[i].local_matrix,local_fil * tamMatrixCol);
		threads_args[i].local_fil = local_fil;
		threads_args[i].colum = tamMatrixCol;
		threads_args[i].rank = i;
		pthread_create(&threads[i],NULL,matrixVectorMultiplication,(void*) &threads_args[i]);
	}
//	int * res = malloc(sizeof(int) * tamMatrixFil);
	for(int i = 0; i < numThreads; i++){
		int * temp = malloc(sizeof(int) * local_fil);
		pthread_join(threads[i],(void **) &temp);
		//memcpy(&res[i*local_fil],temp,sizeof(int) * local_fil);
	}
	GET_TIME(end);
	double seconds = end - ini;
	printf("Time->%lf\n", seconds);
//	printVector(res,tamMatrixFil);
}
