#include <iostream>
#include <stdio.h>
#include<bits/stdc++.h>
#include <omp.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;


int main(int *agrc,char *argv[]){
    int n = 100000;
    //int thread_count = 4;
    int i;
    int *a,tmp;
    int phase;
    unsigned t0,t1;
    for(int thread_count = 1 ; thread_count < 35; thread_count *=2){
        a=(int*)malloc(sizeof(int)*n);
        for(i = 0; i < n; i++) {
            a[i] = rand()%100;
        }
             printf("los elementos son: \n");
             /*
        for(i=0;i<n;i++){
            printf("%d ",a[i] );
        }
        printf("\n");*/
        t0 = clock();
        for(phase = 0 ; phase < n ; phase++){
            if(phase % 2 == 0){
    #pragma omp parallel for num_threads(thread_count) default(none) shared(a,n) private(i,tmp)
                for(i = 1 ; i < n ;i+=2){
                    if(a[i-1] > a[i]){
                        tmp = a[i-1];
                        a[i-1] = a[i];
                        a[i] = tmp;
                    }
                }
            }
            else
    #pragma omp parallel for num_threads(thread_count) default(none) shared(a,n) private(i,tmp)
                for(int i = 1 ; i < n-1 ;i+=2){
                    if(a[i] > a[i+1]){
                        tmp = a[i+1];
                        a[i+1] = a[i];
                        a[i] = tmp;
                    }
                }
        }
        t1 = clock();
        double time1 = (double(t1-t0)/CLOCKS_PER_SEC);
        cout<<"Tamano de la lista : " << n<<"  Numero de Threads : "<< thread_count<<"  Tiempo :"<<time1<<endl;
    }
    /*
    for(i=0;i<n;i++){
        printf("%d ",a[i] );
    }
    printf("\n");*/

    return 0;
}
