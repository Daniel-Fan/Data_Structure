#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string.h>
using namespace std;

#define maxsum 20000

int Partition(int L[maxsum], int low, int high) {  // �㷨10.6(b)
   // ����˳���L��������L.r[low..high]�ļ�¼��ʹ�����¼��λ��
   // ������������λ�ã���ʱ������֮ǰ���󣩵ļ�¼������С������
   int pivotkey;
   L[0] = L[low];            // ���ӱ�ĵ�һ����¼�������¼
   pivotkey = L[low];      // �����¼�ؼ���
   while (low<high) {            // �ӱ�����˽�������м�ɨ��
      while (low<high && L[high]>=pivotkey) --high;
      L[low] = L[high];      // ���������¼С�ļ�¼�Ƶ��Ͷ�
      while (low<high && L[low]<=pivotkey) ++low;
      L[high] = L[low];      // ���������¼��ļ�¼�Ƶ��߶�
   }
   L[low] = L[0];            // �����¼��λ
   return low;                   // ��������λ��
} // Partition

void QSort(int L[maxsum], int low, int high) {  //�㷨10.7
  // ��˳���L�е�������L.r[low..high]���п�������
  int pivotloc;
  if (low < high) {                      // ���ȴ���1
    pivotloc = Partition(L, low, high);  // ��L.r[low..high]һ��Ϊ��
    QSort(L, low, pivotloc-1); // �Ե��ӱ�ݹ�����pivotloc������λ��
    QSort(L, pivotloc+1, high);          // �Ը��ӱ�ݹ�����
  }
} // QSort

int main(){
	int n;
    int L[maxsum];
    memset(L,0,sizeof(L));
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++){
			scanf("%d",&L[i]);
		}
		QSort(L,1,n);
		for(int i=1;i<=n;i++)
		{
			printf("%d ",L[i]);
		}
	} 
}
