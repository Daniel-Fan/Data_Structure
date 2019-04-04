#include<iostream>
#include<vector>
#include<queue>
#include<cstdio>
#define N 1000
using namespace std;
int n,m;
int g[N][N];
bool visit[N];

void dfs(int v) {
    visit[v] = true;
    cout<<v<<" ";
    for(int w=0;w<n;w++)
    if (g[v][w] && !visit[w])  dfs(w);     
} 

void bfs(int v)
{    
   int w;
   queue<int>Q;      
   for ( w=0;  w<n;  w++ )
      if ( !visit[w]) 
	  {          
           visit[w] = true;   
           cout<<w<<" ";
           Q.push(w);        
           while (!Q.empty())  
		   	{
              int u=Q.front();
			  Q.pop();
              for(w=0; w<n; w++)
                 if ( g[u][w] && ! visit[w])  
			 	 {
                    visit[w]=true;  
                    cout<<w<<" ";
                    Q.push(w);
                 }
		   	}
       } 
}


int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		
	    for(int i=0;i<m;i++)
	      {
		     int a,b;
		     scanf("%d%d",&a,&b);
		     g[a][b]=g[b][a]=1;
           }
	    //DFS
		for(int i=0;i<n;i++)
	    {
		   visit[i]=false;
	    }
	    for(int i=0;i<n;i++)
	    {
		   if(!visit[i])
		   dfs(i);
	    }
     	printf("\n");
     	//BFS
     	for(int i=0;i<n;i++)
	    {
		   visit[i]=false;
	    }
	    for(int i=0;i<n;i++)
	    {
		   if(!visit[i])
		   bfs(i);
	    }
	    printf("\n");
	    printf("\n");
	}
}
