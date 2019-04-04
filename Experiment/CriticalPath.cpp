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
typedef int indegree[MAX_VERTEX_NUM];        //��Žڵ��������
int *ve,*vl;        //�¼����緢��ʱ�����ٷ���ʱ�����飬ȫ�ֱ���
int *stack2;            //��ջ�洢��������
int top2;


typedef struct ArcNode
{
        int adjvex;        //�ñ���ָ�Ķ����λ��
        struct ArcNode *nextarc;        //ָ����һ���ߵ�ָ��
        int info;        //���ĳ���(�ؼ�·���еĻ)
}ArcNode;   //��Ľ��

typedef struct VNode{
        VertexType data;        //������Ϣ�������ݵȣ�
        ArcNode *firstarc;        //ָ���һ�������ö���ıߵĻ�ָ��
}VNode, AdjList[MAX_VERTEX_NUM];   //ͷ���

typedef struct ALGraph{
        AdjList vertices;
        int vexnum, arcnum;   //ͼ�ĵ�ǰ�������ͻ���
}ALGraph;

//���ӽڵ�
void add_vex(ALGraph &G)
{
        cin>>G.vexnum;
        for(int i = 0; i < G.vexnum; i++)
        {
                cin>>G.vertices[i].data;   //���춥������
                G.vertices[i].firstarc = NULL;
                //getchar();
        }
}

//���ӱ�
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
                s->adjvex = v2;   //�ñ���ָ��Ķ����λ��Ϊj
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

//�����ڽ�����
void CreateUDN(ALGraph &G, indegree indegree)
{
        add_vex(G);        //���ӽڵ� 
        add_arc(G,indegree);        //���ӱ�        
}



//��������
int TopologicalSort(ALGraph &G, indegree indegree, stack<int> &T)
{
    //��G�޻�·������������������в�����1�����л�·����0��
    ArcNode *q;
    int i,k,j;
	int count=0;
    ve=(int *)malloc( G.vexnum*sizeof(int) );        //�¼����緢��ʱ������
    for(i=0; i<G.vexnum; i++)
        ve[i]=0;    //��ʼ��
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


//��ؼ�·��
void CriticalPath(ALGraph &G, indegree indegree)        //GΪ�����������G�ĸ���ؼ��
{
    stack<int> T;
	ArcNode *q;
    int k,j;
    int ee,el;        //����緢��ʱ�����ٷ���ʱ��
    int i;
    TopologicalSort(G, indegree,T);

    vl=(int *)malloc(G.vexnum*sizeof(int) );        //�¼����緢��ʱ������
    for( i=0; i<G.vexnum; i++)
        vl[i]=ve[G.vexnum-1];    //��ʼ��
    
    cout<<"ve:"<<endl;    //���ve
    for(i=0; i<G.vexnum; i++)
        cout<<ve[i]<<"  ";
    cout<<endl;

    while(!T.empty()){    //��ջ����vl
        for(j=T.top(),T.pop(),q = G.vertices[j].firstarc; q; q = q->nextarc){       //��������¼�����ٷ���ʱ��vlֵ
            k=q->adjvex;
            if(vl[k] - q->info < vl[j])
                vl[j] = vl[k] - q->info;
        }
    }

    cout<<"vl:"<<endl;    //���vl
    for(i=0; i<G.vexnum; i++)
        cout<<vl[i]<<"  ";
    cout<<endl<<endl;

        for(j=0; j<G.vexnum; j++)        //��ee,el�͹ؼ��
        {
            for(q = G.vertices[j].firstarc; q; q = q->nextarc)
            {
                k=q->adjvex;
                ee = ve[j];        //����緢��ʱ��
                el = vl[k] - q->info;        //���ٷ���ʱ��
                if(ee == el)    //������ȼ��ڹؼ�·����
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
        CriticalPath(G,indegree);    //��ؼ�·��
}