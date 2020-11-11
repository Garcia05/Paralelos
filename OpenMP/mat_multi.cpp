#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <time.h>

using namespace std;
int thread_count = 4;
int m = 8000000;
int n = 8;

double* A;
double* x;
double* y;

void mat_multi(double A[], double x[], double y[],int m, int n, int thread_count){
	int i, j;
	double start, finish, elapsed;

	start = clock();
	#  pragma omp parallel for num_threads(thread_count)  \
		default(none) private(i, j)  shared(A, x, y, m, n)
	for (i = 0; i < m; i++) {
		y[i] = 0.0;
		for (j = 0; j < n; j++)
			y[i] += A[i*n+j]*x[j];
	}
	finish = clock();
	elapsed = (finish - start)/CLOCKS_PER_SEC;
	printf("%e sec\n", elapsed);

}

int main(int argc, char* argv[]) {
   srand (time(NULL));

   A = (double *)malloc(m*n*sizeof(double));
   x = (double *)malloc(n*sizeof(double));
   y = (double *)malloc(m*sizeof(double));


   int i, j;
   for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         A[i*n+j] = rand() % 10 + 1;

   for (i = 0; i < n; i++)
      x[i] = rand() % 10 + 1;

   mat_multi(A, x, y, m, n, thread_count);

   free(A);
   free(x);
   free(y);

   return 0;
}