#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include<time.h>
#include<string.h>
#include<iostream>
#include<cmath>
#include<windows.h>
using namespace std;

#define number 10
#define int_MAX1 10000
#define int_MAX2 20000
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
} HTNode,*HuffmanTree;

typedef char **HuffmanCode;

void Select(HuffmanTree &HT,int y,int &s1,int &s2)
{
	int i;
	int w1=int_MAX1;
	int w2=int_MAX2;
	s1=0;
	s2=0;
	for(i=1;i<=y;i++)
	{
		if(HT[i].parent==0)
		{
			if(HT[i].weight<w1)
			{
				s1=i;
				w1=HT[i].weight;
			}
		}
	}
	for(i=1;i<=y;i++)
	{
		if(HT[i].parent==0)
		{
			if(HT[i].weight<w2&&i!=s1)
			{
				s2=i;
				w2=HT[i].weight;
			}
		}
	}
}
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n) {
  int i, j, m, s1,s2;
  char *cd;
  int p;
  int cdlen;

  if (n<=1) return;
  m = 2 * n - 1;
  HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));   // 0号单元未用
  for (i=1; i<=n; i++) { //初始化
    HT[i].weight=w[i-1];
    HT[i].parent=0;
    HT[i].lchild=0;
    HT[i].rchild=0;
  }
  for (i=n+1; i<=m; i++) { //初始化
    HT[i].weight=0;
    HT[i].parent=0;
    HT[i].lchild=0;
    HT[i].rchild=0;
  }
  printf("\n哈夫曼树的构造过程如下所示：\n");
  printf("HT初态:\n  结点  weight  parent  lchild  rchild");
  for (i=1; i<=m; i++)
     printf("\n%4d%8d%8d%8d%8d",i,HT[i].weight,
            HT[i].parent,HT[i].lchild, HT[i].rchild);
  system("pause");
  for (i=n+1; i<=m; i++) {     // 建哈夫曼树
    // 在HT[1..i-1]中选择parent为0且weight最小的两个结点，
    // 其序号分别为s1和s2。
    Select(HT, i-1, s1, s2);
    HT[s1].parent = i;  HT[s2].parent = i;
    HT[i].lchild = s1;  HT[i].rchild = s2;
    HT[i].weight = HT[s1].weight + HT[s2].weight;
    printf("\nselect: s1=%d   s2=%d\n", s1, s2);
    printf("  结点  weight  parent  lchild  rchild");
    for (j=1; j<=i; j++)
      printf("\n%4d%8d%8d%8d%8d",j,HT[j].weight,
             HT[j].parent,HT[j].lchild, HT[j].rchild);
    system("pause");
  }

 //------无栈非递归遍历哈夫曼树，求哈夫曼编码
  HC = (HuffmanCode)malloc((n+1)*sizeof(char *)); 
  cd = (char *)malloc(n*sizeof(char)); // 分配求编码的工作空间
  p = m;  cdlen = 0;
  for (i=1; i<=m; ++i)  // 遍历哈夫曼树时用作结点状态标志
     HT[i].weight = 0;
  while (p) 
  	{
    if (HT[p].weight==0) 
	{               // 向左
      HT[p].weight = 1;
      if (HT[p].lchild != 0) 
	  { 
	     p = HT[p].lchild;  cd[cdlen++] ='0'; 
      }
      else if (HT[p].rchild == 0) 
	  {     // 登记叶子结点的字符的编码
        HC[p] = (char *)malloc((cdlen+1) * sizeof(char));
        cd[cdlen] ='\0';  strcpy(HC[p], cd);    // 复制编码(串)
      }
    } 
	else if (HT[p].weight==1) 
	{        // 向右
      HT[p].weight = 2;
      if (HT[p].rchild != 0) { p = HT[p].rchild;  cd[cdlen++] ='1'; }
    } 
	else 
	{   // HT[p].weight==2，退回退到父结点，编码长度减1
      HT[p].weight = 0; p = HT[p].parent; --cdlen;  
    }
  }
   for(i=1;i<n+1;i++)
  {
      printf("%s\n",HC[i]);
  }
} // HuffmanCoding

int main()
{
	int value[number];
	int i;
	HuffmanCode hc;
	HuffmanTree ht;
	printf("Please input %d values\n",number);
	for(i=0;i<number;i++)
	{
		scanf("%d",&value[i]);
	}
	HuffmanCoding(ht,hc,value,number);
	return 0; 
}
