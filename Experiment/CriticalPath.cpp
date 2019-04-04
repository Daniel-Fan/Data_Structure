#include <iostream>
#include<algorithm>
#include<cstdio>
#include<stack>
#include<string.h>
using namespace std;


#define OK 1

#define MAX_VERTEX_NUM 20 

typedef char VertexType;
typedef int VRType;
typedef int InforType;
typedef int indegree[MAX_VERTEX_NUM];        //存放节点入度数组
int *ve,*vl;        //事件最早发生时间和最迟发生时间数组，全局变量
int *stack2;            //建栈存储拓扑序列
int top2;


typedef struct ArcNode
{
        int adjvex;        //该边所指的顶点的位置
        struct ArcNode *nextarc;        //指向下一条边的指针
        int info;        //弧的长度(关键路径中的活动)
}ArcNode;   //表的结点

typedef struct VNode{
        VertexType data;        //顶点信息（如数据等）
        ArcNode *firstarc;        //指向第一条依附该顶点的边的弧指针
}VNode, AdjList[MAX_VERTEX_NUM];   //头结点

typedef struct ALGraph{
        AdjList vertices;
        int vexnum, arcnum;   //图的当前顶点数和弧数
}ALGraph;

//增加节点
void add_vex(ALGraph &G)
{
        cin>>G.vexnum;
        for(int i = 0; i < G.vexnum; i++)
        {
                cin>>G.vertices[i].data;   //构造顶点向量
                G.vertices[i].firstarc = NULL;
                //getchar();
        }
}

//增加边
void add_arc(ALGraph &G, indegree indegree)
{
        ArcNode *s;
        ArcNode *p;
        int k;
		cin>>G.arcnum;
        for(k=0; k<G.vexnum; k++)
            indegree[k]=0;
        int v1, v2;
        int length;
        for(k = 0; k < G.arcnum; k++)
        {
                cin>>v1>>v2>>length;
                ++indegree[v2];     
                s = (ArcNode*) malloc (sizeof(ArcNode));
                s->adjvex = v2;   //该边所指向的顶点的位置为j
                s->info=length;
                s->nextarc = NULL;
                if(!G.vertices[v1].firstarc){
                    G.vertices[v1].firstarc=s;
                }
                else{
                    for(p = G.vertices[v1].firstarc; p->nextarc; p = p->nextarc)
                            ;
                    p->nextarc=s;
                }
        }
}

//构造邻接链表
void CreateUDN(ALGraph &G, indegree indegree)
{
        add_vex(G);        //增加节点 
        add_arc(G,indegree);        //增加边        
}



//拓扑排序
int TopologicalSort(ALGraph &G, indegree indegree, stack<int> &T)
{
    //若G无回路，则输出拓扑排序序列并返回1，若有回路返回0。
    ArcNode *q;
    int i,k,j;
	int count=0;
    ve=(int *)malloc( G.vexnum*sizeof(int) );        //事件最早发生时间数组
    for(i=0; i<G.vexnum; i++)
        ve[i]=0;    //初始化
    stack<int> S;
    for(j=0;j<G.vexnum;++j){
    	if(indegree[j]==0) S.push(j);
    }
    count=0;
    while(!S.empty()){
    	j=S.top();
    	S.pop();
    	T.push(j);
    	++count;
    	for(q=G.vertices[j].firstarc;q;q=q->nextarc){
	    	k=q->adjvex;
	    	if(--indegree[k]==0) S.push(k);
	    	if(ve[j]+q->info>ve[k]) ve[k]=ve[j]+q->info;
	    }
    }
    if(count<G.vexnum) return -1;
    else return 0;
}


//求关键路径
void CriticalPath(ALGraph &G, indegree indegree)        //G为有向网，输出G的各项关键活动
{
    stack<int> T;
	ArcNode *q;
    int k,j;
    int ee,el;        //活动最早发生时间和最迟发生时间
    int i;
    TopologicalSort(G, indegree,T);

    vl=(int *)malloc(G.vexnum*sizeof(int) );        //事件最早发生时间数组
    for( i=0; i<G.vexnum; i++)
        vl[i]=ve[G.vexnum-1];    //初始化
    
    cout<<"ve:"<<endl;    //输出ve
    for(i=0; i<G.vexnum; i++)
        cout<<ve[i]<<"  ";
    cout<<endl;

    while(!T.empty()){    //出栈是求vl
        for(j=T.top(),T.pop(),q = G.vertices[j].firstarc; q; q = q->nextarc){       //求各顶点事件的最迟发生时间vl值
            k=q->adjvex;
            if(vl[k] - q->info < vl[j])
                vl[j] = vl[k] - q->info;
        }
    }

    cout<<"vl:"<<endl;    //输出vl
    for(i=0; i<G.vexnum; i++)
        cout<<vl[i]<<"  ";
    cout<<endl<<endl;

        for(j=0; j<G.vexnum; j++)        //求ee,el和关键活动
        {
            for(q = G.vertices[j].firstarc; q; q = q->nextarc)
            {
                k=q->adjvex;
                ee = ve[j];        //活动最早发生时间
                el = vl[k] - q->info;        //活动最迟发生时间
                if(ee == el)    //两者相等即在关键路径上
                    cout<<G.vertices[j].data<<"-->"<<G.vertices[k].data
                    <<endl;
            }
        }
}

int main()
{
        ALGraph G;
        indegree indegree;
        CreateUDN(G, indegree);
        CriticalPath(G,indegree);    //求关键路径
}