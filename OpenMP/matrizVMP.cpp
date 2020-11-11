#include <iostream>
#include <stdio.h>
#include<bits/stdc++.h>
#include <omp.h>
#include <stdlib.h>
#include <algorithm>


using namespace std;

int main(int argv, char* argc[]) {
    //int thread_count = 8;
    int m = 8000000;
    int n = 8;
    for(int thread_count = 1 ; thread_count < 35 ;thread_count*=2){
        double *A = (double *)malloc(m*n*sizeof(double));
        double *x = (double *)malloc(n*sizeof(double));
        double *y = (double *)malloc(m*sizeof(double));

        unsigned t0, t1;
        int i, j;
        for (i = 0; i < m; i++)
                for (j = 0; j < n; j++)
                    A[i*n+j] = rand() % 100 + 1;

        for (i = 0; i < n; i++)
                x[i] = rand() % 100 + 1;
        t0 = clock();
        #pragma omp parallel for num_threads(thread_count) default(none) shared(A,x,y,m,n) private(i,j)

        for (i = 0; i < m; i++) {
                y[i] = 0.0;
                for (j = 0; j < n; j++)
                    y[i] += A[i*n+j]*x[j];
        }
        t1 = clock();

        double seconds = (double(t1-t0)/CLOCKS_PER_SEC);
        //printList(root);
        printf( " M :  %i , N : %i Numero de threads : %i , Tiempo : %lf\n \n" ,m,n,thread_count,seconds);
        free(A);
        free(x);
        free(y);
    }
   	return 0;
}
