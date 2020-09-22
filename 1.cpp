#include<iostream> 
#include<ctime>
#include<stdlib.h>
using namespace std; 


int test(int MAX){
	srand (time(NULL));
	unsigned t0,t1,t2,t3;
	double A[MAX][MAX],x[MAX],y[MAX],y2[MAX];

	for(int i = 0 ; i <MAX ;i++){
    	for(int j = 0; j<MAX ;j++){
    		A[i][j]=rand()%100;
    		x[j]=rand()%100;
    	}
    }
    /*
    t0 = clock();
    for (int i = 0 ; i <MAX ;i++){
		for(int j = 0 ; j<MAX ; j++){
			y[i]+= A[i][j]*x[j];
		}
	}
    t1 = clock();
    double time1 = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<" tamano de la matriz : "<<MAX <<"Ejecucion 1 Tiempo : " <<time1<<endl;*/
    t2 = clock();
	for (int j = 0 ; j <MAX ;j++){
		for(int i = 0 ; i<MAX ; i++){
			y[i]+= A[i][j]*x[j];
		}
	}
	t3 = clock();
	double time2 = (double(t3-t2)/CLOCKS_PER_SEC);
    cout<<MAX <<"," <<time2<<endl;
    //cout<<endl;
    return 0;
}
int main(){
	for(int MAX=50 ;MAX<501 ;MAX+=50){
		test(MAX);
	}
	
}