#include<bits/stdc++.h>
#include<ctime>

using namespace std;

int main(){
	unsigned t0,t1,t2,t3;
	for(int Max=50 ;Max < 501 ;Max+=50){
		
		vector<vector<int> > M1(Max,vector<int>(Max));
		vector<vector<int> > M2(Max,vector<int>(Max));
		vector<vector<int> > M3(Max,vector<int>(Max));
		for(int i = 0 ; i <Max ;i++){
	    	for(int j = 0; j<Max ;j++){
	    		M1[i][j]=rand()%10;
	    		M2[i][j]=rand()%10;
	    	}
	    }

	    t0 = clock();
	    for(int i = 0 ;i <Max ;i++){
	    	for(int j = 0 ; j < Max;j++){
	    		for(int k = 0 ;k < Max;k++){
	    			M3[i][j] +=M1[i][k] * M2[k][j];
	    		}
	    	}
	    }
	    t1 = clock();
	    double time1 = (double(t1-t0)/CLOCKS_PER_SEC);
    	cout<<"Ejecucion  con el tamano de la matriz:" << Max <<" :"<<" "<<time1<<endl;
    	//cout<<f<<c<<endl;
    /*
    for(int i = 0 ; i <f ;i++){
    	for(int j = 0; j<c ;j++){
    		cout<<M1[i][j]<<" " ;
    	}
    	cout<<endl;
    }
    cout<<endl;
    for(int i = 0 ; i <f ;i++){
    	for(int j = 0; j<c ;j++){
    		
    		cout<<M2[i][j]<<" ";
    		
    	}
    	cout<<endl;
    }
    cout<<endl;
	for(int i = 0 ; i <f ;i++){
	    	for(int j = 0; j<c ;j++){

	    		cout<<M3[i][j]<<" ";
	    	}
	    	cout<<endl;
	   }*/
	}
	
    

	

}