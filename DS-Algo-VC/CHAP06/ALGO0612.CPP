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

typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
} HTNode,*HuffmanTree;

typedef char **HuffmanCode;

void Select(HuffmanTree &HT,int y,int &s1,int &s2)
{
	int i;
	s1=0;
	s2=0;
	for(i=1;i<=y;i++)
	{
		if(HT[i].parent==0)
		{
			if(HT[i].weight<HT[s1].weight)
			{
				s1=i;
			}
		}
	}
	for(i=1;i<=y;i++)
	{
		if(HT[i].parent==0)
		{
			if(HT[i].weight<HT[s2].weight&&i!=s1)
			{
				s2=i;
			}
		}
	}
}
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n) 
{
  int i, j, m, s1, s2, start;
  char *cd;
  unsigned int c, f;

  if (n<=1) return;
  m = 2 * n - 1;
  HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode)); 
  for (i=1; i<=n; i++) 
  {
    HT[i].weight=w[i-1];
    HT[i].parent=0;
    HT[i].lchild=0;
    HT[i].rchild=0;
  }
  for (i=n+1; i<=m; i++) 
  {
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
   system ("pause");
  for (i=n+1; i<=m; i++) {  // 建哈夫曼树
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
    system ("pause");
  }

  //--- 从叶子到根逆向求每个字符的哈夫曼编码 ---
  cd = (char *)malloc(n*sizeof(char));    // 分配求编码的工作空间
  cd[n-1] = '\0';                         // 编码结束符。
  for (i=1; i<=n; ++i) {                  // 逐个字符求哈夫曼编码
    start = n-1;                          // 编码结束符位置
    for (c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent) 
      // 从叶子到根逆向求编码
      if (HT[f].lchild==c) cd[--start] = '0';
      else cd[--start] = '1';
    HC[i] = (char *)malloc((n-start)*sizeof(char)); 
         // 为第i个字符编码分配空间
    strcpy(HC[i], &cd[start]);    // 从cd复制编码(串)到HC
  }
  free(cd);   // 释放工作空间
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
}
