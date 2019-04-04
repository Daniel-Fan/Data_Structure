#include<iostream>
#include<algorithm>
#include<math.h>
#define maxsum 0x7FFFFFFF
using namespace std;
int map[1000][1000],dist[1000],s[1000];

int Dijkstra(int n,int S,int T){
    int mindis,u;
    for(int i=0; i < n; i++){
        dist[i]= map[S][i];
        s[i]=0;
    }     
    s[S]= 1;
    for(int i = 0; i< n; i++){  
       mindis=maxsum;  u=-1;
       for(int j=0;j<n;j++)  {
           if(!s[j]&&dist[j]<mindis){
		       u=j; mindis = dist[j];
		   }
       }
      s[u]=1;
      for(int j=0;j<n;j++)
      if(u==-1)
         break;
      else
         if(!s[j] && dist[u]+map[u][j]<dist[j]&&map[u][j]<maxsum)
            dist[j]=dist[u]+map[u][j];
     }
     printf("%d\n",dist[T]==maxsum?-1:dist[T]);
}

int main(){
 int N,M;
 int A,B,X;
 int S,T;
 while(~scanf("%d%d",&N,&M)){
 	for(int i=0;i<N;i++)
    	for(int j=0;j<N;j++)
    	 	map[i][j]=map[j][i]=maxsum;
    for(int i=0;i<M;i++){
       scanf("%d%d%d",&A,&B,&X);
  	   if(map[A][B]>X)
		 map[A][B]=map[B][A]=X;
    }
    scanf("%d%d",&S,&T);
    Dijkstra(N,S,T);
 }
}
