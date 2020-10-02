
#include<bits/stdc++.h>
#include<ctime>

using namespace std;
int main(){

	unsigned t0,t1,t2,t3;
	for(int MAX=50 ;MAX < 501 ;MAX+=50){
		vector<vector<int> > M1(MAX,vector<int>(MAX));
		vector<vector<int> > M2(MAX,vector<int>(MAX));
		vector<vector<int> > M3(MAX,vector<int>(MAX));

		for(int i = 0 ; i <MAX ;i++){
		    for(int j = 0; j<MAX ;j++){
		    	M1[i][j]=rand()%10;
		    	M2[i][j]=rand()%10;
		    }
		}
		t0 = clock();
		int temp=2;
		for(int ii = 0 ; ii< MAX ; ii+=temp){
			for(int jj = 0 ; jj< MAX ;jj+=temp){
				for(int kk = 0 ; kk< MAX ;kk+=temp){
					for(int i = ii ; i< min(ii + temp, MAX); i++){
						for(int j = jj ; j< min(jj + temp, MAX) ;j++){
							for(int k = kk ; k< min(kk + temp, MAX);k++){
								M3[i][j] +=M1[i][k] * M2[k][j];
							}
						}
					}
				}
			}
		}
		t1 = clock();
		double time1 = (double(t1-t0)/CLOCKS_PER_SEC);
    	cout<<"Ejecucion 1 con tamano de matriz : " << MAX <<" :"<<","<<time1<<endl;
    	/*
    	for (int i = 0;i < MAX;i++)
		{
			for (int  j= 0; j < MAX; j++)
			{
				cout << M3[i][j] << " ";
				M3[i][j] = 0;
			}
			cout << endl;
		}*/
    	t2 = clock();
	    for(int i = 0 ;i <MAX ;i++){
	    	for(int j = 0 ; j < MAX;j++){
	    		for(int k = 0 ;k < MAX;k++){
	    			M3[i][j] +=M1[i][k] * M2[k][j];
	    		}
	    	}
	    }
	    t3 = clock();
	    double time2 = (double(t3-t2)/CLOCKS_PER_SEC);
    	cout<<"Ejecucion 2 con tamano de matriz : " << MAX <<" :"<<" "<<time2<<endl;
    	/*
    	for (int i = 0;i < MAX;i++)
		{
			for (int  j= 0; j < MAX; j++)
			{
				cout << M3[i][j] << " ";
				M3[i][j] = 0;
			}
			cout << endl;
		}*/
	}
}