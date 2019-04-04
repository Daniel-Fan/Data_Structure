#include<iostream>
#include<algorithm>
#include<math.h>
#define maxsum 0x7FFFFFFF
float map[101][101],dist[101],s[101]; //map记录路线图，dist最短距离，s记录点
struct coordinate{
	int X,Y;
}Coord[1000];
int Dijkstra(int n,int x){
    int mindis,u;
    float total;
    for(int i=1; i <= n; i++){
        if((map[x][i]>1000||map[x][i]<10)&&x!=i){
       	    printf("oh!\n"); return 0;
        }
    
        else{
   	     dist[i]= map[x][i];
        s[i]=0;
        }
		
    }       
    s[x]= 1;
    for(int i = 1; i<= n; i++){  
       mindis=maxsum;  u=-1;
       for(int j=1;j<=n;j++)  {
           if(!s[j]&&dist[j]<mindis){u=j; mindis = dist[j];}
       }
      s[u]=1;
      for(int j=1;j<=n;j++)
         if(!s[j] && dist[u]+map[u][j]<dist[j]&&map[u][j]<maxsum)
            dist[j]=dist[u]+map[u][j];
     }
     total=dist[n]*100;
     printf("%.1f\n",total);
}

int main(){
 int x,y,x2,y2;
 float d;
 int T,n;
 scanf("%d",&T);
 for(int i=1;i<=T;i++){
 	 scanf("%d",&n);
 	 for(int i = 1; i <= n; i++)
            for(int j = i; j <= n;j++)
               map[i][j]=map[j][i]=maxsum; 
 	 for(int i=1;i<=n;i++){
 	 	scanf("%d%d",&x,&y);
 	 	Coord[i].X=x;
 	 	Coord[i].Y=y;
 	 }
 	 for(int i=1;i<n;i++)
            for(int j = i+1; j <= n;j++){
            	x2= (Coord[i].X-Coord[j].X)*(Coord[i].X-Coord[j].X);
            	y2= (Coord[i].Y-Coord[j].Y)*(Coord[i].Y-Coord[j].Y);
            	d=sqrt(x2+y2);
            	map[i][j]=d;
				map[j][i]=d;
            }
 	 Dijkstra(n,1);

 }
 return 0;
}
