#include<iostream>
#define MAX_VALUE 100000
using namespace std; 
int lowcost[1000],cost[100][100],closest[1000];
int prim(int v0,int N){
    int i, j, mindis, minone;  int ans = 0;/*用来记录最小生成树的总长度*/ 
    for(i = 0; i < N; i++)    {
        lowcost[i] = cost[v0][i];
        closest[i] = v0;
    }
    for(i = 0; i < N-1; i++)    {
        mindis = MAX_VALUE;
        for(j = 0; j < N; j++)
          if(lowcost[j] && mindis > lowcost[j])          {
              mindis = lowcost[j];
              minone = j;
          }        /*将找到的最近点加入最小生成树*/
        ans += lowcost[minone];
        lowcost[minone] = 0;         /*修正其他点到最小生成树的距离*/
        for(j = 0; j < N; j++)
          if(cost[j][minone] < lowcost[j])          {
              lowcost[j] = cost[j][minone];
              closest[j] = minone;
          }
    }    return ans;
}
int main(){
	int N;
	while(cin>>N){
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				cin>>cost[i][j];
		cout<<prim(0,N);
	}
}
