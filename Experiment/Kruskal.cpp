#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
#define MAX_VEX 1000
#define MAX_EDGE 5000
	
typedef struct MSTEdge{
   int  vex1,vex2; 
   double weight;
}MSTEdge;

typedef struct ENode
{  int  ivex,jvex;   
   int  weight;     
}ENode;

typedef struct 
{  int  vexnum,edgenum;    
   int  vexlist[MAX_VEX];    
ENode  edgelist[MAX_EDGE];    
}ELGraph;

bool cmp(ENode a,ENode b){
	return a.weight<b.weight;
}

void Kruskal_MST(ELGraph G){
	MSTEdge TE[MAX_EDGE];
	int j,k,v,s1,s2,*Vset,w,n,ans=0;
	Vset=(int*)malloc(G.vexnum*sizeof(int)) ;
    for (j=0; j<G.vexnum; j++)
    Vset[j]=j;
    sort(G.edgelist,G.edgelist+G.edgenum+1,cmp);
    j=0; 
    k=0;
    while (k<G.vexnum-1&&j<G.edgenum){
        s1=Vset[G.edgelist[j].ivex];
        s2=Vset[G.edgelist[j].jvex];
        if  (s1!=s2){
		  TE[k].vex1=G.edgelist[j].ivex; 
          TE[k].vex2=G.edgelist[j].jvex;
          TE[k].weight=G.edgelist[j].weight;         
          k++;
          for(v=0;v<G.vexnum;v++)
               if(Vset[v]==s2)  Vset[v]=s1;
          }
        j++ ;
    }
    free(Vset); 
	for(n=0;n<=k;n++){
		ans=ans+TE[n].weight;
	}
	printf("%d",ans);
}

int main(){
	ELGraph G;
	int num,i=0;
	while(~scanf("%d%d",&G.vexnum,&G.edgenum)){
		num=G.edgenum;
		for(int z=0;z<G.vexnum;z++){
			G.vexlist[z]=z+1;
		}
		while(num--){
			cin>>G.edgelist[i].ivex>>G.edgelist[i].jvex>>G.edgelist[i].weight;
			i++;
		}
		Kruskal_MST(G);
	}
}
