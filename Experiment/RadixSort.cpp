#include<iostream>
#include<algorithm>
#include<cstdio>
#include<stack>
using namespace std;

#define MAX_NUM_OF_KEY 8
#define RADIX 20
#define MAX_SPACE 10000

typedef struct{
	char keys[MAX_NUM_OF_KEY];
	int otheritems;
	int next;
}SLCell;

typedef struct{
	SLCell r[MAX_SPACE];
	int keynum;
	int recnum;
}SLList;

typedef int ArrType[RADIX];

void Collect(SLList &L, int i, ArrType f, ArrType e) {  
  int j,t;
  for (j=0; !f[j]; j++); 
  L.r[0].next = f[j];  
  t = e[j];
  while (j<RADIX) {
    for (j=j+1; j<RADIX && !f[j]; j++);     
    if (j<RADIX) 
      { L.r[t].next = f[j];  t = e[j]; }
  }
  L.r[t].next = 0;  
} // Collect

void Distribute(SLList &L, int i, ArrType &f, ArrType &e) {  
  // �㷨10.15
  // ��̬����L��r���м�¼�Ѱ�(keys[0],...,keys[i-1])����
  // ���㷨����i���ؼ���keys[i]����RADIX���ӱ�
  // ʹͬһ�ӱ��м�¼��keys[i]��ͬ��f[0..RADIX-1]��e[0..RADIX-1]
  // �ֱ�ָ����ӱ��е�һ�������һ����¼��
  int j, p;
  for (j=0; j<RADIX; ++j) f[j] = 0;     // ���ӱ��ʼ��Ϊ�ձ�
  for (p=L.r[0].next;  p!=0; p=L.r[p].next) {
    j = L.r[p].keys[i]-'0';  // ����¼�е�i���ؼ���ӳ�䵽[0..RADIX-1]��
    if (!f[j]) f[j] = p;
    else L.r[e[j]].next = p;
    e[j] = p;                // ��p��ָ�Ľ������j���ӱ���
  }
} // Distribute

void print_SLList2(SLList L, int i){
	int t,j;
	for(j=0,t=0;t<L.recnum;j=L.r[j].next){
		cout<<L.r[L.r[j].next].keys<<" ";
		t++;
	}
}

void RadixSort(SLList &L) {  // �㷨10.17
   // L�ǲ��þ�̬�����ʾ��˳���
   // ��L����������ʹ��L��Ϊ���ؼ�����С���������̬����
   // L.r[0]Ϊͷ��㡣
   int i;
   ArrType f, e;
   for (i=1; i<=L.recnum; ++i) L.r[i-1].next = i;
   L.r[L.recnum].next = 0;     // ��L����Ϊ��̬����
   for (i=L.keynum-1; i>=0; i--) {  
      // �����λ�������ζԸ��ؼ��ֽ��з�����ռ�
      Distribute(L, i, f, e);    // ��i�˷���
      Collect(L, i, f, e);       // ��i���ռ�
      print_SLList2(L, i);
      cout<<endl;
   }
} // RadixSort

void reverse(char A[MAX_NUM_OF_KEY]){
	stack<char> S;
	int n=strlen(A);
	int i;
	for(i=0;i<n;i++){
		S.push(A[i]);
	}
	for(i=0;i<n;i++){
		A[i]=S.top();
		S.pop();
	}
}
int main(){
	SLList L;
	char A[MAX_NUM_OF_KEY];
	int i,n;
	cin>>L.recnum;
	for(i=1;i<=L.recnum;i++){
		cin>>L.r[i].keys;
	}
	L.keynum=strlen(L.r[L.recnum].keys);
	RadixSort(L);
}
