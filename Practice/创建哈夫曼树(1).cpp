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
  printf("\n���������Ĺ������������ʾ��\n");
  printf("HT��̬:\n  ���  weight  parent  lchild  rchild");
  for (i=1; i<=m; i++)
    printf("\n%4d%8d%8d%8d%8d",i,HT[i].weight,
            HT[i].parent,HT[i].lchild, HT[i].rchild);
    system("pause");
  for (i=n+1; i<=m; i++) {  // ����������
    // ��HT[1..i-1]��ѡ��parentΪ0��weight��С��������㣬
    // ����ŷֱ�Ϊs1��s2��
    Select(HT, i-1, s1, s2);
    HT[s1].parent = i;  HT[s2].parent = i;
    HT[i].lchild = s1;  HT[i].rchild = s2;
    HT[i].weight = HT[s1].weight + HT[s2].weight;
    printf("\nselect: s1=%d   s2=%d\n", s1, s2);
    printf("  ���  weight  parent  lchild  rchild");
    for (j=1; j<=i; j++)
      printf("\n%4d%8d%8d%8d%8d",j,HT[j].weight,
             HT[j].parent,HT[j].lchild, HT[j].rchild);
    system ("pause");
  }

  //--- ��Ҷ�ӵ���������ÿ���ַ��Ĺ��������� ---
  HC = (HuffmanCode)malloc((n+1)*sizeof(char *));  
  cd = (char *)malloc(n*sizeof(char));    // ���������Ĺ����ռ�
  cd[n-1] = '\0';                         // �����������
  for (i=1; i<=n; ++i) {                  // ����ַ������������
    start = n-1;                          // ���������λ��
    for (c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent)// ��Ҷ�ӵ������������
    {
    	if (HT[f].lchild==c) cd[--start] = '0';
        else cd[--start] = '1';
    }
	HC[i] = (char *)malloc((n-start)*sizeof(char)); 
         // Ϊ��i���ַ��������ռ�
    strcpy(HC[i], &cd[start]);    // ��cd���Ʊ���(��)��HC
  }
  free(cd);   // �ͷŹ����ռ�
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

