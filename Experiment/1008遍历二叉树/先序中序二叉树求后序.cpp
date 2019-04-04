#include<stdio.h>
#include<stdlib.h>
#include<iostream>    
#include<queue>    
#include<stack>
#include<string.h>
using namespace std; 
#define Number 30

typedef struct BiTNode  
{    
    char data;    
    struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;    


void CreateBiTree(BiTNode **root,char *before, char *middle, int &L)
{
	int i=-1,j,z,ll,rl;
	char ltempbefore[Number];
	char ltempmiddle[Number];
	char rtempbefore[Number];
	char rtempmiddle[Number];
	if(L==0)
	{
		*root=NULL;
		return;
	}
	
	*root = (BiTNode *)malloc(sizeof(BiTNode));
	(*root)->data = *before;
	for(i=0;;i++)
	{
		if(*(middle+i)==*before)
		break;
		else
		continue;
	}
	for(z=0;z<i;z++)
	{
		ltempbefore[z]=before[1+z];
		ltempmiddle[z]=middle[z];
	}
	ltempbefore[z]='\0';
	ltempmiddle[z]='\0';
	for(i,j=0;i+1<L;i++,j++)
	{
		rtempbefore[j]=before[i+1];
		rtempmiddle[j]=middle[i+1];
	}
	rtempbefore[j]='\0';
	rtempmiddle[j]='\0';
	ll=strlen(ltempbefore);
	rl=strlen(rtempbefore);
    CreateBiTree(&((*root)->lchild),ltempbefore,ltempmiddle,ll);
    CreateBiTree(&((*root)->rchild),rtempbefore,rtempmiddle,rl);
}

void PostOrder(BiTNode *root)  
{  
    if(root==NULL)  
        return ;
    PostOrder(root->lchild);       
    PostOrder(root->rchild);      
    printf("%c",root->data);
}    

int main()
{
	int l,i;
	BiTNode *root=NULL;
	char before[Number];
	char middle[Number];
	char after[Number];
	while(scanf("%s",before)!=EOF)
	{
		scanf("%s",middle);
		l=strlen(before);
        CreateBiTree(&root,before,middle,l);
        PostOrder(root);
	}
}
