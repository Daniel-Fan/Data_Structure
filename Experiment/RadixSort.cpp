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
  // 算法10.15
  // 静态链表L的r域中记录已按(keys[0],...,keys[i-1])有序，
  // 本算法按第i个关键字keys[i]建立RADIX个子表，
  // 使同一子表中记录的keys[i]相同。f[0..RADIX-1]和e[0..RADIX-1]
  // 分别指向各子表中第一个和最后一个记录。
  int j, p;
  for (j=0; j<RADIX; ++j) f[j] = 0;     // 各子表初始化为空表
  for (p=L.r[0].next;  p!=0; p=L.r[p].next) {
    j = L.r[p].keys[i]-'0';  // 将记录中第i个关键字映射到[0..RADIX-1]，
    if (!f[j]) f[j] = p;
    else L.r[e[j]].next = p;
    e[j] = p;                // 将p所指的结点插入第j个子表中
  }
} // Distribute

void print_SLList2(SLList L, int i){
	int t,j;
	for(j=0,t=0;t<L.recnum;j=L.r[j].next){
		cout<<L.r[L.r[j].next].keys<<" ";
		t++;
	}
}

void RadixSort(SLList &L) {  // 算法10.17
   // L是采用静态链表表示的顺序表。
   // 对L作基数排序，使得L成为按关键字自小到大的有序静态链表，
   // L.r[0]为头结点。
   int i;
   ArrType f, e;
   for (i=1; i<=L.recnum; ++i) L.r[i-1].next = i;
   L.r[L.recnum].next = 0;     // 将L改造为静态链表
   for (i=L.keynum-1; i>=0; i--) {  
      // 按最低位优先依次对各关键字进行分配和收集
      Distribute(L, i, f, e);    // 第i趟分配
      Collect(L, i, f, e);       // 第i趟收集
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
